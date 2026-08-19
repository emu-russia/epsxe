#include "pch.h"

/* static prototypes for internal functions */
static int zip_inflate_block(int *final_flag);
static int zip_build_huffman_tree(
        uint32_t *lengths,
        unsigned int num_lengths,
        unsigned int literal_codes,
        int base_table,
        int extra_table,
        uint32_t *tree,
        unsigned int *max_bits);
static int zip_free_huffman_tree(int tree);
static unsigned int zip_copy_sliding_window_to_output(const void *src, unsigned int size);
static char * zip_get_filename_from_path(const char *path);
static int zip_print(char *Format, ...);
static int zip_read_compressed_data_to_buffer(FILE *Stream, int cd_entry, int local_header, LPVOID *out_buffer);
static int zip_read_local_file_header(FILE *Stream, int cd_entry, ZipLocalFileHeaderInMem *local_header, uint8_t *Buffer);
static int zip_load_central_directory(FILE *Stream, const char *search_name, int eocd, ZipCentralDirectoryEntry *cd_entry);
static int zip_load_local_file_headers(FILE *Stream, int eocd, ZipCentralDirectoryEntryInMem *cd_entry);
static int zip_compare_filename_case_insensitive(const char *str1, const char *str2);
static int zip_parse_cd_entry(ZipCentralDirectoryEntry *entry, ZipCentralDirectoryEntryInMem *cd_entry);
static int zip_locate_central_dir(FILE *Stream, int *eocd);
static BOOL zip_find_end_of_central_dir_signature(int buffer, int size, uint32_t *offset);
static int zip_get_file_size(FILE *Stream, uint32_t *size);
static int16_t zip_read_uint16_le(int ptr);
static uint32_t zip_read_uint32_le(uint8_t *ptr);

static int zip_inflate_data_with_trees(int ltree, int dtree, unsigned int ltree_bits, unsigned int dtree_bits)
{
  unsigned int window_pos;
  unsigned int bit_count;
  unsigned int bit_buffer;
  uint8_t *in_ptr;
  char bit_shift;
  uint8_t *ltree_node;
  unsigned int node_type;
  int drop_bits;
  unsigned int bits_needed;
  int refill_byte;
  int node_bits;
  char sym_shift;
  unsigned int dist_bit_count;
  unsigned int dist_bit_buffer;
  char dist_shift;
  uint8_t *dtree_node;
  unsigned int dist_node_type;
  int dist_drop_bits;
  unsigned int dist_bits_needed;
  int dist_refill_byte;
  int dist_node_bits;
  unsigned int dist_value;
  unsigned int dist_bits_left;
  int match_refill_byte;
  unsigned int copy_src;
  unsigned int copy_start;
  unsigned int copy_len;
  unsigned int saved_window_pos;
  unsigned int copy_remaining;
  int ltree_mask;
  int dtree_mask;

  window_pos = zip_inflate_window_pos;
  bit_count = zip_inflate_bit_count;
  bit_buffer = zip_inflate_bit_buffer;
  ltree_mask = (uint16_t)zip_bit_masks[ltree_bits];
  dtree_mask = (uint16_t)zip_bit_masks[dtree_bits];
LABEL_2:
  saved_window_pos = window_pos;
  while ( 1 )
  {
    while ( 1 )
    {
      for ( in_ptr = (uint8_t *)zipfile_input_buffer; bit_count < ltree_bits; zipfile_input_buffer = (int)in_ptr )
      {
        bit_shift = bit_count;
        bit_count += 8;
        bit_buffer |= *in_ptr++ << bit_shift;
      }
      ltree_node = (uint8_t *)(ltree + 8 * (bit_buffer & ltree_mask));
      node_type = *ltree_node;
      if ( node_type > 0x10 )
      {
        while ( node_type != 99 )
        {
          drop_bits = ltree_node[1];
          bits_needed = node_type - 16;
          bit_buffer >>= drop_bits;
          bit_count -= drop_bits;
          if ( bit_count < bits_needed )
          {
            do
            {
              refill_byte = *in_ptr << bit_count;
              bit_count += 8;
              bit_buffer |= refill_byte;
              zipfile_input_buffer = (int)++in_ptr;
            }
            while ( bit_count < bits_needed );
            window_pos = saved_window_pos;
          }
          ltree_node = (uint8_t *)(*((uint32_t *)ltree_node + 1) + 8 * (bit_buffer & (uint16_t)zip_bit_masks[bits_needed]));
          node_type = *ltree_node;
          if ( node_type <= 0x10 )
            goto LABEL_11;
        }
        return 1;
      }
LABEL_11:
      node_bits = ltree_node[1];
      bit_buffer >>= node_bits;
      bit_count -= node_bits;
      if ( node_type != 16 )
        break;
      *((uint8_t *)zip_sliding_window + window_pos++) = ltree_node[4];
      saved_window_pos = window_pos;
      if ( window_pos == 0x8000 )
      {
        zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
        window_pos = 0;
        goto LABEL_2;
      }
    }
    if ( node_type == 15 )
      break;
    if ( bit_count < node_type )
    {
      do
      {
        sym_shift = bit_count;
        bit_count += 8;
        bit_buffer |= *in_ptr++ << sym_shift;
        zipfile_input_buffer = (int)in_ptr;
      }
      while ( bit_count < node_type );
      window_pos = saved_window_pos;
    }
    dist_bit_count = bit_count - node_type;
    copy_remaining = *((uint16_t *)ltree_node + 2) + (bit_buffer & (uint16_t)zip_bit_masks[node_type]);
    for ( dist_bit_buffer = bit_buffer >> node_type; dist_bit_count < dtree_bits; zipfile_input_buffer = (int)in_ptr )
    {
      dist_shift = dist_bit_count;
      dist_bit_count += 8;
      dist_bit_buffer |= *in_ptr++ << dist_shift;
    }
    dtree_node = (uint8_t *)(dtree + 8 * (dist_bit_buffer & dtree_mask));
    dist_node_type = *dtree_node;
    if ( dist_node_type > 0x10 )
    {
      while ( dist_node_type != 99 )
      {
        dist_drop_bits = dtree_node[1];
        dist_bits_needed = dist_node_type - 16;
        dist_bit_buffer >>= dist_drop_bits;
        dist_bit_count -= dist_drop_bits;
        if ( dist_bit_count < dist_bits_needed )
        {
          do
          {
            dist_refill_byte = *in_ptr << dist_bit_count;
            dist_bit_count += 8;
            dist_bit_buffer |= dist_refill_byte;
            zipfile_input_buffer = (int)++in_ptr;
          }
          while ( dist_bit_count < dist_bits_needed );
          window_pos = saved_window_pos;
        }
        dtree_node = (uint8_t *)(*((uint32_t *)dtree_node + 1) + 8 * (dist_bit_buffer & (uint16_t)zip_bit_masks[dist_bits_needed]));
        dist_node_type = *dtree_node;
        if ( dist_node_type <= 0x10 )
          goto LABEL_26;
      }
      return 1;
    }
LABEL_26:
    dist_node_bits = dtree_node[1];
    dist_value = dist_bit_buffer >> dist_node_bits;
    dist_bits_left = dist_bit_count - dist_node_bits;
    if ( dist_bits_left < dist_node_type )
    {
      do
      {
        match_refill_byte = *in_ptr << dist_bits_left;
        dist_bits_left += 8;
        dist_value |= match_refill_byte;
        zipfile_input_buffer = (int)++in_ptr;
      }
      while ( dist_bits_left < dist_node_type );
      window_pos = saved_window_pos;
    }
    LOWORD(copy_src) = window_pos - (dist_value & zip_bit_masks[dist_node_type]) - *((uint16_t *)dtree_node + 2);
    bit_buffer = dist_value >> dist_node_type;
    bit_count = dist_bits_left - dist_node_type;
    do
    {
      copy_src &= 0x7FFFu;
      copy_start = copy_src;
      if ( copy_src <= window_pos )
        copy_start = window_pos;
      copy_len = 0x8000 - copy_start;
      if ( 0x8000 - copy_start > copy_remaining )
        copy_len = copy_remaining;
      copy_remaining -= copy_len;
      if ( window_pos - copy_src < copy_len )
      {
        do
        {
          *((uint8_t *)zip_sliding_window + window_pos++) = *((uint8_t *)zip_sliding_window + copy_src++);
          --copy_len;
        }
        while ( copy_len );
      }
      else
      {
        qmemcpy((char *)zip_sliding_window + window_pos, (char *)zip_sliding_window + copy_src, copy_len);
        window_pos = copy_len + saved_window_pos;
        LOWORD(copy_src) = copy_len + copy_src;
      }
      saved_window_pos = window_pos;
      if ( window_pos == 0x8000 )
      {
        zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
        window_pos = 0;
        saved_window_pos = 0;
      }
    }
    while ( copy_remaining );
  }
  zip_inflate_bit_buffer = bit_buffer;
  zip_inflate_bit_count = bit_count;
  zip_inflate_window_pos = window_pos;
  return 0;
}

