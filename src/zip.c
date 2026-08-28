#include "pch.h"

/* ---------------------------------------------------------------------------
 * ZIP archive reader (decompiled from the original ePSXe 1.6.0 binary).
 *
 * Public API: zip_extract_file() / zip_load_file() (see zip.h).
 *
 * Internal inflate implementation (stored / fixed / dynamic DEFLATE blocks,
 * huft-style multi-level Huffman tables) follows the classic zlib inflate
 * algorithm. This file has been cleaned up from the decompiler output:
 *   - EOCD record is parsed into ZipEndOfCentralDirectory (no more writes
 *     into a 4-byte int or reads of uninitialized locals);
 *   - pointers are stored in pointer-sized types (the code previously used
 *     "unsigned int", truncating pointers on x64);
 *   - the DEFLATE base/extra-bits tables, the bit masks and the
 *     code-length order were truncated during decompilation and have been
 *     restored to their full sizes;
 *   - Huffman tree nodes use ZipHuffmanNode (pointer-sized child links) and
 *     the parent-table link bug (offsets[level + 16]) is fixed;
 *   - misc. decompiler artifacts (junk pointer stores, strncmp against a
 *     single-byte "signature", stack overflows) are removed.
 * ------------------------------------------------------------------------- */

/* Exported global stream handle (a decompilation leftover; see zip.h). */
unsigned int Stream;

/* ---------------------------------------------------------------------------
 * Static state
 * ------------------------------------------------------------------------- */

static char *zip_filename;                              /* archive path (for error messages) */
static uint8_t zip_local_file_header_buffer[ZIP_READ_BUFFER_SIZE];
static char zip_path_buffer[0x100];                     /* scratch for zip_get_filename_from_path() */
static uint8_t zip_central_dir_buffer[ZIP_READ_BUFFER_SIZE];
static unsigned int zip_file_size;                      /* size of the currently open archive */

/* Deflate bit masks: zip_bit_masks[n] == (1u << n) - 1. */
static const uint16_t zip_bit_masks[14] = {
    0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff
};

/* Order in which the code-length codes are stored (HCLEN field). */
static const uint8_t zip_code_length_order[19] = {
    0x10, 0x11, 0x12, 0x0, 0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4, 0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xf
};

/* Length codes 257..287: base lengths and extra bits (DEFLATE spec, 3.2.5). */
static const uint16_t zip_length_base[31] = {
    3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
    35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0
};
static const uint8_t zip_length_extra_bits[31] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 112, 112   /* 112 = invalid */
};

/* Distance codes 0..29: base distances and extra bits (DEFLATE spec, 3.2.5). */
static const uint16_t zip_distance_base[30] = {
    1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
    257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577
};
static const uint8_t zip_distance_extra_bits[30] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
    7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
};

/* ---------------------------------------------------------------------------
 * Huffman tree nodes
 *
 * One node per table slot: byte 0 = operation (e), byte 1 = bits (b),
 * the rest = value (v).  e == 16 means "literal byte follows" (in the low
 * byte of v), e == 15 means "end of block", e == 99 means "invalid code";
 * e > 16 means "points to a sub-table" (e - 16 = bits of the sub-table,
 * v = pointer to it); otherwise e = extra bits and v = length/distance base.
 * ------------------------------------------------------------------------- */

typedef struct ZipHuffmanNode {
    uint8_t e;                  /* operation */
    uint8_t b;                  /* bits consumed by this code/sub-table */
    uint16_t reserved;          /* padding */
    uintptr_t v;                /* literal / base value / sub-table pointer */
} ZipHuffmanNode;

/* Header stored before each allocated table: links the tables of one tree
 * into a single list so zip_free_huffman_tree() can release them all. */
typedef struct ZipHuffmanTableHeader {
    uintptr_t next;             /* next table of the same tree (0 = none) */
} ZipHuffmanTableHeader;

/* ---------------------------------------------------------------------------
 * Inflate state (shared between the blocks of one DEFLATE stream)
 * ------------------------------------------------------------------------- */

static uint8_t *zipfile_input_buffer;       /* remaining compressed input */
static uint8_t *zip_sliding_window;         /* 32 KB LZ77 window */
static uint8_t *zip_inflate_output_ptr;     /* next output position */
static unsigned int zip_inflate_bit_buffer; /* pending input bits */
static unsigned int zip_inflate_bit_count;  /* number of pending input bits */
static unsigned int zip_inflate_window_pos; /* fill level of the sliding window */
static unsigned int zip_inflate_max_memory_used;

/* Cached fixed Huffman trees (built on first use, reused for every fixed block). */
static ZipHuffmanNode *zip_inflate_ltree;
static ZipHuffmanNode *zip_inflate_dtree;
static unsigned int zip_inflate_ltree_bits = 9;
static unsigned int zip_inflate_dtree_bits = 6;
static const unsigned int zip_static_ltree_max_bits = 9;
static const unsigned int zip_static_dtree_max_bits = 6;

/* static prototypes for internal functions */
static int zip_inflate_block(int *final_flag);
static int zip_build_huffman_tree(
        uint32_t *lengths,
        unsigned int num_lengths,
        unsigned int literal_codes,
        const uint16_t *base_table,
        const uint8_t *extra_table,
        ZipHuffmanNode **tree,
        unsigned int *max_bits);
static int zip_free_huffman_tree(ZipHuffmanNode *tree);
static ZipHuffmanNode *zip_alloc_huffman_table(unsigned int entries, ZipHuffmanTableHeader **header);
static unsigned int zip_copy_sliding_window_to_output(const void *src, unsigned int size);
static char *zip_get_filename_from_path(const char *path);
static int zip_print(char *Format, ...);
static int zip_read_compressed_data_to_buffer(
        FILE *Stream,
        ZipCentralDirectoryEntryInMem *cd_entry,
        ZipLocalFileHeaderInMem *local_header,
        LPVOID *out_buffer);
static int zip_read_local_file_header(
        FILE *Stream,
        ZipCentralDirectoryEntryInMem *cd_entry,
        ZipLocalFileHeaderInMem *local_header,
        uint8_t *Buffer);
static int zip_load_central_directory(
        FILE *Stream,
        const char *search_name,
        const ZipEndOfCentralDirectory *eocd,
        ZipCentralDirectoryEntryInMem *cd_entry);
static int zip_load_local_file_headers(
        FILE *Stream,
        const ZipEndOfCentralDirectory *eocd,
        ZipCentralDirectoryEntryInMem *cd_entry);
static int zip_compare_filename_case_insensitive(const char *str1, const char *str2);
static int zip_parse_cd_entry(ZipCentralDirectoryEntry *entry, ZipCentralDirectoryEntryInMem *cd_entry);
static int zip_locate_central_dir(FILE *Stream, ZipEndOfCentralDirectory *eocd);
static int zip_find_end_of_central_dir_signature(const uint8_t *buffer, int size, uint32_t *offset);
static int zip_get_file_size(FILE *Stream, uint32_t *size);
static uint16_t zip_read_uint16_le(const uint8_t *ptr);
static uint32_t zip_read_uint32_le(const uint8_t *ptr);

/* ===========================================================================
 * DEFLATE decoder
 * =========================================================================== */

/* Copies [size] bytes from the sliding window to the output buffer. */
static unsigned int zip_copy_sliding_window_to_output(const void *src, unsigned int size)
{
    memcpy(zip_inflate_output_ptr, src, size);
    zip_inflate_output_ptr += size;
    return size;
}

