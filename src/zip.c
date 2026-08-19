#include "pch.h"

/* static prototypes for internal functions */
static int zip_inflate_block(int *a1);
static int zip_build_huffman_tree(
        uint32_t *a1,
        unsigned int a2,
        unsigned int a3,
        int a4,
        int a5,
        uint32_t *a6,
        unsigned int *a7);
static int zip_free_huffman_tree(int a1);
static unsigned int zip_copy_sliding_window_to_output(const void *a1, unsigned int a2);
static char * zip_get_filename_from_path(const char *a1);
static int zip_print(char *Format, ...);
static int zip_read_compressed_data_to_buffer(FILE *Stream, int a2, int a3, LPVOID *a4);
static int zip_read_local_file_header(FILE *Stream, int a2, ZipLocalFileHeaderInMem *a3, uint8_t *Buffer);
static int zip_load_central_directory(FILE *Stream, const char *arg4, int a3, ZipCentralDirectoryEntry *a2);
static int zip_load_local_file_headers(FILE *Stream, int arg4, ZipCentralDirectoryEntryInMem *a2);
static int zip_compare_filename_case_insensitive(const char *a1, const char *a2);
static int zip_parse_cd_entry(ZipCentralDirectoryEntry *a1, ZipCentralDirectoryEntryInMem *a2);
static int zip_locate_central_dir(FILE *Stream, int *a2);
static BOOL zip_find_end_of_central_dir_signature(int a1, int a2, uint32_t *a3);
static int zip_get_file_size(FILE *Stream, uint32_t *a2);
static int16_t zip_read_uint16_le(int a1);
static uint32_t zip_read_uint32_le(uint8_t *a1);

static int zip_inflate_data_with_trees(int a1, int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v4;
  unsigned int v5;
  unsigned int v6;
  uint8_t *i;
  char v8;
  uint8_t *v9;
  unsigned int v10;
  int v11;
  unsigned int v12;
  int v13;
  int v14;
  char v15;
  unsigned int v16;
  unsigned int j;
  char v18;
  uint8_t *v19;
  unsigned int v20;
  int v21;
  unsigned int v22;
  int v23;
  int v24;
  unsigned int v25;
  unsigned int v26;
  int v27;
  unsigned int v28;
  unsigned int v29;
  unsigned int v30;
  unsigned int v32;
  unsigned int v33;
  int v34;
  int v35;

  v4 = zip_inflate_window_pos;
  v5 = zip_inflate_bit_count;
  v6 = zip_inflate_bit_buffer;
  v34 = (uint16_t)zip_bit_masks[a3];
  v35 = (uint16_t)zip_bit_masks[a4];
LABEL_2:
  v32 = v4;
  while ( 1 )
  {
    while ( 1 )
    {
      for ( i = (uint8_t *)zipfile_input_buffer; v5 < a3; zipfile_input_buffer = (int)i )
      {
        v8 = v5;
        v5 += 8;
        v6 |= *i++ << v8;
      }
      v9 = (uint8_t *)(a1 + 8 * (v6 & v34));
      v10 = *v9;
      if ( v10 > 0x10 )
      {
        while ( v10 != 99 )
        {
          v11 = v9[1];
          v12 = v10 - 16;
          v6 >>= v11;
          v5 -= v11;
          if ( v5 < v12 )
          {
            do
            {
              v13 = *i << v5;
              v5 += 8;
              v6 |= v13;
              zipfile_input_buffer = (int)++i;
            }
            while ( v5 < v12 );
            v4 = v32;
          }
          v9 = (uint8_t *)(*((uint32_t *)v9 + 1) + 8 * (v6 & (uint16_t)zip_bit_masks[v12]));
          v10 = *v9;
          if ( v10 <= 0x10 )
            goto LABEL_11;
        }
        return 1;
      }
LABEL_11:
      v14 = v9[1];
      v6 >>= v14;
      v5 -= v14;
      if ( v10 != 16 )
        break;
      *((uint8_t *)zip_sliding_window + v4++) = v9[4];
      v32 = v4;
      if ( v4 == 0x8000 )
      {
        zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
        v4 = 0;
        goto LABEL_2;
      }
    }
    if ( v10 == 15 )
      break;
    if ( v5 < v10 )
    {
      do
      {
        v15 = v5;
        v5 += 8;
        v6 |= *i++ << v15;
        zipfile_input_buffer = (int)i;
      }
      while ( v5 < v10 );
      v4 = v32;
    }
    v16 = v5 - v10;
    v33 = *((uint16_t *)v9 + 2) + (v6 & (uint16_t)zip_bit_masks[v10]);
    for ( j = v6 >> v10; v16 < a4; zipfile_input_buffer = (int)i )
    {
      v18 = v16;
      v16 += 8;
      j |= *i++ << v18;
    }
    v19 = (uint8_t *)(a2 + 8 * (j & v35));
    v20 = *v19;
    if ( v20 > 0x10 )
    {
      while ( v20 != 99 )
      {
        v21 = v19[1];
        v22 = v20 - 16;
        j >>= v21;
        v16 -= v21;
        if ( v16 < v22 )
        {
          do
          {
            v23 = *i << v16;
            v16 += 8;
            j |= v23;
            zipfile_input_buffer = (int)++i;
          }
          while ( v16 < v22 );
          v4 = v32;
        }
        v19 = (uint8_t *)(*((uint32_t *)v19 + 1) + 8 * (j & (uint16_t)zip_bit_masks[v22]));
        v20 = *v19;
        if ( v20 <= 0x10 )
          goto LABEL_26;
      }
      return 1;
    }
LABEL_26:
    v24 = v19[1];
    v25 = j >> v24;
    v26 = v16 - v24;
    if ( v26 < v20 )
    {
      do
      {
        v27 = *i << v26;
        v26 += 8;
        v25 |= v27;
        zipfile_input_buffer = (int)++i;
      }
      while ( v26 < v20 );
      v4 = v32;
    }
    LOWORD(v28) = v4 - (v25 & zip_bit_masks[v20]) - *((uint16_t *)v19 + 2);
    v6 = v25 >> v20;
    v5 = v26 - v20;
    do
    {
      v28 &= 0x7FFFu;
      v29 = v28;
      if ( v28 <= v4 )
        v29 = v4;
      v30 = 0x8000 - v29;
      if ( 0x8000 - v29 > v33 )
        v30 = v33;
      v33 -= v30;
      if ( v4 - v28 < v30 )
      {
        do
        {
          *((uint8_t *)zip_sliding_window + v4++) = *((uint8_t *)zip_sliding_window + v28++);
          --v30;
        }
        while ( v30 );
      }
      else
      {
        qmemcpy((char *)zip_sliding_window + v4, (char *)zip_sliding_window + v28, v30);
        v4 = v30 + v32;
        LOWORD(v28) = v30 + v28;
      }
      v32 = v4;
      if ( v4 == 0x8000 )
      {
        zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
        v4 = 0;
        v32 = 0;
      }
    }
    while ( v33 );
  }
  zip_inflate_bit_buffer = v6;
  zip_inflate_bit_count = v5;
  zip_inflate_window_pos = v4;
  return 0;
}