static int zip_inflate_file()
{
  unsigned int max_memory_used;
  int block_result;
  int final_block;

  zip_inflate_window_pos = 0;
  zip_inflate_bit_count = 0;
  zip_inflate_bit_buffer = 0;
  max_memory_used = 0;
  while ( 1 )
  {
    zip_inflate_max_memory_used = 0;
    block_result = zip_inflate_block(&final_block);
    if ( block_result )
      break;
    if ( zip_inflate_max_memory_used > max_memory_used )
      max_memory_used = zip_inflate_max_memory_used;
    if ( final_block )
    {
      zip_copy_sliding_window_to_output(zip_sliding_window, zip_inflate_window_pos);
      return 0;
    }
  }
  return block_result;
}

static int zip_inflate_block(int *final_flag)
{
  int bit_count;
  unsigned int bit_buffer;
  uint8_t *in_ptr;
  int refill_byte;
  int *input_ptr;
  int is_final;
  unsigned int header_bits;
  unsigned int header_bit_count;
  int header_refill_byte;
  int block_type;
  int static_ltree_result;
  uint8_t *stored_in_ptr;
  int window_pos;
  int align_bits;
  unsigned int stored_bit_count;
  unsigned int stored_bit_buffer;
  int stored_refill_byte;
  unsigned int len_bit_count;
  int stored_len;
  unsigned int stored_nlen;
  int len_refill_byte;
  unsigned int byte_buffer;
  unsigned int byte_bit_count;
  char byte_shift;
  int static_dtree_result;
  uint8_t *dyn_in_ptr;
  unsigned int hlit_bit_buffer;
  unsigned int hlit_bit_count;
  int hlit_refill_byte;
  unsigned int hlit;
  unsigned int hdist_bit_count;
  unsigned int hdist_bit_buffer;
  int hdist_refill_byte;
  unsigned int hdist;
  unsigned int hclen_bit_count;
  unsigned int hclen_bit_buffer;
  int hclen_refill_byte;
  unsigned int hclen;
  unsigned int clen_bit_buffer;
  unsigned int clen_bit_count;
  unsigned int clen_index;
  char clen_shift;
  int order_index;
  int code_length;
  int clen_order;
  int clen_tree_result;
  unsigned int clen_bits;
  int saved_result;
  unsigned int lit_count;
  uint16_t tree_mask;
  unsigned int clen_pos;
  uint8_t *clen_in_ptr;
  int clen_refill_byte;
  int node_bits;
  int node_value;
  int repeat16_refill_byte;
  unsigned int repeat16_count;
  int repeat17_refill_byte;
  int repeat_count;
  int repeat18_refill_byte;
  int dyn_ltree_result;
  unsigned int dyn_dtree_result;
  int ltree;
  unsigned int tree_bits;
  int prev_code_length;
  unsigned int total_codes;
  int dtree;
  unsigned int dtree_bits;
  unsigned int hlit_count;
  unsigned int hdist_count;
  int clen_mask;
  uint32_t code_lengths[32];
  uint32_t static_lengths1[144];
  uint32_t static_lengths2[112];
  uint32_t static_lengths3[24];
  uint32_t static_lengths4[8];

  bit_count = zip_inflate_bit_count;
  bit_buffer = zip_inflate_bit_buffer;
  if ( !zip_inflate_bit_count )
  {
    in_ptr = (uint8_t *)zipfile_input_buffer;
    do
    {
      refill_byte = *in_ptr << bit_count;
      bit_count += 8;
      bit_buffer |= refill_byte;
      zipfile_input_buffer = (int)++in_ptr;
    }
    while ( !bit_count );
  }
  input_ptr = final_flag;
  is_final = bit_buffer & 1;
  header_bits = bit_buffer >> 1;
  header_bit_count = bit_count - 1;
  *final_flag = is_final;
  if ( header_bit_count < 2 )
  {
    input_ptr = (int *)zipfile_input_buffer;
    do
    {
      header_refill_byte = *(uint8_t *)input_ptr << header_bit_count;
      header_bit_count += 8;
      header_bits |= header_refill_byte;
      input_ptr = (int *)((char *)input_ptr + 1);
      zipfile_input_buffer = (int)input_ptr;
    }
    while ( header_bit_count < 2 );
  }
  block_type = header_bits & 3;
  zip_inflate_bit_buffer = header_bits >> 2;
  zip_inflate_bit_count = header_bit_count - 2;
  if ( block_type == 2 )
  {
    dyn_in_ptr = (uint8_t *)zipfile_input_buffer;
    hlit_bit_buffer = zip_inflate_bit_buffer;
    for ( hlit_bit_count = zip_inflate_bit_count; hlit_bit_count < 5; zipfile_input_buffer = (int)dyn_in_ptr )
    {
      hlit_refill_byte = *dyn_in_ptr << hlit_bit_count;
      hlit_bit_count += 8;
      hlit_bit_buffer |= hlit_refill_byte;
      ++dyn_in_ptr;
    }
    hlit = (hlit_bit_buffer & 0x1F) + 257;
    hdist_bit_count = hlit_bit_count - 5;
    hdist_bit_buffer = hlit_bit_buffer >> 5;
    for ( hlit_count = hlit; hdist_bit_count < 5; zipfile_input_buffer = (int)dyn_in_ptr )
    {
      hdist_refill_byte = *dyn_in_ptr << hdist_bit_count;
      hdist_bit_count += 8;
      hdist_bit_buffer |= hdist_refill_byte;
      ++dyn_in_ptr;
    }
    hdist = (hdist_bit_buffer & 0x1F) + 1;
    hclen_bit_count = hdist_bit_count - 5;
    hclen_bit_buffer = hdist_bit_buffer >> 5;
    for ( hdist_count = hdist; hclen_bit_count < 4; zipfile_input_buffer = (int)dyn_in_ptr )
    {
      hclen_refill_byte = *dyn_in_ptr << hclen_bit_count;
      hclen_bit_count += 8;
      hclen_bit_buffer |= hclen_refill_byte;
      ++dyn_in_ptr;
    }
    hclen = (hclen_bit_buffer & 0xF) + 4;
    clen_bit_buffer = hclen_bit_buffer >> 4;
    clen_bit_count = hclen_bit_count - 4;
    if ( hlit <= 0x120 && hdist <= 0x20 )
    {
      clen_index = 0;
      if ( !hclen )
        goto LABEL_94;
      do
      {
        for ( ; clen_bit_count < 3; zipfile_input_buffer = (int)dyn_in_ptr )
        {
          clen_shift = clen_bit_count;
          clen_bit_count += 8;
          clen_bit_buffer |= *dyn_in_ptr++ << clen_shift;
        }
        order_index = zip_code_length_order[clen_index];
        code_length = clen_bit_buffer & 7;
        clen_bit_buffer >>= 3;
        clen_bit_count -= 3;
        ++clen_index;
        code_lengths[order_index] = code_length;
      }
      while ( clen_index < hclen );
      if ( clen_index < 0x13 )
      {
LABEL_94:
        do
        {
          clen_order = zip_code_length_order[clen_index++];
          code_lengths[clen_order] = 0;
        }
        while ( clen_index < 0x13 );
      }
      tree_bits = 7;
      clen_tree_result = zip_build_huffman_tree(code_lengths, 0x13u, 0x13u, 0, 0, &ltree, &tree_bits);
      clen_bits = tree_bits;
      saved_result = clen_tree_result;
      if ( !tree_bits )
      {
        zip_free_huffman_tree(ltree);
        return 1;
      }
      if ( clen_tree_result )
      {
        if ( clen_tree_result == 1 )
          zip_free_huffman_tree(ltree);
        return saved_result;
      }
      lit_count = hlit_count;
      tree_mask = zip_bit_masks[tree_bits];
      clen_pos = 0;
      total_codes = hlit_count + hdist_count;
      prev_code_length = 0;
      clen_mask = tree_mask;
      if ( hlit_count + hdist_count )
      {
        clen_in_ptr = (uint8_t *)zipfile_input_buffer;
        while ( 1 )
        {
          if ( clen_bit_count < clen_bits )
          {
            do
            {
              clen_refill_byte = *clen_in_ptr << clen_bit_count;
              clen_bit_count += 8;
              clen_bit_buffer |= clen_refill_byte;
              zipfile_input_buffer = (int)++clen_in_ptr;
            }
            while ( clen_bit_count < tree_bits );
          }
          dtree = ltree + 8 * (clen_bit_buffer & clen_mask);
          node_bits = *(uint8_t *)(dtree + 1);
          clen_bit_buffer >>= node_bits;
          clen_bit_count -= node_bits;
          node_value = *(uint16_t *)(dtree + 4);
          if ( (uint16_t)node_value >= 0x10u )
          {
            if ( (uint16_t)node_value == 16 )
            {
              for ( ; clen_bit_count < 2; zipfile_input_buffer = (int)clen_in_ptr )
              {
                repeat16_refill_byte = *clen_in_ptr << clen_bit_count;
                clen_bit_count += 8;
                clen_bit_buffer |= repeat16_refill_byte;
                ++clen_in_ptr;
              }
              repeat16_count = (clen_bit_buffer & 3) + 3;
              clen_bit_buffer >>= 2;
              clen_bit_count -= 2;
              if ( clen_pos + repeat16_count > total_codes )
                return 1;
              if ( repeat16_count )
              {
                memset32(&code_lengths[clen_pos], prev_code_length, repeat16_count);
                clen_pos += repeat16_count;
              }
            }
            else
            {
              if ( node_value == 17 )
              {
                for ( ; clen_bit_count < 3; zipfile_input_buffer = (int)clen_in_ptr )
                {
                  repeat17_refill_byte = *clen_in_ptr << clen_bit_count;
                  clen_bit_count += 8;
                  clen_bit_buffer |= repeat17_refill_byte;
                  ++clen_in_ptr;
                }
                repeat_count = (clen_bit_buffer & 7) + 3;
                clen_bit_buffer >>= 3;
                clen_bit_count -= 3;
              }
              else
              {
                for ( ; clen_bit_count < 7; zipfile_input_buffer = (int)clen_in_ptr )
                {
                  repeat18_refill_byte = *clen_in_ptr << clen_bit_count;
                  clen_bit_count += 8;
                  clen_bit_buffer |= repeat18_refill_byte;
                  ++clen_in_ptr;
                }
                repeat_count = (clen_bit_buffer & 0x7F) + 11;
                clen_bit_buffer >>= 7;
                clen_bit_count -= 7;
              }
              if ( clen_pos + repeat_count > total_codes )
                return 1;
              if ( repeat_count )
              {
                memset(&code_lengths[clen_pos], 0, 4 * repeat_count);
                clen_pos += repeat_count;
              }
              prev_code_length = 0;
            }
          }
          else
          {
            code_lengths[clen_pos] = node_value;
            prev_code_length = node_value;
            ++clen_pos;
          }
          if ( clen_pos >= total_codes )
            break;
          clen_bits = tree_bits;
        }
        lit_count = hlit_count;
      }
      zip_free_huffman_tree(ltree);
      tree_bits = zip_static_ltree_max_bits;
      zip_inflate_bit_buffer = clen_bit_buffer;
      zip_inflate_bit_count = clen_bit_count;
      dyn_ltree_result = zip_build_huffman_tree(code_lengths, lit_count, 0x101u, (int)zip_length_base, (int)zip_length_extra_bits, &ltree, &tree_bits);
      if ( !tree_bits )
      {
        dyn_ltree_result = 1;
        goto LABEL_82;
      }
      if ( dyn_ltree_result )
      {
        if ( dyn_ltree_result != 1 )
          return dyn_ltree_result;
LABEL_82:
        printf("%s", "(incomplete l-tree)  ");
        zip_free_huffman_tree(ltree);
        return dyn_ltree_result;
      }
      dtree_bits = zip_static_dtree_max_bits;
      dyn_dtree_result = zip_build_huffman_tree(&code_lengths[lit_count], hdist_count, 0, (int)zip_distance_base, (int)zip_distance_extra_bits, &dtree, &dtree_bits);
      if ( dtree_bits || lit_count <= 0x101 )
      {
        if ( dyn_dtree_result >= 2 )
        {
          zip_free_huffman_tree(ltree);
          return dyn_dtree_result;
        }
        if ( !zip_inflate_data_with_trees(ltree, dtree, tree_bits, dtree_bits) )
        {
          zip_free_huffman_tree(ltree);
          zip_free_huffman_tree(dtree);
          return 0;
        }
      }
      else
      {
        printf("%s", "(incomplete d-tree)  ");
        zip_free_huffman_tree(ltree);
      }
    }
    return 1;
  }
  if ( (header_bits & 3) != 0 )
  {
    if ( block_type != 1 )
      return 2;
    code_lengths[31] = input_ptr;
    if ( zip_inflate_ltree )
      return zip_inflate_data_with_trees(
               zip_inflate_ltree,
               zip_inflate_dtree,
               zip_inflate_ltree_bits,
               zip_inflate_dtree_bits) != 0;
    memset32(static_lengths1, 8, 0x90u);
    memset32(static_lengths2, 9, 0x70u);
    memset32(static_lengths3, 7, 0x18u);
    memset32(static_lengths4, 8, 8u);
    zip_inflate_ltree_bits = 7;
    static_ltree_result = zip_build_huffman_tree(
               static_lengths1,
               0x120u,
               0x101u,
               (int)zip_length_base,
               (int)zip_length_extra_bits,
               &zip_inflate_ltree,
               (unsigned int *)&zip_inflate_ltree_bits);
    if ( static_ltree_result )
    {
      zip_inflate_ltree = 0;
      return static_ltree_result;
    }
    memset32(static_lengths1, 5, 0x1Eu);
    zip_inflate_dtree_bits = 5;
    static_dtree_result = zip_build_huffman_tree(
            static_lengths1,
            0x1Eu,
            0,
            (int)zip_distance_base,
            (int)zip_distance_extra_bits,
            &zip_inflate_dtree,
            (unsigned int *)&zip_inflate_dtree_bits);
    if ( static_dtree_result <= 1 )
    {
      return zip_inflate_data_with_trees(
               zip_inflate_ltree,
               zip_inflate_dtree,
               zip_inflate_ltree_bits,
               zip_inflate_dtree_bits) != 0;
    }
    else
    {
      zip_free_huffman_tree(zip_inflate_ltree);
      zip_inflate_ltree = 0;
      return static_dtree_result;
    }
  }
  else
  {
    stored_in_ptr = (uint8_t *)zipfile_input_buffer;
    window_pos = zip_inflate_window_pos;
    static_lengths4[5] = input_ptr;
    align_bits = zip_inflate_bit_count & 7;
    stored_bit_count = zip_inflate_bit_count - align_bits;
    for ( stored_bit_buffer = (unsigned int)zip_inflate_bit_buffer >> align_bits; stored_bit_count < 0x10; zipfile_input_buffer = (int)stored_in_ptr )
    {
      stored_refill_byte = *stored_in_ptr << stored_bit_count;
      stored_bit_count += 8;
      stored_bit_buffer |= stored_refill_byte;
      ++stored_in_ptr;
    }
    len_bit_count = stored_bit_count - 16;
    stored_len = (uint16_t)stored_bit_buffer;
    for ( stored_nlen = HIWORD(stored_bit_buffer); len_bit_count < 0x10; zipfile_input_buffer = (int)stored_in_ptr )
    {
      len_refill_byte = *stored_in_ptr << len_bit_count;
      len_bit_count += 8;
      stored_nlen |= len_refill_byte;
      ++stored_in_ptr;
    }
    if ( stored_len == (uint16_t)~(uint16_t)stored_nlen )
    {
      byte_buffer = HIWORD(stored_nlen);
      byte_bit_count = len_bit_count - 16;
      if ( stored_len )
      {
        while ( 1 )
        {
          for ( ; byte_bit_count < 8; zipfile_input_buffer = (int)stored_in_ptr )
          {
            byte_shift = byte_bit_count;
            byte_bit_count += 8;
            byte_buffer |= *stored_in_ptr++ << byte_shift;
          }
          *((uint8_t *)zip_sliding_window + window_pos++) = byte_buffer;
          if ( window_pos == 0x8000 )
          {
            zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
            window_pos = 0;
          }
          byte_buffer >>= 8;
          byte_bit_count -= 8;
          if ( !--stored_len )
            break;
          stored_in_ptr = (uint8_t *)zipfile_input_buffer;
        }
      }
      zip_inflate_bit_count = byte_bit_count;
      zip_inflate_window_pos = window_pos;
      zip_inflate_bit_buffer = byte_buffer;
      return 0;
    }
    else
    {
      return 1;
    }
  }
}