/* Inflates the remaining input (zipfile_input_buffer) using the given
 * literal/length and distance trees.  Returns 0 on success, 1 on error. */
static int zip_inflate_data_with_trees(
        ZipHuffmanNode *ltree,
        ZipHuffmanNode *dtree,
        unsigned int ltree_bits,
        unsigned int dtree_bits)
{
    unsigned int window_pos = zip_inflate_window_pos;
    unsigned int bit_count = zip_inflate_bit_count;
    unsigned int bit_buffer = zip_inflate_bit_buffer;
    uint8_t *in_ptr = zipfile_input_buffer;
    unsigned int ltree_mask = zip_bit_masks[ltree_bits];
    unsigned int dtree_mask = zip_bit_masks[dtree_bits];

    for (;;)
    {
        ZipHuffmanNode *node;
        unsigned int node_type;
        unsigned int saved_window_pos = window_pos;

        /* --- Decode a literal/length code --- */
        while (bit_count < ltree_bits)
        {
            bit_buffer |= (unsigned int)*in_ptr++ << bit_count;
            bit_count += 8;
        }
        zipfile_input_buffer = in_ptr;
        node = ltree + (bit_buffer & ltree_mask);
        node_type = node->e;
        if (node_type > 0x10)
        {
            do
            {
                unsigned int drop;
                unsigned int bits_needed;

                if (node_type == 99)
                    return 1;                       /* invalid code */
                drop = node->b;
                bits_needed = node_type - 16;       /* bits in the sub-table */
                bit_buffer >>= drop;
                bit_count -= drop;
                while (bit_count < bits_needed)
                {
                    bit_buffer |= (unsigned int)*in_ptr << bit_count;
                    bit_count += 8;
                    zipfile_input_buffer = ++in_ptr;
                }
                window_pos = saved_window_pos;
                node = (ZipHuffmanNode *)node->v + (bit_buffer & zip_bit_masks[bits_needed]);
                node_type = node->e;
            } while (node_type > 0x10);
        }
        {
            unsigned int node_bits = node->b;
            bit_buffer >>= node_bits;
            bit_count -= node_bits;
        }
        if (node_type == 16)
        {
            /* literal byte */
            zip_sliding_window[window_pos++] = (uint8_t)node->v;
            saved_window_pos = window_pos;
            if (window_pos == ZIP_SLIDING_WINDOW_SIZE)
            {
                zip_copy_sliding_window_to_output(zip_sliding_window, ZIP_SLIDING_WINDOW_SIZE);
                window_pos = 0;
            }
            continue;
        }
        if (node_type == 15)
            break;                                  /* end of block */

        /* length code: node->e = extra bits, node->v = length base */
        {
            unsigned int extra = node_type;
            unsigned int length = (uint16_t)node->v;
            unsigned int dist;
            unsigned int dist_extra;
            unsigned int dist_base;
            unsigned int copy_remaining;
            unsigned int copy_src;
            unsigned int copy_len;
            unsigned int copy_start;

            if (extra)
            {
                while (bit_count < extra)
                {
                    bit_buffer |= (unsigned int)*in_ptr++ << bit_count;
                    bit_count += 8;
                }
                zipfile_input_buffer = in_ptr;
                length += bit_buffer & zip_bit_masks[extra];
                bit_buffer >>= extra;
                bit_count -= extra;
                window_pos = saved_window_pos;
            }

            /* --- Decode a distance code --- */
            while (bit_count < dtree_bits)
            {
                bit_buffer |= (unsigned int)*in_ptr++ << bit_count;
                bit_count += 8;
            }
            zipfile_input_buffer = in_ptr;
            node = dtree + (bit_buffer & dtree_mask);
            node_type = node->e;
            if (node_type > 0x10)
            {
                do
                {
                    unsigned int drop;
                    unsigned int bits_needed;

                    if (node_type == 99)
                        return 1;
                    drop = node->b;
                    bits_needed = node_type - 16;
                    bit_buffer >>= drop;
                    bit_count -= drop;
                    while (bit_count < bits_needed)
                    {
                        bit_buffer |= (unsigned int)*in_ptr << bit_count;
                        bit_count += 8;
                        zipfile_input_buffer = ++in_ptr;
                    }
                    window_pos = saved_window_pos;
                    node = (ZipHuffmanNode *)node->v + (bit_buffer & zip_bit_masks[bits_needed]);
                    node_type = node->e;
                } while (node_type > 0x10);
            }
            dist_extra = node_type;
            dist_base = (uint16_t)node->v;
            if (dist_extra == 15 || dist_extra == 16)
                return 1;                   /* invalid distance code in a corrupt stream */
            {
                unsigned int node_bits = node->b;
                bit_buffer >>= node_bits;
                bit_count -= node_bits;
            }
            if (dist_extra)
            {
                while (bit_count < dist_extra)
                {
                    bit_buffer |= (unsigned int)*in_ptr << bit_count;
                    bit_count += 8;
                    zipfile_input_buffer = ++in_ptr;
                }
                window_pos = saved_window_pos;
            }
            dist = dist_base + (bit_buffer & zip_bit_masks[dist_extra]);
            bit_buffer >>= dist_extra;
            bit_count -= dist_extra;

            /* --- Copy [length] bytes from [dist] bytes back --- */
            copy_remaining = length;
            copy_src = (window_pos - dist) & 0x7FFFu;
            do
            {
                copy_start = (copy_src <= window_pos) ? window_pos : copy_src;
                copy_len = ZIP_SLIDING_WINDOW_SIZE - copy_start;
                if (copy_len > copy_remaining)
                    copy_len = copy_remaining;
                copy_remaining -= copy_len;
                if (window_pos - copy_src < copy_len)
                {
                    /* overlapping copy, byte by byte */
                    do
                    {
                        zip_sliding_window[window_pos++] = zip_sliding_window[copy_src++];
                        --copy_len;
                    } while (copy_len);
                }
                else
                {
                    memcpy(zip_sliding_window + window_pos, zip_sliding_window + copy_src, copy_len);
                    window_pos = saved_window_pos + copy_len;
                    copy_src = (copy_src + copy_len) & 0x7FFFu;
                }
                saved_window_pos = window_pos;
                if (window_pos == ZIP_SLIDING_WINDOW_SIZE)
                {
                    zip_copy_sliding_window_to_output(zip_sliding_window, ZIP_SLIDING_WINDOW_SIZE);
                    window_pos = 0;
                    saved_window_pos = 0;
                }
            } while (copy_remaining);
        }
    }

    zip_inflate_bit_buffer = bit_buffer;
    zip_inflate_bit_count = bit_count;
    zip_inflate_window_pos = window_pos;
    return 0;
}

/* Inflates the whole compressed stream (zipfile_input_buffer) into the
 * output buffer.  Returns 0 on success, non-zero on error. */
static int zip_inflate_file(void)
{
    unsigned int max_memory_used = 0;
    int final_block;
    int block_result;

    zip_inflate_window_pos = 0;
    zip_inflate_bit_count = 0;
    zip_inflate_bit_buffer = 0;
    for (;;)
    {
        zip_inflate_max_memory_used = 0;
        block_result = zip_inflate_block(&final_block);
        if (block_result)
            break;
        if (zip_inflate_max_memory_used > max_memory_used)
            max_memory_used = zip_inflate_max_memory_used;
        if (final_block)
        {
            zip_copy_sliding_window_to_output(zip_sliding_window, zip_inflate_window_pos);
            return 0;
        }
    }
    return block_result;
}