static int zip_inflate_file()
{
  unsigned int v0;
  int result;
  int v2;

  zip_inflate_window_pos = 0;
  zip_inflate_bit_count = 0;
  zip_inflate_bit_buffer = 0;
  v0 = 0;
  while ( 1 )
  {
    zip_inflate_max_memory_used = 0;
    result = zip_inflate_block(&v2);
    if ( result )
      break;
    if ( zip_inflate_max_memory_used > v0 )
      v0 = zip_inflate_max_memory_used;
    if ( v2 )
    {
      zip_copy_sliding_window_to_output(zip_sliding_window, zip_inflate_window_pos);
      return 0;
    }
  }
  return result;
}

static int zip_inflate_block(int *a1)
{
  int v1;
  unsigned int v2;
  uint8_t *v3;
  int v4;
  int *v5;
  int v6;
  unsigned int v7;
  unsigned int v8;
  int v9;
  int v10;
  int result;
  uint8_t *v12;
  int v13;
  int v14;
  unsigned int v15;
  unsigned int m;
  int v17;
  unsigned int v18;
  int v19;
  unsigned int n;
  int v21;
  unsigned int v22;
  unsigned int v23;
  char v24;
  int v25;
  uint8_t *v26;
  unsigned int v27;
  unsigned int i;
  int v29;
  unsigned int v30;
  unsigned int v31;
  unsigned int v32;
  int v33;
  unsigned int v34;
  unsigned int v35;
  unsigned int v36;
  int v37;
  unsigned int v38;
  unsigned int v39;
  unsigned int v40;
  unsigned int v41;
  char v42;
  int v43;
  int v44;
  int v45;
  int v46;
  unsigned int v47;
  int v48;
  unsigned int v49;
  uint16_t v50;
  unsigned int v51;
  uint8_t *v52;
  int v53;
  int v54;
  int v55;
  int v56;
  unsigned int v57;
  int v58;
  int v59;
  int v60;
  int v61;
  unsigned int v62;
  int v63;
  unsigned int v64;
  int v65;
  unsigned int v66;
  int v67;
  unsigned int v68;
  unsigned int j;
  unsigned int k;
  int v71;
  uint32_t v72[32];
  uint32_t v73[144];
  uint32_t v74[112];
  uint32_t v75[24];
  uint32_t v76[8];

  v1 = zip_inflate_bit_count;
  v2 = zip_inflate_bit_buffer;
  if ( !zip_inflate_bit_count )
  {
    v3 = (uint8_t *)zipfile_input_buffer;
    do
    {
      v4 = *v3 << v1;
      v1 += 8;
      v2 |= v4;
      zipfile_input_buffer = (int)++v3;
    }
    while ( !v1 );
  }
  v5 = a1;
  v6 = v2 & 1;
  v7 = v2 >> 1;
  v8 = v1 - 1;
  *a1 = v6;
  if ( v8 < 2 )
  {
    v5 = (int *)zipfile_input_buffer;
    do
    {
      v9 = *(uint8_t *)v5 << v8;
      v8 += 8;
      v7 |= v9;
      v5 = (int *)((char *)v5 + 1);
      zipfile_input_buffer = (int)v5;
    }
    while ( v8 < 2 );
  }
  v10 = v7 & 3;
  zip_inflate_bit_buffer = v7 >> 2;
  zip_inflate_bit_count = v8 - 2;
  if ( v10 == 2 )
  {
    v26 = (uint8_t *)zipfile_input_buffer;
    v27 = zip_inflate_bit_buffer;
    for ( i = zip_inflate_bit_count; i < 5; zipfile_input_buffer = (int)v26 )
    {
      v29 = *v26 << i;
      i += 8;
      v27 |= v29;
      ++v26;
    }
    v30 = (v27 & 0x1F) + 257;
    v31 = i - 5;
    v32 = v27 >> 5;
    for ( j = v30; v31 < 5; zipfile_input_buffer = (int)v26 )
    {
      v33 = *v26 << v31;
      v31 += 8;
      v32 |= v33;
      ++v26;
    }
    v34 = (v32 & 0x1F) + 1;
    v35 = v31 - 5;
    v36 = v32 >> 5;
    for ( k = v34; v35 < 4; zipfile_input_buffer = (int)v26 )
    {
      v37 = *v26 << v35;
      v35 += 8;
      v36 |= v37;
      ++v26;
    }
    v38 = (v36 & 0xF) + 4;
    v39 = v36 >> 4;
    v40 = v35 - 4;
    if ( v30 <= 0x120 && v34 <= 0x20 )
    {
      v41 = 0;
      if ( !v38 )
        goto LABEL_94;
      do
      {
        for ( ; v40 < 3; zipfile_input_buffer = (int)v26 )
        {
          v42 = v40;
          v40 += 8;
          v39 |= *v26++ << v42;
        }
        v43 = zip_code_length_order[v41];
        v44 = v39 & 7;
        v39 >>= 3;
        v40 -= 3;
        ++v41;
        v72[v43] = v44;
      }
      while ( v41 < v38 );
      if ( v41 < 0x13 )
      {
LABEL_94:
        do
        {
          v45 = zip_code_length_order[v41++];
          v72[v45] = 0;
        }
        while ( v41 < 0x13 );
      }
      v64 = 7;
      v46 = zip_build_huffman_tree(v72, 0x13u, 0x13u, 0, 0, &v63, &v64);
      v47 = v64;
      v48 = v46;
      if ( !v64 )
      {
        zip_free_huffman_tree(v63);
        return 1;
      }
      if ( v46 )
      {
        if ( v46 == 1 )
          zip_free_huffman_tree(v63);
        return v48;
      }
      v49 = j;
      v50 = zip_bit_masks[v64];
      v51 = 0;
      v66 = j + k;
      v65 = 0;
      v71 = v50;
      if ( j + k )
      {
        v52 = (uint8_t *)zipfile_input_buffer;
        while ( 1 )
        {
          if ( v40 < v47 )
          {
            do
            {
              v53 = *v52 << v40;
              v40 += 8;
              v39 |= v53;
              zipfile_input_buffer = (int)++v52;
            }
            while ( v40 < v64 );
          }
          v67 = v63 + 8 * (v39 & v71);
          v54 = *(uint8_t *)(v67 + 1);
          v39 >>= v54;
          v40 -= v54;
          v55 = *(uint16_t *)(v67 + 4);
          if ( (uint16_t)v55 >= 0x10u )
          {
            if ( (uint16_t)v55 == 16 )
            {
              for ( ; v40 < 2; zipfile_input_buffer = (int)v52 )
              {
                v56 = *v52 << v40;
                v40 += 8;
                v39 |= v56;
                ++v52;
              }
              v57 = (v39 & 3) + 3;
              v39 >>= 2;
              v40 -= 2;
              if ( v51 + v57 > v66 )
                return 1;
              if ( v57 )
              {
                memset32(&v72[v51], v65, v57);
                v51 += v57;
              }
            }
            else
            {
              if ( v55 == 17 )
              {
                for ( ; v40 < 3; zipfile_input_buffer = (int)v52 )
                {
                  v58 = *v52 << v40;
                  v40 += 8;
                  v39 |= v58;
                  ++v52;
                }
                v59 = (v39 & 7) + 3;
                v39 >>= 3;
                v40 -= 3;
              }
              else
              {
                for ( ; v40 < 7; zipfile_input_buffer = (int)v52 )
                {
                  v60 = *v52 << v40;
                  v40 += 8;
                  v39 |= v60;
                  ++v52;
                }
                v59 = (v39 & 0x7F) + 11;
                v39 >>= 7;
                v40 -= 7;
              }
              if ( v51 + v59 > v66 )
                return 1;
              if ( v59 )
              {
                memset(&v72[v51], 0, 4 * v59);
                v51 += v59;
              }
              v65 = 0;
            }
          }
          else
          {
            v72[v51] = v55;
            v65 = v55;
            ++v51;
          }
          if ( v51 >= v66 )
            break;
          v47 = v64;
        }
        v49 = j;
      }
      zip_free_huffman_tree(v63);
      v64 = zip_static_ltree_max_bits;
      zip_inflate_bit_buffer = v39;
      zip_inflate_bit_count = v40;
      v61 = zip_build_huffman_tree(v72, v49, 0x101u, (int)zip_length_base, (int)zip_length_extra_bits, &v63, &v64);
      if ( !v64 )
      {
        v61 = 1;
        goto LABEL_82;
      }
      if ( v61 )
      {
        if ( v61 != 1 )
          return v61;
LABEL_82:
        printf("%s", "(incomplete l-tree)  ");
        zip_free_huffman_tree(v63);
        return v61;
      }
      v68 = zip_static_dtree_max_bits;
      v62 = zip_build_huffman_tree(&v72[v49], k, 0, (int)zip_distance_base, (int)zip_distance_extra_bits, &v67, &v68);
      if ( v68 || v49 <= 0x101 )
      {
        if ( v62 >= 2 )
        {
          zip_free_huffman_tree(v63);
          return v62;
        }
        if ( !zip_inflate_data_with_trees(v63, v67, v64, v68) )
        {
          zip_free_huffman_tree(v63);
          zip_free_huffman_tree(v67);
          return 0;
        }
      }
      else
      {
        printf("%s", "(incomplete d-tree)  ");
        zip_free_huffman_tree(v63);
      }
    }
    return 1;
  }
  if ( (v7 & 3) != 0 )
  {
    if ( v10 != 1 )
      return 2;
    v72[31] = v5;
    if ( zip_inflate_ltree )
      return zip_inflate_data_with_trees(
               zip_inflate_ltree,
               zip_inflate_dtree,
               zip_inflate_ltree_bits,
               zip_inflate_dtree_bits) != 0;
    memset32(v73, 8, 0x90u);
    memset32(v74, 9, 0x70u);
    memset32(v75, 7, 0x18u);
    memset32(v76, 8, 8u);
    zip_inflate_ltree_bits = 7;
    result = zip_build_huffman_tree(
               v73,
               0x120u,
               0x101u,
               (int)zip_length_base,
               (int)zip_length_extra_bits,
               &zip_inflate_ltree,
               (unsigned int *)&zip_inflate_ltree_bits);
    if ( result )
    {
      zip_inflate_ltree = 0;
      return result;
    }
    memset32(v73, 5, 0x1Eu);
    zip_inflate_dtree_bits = 5;
    v25 = zip_build_huffman_tree(
            v73,
            0x1Eu,
            0,
            (int)zip_distance_base,
            (int)zip_distance_extra_bits,
            &zip_inflate_dtree,
            (unsigned int *)&zip_inflate_dtree_bits);
    if ( v25 <= 1 )
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
      return v25;
    }
  }
  else
  {
    v12 = (uint8_t *)zipfile_input_buffer;
    v13 = zip_inflate_window_pos;
    v76[5] = v5;
    v14 = zip_inflate_bit_count & 7;
    v15 = zip_inflate_bit_count - v14;
    for ( m = (unsigned int)zip_inflate_bit_buffer >> v14; v15 < 0x10; zipfile_input_buffer = (int)v12 )
    {
      v17 = *v12 << v15;
      v15 += 8;
      m |= v17;
      ++v12;
    }
    v18 = v15 - 16;
    v19 = (uint16_t)m;
    for ( n = HIWORD(m); v18 < 0x10; zipfile_input_buffer = (int)v12 )
    {
      v21 = *v12 << v18;
      v18 += 8;
      n |= v21;
      ++v12;
    }
    if ( v19 == (uint16_t)~(uint16_t)n )
    {
      v22 = HIWORD(n);
      v23 = v18 - 16;
      if ( v19 )
      {
        while ( 1 )
        {
          for ( ; v23 < 8; zipfile_input_buffer = (int)v12 )
          {
            v24 = v23;
            v23 += 8;
            v22 |= *v12++ << v24;
          }
          *((uint8_t *)zip_sliding_window + v13++) = v22;
          if ( v13 == 0x8000 )
          {
            zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
            v13 = 0;
          }
          v22 >>= 8;
          v23 -= 8;
          if ( !--v19 )
            break;
          v12 = (uint8_t *)zipfile_input_buffer;
        }
      }
      zip_inflate_bit_count = v23;
      zip_inflate_window_pos = v13;
      zip_inflate_bit_buffer = v22;
      return 0;
    }
    else
    {
      return 1;
    }
  }
}

