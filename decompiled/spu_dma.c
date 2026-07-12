#include "pch.h"
void spu_dma()
{
  unsigned int v0; // ebp
  int v1; // edi
  int v2; // esi
  int v3; // eax
  int v4; // esi
  unsigned __int16 *j; // ebx
  int v6; // esi
  unsigned __int16 *k; // ebx
  int v8; // esi
  int v9; // edi
  unsigned __int16 v10; // ax
  int i; // esi
  unsigned __int16 v12; // ax

  v0 = dword_516510;
  v1 = HIWORD(dword_516514);
  v2 = (unsigned __int16)dword_516514;
  v3 = dma_mem_read(dword_516510);
  if ( sound_enabled )
  {
    if ( *(_DWORD *)dword_516518 == 16777728 )
    {
      v8 = v1 * v2;
      if ( spu_use_external_plugin == 1 )
      {
        if ( SPUreadDMAMem )
        {
          SPUreadDMAMem(v3, 2 * v8);
        }
        else if ( 2 * v8 )
        {
          v9 = 2 * v8;
          do
          {
            v10 = SPUreadDMA();
            hw_reg_write_half(v0, v10);
            v0 += 2;
            --v9;
          }
          while ( v9 );
        }
        if ( dword_50C36C == 1 && v8 )
          sub_4281B0(dword_516510, v8);
      }
      else
      {
        for ( i = 2 * v8; i; dword_8A8080 += 2 )
        {
          v12 = SPUgetOne(dword_8A8080);
          hw_reg_write_half(v0, v12);
          v0 += 2;
          --i;
        }
      }
    }
    else if ( *(_DWORD *)dword_516518 == 16777729 )
    {
      if ( spu_use_external_plugin == 1 )
      {
        if ( SPUwriteDMAMem )
        {
          SPUwriteDMAMem(v3, 2 * v1 * v2);
        }
        else
        {
          v4 = 2 * v1 * v2;
          for ( j = (unsigned __int16 *)dma_mem_read(v0); v4; --v4 )
            SPUwriteDMA(*j++);
        }
      }
      else
      {
        v6 = 2 * v1 * v2;
        for ( k = (unsigned __int16 *)dma_mem_read(v0); v6; dword_8A8080 += 2 )
        {
          SPUputOne(dword_8A8080, *k++);
          --v6;
        }
      }
    }
    else if ( (*(_DWORD *)dword_516518 & 0x1000000) != 0 )
    {
      ui_error(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(_DWORD *)dword_516518,
        v0,
        v1,
        v2);
    }
  }
}