/* Inflates one DEFLATE block.  Returns 0 on success, 1 on invalid data,
 * 2 on an unknown block type. */
static int zip_inflate_block(int *final_flag)
{
    uint8_t *in_ptr;
    unsigned int bit_count;
    unsigned int bit_buffer;
    unsigned int header_bits;
    unsigned int header_bit_count;
    int block_type;

    bit_count = zip_inflate_bit_count;
    bit_buffer = zip_inflate_bit_buffer;
    if (!bit_count)
    {
        in_ptr = zipfile_input_buffer;
        bit_buffer |= (unsigned int)*in_ptr++ << bit_count;
        bit_count += 8;
        zipfile_input_buffer = in_ptr;
    }

    /* Read the 3-bit block header (BFINAL, BTYPE). */
    *final_flag = bit_buffer & 1;
    header_bits = bit_buffer >> 1;
    header_bit_count = bit_count - 1;
    if (header_bit_count < 2)
    {
        in_ptr = zipfile_input_buffer;
        do
        {
            header_bits |= (unsigned int)*in_ptr++ << header_bit_count;
            header_bit_count += 8;
            zipfile_input_buffer = in_ptr;
        } while (header_bit_count < 2);
    }
    block_type = header_bits & 3;
    bit_buffer = header_bits >> 2;
    bit_count = header_bit_count - 2;
    zip_inflate_bit_buffer = bit_buffer;
    zip_inflate_bit_count = bit_count;

    if (block_type == 2)
    {
        /* ------------------------- Dynamic Huffman block ------------------------- */
        uint32_t code_lengths[320];     /* literal/length (<= 288) + distance (<= 32) lengths */
        uint8_t *dyn_in_ptr = zipfile_input_buffer;
        unsigned int hlit_bit_buffer;
        unsigned int hlit_bit_count;
        unsigned int hdist_bit_buffer;
        unsigned int hdist_bit_count;
        unsigned int hclen_bit_buffer;
        unsigned int hclen_bit_count;
        unsigned int clen_bit_buffer;
        unsigned int clen_bit_count;
        unsigned int hlit;
        unsigned int hdist;
        unsigned int hclen;
        unsigned int clen_index;
        unsigned int clen_pos;
        unsigned int total_codes;
        unsigned int lit_count;
        unsigned int hdist_count;
        int prev_code_length = 0;
        ZipHuffmanNode *ltree;
        ZipHuffmanNode *dtree;
        unsigned int tree_bits;
        unsigned int dtree_bits;
        int result;

        /* HLIT (5 bits): number of literal/length codes - 257. */
        hlit_bit_buffer = zip_inflate_bit_buffer;
        hlit_bit_count = zip_inflate_bit_count;
        while (hlit_bit_count < 5)
        {
            hlit_bit_buffer |= (unsigned int)*dyn_in_ptr++ << hlit_bit_count;
            hlit_bit_count += 8;
            zipfile_input_buffer = dyn_in_ptr;
        }
        hlit = (hlit_bit_buffer & 0x1F) + 257;

        /* HDIST (5 bits): number of distance codes - 1. */
        hdist_bit_count = hlit_bit_count - 5;
        hdist_bit_buffer = hlit_bit_buffer >> 5;
        while (hdist_bit_count < 5)
        {
            hdist_bit_buffer |= (unsigned int)*dyn_in_ptr++ << hdist_bit_count;
            hdist_bit_count += 8;
            zipfile_input_buffer = dyn_in_ptr;
        }
        hdist = (hdist_bit_buffer & 0x1F) + 1;

        /* HCLEN (4 bits): number of code-length codes - 4. */
        hclen_bit_count = hdist_bit_count - 5;
        hclen_bit_buffer = hdist_bit_buffer >> 5;
        while (hclen_bit_count < 4)
        {
            hclen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << hclen_bit_count;
            hclen_bit_count += 8;
            zipfile_input_buffer = dyn_in_ptr;
        }
        hclen = (hclen_bit_buffer & 0xF) + 4;
        clen_bit_buffer = hclen_bit_buffer >> 4;
        clen_bit_count = hclen_bit_count - 4;

        if (hlit > 0x120 || hdist > 0x20)
            return 1;                       /* HLIT > 288 or HDIST > 32 */

        /* Read the HCLEN 3-bit code lengths (in zip_code_length_order). */
        memset(code_lengths, 0, sizeof(code_lengths));
        for (clen_index = 0; clen_index < hclen; ++clen_index)
        {
            unsigned int order_index;
            while (clen_bit_count < 3)
            {
                clen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << clen_bit_count;
                clen_bit_count += 8;
                zipfile_input_buffer = dyn_in_ptr;
            }
            order_index = zip_code_length_order[clen_index];
            code_lengths[order_index] = clen_bit_buffer & 7;
            clen_bit_buffer >>= 3;
            clen_bit_count -= 3;
        }

        /* Build the code-length tree (all 19 codes are "simple"). */
        tree_bits = 7;
        result = zip_build_huffman_tree(code_lengths, 19, 19, NULL, NULL, &ltree, &tree_bits);
        if (!tree_bits)
        {
            zip_free_huffman_tree(ltree);
            return 1;
        }
        if (result)
        {
            if (result == 1)
                zip_free_huffman_tree(ltree);
            return result;
        }

        /* Decode the literal/length and distance code lengths. */
        lit_count = hlit;
        hdist_count = hdist;
        total_codes = lit_count + hdist_count;
        clen_pos = 0;
        {
            unsigned int clen_bits = tree_bits;
            unsigned int clen_mask = zip_bit_masks[tree_bits];
            while (clen_pos < total_codes)
            {
                ZipHuffmanNode *node;
                unsigned int node_bits;
                unsigned int node_value;

                while (clen_bit_count < clen_bits)
                {
                    clen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << clen_bit_count;
                    clen_bit_count += 8;
                    zipfile_input_buffer = dyn_in_ptr;
                }
                node = ltree + (clen_bit_buffer & clen_mask);
                node_bits = node->b;
                clen_bit_buffer >>= node_bits;
                clen_bit_count -= node_bits;
                node_value = (uint16_t)node->v;
                if (node_value >= 0x10)
                {
                    /* repeat codes 16/17/18 */
                    unsigned int repeat;
                    if (node_value == 16)
                    {
                        while (clen_bit_count < 2)
                        {
                            clen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << clen_bit_count;
                            clen_bit_count += 8;
                            zipfile_input_buffer = dyn_in_ptr;
                        }
                        repeat = (clen_bit_buffer & 3) + 3;
                        clen_bit_buffer >>= 2;
                        clen_bit_count -= 2;
                        if (clen_pos + repeat > total_codes)
                        {
                            zip_free_huffman_tree(ltree);
                            return 1;
                        }
                        memset32(&code_lengths[clen_pos], prev_code_length, repeat);
                        clen_pos += repeat;
                    }
                    else if (node_value == 17)
                    {
                        while (clen_bit_count < 3)
                        {
                            clen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << clen_bit_count;
                            clen_bit_count += 8;
                            zipfile_input_buffer = dyn_in_ptr;
                        }
                        repeat = (clen_bit_buffer & 7) + 3;
                        clen_bit_buffer >>= 3;
                        clen_bit_count -= 3;
                        if (clen_pos + repeat > total_codes)
                        {
                            zip_free_huffman_tree(ltree);
                            return 1;
                        }
                        memset(&code_lengths[clen_pos], 0, repeat * sizeof(uint32_t));
                        clen_pos += repeat;
                        prev_code_length = 0;
                    }
                    else /* node_value == 18 */
                    {
                        while (clen_bit_count < 7)
                        {
                            clen_bit_buffer |= (unsigned int)*dyn_in_ptr++ << clen_bit_count;
                            clen_bit_count += 8;
                            zipfile_input_buffer = dyn_in_ptr;
                        }
                        repeat = (clen_bit_buffer & 0x7F) + 11;
                        clen_bit_buffer >>= 7;
                        clen_bit_count -= 7;
                        if (clen_pos + repeat > total_codes)
                        {
                            zip_free_huffman_tree(ltree);
                            return 1;
                        }
                        memset(&code_lengths[clen_pos], 0, repeat * sizeof(uint32_t));
                        clen_pos += repeat;
                        prev_code_length = 0;
                    }
                }
                else
                {
                    code_lengths[clen_pos] = node_value;
                    prev_code_length = node_value;
                    ++clen_pos;
                }
                clen_bits = tree_bits;
            }
        }
        zip_free_huffman_tree(ltree);
        zip_inflate_bit_buffer = clen_bit_buffer;
        zip_inflate_bit_count = clen_bit_count;

        /* Build the literal/length tree. */
        tree_bits = zip_static_ltree_max_bits;
        result = zip_build_huffman_tree(code_lengths, lit_count, 0x101,
                                        zip_length_base, zip_length_extra_bits,
                                        &ltree, &tree_bits);
        if (!tree_bits || result)
        {
            if (result && result != 1)
                return result;
            printf("%s", "(incomplete l-tree)  ");
            zip_free_huffman_tree(ltree);
            return 1;
        }

        /* Build the distance tree. */
        dtree_bits = zip_static_dtree_max_bits;
        result = zip_build_huffman_tree(&code_lengths[lit_count], hdist_count, 0,
                                        zip_distance_base, zip_distance_extra_bits,
                                        &dtree, &dtree_bits);
        if (dtree_bits || lit_count <= 0x101)
        {
            if (result >= 2)
            {
                zip_free_huffman_tree(ltree);
                return result;
            }
            if (!zip_inflate_data_with_trees(ltree, dtree, tree_bits, dtree_bits))
            {
                zip_free_huffman_tree(ltree);
                zip_free_huffman_tree(dtree);
                return 0;
            }
            zip_free_huffman_tree(ltree);
            zip_free_huffman_tree(dtree);
            return 1;
        }
        printf("%s", "(incomplete d-tree)  ");
        zip_free_huffman_tree(ltree);
        return 1;
    }

    if (block_type == 1)
    {
        /* --------------------------- Fixed Huffman block -------------------------- */
        uint32_t static_lengths[288];
        int result;

        if (zip_inflate_ltree)
            return zip_inflate_data_with_trees(zip_inflate_ltree, zip_inflate_dtree,
                                               zip_inflate_ltree_bits, zip_inflate_dtree_bits) != 0;

        /* Fixed literal/length tree: 144 codes of 8 bits, 112 of 9,
           24 of 7 and 8 of 8 (DEFLATE spec, 3.2.6). */
        memset32(static_lengths, 8, 144);
        memset32(static_lengths + 144, 9, 112);
        memset32(static_lengths + 256, 7, 24);
        memset32(static_lengths + 280, 8, 8);
        zip_inflate_ltree_bits = 7;
        result = zip_build_huffman_tree(static_lengths, 0x120, 0x101,
                                        zip_length_base, zip_length_extra_bits,
                                        &zip_inflate_ltree, &zip_inflate_ltree_bits);
        if (result)
        {
            zip_inflate_ltree = NULL;
            return result;
        }

        /* Fixed distance tree: 30 codes of 5 bits. */
        memset32(static_lengths, 5, 30);
        zip_inflate_dtree_bits = 5;
        result = zip_build_huffman_tree(static_lengths, 0x1E, 0,
                                        zip_distance_base, zip_distance_extra_bits,
                                        &zip_inflate_dtree, &zip_inflate_dtree_bits);
        if (result <= 1)
            return zip_inflate_data_with_trees(zip_inflate_ltree, zip_inflate_dtree,
                                               zip_inflate_ltree_bits, zip_inflate_dtree_bits) != 0;
        zip_free_huffman_tree(zip_inflate_ltree);
        zip_inflate_ltree = NULL;
        return result;
    }

    if (block_type == 0)
    {
        /* ------------------------------ Stored block ------------------------------ */
        uint8_t *stored_in_ptr = zipfile_input_buffer;
        unsigned int window_pos = zip_inflate_window_pos;
        unsigned int align_bits = zip_inflate_bit_count & 7;
        unsigned int stored_bit_count;
        unsigned int stored_bit_buffer;
        unsigned int len_bit_count;
        unsigned int stored_len;
        unsigned int stored_nlen;
        unsigned int byte_buffer;
        unsigned int byte_bit_count;

        /* Align to the next byte boundary, then read LEN (16 bits). */
        stored_bit_count = zip_inflate_bit_count - align_bits;
        stored_bit_buffer = zip_inflate_bit_buffer >> align_bits;
        while (stored_bit_count < 16)
        {
            stored_bit_buffer |= (unsigned int)*stored_in_ptr++ << stored_bit_count;
            stored_bit_count += 8;
            zipfile_input_buffer = stored_in_ptr;
        }
        len_bit_count = stored_bit_count - 16;
        stored_len = (uint16_t)stored_bit_buffer;

        /* Read NLEN (16 bits) and verify LEN == ~NLEN. */
        stored_nlen = stored_bit_buffer >> 16;
        while (len_bit_count < 16)
        {
            stored_nlen |= (unsigned int)*stored_in_ptr++ << len_bit_count;
            len_bit_count += 8;
            zipfile_input_buffer = stored_in_ptr;
        }
        if (stored_len != (uint16_t)~stored_nlen)
            return 1;

        /* Copy the stored bytes into the sliding window. */
        byte_buffer = stored_nlen >> 16;    /* buffered bytes after LEN/NLEN */
        byte_bit_count = len_bit_count - 16;
        while (stored_len--)
        {
            while (byte_bit_count < 8)
            {
                byte_buffer |= (unsigned int)*stored_in_ptr++ << byte_bit_count;
                byte_bit_count += 8;
                zipfile_input_buffer = stored_in_ptr;
            }
            zip_sliding_window[window_pos++] = (uint8_t)byte_buffer;
            if (window_pos == ZIP_SLIDING_WINDOW_SIZE)
            {
                zip_copy_sliding_window_to_output(zip_sliding_window, ZIP_SLIDING_WINDOW_SIZE);
                window_pos = 0;
            }
            byte_buffer >>= 8;
            byte_bit_count -= 8;
            stored_in_ptr = zipfile_input_buffer;
        }
        zip_inflate_bit_count = byte_bit_count;
        zip_inflate_window_pos = window_pos;
        zip_inflate_bit_buffer = byte_buffer;
        return 0;
    }

    return 2;   /* unknown block type (BTYPE == 3) */
}