static int zip_build_huffman_tree(
        uint32_t *a1,
        unsigned int a2,
        unsigned int a3,
        int a4,
        int a5,
        uint32_t *a6,
        unsigned int *a7)
{
  uint32_t *v7;
  unsigned int v8;
  uint32_t *v9;
  int result;
  unsigned int i;
  unsigned int v12;
  signed int v13;
  unsigned int v14;
  int j;
  int v16;
  unsigned int v17;
  int v18;
  int v19;
  int v20;
  unsigned int v21;
  int v22;
  int *v23;
  unsigned int v24;
  int v25;
  int v26;
  unsigned int *v27;
  int v28;
  unsigned int v29;
  unsigned int v30;
  signed int v31;
  unsigned int v32;
  unsigned int v33;
  unsigned int v34;
  unsigned int v35;
  uint32_t *v36;
  unsigned int v37;
  unsigned int v38;
  unsigned int v39;
  uint32_t *v40;
  char *v41;
  unsigned int v42;
  unsigned int v43;
  int v44;
  unsigned int v45;
  int v46;
  unsigned int v47;
  char *v48;
  unsigned int k;
  int v50;
  signed int v51;
  int v52;
  unsigned int *v53;
  int v54;
  char *v55;
  uint32_t *v56;
  unsigned int m;
  signed int v58;
  char v59;
  unsigned int v60;
  char *v61;
  int v62;
  uint32_t v63[17];
  int v64;
  uint32_t v65[16];
  uint32_t v66[17];
  int v67[16];
  uint32_t v68[288];
  int v69;

  if ( a2 <= 0x100 )
    v60 = 16;
  else
    v60 = a1[256];
  memset(v63, 0, sizeof(v63));
  v7 = a1;
  v8 = a2;
  do
  {
    v9 = &v63[*v7++];
    --v8;
    ++*v9;
  }
  while ( v8 );
  if ( v63[0] == a2 )
  {
    *a6 = 0;
    *a7 = 0;
    return 0;
  }
  for ( i = 1; i <= 0x10; ++i )
  {
    v12 = 0;
    if ( v63[i] )
      break;
  }
  v13 = i;
  v51 = i;
  if ( *a7 < i )
    *a7 = i;
  v14 = 16;
  do
  {
    if ( v63[v14] )
      break;
    --v14;
  }
  while ( v14 );
  v58 = v14;
  if ( *a7 > v14 )
    *a7 = v14;
  for ( j = 1 << i; i < v14; j = 2 * v16 )
  {
    v16 = j - v63[i];
    if ( v16 < 0 )
      return 2;
    ++i;
  }
  v17 = v14;
  v18 = v63[v14];
  v19 = j - v18;
  v62 = v19;
  if ( v19 < 0 )
    return 2;
  v63[v14] = v19 + v18;
  v20 = 0;
  v21 = v14 - 1;
  v66[1] = 0;
  if ( v21 )
  {
    v22 = 0;
    do
    {
      v20 += v63[v22 + 1];
      v66[v22 + 2] = v20;
      ++v22;
      --v21;
    }
    while ( v21 );
  }
  memset(v68, 0, sizeof(v68));
  v23 = a1;
  v24 = 0;
  do
  {
    v25 = *v23++;
    if ( v25 )
    {
      v26 = v66[v25];
      v68[v26] = v24;
      v66[v25] = v26 + 1;
    }
    ++v24;
  }
  while ( v24 < a2 );
  v69 = v66[v17];
  v27 = v68;
  v28 = -1;
  v29 = 0;
  v30 = 0;
  m = 0;
  v66[0] = 0;
  v53 = v68;
  v64 = 0;
  v67[0] = 0;
  v61 = nullptr;
  if ( v13 > v58 )
  {
LABEL_65:
    *a7 = v65[0];
    if ( !v62 )
      return 0;
    result = 1;
    if ( v58 == 1 )
      return 0;
  }
  else
  {
    v59 = v13 - 1;
    v56 = &v63[v13];
    while ( 1 )
    {
      v52 = *v56;
      if ( *v56 )
        break;
LABEL_64:
      ++v56;
      ++v13;
      ++v59;
      v51 = v13;
      if ( v13 > v58 )
        goto LABEL_65;
    }
    while ( 1 )
    {
      --v52;
      v31 = v29 + v65[v28];
      if ( v13 > v31 )
        break;
LABEL_49:
      if ( v27 < &v68[v69] )
      {
        v45 = *v27;
        if ( *v27 >= a3 )
        {
          v45 = 2 * (v45 - a3);
          LOBYTE(v54) = *(uint8_t *)(v45 + a5);
          LOWORD(v45) = *(uint16_t *)(v45 + a4);
        }
        else
        {
          LOBYTE(v54) = (v45 < 0x100) + 15;
        }
        LOWORD(v55) = v45;
        v53 = v27 + 1;
      }
      else
      {
        LOBYTE(v54) = 99;
      }
      v46 = 1 << (v51 - v29);
      v47 = v12 >> v29;
      if ( v12 >> v29 < v30 )
      {
        v48 = &v61[8 * v47];
        do
        {
          BYTE1(v54) = v51 - v29;
          *(uint32_t *)v48 = v54;
          *((uint32_t *)v48 + 1) = v55;
          v47 += v46;
          v48 += 8 * v46;
        }
        while ( v47 < v30 );
        v12 = m;
      }
      for ( k = 1 << v59; (k & v12) != 0; k >>= 1 )
        v12 ^= k;
      v12 ^= k;
      for ( m = v12; (v12 & ((1 << v29) - 1)) != v66[v28]; v29 -= v50 )
        v50 = v65[--v28];
      v27 = v53;
      v13 = v51;
      if ( !v52 )
        goto LABEL_64;
    }
    while ( 1 )
    {
      v32 = v31;
      v33 = v58 - v31;
      ++v28;
      if ( v58 - v31 > *a7 )
        v33 = *a7;
      v34 = v51 - v31;
      v35 = 1 << (v51 - v31);
      if ( v35 > v52 + 1 )
      {
        v36 = v56;
        v37 = -1 - v52 + v35;
        if ( ++v34 < v33 )
        {
          do
          {
            v38 = v36[1];
            ++v36;
            v39 = 2 * v37;
            if ( v39 <= v38 )
              break;
            v37 = v39 - v38;
            ++v34;
          }
          while ( v34 < v33 );
        }
      }
      if ( v34 + v32 > v60 && v32 < v60 )
        v34 = v60 - v32;
      v30 = 1 << v34;
      v65[v28] = v34;
      v40 = malloc(8 * (1 << v34) + 8);
      if ( !v40 )
        break;
      zip_inflate_max_memory_used += v30 + 1;
      v41 = (char *)(v40 + 2);
      *a6 = v40 + 2;
      a6 = v40 + 1;
      v40[1] = 0;
      v61 = (char *)(v40 + 2);
      v67[v28] = (int)(v40 + 2);
      if ( v28 )
      {
        LOBYTE(v54) = v34 + 16;
        BYTE1(v54) = v65[v28 - 1];
        v42 = v32;
        v66[v28] = m;
        v55 = v41;
        v43 = (m & ((1 << v32) - 1)) >> (v32 - LOBYTE(v65[v28 - 1]));
        v44 = v66[v28 + 16];
        *(uint32_t *)(v44 + 8 * v43) = v54;
        *(uint32_t *)(v44 + 8 * v43 + 4) = v55;
      }
      else
      {
        v42 = v32;
      }
      v31 = v65[v28] + v42;
      if ( v51 <= v31 )
      {
        v29 = v32;
        v12 = m;
        v27 = v53;
        goto LABEL_49;
      }
    }
    if ( v28 )
      zip_free_huffman_tree(v67[0]);
    return 3;
  }
  return result;
}

