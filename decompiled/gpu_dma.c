#include "pch.h"
char gpu_dma()
{
  int v0; // ebp
  int v1; // edi
  int v2; // esi
  _DWORD *v3; // ebx
  char result; // al
  unsigned int v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int i; // esi
  unsigned int v11; // eax
  unsigned int v12; // [esp+10h] [ebp-4h]

  v0 = dword_5164F8;
  v1 = HIWORD(dword_5164FC);
  v2 = (unsigned __int16)dword_5164FC;
  v3 = (_DWORD *)dma_mem_read(dword_5164F8);
  v12 = 0;
  if ( *(_DWORD *)dword_516500 == 0x1000200 )
  {
    if ( GPUreadDataMem )
    {
      v9 = v1 * v2;
      GPUreadDataMem(v3, v9);
      if ( dword_50C36C == 1 && v9 )
        sub_4281B0(v0, v9);
    }
    else
    {
      if ( dword_50C36C == 1 && v1 * v2 )
        sub_4281B0(v0, v1 * v2);
      for ( i = v1 * v2; i; --i )
      {
        v11 = GPUreadData();
        gpu_dma_write(v0, v11);
        v0 += 4;
      }
    }
    goto LABEL_27;
  }
  if ( *(_DWORD *)dword_516500 == 0x1000201 )
  {
    v8 = v1 * v2;
    if ( GPUwriteDataMem )
    {
      GPUwriteDataMem(v3, v8);
    }
    else
    {
      for ( ; v8; --v8 )
        GPUwriteData(*v3++);
    }
LABEL_27:
    result = dma_assert_int(2u);
    byte_50C216 = 0;
    return result;
  }
  result = dword_516500[0] - 1;
  if ( *(_DWORD *)dword_516500 == 16778241 )
  {
    GPUdmaChain(ram, v0 & 0x1FFFFF);
    while ( 1 )
    {
      v5 = gpu_dma_read(v0);
      v6 = HIBYTE(v5) + v12;
      v7 = v5 & 0xFFFFFF;
      v12 = v6;
      v0 = v7;
      if ( !v7 || v7 == 0xFFFFFF )
        break;
      if ( v6 >= 0x40 )
        goto LABEL_10;
    }
    if ( v6 >= 0x40 )
    {
LABEL_10:
      byte_50C214 = 1;
      byte_50C216 = 1;
      return 1;
    }
    *(_DWORD *)dword_516500 &= ~0x1000000u;
    result = dma_assert_int(2u);
    byte_50C216 = -2;
  }
  else if ( (*(_DWORD *)dword_516500 & 0x1000000) != 0 )
  {
    ui_error(
      "DMA[2] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
      *(_DWORD *)dword_516500,
      v0,
      v1,
      v2);
  }
  return result;
}