/* ===========================================================================
 * Huffman table construction (classic zlib huft_build algorithm)
 *
 * Builds the multi-level lookup tables for the given code lengths.  Returns
 * 0 on success, 1 when the code set is incomplete (tables are still built),
 * 2 when it is over-subscribed, 3 on out-of-memory.
 * =========================================================================== */

static ZipHuffmanNode *zip_alloc_huffman_table(unsigned int entries, ZipHuffmanTableHeader **header)
{
    ZipHuffmanTableHeader *hdr = (ZipHuffmanTableHeader *)malloc(
            sizeof(ZipHuffmanTableHeader) + (size_t)entries * sizeof(ZipHuffmanNode));
    if (!hdr)
        return NULL;
    hdr->next = 0;
    *header = hdr;
    return (ZipHuffmanNode *)((uint8_t *)hdr + sizeof(ZipHuffmanTableHeader));
}

static int zip_free_huffman_tree(ZipHuffmanNode *tree)
{
    while (tree)
    {
        ZipHuffmanTableHeader *hdr = (ZipHuffmanTableHeader *)((uint8_t *)tree - sizeof(ZipHuffmanTableHeader));
        ZipHuffmanNode *next = (ZipHuffmanNode *)(uintptr_t)hdr->next;
        free(hdr);
        tree = next;
    }
    return 0;
}