static int zip_free_huffman_tree(int a1)
{
  int v1;
  int v2;

  v1 = a1;
  if ( a1 )
  {
    do
    {
      v2 = *(uint32_t *)(v1 - 4);
      free((LPVOID)(v1 - 8));
      v1 = v2;
    }
    while ( v2 );
  }
  return 0;
}

static unsigned int zip_copy_sliding_window_to_output(const void *a1, unsigned int a2)
{
  qmemcpy((void *)zip_inflate_output_ptr, a1, a2);
  zip_inflate_output_ptr += a2;
  return a2;
}

int zip_extract_file(char *FileName, char *arg4, LPVOID *arg8, size_t *a4)
{
  FILE *v4;
  FILE *v5;
  int file_size;
  char *v8;
  char v9;
  void *v11;
  int v12;
  int v13;
  LPVOID v14;
  LPVOID lpMem;
  int v16;
  int16_t v17;
  int16_t v18;
  int16_t v19;
  int16_t v20;
  ZipLocalFileHeaderInMem a3;
  char ArgList[32];
  ZipCentralDirectoryEntry a2;

  lpMem = nullptr;
  v14 = nullptr;
  *(uint32_t *)zip_filename = zip_get_filename_from_path(FileName);
  v4 = fopen(FileName, "rb");
  v5 = v4;
  if ( v4 )
  {
    file_size = zip_get_file_size(v4, &zip_file_size);
    if ( file_size )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(const char **)zip_filename);
    }
    else
    {
      file_size = zip_locate_central_dir(v5, &v16);
      if ( file_size )
      {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", *(const char **)zip_filename);
      }
      else
      {
        if ( v17 != v18 || v19 != v20 || !v20 )
        {
          file_size = -1;
          zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
          goto LABEL_13;
        }
        v8 = ArgList;
        do
        {
          v13 = *arg4++;
          v9 = toupper(v13);
          *v8++ = v9;
        }
        while ( v9 );
        file_size = zip_load_central_directory(v5, ArgList, (int)&v16, &a2);
        if ( file_size )
        {
          zip_print("Could not find %s in zipfile %s\n", ArgList, *(uint32_t *)zip_filename);
        }
        else
        {
          file_size = zip_read_local_file_header(v5, (int)&a2, &a3, (uint8_t *)&zip_central_dir_buffer);
          if ( !file_size )
          {
            if ( a3.compression_method )
            {
              if ( a3.compression_method == 8 )
              {
                file_size = zip_read_compressed_data_to_buffer(v5, (int)&a2, (int)&a3, &lpMem);
                if ( file_size )
                {
                  zip_print("Could not create input buffer for zipfile %s\n", *(const char **)zip_filename);
                  goto LABEL_13;
                }
                zipfile_input_buffer = (int)lpMem;
                v11 = malloc(a3.uncompressed_size);
                v14 = v11;
                if ( !v11 )
                {
                  zip_print(
                    "Couldn't allocate %d bytes for zipfile %s output buffer\n",
                    *(uint32_t *)zip_filename,
                    (const char *)a3.uncompressed_size);
                  file_size = -1;
                  goto LABEL_13;
                }
                zip_inflate_output_ptr = (int)v11;
                zip_sliding_window = malloc(0x8000u);
                if ( !zip_sliding_window )
                {
                  zip_print("Could not create 32K sliding window for zipfile %s\n", *(const char **)zip_filename);
                  file_size = -1;
                  goto LABEL_13;
                }
                v12 = zip_inflate_file();
                file_size = v12;
                if ( v12 )
                {
                  zip_print("Error %d inflating compressed file from zipfile %s\n", v12, *(uint32_t *)zip_filename);
                  goto LABEL_13;
                }
              }
            }
            else
            {
              file_size = zip_read_compressed_data_to_buffer(v5, (int)&a2, (int)&a3, &v14);
              if ( file_size )
              {
                zip_print("Couldn't extract uncompressed file from zipfile %s\n", *(const char **)zip_filename);
                goto LABEL_13;
              }
            }
            *arg8 = v14;
            *a4 = a3.uncompressed_size;
            v14 = nullptr;
            goto LABEL_13;
          }
          zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
        }
      }
    }