static int zip_build_huffman_tree(
        uint32_t *lengths,
        unsigned int num_lengths,
        unsigned int literal_codes,
        int base_table,
        int extra_table,
        uint32_t *tree,
        unsigned int *max_bits)
{
  uint32_t *p;
  unsigned int left;
  uint32_t *count_ptr;
  int status;
  unsigned int cur_bits;
  unsigned int bit_pattern;
  signed int bits;
  unsigned int scan_len;
  int avail_codes;
  int diff;
  unsigned int top_len;
  int max_count;
  int dummy_codes;
  int offset;
  unsigned int steps;
  int idx;
  int *len_p;
  unsigned int sym;
  int len;
  int pos;
  unsigned int *sym_p;
  int level;
  unsigned int bits_before;
  unsigned int table_size;
  signed int bits_so_far;
  unsigned int bits_cur;
  unsigned int bits_rem;
  unsigned int table_bits;
  unsigned int entries;
  uint32_t *counts_save;
  unsigned int avail;
  unsigned int next_count;
  unsigned int twice_avail;
  uint32_t *new_table;
  char *table_ptr;
  unsigned int bits_saved;
  unsigned int parent_idx;
  int parent_tbl;
  unsigned int sym_idx;
  int fill_count;
  unsigned int entry_idx;
  char *entry_ptr;
  unsigned int mask;
  int prev_bits;
  signed int cur_len;
  int codes_remain;
  unsigned int *saved_sym_p;
  int entry_word;
  char *entry_base;
  uint32_t *counts_p;
  unsigned int pattern;
  signed int max_len;
  char bits_minus_one;
  unsigned int max_bits_allowed;
  char *cur_table;
  int incomplete;
  uint32_t counts[17];
  uint32_t level_bits[16];
  uint32_t offsets[17];
  int level_tables[16];
  uint32_t symbols[288];
  int top_start;

  if ( num_lengths <= 0x100 )
    max_bits_allowed = 16;
  else
    max_bits_allowed = lengths[256];
  memset(counts, 0, sizeof(counts));
  p = lengths;
  left = num_lengths;
  do
  {
    count_ptr = &counts[*p++];
    --left;
    ++*count_ptr;
  }
  while ( left );
  if ( counts[0] == num_lengths )
  {
    *tree = 0;
    *max_bits = 0;
    return 0;
  }
  for ( cur_bits = 1; cur_bits <= 0x10; ++cur_bits )
  {
    bit_pattern = 0;
    if ( counts[cur_bits] )
      break;
  }
  bits = cur_bits;
  cur_len = cur_bits;
  if ( *max_bits < cur_bits )
    *max_bits = cur_bits;
  scan_len = 16;
  do
  {
    if ( counts[scan_len] )
      break;
    --scan_len;
  }
  while ( scan_len );
  max_len = scan_len;
  if ( *max_bits > scan_len )
    *max_bits = scan_len;
  for ( avail_codes = 1 << cur_bits; cur_bits < scan_len; avail_codes = 2 * diff )
  {
    diff = avail_codes - counts[cur_bits];
    if ( diff < 0 )
      return 2;
    ++cur_bits;
  }
  top_len = scan_len;
  max_count = counts[scan_len];
  dummy_codes = avail_codes - max_count;
  incomplete = dummy_codes;
  if ( dummy_codes < 0 )
    return 2;
  counts[scan_len] = dummy_codes + max_count;
  offset = 0;
  steps = scan_len - 1;
  offsets[1] = 0;
  if ( steps )
  {
    idx = 0;
    do
    {
      offset += counts[idx + 1];
      offsets[idx + 2] = offset;
      ++idx;
      --steps;
    }
    while ( steps );
  }
  memset(symbols, 0, sizeof(symbols));
  len_p = lengths;
  sym = 0;
  do
  {
    len = *len_p++;
    if ( len )
    {
      pos = offsets[len];
      symbols[pos] = sym;
      offsets[len] = pos + 1;
    }
    ++sym;
  }
  while ( sym < num_lengths );
  top_start = offsets[top_len];
  sym_p = symbols;
  level = -1;
  bits_before = 0;
  table_size = 0;
  pattern = 0;
  offsets[0] = 0;
  saved_sym_p = symbols;
  level_tables[0] = 0;
  cur_table = nullptr;
  if ( bits > max_len )
  {
LABEL_65:
    *max_bits = level_bits[0];
    if ( !incomplete )
      return 0;
    status = 1;
    if ( max_len == 1 )
      return 0;
  }
  else
  {
    bits_minus_one = bits - 1;
    counts_p = &counts[bits];
    while ( 1 )
    {
      codes_remain = *counts_p;
      if ( *counts_p )
        break;
LABEL_64:
      ++counts_p;
      ++bits;
      ++bits_minus_one;
      cur_len = bits;
      if ( bits > max_len )
        goto LABEL_65;
    }
    while ( 1 )
    {
      --codes_remain;
      bits_so_far = bits_before + level_bits[level];
      if ( bits > bits_so_far )
        break;
LABEL_49:
      if ( sym_p < &symbols[top_start] )
      {
        sym_idx = *sym_p;
        if ( *sym_p >= literal_codes )
        {
          sym_idx = 2 * (sym_idx - literal_codes);
          LOBYTE(entry_word) = *(uint8_t *)(sym_idx + extra_table);
          LOWORD(sym_idx) = *(uint16_t *)(sym_idx + base_table);
        }
        else
        {
          LOBYTE(entry_word) = (sym_idx < 0x100) + 15;
        }
        LOWORD(entry_base) = sym_idx;
        saved_sym_p = sym_p + 1;
      }
      else
      {
        LOBYTE(entry_word) = 99;
      }
      fill_count = 1 << (cur_len - bits_before);
      entry_idx = bit_pattern >> bits_before;
      if ( bit_pattern >> bits_before < table_size )
      {
        entry_ptr = &cur_table[8 * entry_idx];
        do
        {
          BYTE1(entry_word) = cur_len - bits_before;
          *(uint32_t *)entry_ptr = entry_word;
          *((uint32_t *)entry_ptr + 1) = entry_base;
          entry_idx += fill_count;
          entry_ptr += 8 * fill_count;
        }
        while ( entry_idx < table_size );
        bit_pattern = pattern;
      }
      for ( mask = 1 << bits_minus_one; (mask & bit_pattern) != 0; mask >>= 1 )
        bit_pattern ^= mask;
      bit_pattern ^= mask;
      for ( pattern = bit_pattern; (bit_pattern & ((1 << bits_before) - 1)) != offsets[level]; bits_before -= prev_bits )
        prev_bits = level_bits[--level];
      sym_p = saved_sym_p;
      bits = cur_len;
      if ( !codes_remain )
        goto LABEL_64;
    }
    while ( 1 )
    {
      bits_cur = bits_so_far;
      bits_rem = max_len - bits_so_far;
      ++level;
      if ( max_len - bits_so_far > *max_bits )
        bits_rem = *max_bits;
      table_bits = cur_len - bits_so_far;
      entries = 1 << (cur_len - bits_so_far);
      if ( entries > codes_remain + 1 )
      {
        counts_save = counts_p;
        avail = -1 - codes_remain + entries;
        if ( ++table_bits < bits_rem )
        {
          do
          {
            next_count = counts_save[1];
            ++counts_save;
            twice_avail = 2 * avail;
            if ( twice_avail <= next_count )
              break;
            avail = twice_avail - next_count;
            ++table_bits;
          }
          while ( table_bits < bits_rem );
        }
      }
      if ( table_bits + bits_cur > max_bits_allowed && bits_cur < max_bits_allowed )
        table_bits = max_bits_allowed - bits_cur;
      table_size = 1 << table_bits;
      level_bits[level] = table_bits;
      new_table = malloc(8 * (1 << table_bits) + 8);
      if ( !new_table )
        break;
      zip_inflate_max_memory_used += table_size + 1;
      table_ptr = (char *)(new_table + 2);
      *tree = new_table + 2;
      tree = new_table + 1;
      new_table[1] = 0;
      cur_table = (char *)(new_table + 2);
      level_tables[level] = (int)(new_table + 2);
      if ( level )
      {
        LOBYTE(entry_word) = table_bits + 16;
        BYTE1(entry_word) = level_bits[level - 1];
        bits_saved = bits_cur;
        offsets[level] = pattern;
        entry_base = table_ptr;
        parent_idx = (pattern & ((1 << bits_cur) - 1)) >> (bits_cur - LOBYTE(level_bits[level - 1]));
        parent_tbl = offsets[level + 16];
        *(uint32_t *)(parent_tbl + 8 * parent_idx) = entry_word;
        *(uint32_t *)(parent_tbl + 8 * parent_idx + 4) = entry_base;
      }
      else
      {
        bits_saved = bits_cur;
      }
      bits_so_far = level_bits[level] + bits_saved;
      if ( cur_len <= bits_so_far )
      {
        bits_before = bits_cur;
        bit_pattern = pattern;
        sym_p = saved_sym_p;
        goto LABEL_49;
      }
    }
    if ( level )
      zip_free_huffman_tree(level_tables[0]);
    return 3;
  }
  return status;
}