static int zip_build_huffman_tree(
        uint32_t *lengths,
        unsigned int num_lengths,
        unsigned int literal_codes,
        const uint16_t *base_table,
        const uint8_t *extra_table,
        ZipHuffmanNode **tree,
        unsigned int *max_bits)
{
    uint32_t counts[17];            /* number of codes of each bit length (0..16) */
    uint32_t symbols[288];          /* code values in order of bit length */
    ZipHuffmanNode *level_tables[17]; /* table stack (one per level) */
    uint32_t level_bits[17];        /* table size (bits) per level */
    ZipHuffmanNode *list_head;      /* root of the allocated tables (for freeing) */
    ZipHuffmanNode *last_table;     /* previously allocated table (linked to the new one) */
    ZipHuffmanNode *cur_table;      /* table currently being filled */
    unsigned int i, j, k;           /* counters */
    unsigned int g;                 /* maximum code length */
    unsigned int l;                 /* bits per table (requested/actual) */
    unsigned int w;                 /* bits decoded before the current table */
    unsigned int a;                 /* number of codes of length k */
    unsigned int f;                 /* repeat count when filling entries */
    unsigned int z;                 /* number of entries in the current table */
    unsigned int y;                 /* number of dummy codes added */
    unsigned int mask;              /* (1 << w) - 1, for the backup loop */
    uint32_t *p;                    /* pointer into lengths[] / symbols[] */
    ZipHuffmanNode *q;              /* points to the current table */
    ZipHuffmanNode r;               /* table entry for structure assignment */
    unsigned int x[17];             /* saved code pattern per level (backup) */
    unsigned int *xp;               /* pointer into x[] */
    unsigned int top_start;         /* end of the real symbols (== number of values) */
    unsigned int max_bits_allowed;
    int incomplete;                 /* non-zero when dummy codes were added */
    int h;                          /* current table level */

    /* Bound the first table size: for more than 256 codes the limit is the
       length of code 256 (the end-of-block code). */
    max_bits_allowed = (num_lengths <= 0x100) ? 16 : lengths[256];

    /* Count the number of codes of each length. */
    memset(counts, 0, sizeof(counts));
    for (i = 0; i < num_lengths; ++i)
        ++counts[lengths[i]];
    if (counts[0] == num_lengths)   /* no codes at all */
    {
        *tree = NULL;
        *max_bits = 0;
        return 0;
    }

    /* Find the minimum and maximum code length and clamp *max_bits. */
    l = *max_bits;
    for (j = 1; j <= 16; ++j)
        if (counts[j])
            break;
    k = j;                          /* minimum code length */
    if (l < j)
        l = j;
    for (i = 16; i != 0; --i)
        if (counts[i])
            break;
    g = i;                          /* maximum code length */
    if (l > i)
        l = i;
    *max_bits = l;

    /* Adjust the last length count to fill out all codes (Kraft inequality). */
    for (y = 1 << j; j < i; ++j, y <<= 1)
        if ((y -= counts[j]) < 0)
            return 2;               /* over-subscribed */
    if ((y -= counts[i]) < 0)
        return 2;
    counts[i] += y;
    incomplete = (y != 0) ? 1 : 0;

    /* Generate the starting offsets into the value table for each length. */
    x[1] = 0;
    j = 0;
    p = counts + 1;
    xp = x + 2;
    while (--i)                     /* i == g here */
        *xp++ = (j += *p++);

    /* Make a table of values in order of bit length. */
    p = lengths;
    for (i = 0; i < num_lengths; ++i)
        if ((j = *p++) != 0)
            symbols[x[j]++] = i;
    top_start = x[g];               /* == number of values */

    /* Generate the Huffman codes and, for each, the table entries. */
    x[0] = i = 0;                   /* first Huffman code is zero */
    p = symbols;                    /* grab values in bit order */
    h = -1;                         /* no tables yet--level -1 */
    w = 0;                          /* bits decoded before the current table */
    q = NULL;
    cur_table = NULL;
    list_head = NULL;
    last_table = NULL;

    /* Go through the bit lengths; k is the bits in the shortest code. */
    for (; k <= g; ++k)
    {
        a = counts[k];
        while (a--)
        {
            /* Here i is the Huffman code of length k bits for value *p.
               Make tables up to the level required by this code. */
            while (k > w)
            {
                unsigned int table_bits;
                unsigned int bits_rem;
                unsigned int entries;
                ZipHuffmanTableHeader *header;

                ++h;
                bits_rem = g - w;
                if (bits_rem > *max_bits)
                    bits_rem = *max_bits;

                /* Compute the minimum table size <= bits_rem bits. */
                table_bits = k - w;
                entries = 1u << table_bits;
                if (entries > a + 1)
                {
                    /* Too few codes for a table_bits-bit table: try smaller. */
                    unsigned int avail = entries - a - 1;
                    if (++table_bits < bits_rem)
                    {
                        uint32_t *counts_p = counts + k;
                        do
                        {
                            unsigned int twice_avail = 2 * avail;
                            ++counts_p;
                            if (twice_avail <= *counts_p)
                                break;
                            avail = twice_avail - *counts_p;
                            ++table_bits;
                        } while (table_bits < bits_rem);
                    }
                }
                if (table_bits + w > max_bits_allowed && w < max_bits_allowed)
                    table_bits = max_bits_allowed - w;
                z = 1u << table_bits;

                /* Allocate the new table and link it into the tree's list. */
                q = zip_alloc_huffman_table(z, &header);
                if (!q)
                {
                    if (list_head)
                        zip_free_huffman_tree(list_head);
                    return 3;       /* out of memory */
                }
                level_tables[h] = q;
                level_bits[h] = table_bits;
                if (last_table)
                    ((ZipHuffmanTableHeader *)((uint8_t *)last_table - sizeof(ZipHuffmanTableHeader)))->next = (uintptr_t)q;
                last_table = q;
                if (!list_head)
                    list_head = q;
                zip_inflate_max_memory_used += z + 1;
                cur_table = q;

                /* Connect the new table to its parent, if there is one. */
                if (h)
                {
                    unsigned int parent_idx;
                    x[h] = i;       /* save the pattern for backing up */
                    r.b = (uint8_t)level_bits[h - 1];   /* bits to dump before this table */
                    r.e = (uint8_t)(16 + table_bits);   /* bits in this table */
                    r.v = (uintptr_t)q;                 /* pointer to this table */
                    parent_idx = (i >> (w - level_bits[h - 1])) & zip_bit_masks[level_bits[h - 1]];
                    level_tables[h - 1][parent_idx] = r;   /* connect to the parent table */
                }
                else
                    *tree = q;      /* the first table is the returned result */
                w += table_bits;
            }

            /* Set up the table entry in r. */
            r.b = (uint8_t)(k - (w - level_bits[h]));
            if (p >= symbols + top_start)
                r.e = 99;           /* out of values--invalid code */
            else if (*p < literal_codes)
            {
                r.e = (uint8_t)((*p < 0x100) ? 16 : 15);    /* 16 = literal, 15 = end of block */
                r.v = *p++;         /* simple code is just the value */
            }
            else
            {
                r.e = extra_table[*p - literal_codes];      /* non-simple--look up in the lists */
                r.v = base_table[*p++ - literal_codes];
            }

            /* Fill the code-like entries with r. */
            f = 1u << r.b;
            for (j = i >> (w - level_bits[h]); j < z; j += f)
                cur_table[j] = r;

            /* Backwards increment the k-bit code i. */
            for (j = 1u << (k - 1); i & j; j >>= 1)
                i ^= j;
            i ^= j;

            /* Back up over finished tables. */
            mask = (1u << (w - level_bits[h])) - 1;
            while ((i & mask) != x[h])
            {
                w -= level_bits[h]; /* drop the current table's bits from the covered total */
                --h;                /* move up to the parent table */
                mask = (1u << (w - level_bits[h])) - 1;
            }
        }
    }

    /* Return 1 (incomplete) if dummy codes were added and the code set is
       not a single-code set, 0 otherwise.  *max_bits receives the actual
       size (in bits) of the first table, which may be smaller than the
       requested value. */
    *max_bits = level_bits[0];
    return (incomplete && g != 1) ? 1 : 0;
}