LABEL_13:
    fclose(v5);
    goto LABEL_14;
  }
  zip_print("Could not open zipfile %s\n", FileName);
  file_size = -1;
LABEL_14:
  if ( lpMem )
    free(lpMem);
  if ( v14 )
    free(v14);
  if ( zip_sliding_window )
  {
    free(zip_sliding_window);
    zip_sliding_window = nullptr;
  }
  return file_size;
}

static char * zip_get_filename_from_path(const char *a1)
{
  char *result;
  char *v2;

  strcpy(zip_path_buffer, a1);
  result = strtok(zip_path_buffer, "/\\:");
  if ( result )
  {
    do
    {
      v2 = result;
      result = strtok(nullptr, "/\\:");
    }
    while ( result );
    return v2;
  }
  return result;
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
  FILE *v1;
  FILE *v2;
  int v4;
  int16_t v5;
  int16_t v6;
  int16_t v7;
  int16_t v8;
  int v9[13];

  *(uint32_t *)zip_filename = zip_get_filename_from_path(FileName);
  v1 = fopen(FileName, "rb");
  v2 = v1;
  if ( v1 )
  {
    if ( zip_get_file_size(v1, &zip_file_size) )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(uint32_t *)zip_filename);
    }
    else if ( zip_locate_central_dir(v2, &v4) )
    {
      zip_print("Error reading 'end of central directory' in zipfile %s\n", *(uint32_t *)zip_filename);
    }
    else
    {
      if ( v5 == v6 && v7 == v8 && v8 )
      {
        zip_load_local_file_headers(v2, (int)&v4, (ZipCentralDirectoryEntryInMem *)v9);
        fclose(v2);
        return 0;
      }
      zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(uint32_t *)zip_filename);
    }
    fclose(v2);
  }
  return 0;
}