static int zip_free_huffman_tree(int tree)
{
  int node;
  int next;

  node = tree;
  if ( tree )
  {
    do
    {
      next = *(uint32_t *)(node - 4);
      free((LPVOID)(node - 8));
      node = next;
    }
    while ( next );
  }
  return 0;
}

static unsigned int zip_copy_sliding_window_to_output(const void *src, unsigned int size)
{
  qmemcpy((void *)zip_inflate_output_ptr, src, size);
  zip_inflate_output_ptr += size;
  return size;
}

int zip_extract_file(char *FileName, char *search_name, LPVOID *out_data, size_t *out_size)
{
  FILE *fp;
  FILE *file;
  int file_size;
  char *name_ptr;
  char upper_ch;
  void *out_buffer;
  int inflate_result;
  int ch;
  LPVOID data;
  LPVOID lpMem;
  int eocd;
  int16_t disk_number;
  int16_t cd_start_disk;
  int16_t entries_this_disk;
  int16_t total_entries;
  ZipLocalFileHeaderInMem local_header;
  char ArgList[32];
  ZipCentralDirectoryEntry cd_entry;

  lpMem = nullptr;
  data = nullptr;
  *(uint32_t *)zip_filename = zip_get_filename_from_path(FileName);
  fp = fopen(FileName, "rb");
  file = fp;
  if ( fp )
  {
    file_size = zip_get_file_size(fp, &zip_file_size);
    if ( file_size )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(const char **)zip_filename);
    }
    else
    {
      file_size = zip_locate_central_dir(file, &eocd);
      if ( file_size )
      {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", *(const char **)zip_filename);
      }
      else
      {
        if ( disk_number != cd_start_disk || entries_this_disk != total_entries || !total_entries )
        {
          file_size = -1;
          zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
          goto LABEL_13;
        }
        name_ptr = ArgList;
        do
        {
          ch = *search_name++;
          upper_ch = toupper(ch);
          *name_ptr++ = upper_ch;
        }
        while ( upper_ch );
        file_size = zip_load_central_directory(file, ArgList, (int)&eocd, &cd_entry);
        if ( file_size )
        {
          zip_print("Could not find %s in zipfile %s\n", ArgList, *(uint32_t *)zip_filename);
        }
        else
        {
          file_size = zip_read_local_file_header(file, (int)&cd_entry, &local_header, (uint8_t *)&zip_central_dir_buffer);
          if ( !file_size )
          {
            if ( local_header.compression_method )
            {
              if ( local_header.compression_method == 8 )
              {
                file_size = zip_read_compressed_data_to_buffer(file, (int)&cd_entry, (int)&local_header, &lpMem);
                if ( file_size )
                {
                  zip_print("Could not create input buffer for zipfile %s\n", *(const char **)zip_filename);
                  goto LABEL_13;
                }
                zipfile_input_buffer = (int)lpMem;
                out_buffer = malloc(local_header.uncompressed_size);
                data = out_buffer;
                if ( !out_buffer )
                {
                  zip_print(
                    "Couldn't allocate %d bytes for zipfile %s output buffer\n",
                    *(uint32_t *)zip_filename,
                    (const char *)local_header.uncompressed_size);
                  file_size = -1;
                  goto LABEL_13;
                }
                zip_inflate_output_ptr = (int)out_buffer;
                zip_sliding_window = malloc(0x8000u);
                if ( !zip_sliding_window )
                {
                  zip_print("Could not create 32K sliding window for zipfile %s\n", *(const char **)zip_filename);
                  file_size = -1;
                  goto LABEL_13;
                }
                inflate_result = zip_inflate_file();
                file_size = inflate_result;
                if ( inflate_result )
                {
                  zip_print("Error %d inflating compressed file from zipfile %s\n", inflate_result, *(uint32_t *)zip_filename);
                  goto LABEL_13;
                }
              }
            }
            else
            {
              file_size = zip_read_compressed_data_to_buffer(file, (int)&cd_entry, (int)&local_header, &data);
              if ( file_size )
              {
                zip_print("Couldn't extract uncompressed file from zipfile %s\n", *(const char **)zip_filename);
                goto LABEL_13;
              }
            }
            *out_data = data;
            *out_size = local_header.uncompressed_size;
            data = nullptr;
            goto LABEL_13;
          }
          zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
        }
      }
    }