/* ===========================================================================
 * ZIP parsing helpers
 * =========================================================================== */

/* Returns the last path component of a path (e.g. "C:\\dir\\file.zip" -> "file.zip"). */
static char *zip_get_filename_from_path(const char *path)
{
    char *token;
    char *last_token = NULL;

    strcpy(zip_path_buffer, path);
    token = strtok(zip_path_buffer, "/\\:");
    while (token)
    {
        last_token = token;
        token = strtok(NULL, "/\\:");
    }
    return last_token;
}

static int zip_print(char *Format, ...)
{
    char Buffer[256];
    va_list ArgList;
    int len;

    va_start(ArgList, Format);
    len = vsnprintf(Buffer, sizeof(Buffer), Format, ArgList);
    va_end(ArgList);
    printf("%s", Buffer);
    return len;
}

static int zip_get_file_size(FILE *Stream, uint32_t *size)
{
    long pos;

    if (fseek(Stream, 0, SEEK_END))
        return -1;
    pos = ftell(Stream);
    if (pos < 0)
        return -1;
    *size = (uint32_t)pos;
    return 0;
}

static uint16_t zip_read_uint16_le(const uint8_t *ptr)
{
    return (uint16_t)(ptr[0] | ((uint16_t)ptr[1] << 8));
}

static uint32_t zip_read_uint32_le(const uint8_t *ptr)
{
    return (uint32_t)ptr[0]
         | ((uint32_t)ptr[1] << 8)
         | ((uint32_t)ptr[2] << 16)
         | ((uint32_t)ptr[3] << 24);
}

/* Scans the given buffer (the tail of the archive) for the end-of-central-
 * directory signature; returns 0 when found (offset set) and 1 otherwise. */
static int zip_find_end_of_central_dir_signature(const uint8_t *buffer, int size, uint32_t *offset)
{
    int pos = size - 22;

    while (pos >= 0)
    {
        if (zip_read_uint32_le(buffer + pos) == ZIP_END_OF_CD_SIGNATURE)
        {
            *offset = (uint32_t)pos;
            return 0;
        }
        --pos;
    }
    return 1;
}

/* Locates and parses the end-of-central-directory record of the archive. */
static int zip_locate_central_dir(FILE *Stream, ZipEndOfCentralDirectory *eocd)
{
    size_t read_size = zip_file_size;
    uint32_t eocd_offset;
    const uint8_t *eocd_ptr;

    if (read_size > ZIP_READ_BUFFER_SIZE)
        read_size = ZIP_READ_BUFFER_SIZE;
    if (fseek(Stream, -(long)read_size, SEEK_END))
    {
        zip_print("Error in zipfile %s: fseek failed\n", zip_filename);
        return -1;
    }
    if (fread(zip_central_dir_buffer, 1, read_size, Stream) != read_size)
    {
        zip_print("Error in zipfile %s: couldn't read %lu bytes from end of file\n", zip_filename, (unsigned long)read_size);
        return -1;
    }
    if (zip_find_end_of_central_dir_signature(zip_central_dir_buffer, (int)read_size, &eocd_offset))
    {
        zip_print("Error in zipfile %s: couldn't find 'end of central dir' signature\n", zip_filename);
        return -1;
    }
    eocd_ptr = zip_central_dir_buffer + eocd_offset;
    eocd->signature = zip_read_uint32_le(eocd_ptr);
    eocd->disk_number = zip_read_uint16_le(eocd_ptr + 4);
    eocd->cd_start_disk = zip_read_uint16_le(eocd_ptr + 6);
    eocd->entries_this_disk = zip_read_uint16_le(eocd_ptr + 8);
    eocd->total_entries = zip_read_uint16_le(eocd_ptr + 10);
    eocd->central_dir_size = zip_read_uint32_le(eocd_ptr + 12);
    eocd->central_dir_offset = zip_read_uint32_le(eocd_ptr + 16);
    eocd->comment_length = zip_read_uint16_le(eocd_ptr + 20);
    return 0;
}

/* Copies the on-disk central directory entry into the in-memory structure
 * (little-endian reads, filename pointer into the read buffer). */
static int zip_parse_cd_entry(ZipCentralDirectoryEntry *entry, ZipCentralDirectoryEntryInMem *cd_entry)
{
    cd_entry->signature = zip_read_uint32_le((uint8_t *)entry);
    cd_entry->version_made_by = zip_read_uint16_le((uint8_t *)&entry->version_made_by);
    cd_entry->version_needed = zip_read_uint16_le((uint8_t *)&entry->version_needed);
    cd_entry->general_purpose_bit_flag = zip_read_uint16_le((uint8_t *)&entry->general_purpose_bit_flag);
    cd_entry->compression_method = zip_read_uint16_le((uint8_t *)&entry->compression_method);
    cd_entry->last_mod_time = zip_read_uint16_le((uint8_t *)&entry->last_mod_time);
    cd_entry->last_mod_date = zip_read_uint16_le((uint8_t *)&entry->last_mod_date);
    cd_entry->crc32 = zip_read_uint32_le((uint8_t *)&entry->crc32);
    cd_entry->compressed_size = zip_read_uint32_le((uint8_t *)&entry->compressed_size);
    cd_entry->uncompressed_size = zip_read_uint32_le((uint8_t *)&entry->uncompressed_size);
    cd_entry->filename_length = zip_read_uint16_le((uint8_t *)&entry->filename_length);
    cd_entry->extra_field_length = zip_read_uint16_le((uint8_t *)&entry->extra_field_length);
    cd_entry->file_comment_length = zip_read_uint16_le((uint8_t *)&entry->file_comment_length);
    cd_entry->disk_number_start = zip_read_uint16_le((uint8_t *)&entry->disk_number_start);
    cd_entry->internal_attributes = zip_read_uint16_le((uint8_t *)&entry->internal_attributes);
    cd_entry->external_attributes = zip_read_uint32_le((uint8_t *)&entry->external_attributes);
    cd_entry->local_header_offset = zip_read_uint32_le((uint8_t *)&entry->local_header_offset);
    cd_entry->filename = (char *)&entry[1];
    return (int)cd_entry->local_header_offset;
}