static int zip_read_compressed_data_to_buffer(FILE *Stream, int a2, int a3, LPVOID *a4)
{
  size_t v4;
  void *v5;
  int v7;

  v4 = *(uint32_t *)(a3 + 20);
  v5 = malloc(v4);
  *a4 = v5;
  if ( !v5 )
  {
    zip_print("Couldn't allocate %ld bytes for input buffer for zipfile %s\n", v4, *(const char **)zip_filename);
    return -1;
  }
  v7 = fseek(Stream, *(uint16_t *)(a3 + 28) + *(uint16_t *)(a3 + 30) + *(uint32_t *)(a2 + 44) + 30, 0);
  if ( v7 )
  {
    zip_print("Error reading zipfile %s: fseek to compressed data failed\n", *(const char **)zip_filename);
LABEL_7:
    if ( *a4 )
    {
      free(*a4);
      *a4 = nullptr;
    }
    return v7;
  }
  if ( fread(*a4, 1u, v4, Stream) != v4 )
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes of compressed data\n", *(const char **)zip_filename, v4);
    v7 = -1;
    goto LABEL_7;
  }
  return v7;
}

static int zip_read_local_file_header(FILE *Stream, int a2, ZipLocalFileHeaderInMem *a3, uint8_t *Buffer)
{
  int v4;
  size_t v5;
  int v6;

  v4 = *(uint32_t *)(a2 + 44);
  v5 = zip_file_size - v4;
  if ( zip_file_size - v4 >= 0x2000 )
    v5 = 0x2000;
  v6 = fseek(Stream, v4, 0);
  if ( v6 )
  {
    zip_print("Error in zipfile %s: couldn't fseek to local file header\n", *(const char **)zip_filename);
    return v6;
  }
  else if ( fread(Buffer, 1u, v5, Stream) == v5 )
  {

    a3->signature = zip_read_uint32_le(Buffer);
    a3->version_needed = zip_read_uint16_le((int)(Buffer + 4));
    a3->general_purpose_bit_flag = zip_read_uint16_le((int)(Buffer + 6));
    a3->compression_method = zip_read_uint16_le((int)(Buffer + 8));
    a3->last_mod_time = zip_read_uint16_le((int)(Buffer + 10));
    a3->last_mod_date = zip_read_uint16_le((int)(Buffer + 12));
    a3->crc32 = zip_read_uint32_le(Buffer + 14);
    a3->compressed_size = zip_read_uint32_le(Buffer + 18);
    a3->uncompressed_size = zip_read_uint32_le(Buffer + 22);
    a3->filename_length = zip_read_uint16_le((int)(Buffer + 26));
    a3->extra_field_length = zip_read_uint16_le((int)(Buffer + 28));
    a3->filename = (char *)(Buffer + 30);
    return 0;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from local file header", *(const char **)zip_filename, v5);
    return -1;
  }
}