LABEL_13:
    fclose(file);
    goto LABEL_14;
  }
  zip_print("Could not open zipfile %s\n", FileName);
  file_size = -1;
LABEL_14:
  if ( lpMem )
    free(lpMem);
  if ( data )
    free(data);
  if ( zip_sliding_window )
  {
    free(zip_sliding_window);
    zip_sliding_window = nullptr;
  }
  return file_size;
}

static char * zip_get_filename_from_path(const char *path)
{
  char *token;
  char *last_token;

  strcpy(zip_path_buffer, path);
  token = strtok(zip_path_buffer, "/\\:");
  if ( token )
  {
    do
    {
      last_token = token;
      token = strtok(nullptr, "/\\:");
    }
    while ( token );
    return last_token;
  }
  return token;
}

static int zip_print(char *Format, ...)
{
  char Buffer[256];
  va_list ArgList;

  va_start(ArgList, Format);
  vsprintf(Buffer, Format, ArgList);
  return printf(Buffer);
}

int zip_load_file(char *FileName)
{
  FILE *fp;
  FILE *file;
  int eocd;
  int16_t disk_number;
  int16_t cd_start_disk;
  int16_t entries_this_disk;
  int16_t total_entries;
  int entry_buf[13];

  *(uint32_t *)zip_filename = zip_get_filename_from_path(FileName);
  fp = fopen(FileName, "rb");
  file = fp;
  if ( fp )
  {
    if ( zip_get_file_size(fp, &zip_file_size) )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(uint32_t *)zip_filename);
    }
    else if ( zip_locate_central_dir(file, &eocd) )
    {
      zip_print("Error reading 'end of central directory' in zipfile %s\n", *(uint32_t *)zip_filename);
    }
    else
    {
      if ( disk_number == cd_start_disk && entries_this_disk == total_entries && total_entries )
      {
        zip_load_local_file_headers(file, (int)&eocd, (ZipCentralDirectoryEntryInMem *)entry_buf);
        fclose(file);
        return 0;
      }
      zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(uint32_t *)zip_filename);
    }
    fclose(file);
  }
  return 0;
}

