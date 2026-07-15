#include "pch.h"
unsigned int __cdecl zip_inflate_block(int *a1)
{
  int v1; // ecx
  unsigned int v2; // eax
  unsigned __int8 *v3; // esi
  int v4; // edx
  int *v5; // esi
  int v6; // edx
  unsigned int v7; // eax
  unsigned int v8; // ecx
  int v9; // edx
  int v10; // edx
  unsigned int result; // eax
  unsigned __int8 *v12; // eax
  int v13; // ebp
  int v14; // ecx
  unsigned int v15; // esi
  unsigned int m; // ebx
  int v17; // edx
  unsigned int v18; // esi
  int v19; // edi
  unsigned int n; // ebx
  int v21; // edx
  unsigned int v22; // ebx
  unsigned int v23; // esi
  char v24; // cl
  int v25; // esi
  unsigned __int8 *v26; // eax
  unsigned int v27; // ebx
  unsigned int i; // esi
  int v29; // edx
  unsigned int v30; // edx
  unsigned int v31; // esi
  unsigned int v32; // ebx
  int v33; // edi
  unsigned int v34; // edi
  unsigned int v35; // esi
  unsigned int v36; // ebx
  int v37; // ebp
  unsigned int v38; // ebp
  unsigned int v39; // ebx
  unsigned int v40; // esi
  unsigned int v41; // edi
  char v42; // cl
  int v43; // edx
  int v44; // ecx
  int v45; // ecx
  int v46; // eax
  unsigned int v47; // ecx
  int v48; // edi
  unsigned int v49; // ebp
  unsigned __int16 v50; // dx
  unsigned int v51; // edi
  unsigned __int8 *v52; // edx
  int v53; // eax
  int v54; // ecx
  int v55; // ecx
  int v56; // eax
  unsigned int v57; // ecx
  int v58; // eax
  int v59; // ecx
  int v60; // eax
  int v61; // esi
  unsigned int v62; // esi
  int v63; // [esp+0h] [ebp-524h] BYREF
  unsigned int v64; // [esp+4h] [ebp-520h] BYREF
  int v65; // [esp+8h] [ebp-51Ch]
  unsigned int v66; // [esp+Ch] [ebp-518h]
  int v67; // [esp+10h] [ebp-514h] BYREF
  unsigned int v68; // [esp+14h] [ebp-510h] BYREF
  unsigned int j; // [esp+18h] [ebp-50Ch]
  unsigned int k; // [esp+1Ch] [ebp-508h]
  int v71; // [esp+20h] [ebp-504h]
  _DWORD v72[32]; // [esp+24h] [ebp-500h] BYREF
  _DWORD v73[144]; // [esp+A4h] [ebp-480h] BYREF
  _DWORD v74[112]; // [esp+2E4h] [ebp-240h] BYREF
  _DWORD v75[24]; // [esp+4A4h] [ebp-80h] BYREF
  _DWORD v76[8]; // [esp+504h] [ebp-20h] BYREF

  v1 = zip_inflate_bit_count;
  v2 = zip_inflate_bit_buffer;
  if ( !zip_inflate_bit_count )
  {
    v3 = (unsigned __int8 *)zipfile_input_buffer;
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
      v9 = *(unsigned __int8 *)v5 << v8;
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
    v26 = (unsigned __int8 *)zipfile_input_buffer;
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
        v52 = (unsigned __int8 *)zipfile_input_buffer;
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
          v54 = *(unsigned __int8 *)(v67 + 1);
          v39 >>= v54;
          v40 -= v54;
          v55 = *(unsigned __int16 *)(v67 + 4);
          if ( (unsigned __int16)v55 >= 0x10u )
          {
            if ( (unsigned __int16)v55 == 16 )
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
    v12 = (unsigned __int8 *)zipfile_input_buffer;
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
    v19 = (unsigned __int16)m;
    for ( n = HIWORD(m); v18 < 0x10; zipfile_input_buffer = (int)v12 )
    {
      v21 = *v12 << v18;
      v18 += 8;
      n |= v21;
      ++v12;
    }
    if ( v19 == (unsigned __int16)~(_WORD)n )
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
          *((_BYTE *)zip_sliding_window + v13++) = v22;
          if ( v13 == 0x8000 )
          {
            zip_copy_sliding_window_to_output(zip_sliding_window, 0x8000u);
            v13 = 0;
          }
          v22 >>= 8;
          v23 -= 8;
          if ( !--v19 )
            break;
          v12 = (unsigned __int8 *)zipfile_input_buffer;
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