static int zip_load_central_directory(FILE *Stream, const char *arg4, int a3, ZipCentralDirectoryEntry *a2)
{
  int v4;
  size_t v5;
  int v7;
  char v8;
  uint16_t filename_length;
  uint16_t compression_method;
  int v11;
  ZipCentralDirectoryEntry *a1;
  char v13[256];

  v4 = 0;
  v5 = 0x2000;
  if ( *(uint32_t *)(a3 + 12) <= 0x2000u )
    v5 = *(uint32_t *)(a3 + 12);
  if ( fseek(Stream, *(uint32_t *)(a3 + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, v5, Stream) == v5 )
  {
    v11 = 0;
    a1 = &zip_central_dir_buffer;
    while ( v11 < *(uint16_t *)(a3 + 10) )
    {
      zip_parse_cd_entry(a1, (ZipCentralDirectoryEntryInMem *)a2);
      v7 = 0;
      if ( a2->filename_length )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(*(char *)(*(uint32_t *)((char *)&a2[1].signature + 2) + v7));
          filename_length = a2->filename_length;
          v13[v7++] = v8;
        }
        while ( v7 < filename_length );
      }
      v13[v7] = 0;
      if ( !zip_compare_filename_case_insensitive(v13, arg4) )
      {
        compression_method = a2->compression_method;
        v4 = 1;
        if ( compression_method && compression_method != 8 )
        {
          v4 = 0;
          zip_print(
            "Error in zipfile %s: compression method for file %s unsupported.\n",
            *(const char **)zip_filename,
            arg4);
          zip_print("Method: $%04x  must be $0000 (Stored) or $0008 (Deflated)\n", a2->compression_method);
        }
        if ( LOBYTE(a2->version_needed) > 0x14u )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: version for file %s too new.\n", *(const char **)zip_filename, arg4);
          zip_print("Version: $%02x must be $14 or less\n", LOBYTE(a2->version_needed));
        }
        if ( HIBYTE(a2->version_needed) )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: OS for file %s not supported.\n", *(const char **)zip_filename, arg4);
          zip_print("OS: $%02x must be $00\n", HIBYTE(a2->version_needed));
        }
        if ( a2->disk_number_start != *(uint16_t *)(a3 + 4) )
        {
          v4 = 0;
          zip_print("Error in zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
        }
      }
      a1 = (ZipCentralDirectoryEntry *)((char *)a1
                                      + a2->filename_length
                                      + a2->extra_field_length
                                      + a2->file_comment_length
                                      + 46);
      ++v11;
      if ( v4 )
        return 0;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, v5);
    return -1;
  }
}

static int zip_load_local_file_headers(FILE *Stream, int arg4, ZipCentralDirectoryEntryInMem *a2)
{
  size_t v3;
  int v5;
  ZipCentralDirectoryEntry *v6;
  int v7;
  char v8;
  uint16_t filename_length;
  int v10;
  char *v11;
  char *v12;
  char v13;
  ZipLocalFileHeaderInMem a3;
  uint8_t v15[256];

  v3 = *(uint32_t *)(arg4 + 12);
  if ( v3 > 0x2000 )
    v3 = 0x2000;
  if ( fseek(Stream, *(uint32_t *)(arg4 + 16), 0) )
  {
    zip_print("Error in zipfile %s: couldn't fseek to start of central directory\n", *(const char **)zip_filename);
    return -1;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, v3, Stream) == v3 )
  {
    v5 = 0;
    v6 = &zip_central_dir_buffer;
    while ( v5 < *(uint16_t *)(arg4 + 10) )
    {
      zip_parse_cd_entry(v6, a2);
      v7 = 0;
      if ( a2->filename_length )
      {
        do
        {
          if ( v7 >= 254 )
            break;
          v8 = toupper(a2->filename[v7]);
          filename_length = a2->filename_length;
          v15[v7++] = v8;
        }
        while ( v7 < filename_length );
      }
      v15[v7] = 0;
      if ( zip_read_local_file_header(Stream, (int)a2, &a3, zip_local_file_header_buffer) )
        zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
      if ( v5 < 256 )
      {
        v10 = zip_num_entries_loaded;
        v11 = v15;
        v12 = &zip_entry_names[(zip_num_entries_loaded << 8) - (uint32_t)v15];
        do
        {
          v13 = *v11;
          v11[(uint32_t)v12] = *v11;
          ++v11;
        }
        while ( v13 );
        Size[v10] = a3.uncompressed_size;
        zip_num_entries_loaded = v10 + 1;
      }
      v6 = (ZipCentralDirectoryEntry *)((char *)v6
                                      + a2->filename_length
                                      + a2->extra_field_length
                                      + a2->file_comment_length
                                      + 46);
      ++v5;
    }
    return -1;
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from central directory\n", *(const char **)zip_filename, v3);
    return -1;
  }
}