/* Reads the local file header of the given entry into local_header. */
static int zip_read_local_file_header(
        FILE *Stream,
        ZipCentralDirectoryEntryInMem *cd_entry,
        ZipLocalFileHeaderInMem *local_header,
        uint8_t *Buffer)
{
    size_t read_size;
    uint32_t offset = cd_entry->local_header_offset;

    if (offset >= zip_file_size)
        return -1;
    read_size = zip_file_size - offset;
    if (read_size > ZIP_READ_BUFFER_SIZE)
        read_size = ZIP_READ_BUFFER_SIZE;
    if (fseek(Stream, (long)offset, SEEK_SET))
    {
        zip_print("Error in zipfile %s: couldn't fseek to local file header\n", zip_filename);
        return -1;
    }
    if (fread(Buffer, 1, read_size, Stream) != read_size)
    {
        zip_print("Error in zipfile %s: couldn't read %lu bytes from local file header\n", zip_filename, (unsigned long)read_size);
        return -1;
    }

    local_header->signature = zip_read_uint32_le(Buffer);
    local_header->version_needed = zip_read_uint16_le(Buffer + 4);
    local_header->general_purpose_bit_flag = zip_read_uint16_le(Buffer + 6);
    local_header->compression_method = zip_read_uint16_le(Buffer + 8);
    local_header->last_mod_time = zip_read_uint16_le(Buffer + 10);
    local_header->last_mod_date = zip_read_uint16_le(Buffer + 12);
    local_header->crc32 = zip_read_uint32_le(Buffer + 14);
    local_header->compressed_size = zip_read_uint32_le(Buffer + 18);
    local_header->uncompressed_size = zip_read_uint32_le(Buffer + 22);
    local_header->filename_length = zip_read_uint16_le(Buffer + 26);
    local_header->extra_field_length = zip_read_uint16_le(Buffer + 28);
    local_header->filename = (char *)(Buffer + 30);
    return 0;
}

/* Reads the entry data (stored or deflated) into a newly allocated buffer. */
static int zip_read_compressed_data_to_buffer(
        FILE *Stream,
        ZipCentralDirectoryEntryInMem *cd_entry,
        ZipLocalFileHeaderInMem *local_header,
        LPVOID *out_buffer)
{
    size_t compressed_size = local_header->compressed_size;
    long data_offset = (long)cd_entry->local_header_offset + 30
                     + local_header->filename_length + local_header->extra_field_length;
    void *buffer = malloc(compressed_size);

    *out_buffer = buffer;
    if (!buffer)
    {
        zip_print("Couldn't allocate %lu bytes for input buffer for zipfile %s\n", (unsigned long)compressed_size, zip_filename);
        return -1;
    }
    if (fseek(Stream, data_offset, SEEK_SET))
    {
        zip_print("Error reading zipfile %s: fseek to compressed data failed\n", zip_filename);
        free(buffer);
        *out_buffer = NULL;
        return -1;
    }
    if (fread(buffer, 1, compressed_size, Stream) != compressed_size)
    {
        zip_print("Error in zipfile %s: couldn't read %lu bytes of compressed data\n", zip_filename, (unsigned long)compressed_size);
        free(buffer);
        *out_buffer = NULL;
        return -1;
    }
    return 0;
}

/* Searches the central directory for search_name (case-insensitive, matching
 * either the full entry name or its final path component) and fills
 * cd_entry with the matching entry.  Returns 0 on success, non-zero on error. */
static int zip_load_central_directory(
        FILE *Stream,
        const char *search_name,
        const ZipEndOfCentralDirectory *eocd,
        ZipCentralDirectoryEntryInMem *cd_entry)
{
    size_t read_size = eocd->central_dir_size;
    int entry_index;
    int name_index;
    ZipCentralDirectoryEntry *entry;
    char name_buf[ZIP_MAX_FILENAME_LEN];

    if (read_size > ZIP_READ_BUFFER_SIZE)
        read_size = ZIP_READ_BUFFER_SIZE;
    if (fseek(Stream, (long)eocd->central_dir_offset, SEEK_SET))
    {
        zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", zip_filename);
        return -1;
    }
    if (fread(zip_central_dir_buffer, 1, read_size, Stream) != read_size)
    {
        zip_print("Error in zipfile %s: couldn't read %lu bytes from central directory\n", zip_filename, (unsigned long)read_size);
        return -1;
    }

    entry = (ZipCentralDirectoryEntry *)zip_central_dir_buffer;
    for (entry_index = 0; entry_index < eocd->total_entries; ++entry_index)
    {
        int found = 0;

        zip_parse_cd_entry(entry, cd_entry);
        name_index = 0;
        if (cd_entry->filename_length)
        {
            do
            {
                if (name_index >= ZIP_MAX_FILENAME_LEN - 1)
                    break;
                name_buf[name_index] = (char)toupper((unsigned char)cd_entry->filename[name_index]);
                ++name_index;
            } while (name_index < cd_entry->filename_length);
        }
        name_buf[name_index] = 0;

        if (!zip_compare_filename_case_insensitive(name_buf, search_name))
        {
            found = 1;
            if (cd_entry->compression_method && cd_entry->compression_method != 8)
            {
                found = 0;
                zip_print("Error in zipfile %s: compression method for file %s unsupported.\n", zip_filename, search_name);
                zip_print("Method: $%04x  must be $0000 (Stored) or $0008 (Deflated)\n", cd_entry->compression_method);
            }
            if ((uint8_t)cd_entry->version_needed > 0x14)
            {
                found = 0;
                zip_print("Error in zipfile %s: version for file %s too new.\n", zip_filename, search_name);
                zip_print("Version: $%02x must be $14 or less\n", (uint8_t)cd_entry->version_needed);
            }
            if ((cd_entry->version_needed >> 8) != 0)
            {
                found = 0;
                zip_print("Error in zipfile %s: OS for file %s not supported.\n", zip_filename, search_name);
                zip_print("OS: $%02x must be $00\n", cd_entry->version_needed >> 8);
            }
            if (cd_entry->disk_number_start != eocd->disk_number)
            {
                found = 0;
                zip_print("Error in zipfile %s: zipfile cannot span disks\n", zip_filename);
            }
            if (found)
                return 0;
        }
        entry = (ZipCentralDirectoryEntry *)((char *)entry
                                        + cd_entry->filename_length
                                        + cd_entry->extra_field_length
                                        + cd_entry->file_comment_length
                                        + 46);
    }
    return -1;
}

/* Loads all central directory entries and their local file headers into
 * zip_entry_names / Size[] / zip_num_entries_loaded. */