static int zip_read_compressed_data_to_buffer(FILE *Stream, int cd_entry, int local_header, LPVOID *out_buffer)
{
  size_t compressed_size;
  void *buffer;
  int status;

  compressed_size = *(uint32_t *)(local_header + 20);
  buffer = malloc(compressed_size);
  *out_buffer = buffer;
  if ( !buffer )
  {
    zip_print("Couldn't allocate %ld bytes for input buffer for zipfile %s\n", compressed_size, *(const char **)zip_filename);
    return -1;
  }
  status = fseek(Stream, *(uint16_t *)(local_header + 28) + *(uint16_t *)(local_header + 30) + *(uint32_t *)(cd_entry + 44) + 30, 0);
  if ( status )
  {
    zip_print("Error reading zipfile %s: fseek to compressed data failed\n", *(const char **)zip_filename);
LABEL_7:
    if ( *out_buffer )
    {
      free(*out_buffer);
      *out_buffer = nullptr;
    }
    return status;
  }
  if ( fread(*out_buffer, 1u, compressed_size, Stream) != compressed_size )
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes of compressed data\n", *(const char **)zip_filename, compressed_size);
    status = -1;
    goto LABEL_7;
  }
  return status;
}

static int zip_read_local_file_header(FILE *Stream, int cd_entry, ZipLocalFileHeaderInMem *local_header, uint8_t *Buffer)
{
  int offset;
  size_t read_size;
  int status;

  offset = *(uint32_t *)(cd_entry + 44);
  read_size = zip_file_size - offset;
  if ( zip_file_size - offset >= 0x2000 )
    read_size = 0x2000;
  status = fseek(Stream, offset, 0);
  if ( status )
  {
    zip_print("Error in zipfile %s: couldn't fseek to local file header\n", *(const char **)zip_filename);
    return status;
  }
  else if ( fread(Buffer, 1u, read_size, Stream) == read_size )
  {

    local_header->signature = zip_read_uint32_le(Buffer);
    local_header->version_needed = zip_read_uint16_le((int)(Buffer + 4));
    local_header->general_purpose_bit_flag = zip_read_uint16_le((int)(Buffer + 6));
    local_header->compression_method = zip_read_uint16_le((int)(Buffer + 8));
    local_header->last_mod_time = zip_read_uint16_le((int)(Buffer + 10));
    local_header->last_mod_date = zip_read_uint16_le((int)(Buffer + 12));
    local_header->crc32 = zip_read_uint32_le(Buffer + 14);
    local_header->compressed_size = zip_read_uint32_le(Buffer + 18);
    local_header->uncompressed_size = zip_read_uint32_le(Buffer + 22);
    local_header->filename_length = zip_read_uint16_le((int)(Buffer + 26));
    local_header->extra_field_length = zip_read_uint16_le((int)(Buffer + 28));
    local_header->filename = (char *)(Buffer + 30);
    return 0;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from local file header", *(const char **)zip_filename, read_size);
    return -1;
  }
}