static int zip_compare_filename_case_insensitive(const char *a1, const char *a2)
{
  const char *v2;
  const char *i;
  bool v4;
  uint8_t v5;
  uint8_t v6;
  char *v8;
  char *v9;
  const char *v10;
  uint8_t v11;
  uint8_t v12;
  char String[256];

  v2 = a2;
  if ( strlen(a1) == strlen(a2) )
  {
    for ( i = a1; ; i += 2 )
    {
      v4 = *i < (unsigned int)*v2;
      if ( *i != *v2 )
        break;
      if ( !*i )
        return 0;
      v5 = i[1];
      v6 = v2[1];
      v4 = v5 < v6;
      if ( v5 != v6 )
        break;
      v2 += 2;
      if ( !v5 )
        return 0;
    }
  }
  else
  {
    if ( a1[strlen(a1) - 1] == 47 )
      return 1;
    strcpy(String, a1);
    v8 = strtok(String, "/");
    if ( !v8 )
      return 1;
    do
    {
      v9 = v8;
      v8 = strtok(nullptr, "/");
    }
    while ( v8 );
    v10 = v9;
    while ( 1 )
    {
      v4 = *v10 < (unsigned int)*v2;
      if ( *v10 != *v2 )
        break;
      if ( *v10 )
      {
        v11 = v10[1];
        v12 = v2[1];
        v4 = v11 < v12;
        if ( v11 != v12 )
          return -v4 - (v4 - 1);
        v10 += 2;
        v2 += 2;
        if ( v11 )
          continue;
      }
      return 0;
    }
  }
  return -v4 - (v4 - 1);
}

static int zip_parse_cd_entry(ZipCentralDirectoryEntry *a1, ZipCentralDirectoryEntryInMem *a2)
{
  int result;

  a2->signature = zip_read_uint32_le((uint8_t *)a1);
  a2->version_made_by = a1->version_made_by;
  a2->version_needed = a1->version_needed;
  a2->general_purpose_bit_flag = zip_read_uint16_le((int)&a1->general_purpose_bit_flag);
  a2->compression_method = zip_read_uint16_le((int)&a1->compression_method);
  a2->last_mod_time = zip_read_uint16_le((int)&a1->last_mod_time);
  a2->last_mod_date = zip_read_uint16_le((int)&a1->last_mod_date);
  a2->crc32 = zip_read_uint32_le((uint8_t *)&a1->crc32);
  a2->compressed_size = zip_read_uint32_le((uint8_t *)&a1->compressed_size);
  a2->uncompressed_size = zip_read_uint32_le((uint8_t *)&a1->uncompressed_size);
  a2->filename_length = zip_read_uint16_le((int)&a1->filename_length);
  a2->extra_field_length = zip_read_uint16_le((int)&a1->extra_field_length);
  a2->file_comment_length = zip_read_uint16_le((int)&a1->file_comment_length);
  a2->disk_number_start = zip_read_uint16_le((int)&a1->disk_number_start);
  a2->internal_attributes = zip_read_uint16_le((int)&a1->internal_attributes);
  a2->external_attributes = zip_read_uint32_le((uint8_t *)&a1->external_attributes);
  result = zip_read_uint32_le((uint8_t *)&a1->local_header_offset);
  a2->filename = (char *)&a1[1];
  a2->local_header_offset = result;
  return result;
}

static int zip_locate_central_dir(FILE *Stream, int *a2)
{
  size_t v2;
  FILE *v3;
  int v4;
  BOOL end_of_central_dir_signature;
  uint8_t *v7;
  uint32_t uint32_le;
  int *v9;

  v2 = zip_file_size;
  if ( (int)zip_file_size > 0x2000 )
    v2 = 0x2000;
  v3 = Stream;
  v4 = fseek(Stream, -v2, 2);
  if ( v4 )
  {
    zip_print("Error in zipfile %s: fseek failed\n", *(const char **)zip_filename);
    return v4;
  }
  else if ( fread(&zip_central_dir_buffer, 1u, v2, v3) == v2 )
  {
    end_of_central_dir_signature = zip_find_end_of_central_dir_signature((int)&zip_central_dir_buffer, v2, &Stream);
    if ( end_of_central_dir_signature )
    {
      zip_print("Error in zipfile %s: couldn't find 'end of central dir' signature\n", *(const char **)zip_filename);
      return end_of_central_dir_signature;
    }
    else
    {
      v7 = (uint8_t *)&zip_central_dir_buffer + (uint32_t)Stream;
      uint32_le = zip_read_uint32_le((uint8_t *)&zip_central_dir_buffer + (uint32_t)Stream);
      v9 = a2;
      *a2 = uint32_le;
      *((uint16_t *)v9 + 2) = zip_read_uint16_le((int)(v7 + 4));
      *((uint16_t *)v9 + 3) = zip_read_uint16_le((int)(v7 + 6));
      *((uint16_t *)v9 + 4) = zip_read_uint16_le((int)(v7 + 8));
      *((uint16_t *)v9 + 5) = zip_read_uint16_le((int)(v7 + 10));
      v9[3] = zip_read_uint32_le(v7 + 12);
      v9[4] = zip_read_uint32_le(v7 + 16);
      *((uint16_t *)v9 + 10) = zip_read_uint16_le((int)(v7 + 20));
      return 0;
    }
  }
  else
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes from end of file\n", *(const char **)zip_filename, v2);
    return -1;
  }
}

static BOOL zip_find_end_of_central_dir_signature(int a1, int a2, uint32_t *a3)
{
  int v3;
  int v4;

  v3 = a2 - 22;
  v4 = 0;
  if ( a2 - 22 >= 0 )
  {
    while ( strncmp((const char *)(v3 + a1), zip_signature, 4u) )
    {
      if ( --v3 < 0 )
        return 1;
    }
    v4 = 1;
    *a3 = v3;
  }
  return v4 == 0;
}

static int zip_get_file_size(FILE *Stream, uint32_t *a2)
{
  int v2;
  int result;

  v2 = fseek(Stream, 0, 2);
  if ( v2 )
    return v2;
  result = ftell(Stream);
  *a2 = result;
  if ( result != -1 )
    return v2;
  return result;
}

static int16_t zip_read_uint16_le(int a1)
{
  return *(uint16_t *)a1;
}

static uint32_t zip_read_uint32_le(uint8_t *a1)
{
  return *a1 | ((a1[1] | (*((uint16_t *)a1 + 1) << 8)) << 8);
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