static int zip_load_local_file_headers(
        FILE *Stream,
        const ZipEndOfCentralDirectory *eocd,
        ZipCentralDirectoryEntryInMem *cd_entry)
{
    size_t read_size = eocd->central_dir_size;
    int entry_index;
    int name_index;
    int entry_slot;
    ZipCentralDirectoryEntry *entry;
    ZipLocalFileHeaderInMem local_header;
    char name_buf[ZIP_MAX_FILENAME_LEN];

    if (read_size > ZIP_READ_BUFFER_SIZE)
        read_size = ZIP_READ_BUFFER_SIZE;
    if (fseek(Stream, (long)eocd->central_dir_offset, SEEK_SET))
    {
        zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", zip_filename);
        return -1;
    }
    if (fread(zip_central_dir_buffer, 1, read_size, Stream) != read_size)
    {
        zip_print("Error in zipfile %s: couldn't read %lu bytes from central directory\n", zip_filename, (unsigned long)read_size);
        return -1;
    }

    entry = (ZipCentralDirectoryEntry *)zip_central_dir_buffer;
    for (entry_index = 0; entry_index < eocd->total_entries; ++entry_index)
    {
        zip_parse_cd_entry(entry, cd_entry);
        name_index = 0;
        if (cd_entry->filename_length)
        {
            do
            {
                if (name_index >= ZIP_MAX_FILENAME_LEN - 1)
                    break;
                name_buf[name_index] = (char)toupper((unsigned char)cd_entry->filename[name_index]);
                ++name_index;
            } while (name_index < cd_entry->filename_length);
        }
        name_buf[name_index] = 0;

        if (zip_read_local_file_header(Stream, cd_entry, &local_header, zip_local_file_header_buffer))
            zip_print("Error reading 'local file header' in zipfile %s\n", zip_filename);
        if (entry_index < 256)
        {
            entry_slot = zip_num_entries_loaded;
            strcpy((char *)&zip_entry_names[entry_slot << 8], name_buf);
            Size[entry_slot] = local_header.uncompressed_size;
            zip_num_entries_loaded = entry_slot + 1;
        }
        entry = (ZipCentralDirectoryEntry *)((char *)entry
                                        + cd_entry->filename_length
                                        + cd_entry->extra_field_length
                                        + cd_entry->file_comment_length
                                        + 46);
    }
    return 0;
}

/* Case-insensitive comparison of two (already upper-cased) names.  Returns 0
 * when str1 equals str2 or when the final path component of str1 equals
 * str2 (archive entries may carry directory prefixes), non-zero otherwise. */
static int zip_compare_filename_case_insensitive(const char *str1, const char *str2)
{
    if (strcmp(str1, str2) == 0)
        return 0;
    {
        const char *last = strrchr(str1, '/');
        if (last && strcmp(last + 1, str2) == 0)
            return 0;
    }
    return 1;
}

/* ===========================================================================
 * Public API
 * =========================================================================== */

int zip_extract_file(char *FileName, char *search_name, LPVOID *out_data, size_t *out_size)
{
    FILE *file;
    int status;
    int name_len;
    int i;
    void *out_buffer = NULL;
    LPVOID data = NULL;
    LPVOID lpMem = NULL;
    ZipEndOfCentralDirectory eocd;
    ZipLocalFileHeaderInMem local_header;
    ZipCentralDirectoryEntryInMem cd_entry;
    char ArgList[ZIP_MAX_FILENAME_LEN];

    zip_filename = zip_get_filename_from_path(FileName);
    file = fopen(FileName, "rb");
    if (!file)
    {
        zip_print("Could not open zipfile %s\n", FileName);
        return -1;
    }
    if (zip_get_file_size(file, &zip_file_size))
    {
        zip_print("Error in zipfile %s: get_file_length() failed\n", zip_filename);
        fclose(file);
        return -1;
    }
    if (zip_locate_central_dir(file, &eocd))
    {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", zip_filename);
        fclose(file);
        return -1;
    }
    if (eocd.disk_number != eocd.cd_start_disk
        || eocd.entries_this_disk != eocd.total_entries
        || !eocd.total_entries)
    {
        zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", zip_filename);
        fclose(file);
        return -1;
    }

    /* Upper-case the requested entry name (search is case-insensitive). */
    name_len = (int)strlen(search_name);
    if (name_len >= ZIP_MAX_FILENAME_LEN)
        name_len = ZIP_MAX_FILENAME_LEN - 1;
    for (i = 0; i < name_len; ++i)
        ArgList[i] = (char)toupper((unsigned char)search_name[i]);
    ArgList[name_len] = 0;

    status = zip_load_central_directory(file, ArgList, &eocd, &cd_entry);
    if (status)
    {
        zip_print("Could not find %s in zipfile %s\n", ArgList, zip_filename);
        fclose(file);
        return -1;
    }

    status = zip_read_local_file_header(file, &cd_entry, &local_header, zip_local_file_header_buffer);
    if (status)
    {
        zip_print("Error reading 'local file header' in zipfile %s\n", zip_filename);
        fclose(file);
        return -1;
    }

    if (local_header.compression_method == 8)
    {
        /* Deflated entry: read the compressed data and inflate it. */
        status = zip_read_compressed_data_to_buffer(file, &cd_entry, &local_header, &lpMem);
        if (status)
        {
            zip_print("Could not create input buffer for zipfile %s\n", zip_filename);
            fclose(file);
            return -1;
        }
        zipfile_input_buffer = (uint8_t *)lpMem;
        out_buffer = malloc(local_header.uncompressed_size);
        data = out_buffer;
        if (!out_buffer)
        {
            zip_print("Couldn't allocate %lu bytes for zipfile %s output buffer\n", (unsigned long)local_header.uncompressed_size, zip_filename);
            free(lpMem);
            fclose(file);
            return -1;
        }
        zip_inflate_output_ptr = (uint8_t *)out_buffer;
        zip_sliding_window = (uint8_t *)malloc(ZIP_SLIDING_WINDOW_SIZE);
        if (!zip_sliding_window)
        {
            zip_print("Could not create 32K sliding window for zipfile %s\n", zip_filename);
            free(lpMem);
            free(data);
            fclose(file);
            return -1;
        }
        status = zip_inflate_file();
        free(zip_sliding_window);
        zip_sliding_window = NULL;
        if (status)
        {
            zip_print("Error %d inflating compressed file from zipfile %s\n", status, zip_filename);
            free(lpMem);
            free(data);
            fclose(file);
            return -1;
        }
    }
    else if (local_header.compression_method == 0)
    {
        /* Stored entry: read the raw data. */
        status = zip_read_compressed_data_to_buffer(file, &cd_entry, &local_header, &data);
        if (status)
        {
            zip_print("Couldn't extract uncompressed file from zipfile %s\n", zip_filename);
            fclose(file);
            return -1;
        }
    }
    else
    {
        zip_print("Error in zipfile %s: compression method %u unsupported.\n", zip_filename, local_header.compression_method);
        fclose(file);
        return -1;
    }

    *out_data = data;
    *out_size = local_header.uncompressed_size;
    data = NULL;
    fclose(file);
    return 0;
}

int zip_load_file(char *FileName)
{
    FILE *file;
    ZipEndOfCentralDirectory eocd;
    ZipCentralDirectoryEntryInMem cd_entry;

    zip_filename = zip_get_filename_from_path(FileName);
    file = fopen(FileName, "rb");
    if (!file)
        return -1;
    if (zip_get_file_size(file, &zip_file_size))
    {
        zip_print("Error in zipfile %s: get_file_length() failed\n", zip_filename);
        fclose(file);
        return -1;
    }
    if (zip_locate_central_dir(file, &eocd))
    {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", zip_filename);
        fclose(file);
        return -1;
    }
    if (eocd.disk_number == eocd.cd_start_disk
        && eocd.entries_this_disk == eocd.total_entries
        && eocd.total_entries)
    {
        zip_load_local_file_headers(file, &eocd, &cd_entry);
        fclose(file);
        return 0;
    }
    zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", zip_filename);
    fclose(file);
    return -1;
}