static int zip_load_central_directory(FILE *Stream, const char *search_name, int eocd, ZipCentralDirectoryEntry *cd_entry)
{
  int found;
  size_t read_size;
  int name_index;
  char ch;
  uint16_t filename_length;
  uint16_t compression_method;
  int entry_index;
  ZipCentralDirectoryEntry *entry;
  char name_buf[256];

  found = 0;
  read_size = 0x2000;
  if ( *(uint32_t *)(eocd + 12) <= 0x2000u )
    read_size = *(uint32_t *)(eocd + 12);
  if ( fseek(Stream, *(uint32_t *)(eocd + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, read_size, Stream) == read_size )
  {
    entry_index = 0;
    entry = &zip_central_dir_buffer;
    while ( entry_index < *(uint16_t *)(eocd + 10) )
    {
      zip_parse_cd_entry(entry, (ZipCentralDirectoryEntryInMem *)cd_entry);
      name_index = 0;
      if ( cd_entry->filename_length )
      {
        do
        {
          if ( name_index >= 254 )
            break;
          ch = toupper(*(char *)(*(uint32_t *)((char *)&cd_entry[1].signature + 2) + name_index));
          filename_length = cd_entry->filename_length;
          name_buf[name_index++] = ch;
        }
        while ( name_index < filename_length );
      }
      name_buf[name_index] = 0;
      if ( !zip_compare_filename_case_insensitive(name_buf, search_name) )
      {
        compression_method = cd_entry->compression_method;
        found = 1;
        if ( compression_method && compression_method != 8 )
        {
          found = 0;
          zip_print(
            "Error in zipfile %s: compression method for file %s unsupported.\n",
            *(const char **)zip_filename,
            search_name);
          zip_print("Method: $%04x  must be $0000 (Stored) or $0008 (Deflated)\n", cd_entry->compression_method);
        }
        if ( LOBYTE(cd_entry->version_needed) > 0x14u )
        {
          found = 0;
          zip_print("Error in zipfile %s: version for file %s too new.\n", *(const char **)zip_filename, search_name);
          zip_print("Version: $%02x must be $14 or less\n", LOBYTE(cd_entry->version_needed));
        }
        if ( HIBYTE(cd_entry->version_needed) )
        {
          found = 0;
          zip_print("Error in zipfile %s: OS for file %s not supported.\n", *(const char **)zip_filename, search_name);
          zip_print("OS: $%02x must be $00\n", HIBYTE(cd_entry->version_needed));
        }
        if ( cd_entry->disk_number_start != *(uint16_t *)(eocd + 4) )
        {
          found = 0;
          zip_print("Error in zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
        }
      }
      entry = (ZipCentralDirectoryEntry *)((char *)entry
                                      + cd_entry->filename_length
                                      + cd_entry->extra_field_length
                                      + cd_entry->file_comment_length
                                      + 46);
      ++entry_index;
      if ( found )
        return 0;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, read_size);
    return -1;
  }
}

static int zip_load_local_file_headers(FILE *Stream, int eocd, ZipCentralDirectoryEntryInMem *cd_entry)
{
  size_t read_size;
  int entry_index;
  ZipCentralDirectoryEntry *entry;
  int name_index;
  char upper_ch;
  uint16_t filename_length;
  int entry_slot;
  char *name_ptr;
  char *dst;
  char ch;
  ZipLocalFileHeaderInMem local_header;
  uint8_t name_buf[256];

  read_size = *(uint32_t *)(eocd + 12);
  if ( read_size > 0x2000 )
    read_size = 0x2000;
  if ( fseek(Stream, *(uint32_t *)(eocd + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, read_size, Stream) == read_size )
  {
    entry_index = 0;
    entry = &zip_central_dir_buffer;
    while ( entry_index < *(uint16_t *)(eocd + 10) )
    {
      zip_parse_cd_entry(entry, cd_entry);
      name_index = 0;
      if ( cd_entry->filename_length )
      {
        do
        {
          if ( name_index >= 254 )
            break;
          upper_ch = toupper(cd_entry->filename[name_index]);
          filename_length = cd_entry->filename_length;
          name_buf[name_index++] = upper_ch;
        }
        while ( name_index < filename_length );
      }
      name_buf[name_index] = 0;
      if ( zip_read_local_file_header(Stream, (int)cd_entry, &local_header, zip_local_file_header_buffer) )
        zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
      if ( entry_index < 256 )
      {
        entry_slot = zip_num_entries_loaded;
        name_ptr = name_buf;
        dst = &zip_entry_names[(zip_num_entries_loaded << 8) - (uint32_t)name_buf];
        do
        {
          ch = *name_ptr;
          name_ptr[(uint32_t)dst] = *name_ptr;
          ++name_ptr;
        }
        while ( ch );
        Size[entry_slot] = local_header.uncompressed_size;
        zip_num_entries_loaded = entry_slot + 1;
      }
      entry = (ZipCentralDirectoryEntry *)((char *)entry
                                      + cd_entry->filename_length
                                      + cd_entry->extra_field_length
                                      + cd_entry->file_comment_length
                                      + 46);
      ++entry_index;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, read_size);
    return -1;
  }
}

static int zip_compare_filename_case_insensitive(const char *str1, const char *str2)
{
  const char *p2;
  const char *p1;
  bool less;
  uint8_t c1;
  uint8_t c2;
  char *token;
  char *last_token;
  const char *q1;
  uint8_t c1b;
  uint8_t c2b;
  char String[256];

  p2 = str2;
  if ( strlen(str1) == strlen(str2) )
  {
    for ( p1 = str1; ; p1 += 2 )
    {
      less = *p1 < (unsigned int)*p2;
      if ( *p1 != *p2 )
        break;
      if ( !*p1 )
        return 0;
      c1 = p1[1];
      c2 = p2[1];
      less = c1 < c2;
      if ( c1 != c2 )
        break;
      p2 += 2;
      if ( !c1 )
        return 0;
    }
  }
  else
  {
    if ( str1[strlen(str1) - 1] == 47 )
      return 1;
    strcpy(String, str1);
    token = strtok(String, "/");
    if ( !token )
      return 1;
    do
    {
      last_token = token;
      token = strtok(nullptr, "/");
    }
    while ( token );
    q1 = last_token;
    while ( 1 )
    {
      less = *q1 < (unsigned int)*p2;
      if ( *q1 != *p2 )
        break;
      if ( *q1 )
      {
        c1b = q1[1];
        c2b = p2[1];
        less = c1b < c2b;
        if ( c1b != c2b )
          return -less - (less - 1);
        q1 += 2;
        p2 += 2;
        if ( c1b )
          continue;
      }
      return 0;
    }
  }
  return -less - (less - 1);
}

static int zip_parse_cd_entry(ZipCentralDirectoryEntry *entry, ZipCentralDirectoryEntryInMem *cd_entry)
{
  int local_header_offset;

  cd_entry->signature = zip_read_uint32_le((uint8_t *)entry);
  cd_entry->version_made_by = entry->version_made_by;
  cd_entry->version_needed = entry->version_needed;
  cd_entry->general_purpose_bit_flag = zip_read_uint16_le((int)&entry->general_purpose_bit_flag);
  cd_entry->compression_method = zip_read_uint16_le((int)&entry->compression_method);
  cd_entry->last_mod_time = zip_read_uint16_le((int)&entry->last_mod_time);
  cd_entry->last_mod_date = zip_read_uint16_le((int)&entry->last_mod_date);
  cd_entry->crc32 = zip_read_uint32_le((uint8_t *)&entry->crc32);
  cd_entry->compressed_size = zip_read_uint32_le((uint8_t *)&entry->compressed_size);
  cd_entry->uncompressed_size = zip_read_uint32_le((uint8_t *)&entry->uncompressed_size);
  cd_entry->filename_length = zip_read_uint16_le((int)&entry->filename_length);
  cd_entry->extra_field_length = zip_read_uint16_le((int)&entry->extra_field_length);
  cd_entry->file_comment_length = zip_read_uint16_le((int)&entry->file_comment_length);
  cd_entry->disk_number_start = zip_read_uint16_le((int)&entry->disk_number_start);
  cd_entry->internal_attributes = zip_read_uint16_le((int)&entry->internal_attributes);
  cd_entry->external_attributes = zip_read_uint32_le((uint8_t *)&entry->external_attributes);
  local_header_offset = zip_read_uint32_le((uint8_t *)&entry->local_header_offset);
  cd_entry->filename = (char *)&entry[1];
  cd_entry->local_header_offset = local_header_offset;
  return local_header_offset;
}

static int zip_locate_central_dir(FILE *Stream, int *eocd)
{
  size_t read_size;
  FILE *file;
  int status;
  BOOL end_of_central_dir_signature;
  uint8_t *eocd_ptr;
  uint32_t signature;
  int *record;

  read_size = zip_file_size;
  if ( (int)zip_file_size > 0x2000 )
    read_size = 0x2000;
  file = Stream;
  status = fseek(Stream, -read_size, 2);
  if ( status )
  {
    zip_print("Error in zipfile %s: fseek failed\n", *(const char **)zip_filename);
    return status;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, read_size, file) == read_size )
  {
    end_of_central_dir_signature = zip_find_end_of_central_dir_signature((int)&zip_central_dir_buffer, read_size, &Stream);
    if ( end_of_central_dir_signature )
    {
      zip_print("Error in zipfile %s: couldn't find 'end of central dir' signature\n", *(const char **)zip_filename);
      return end_of_central_dir_signature;
    }
    else
    {
      eocd_ptr = (uint8_t *)&zip_central_dir_buffer + (uint32_t)Stream;
      signature = zip_read_uint32_le((uint8_t *)&zip_central_dir_buffer + (uint32_t)Stream);
      record = eocd;
      *eocd = signature;
      *((uint16_t *)record + 2) = zip_read_uint16_le((int)(eocd_ptr + 4));
      *((uint16_t *)record + 3) = zip_read_uint16_le((int)(eocd_ptr + 6));
      *((uint16_t *)record + 4) = zip_read_uint16_le((int)(eocd_ptr + 8));
      *((uint16_t *)record + 5) = zip_read_uint16_le((int)(eocd_ptr + 10));
      record[3] = zip_read_uint32_le(eocd_ptr + 12);
      record[4] = zip_read_uint32_le(eocd_ptr + 16);
      *((uint16_t *)record + 10) = zip_read_uint16_le((int)(eocd_ptr + 20));
      return 0;
    }
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from end of file\n", *(const char **)zip_filename, read_size);
    return -1;
  }
}

static BOOL zip_find_end_of_central_dir_signature(int buffer, int size, uint32_t *offset)
{
  int pos;
  int found;

  pos = size - 22;
  found = 0;
  if ( size - 22 >= 0 )
  {
    while ( strncmp((const char *)(pos + buffer), zip_signature, 4u) )
    {
      if ( --pos < 0 )
        return 1;
    }
    found = 1;
    *offset = pos;
  }
  return found == 0;
}

static int zip_get_file_size(FILE *Stream, uint32_t *size)
{
  int status;
  int pos;

  status = fseek(Stream, 0, 2);
  if ( status )
    return status;
  pos = ftell(Stream);
  *size = pos;
  if ( pos != -1 )
    return status;
  return pos;
}

static int16_t zip_read_uint16_le(int ptr)
{
  return *(uint16_t *)ptr;
}

static uint32_t zip_read_uint32_le(uint8_t *ptr)
{
  return *ptr | ((ptr[1] | (*((uint16_t *)ptr + 1) << 8)) << 8);
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int Stream;
unsigned char zip_local_file_header_buffer[0x2000];
unsigned char zip_path_buffer[0x100];
unsigned short zip_bit_masks[12] = {0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x1ff, 0x3ff, 0x7ff};
unsigned char zip_central_dir_buffer[0x2000];
unsigned int zip_code_length_order[14] = {0x10, 0x11, 0x12, 0x0, 0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4, 0xc, 0x3};
unsigned char zip_distance_base[17] = {0x1, 0x0, 0x2, 0x0, 0x3, 0x0, 0x4, 0x0, 0x5, 0x0, 0x7, 0x0, 0x9, 0x0, 0xd, 0x0, 0x11};
unsigned char zip_distance_extra_bits[22] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x2, 0x0, 0x2, 0x0, 0x3, 0x0, 0x3, 0x0, 0x4, 0x0};
unsigned int zip_file_size;
unsigned int zip_filename;
unsigned int zip_inflate_bit_buffer;
unsigned int zip_inflate_bit_count;
unsigned int zip_inflate_dtree;
unsigned int zip_inflate_dtree_bits;
unsigned int zip_inflate_ltree;
unsigned int zip_inflate_ltree_bits;
unsigned int zip_inflate_max_memory_used;
unsigned int zip_inflate_output_ptr;
unsigned int zip_inflate_window_pos;
unsigned char zip_length_base[17] = {0x3, 0x0, 0x4, 0x0, 0x5, 0x0, 0x6, 0x0, 0x7, 0x0, 0x8, 0x0, 0x9, 0x0, 0xa, 0x0, 0xb};
unsigned char zip_length_extra_bits[30] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x2, 0x0, 0x2, 0x0, 0x2, 0x0};
unsigned char zip_signature = 0x50;
unsigned int zip_sliding_window;
unsigned int zip_static_dtree_max_bits = 0x6;
unsigned int zip_static_ltree_max_bits = 0x9;
unsigned int zipfile_input_buffer;
