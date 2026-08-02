#include "pch.h"
void spucore_dma()
{
  unsigned int v0; // esi
  int v1; // ebx
  int v2; // edi
  int *v3; // eax
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ebx
  int v7; // edi
  int v8; // ebx
  unsigned __int16 fifo; // ax

  v0 = dword_516510;
  v1 = HIWORD(dword_516514);
  v2 = (unsigned __int16)dword_516514;
  if ( sound_enabled )
  {
    dword_4F75A0 = 0;
    if ( *(_DWORD *)dword_516518 == 0x1000200 )
    {
      v7 = HIWORD(dword_516514) * (unsigned __int16)dword_516514;
      if ( 2 * v7 )
      {
        v8 = 2 * v7;
        do
        {
          fifo = spucore_dma_read_fifo();
          mem_hw_reg_write_half(v0, fifo);
          v0 += 2;
          --v8;
        }
        while ( v8 );
      }
      if ( dynarec_enabled == 1 && v7 )
        dynarec_invalidate_range(dword_516510, v7);
    }
    else if ( *(_DWORD *)dword_516518 == 0x1000201 )
    {
      v3 = (int *)mem_dma_read(dword_516510);
      v4 = v1 * v2;
      v5 = dword_4F7554;
      v6 = 4 * v4 + dword_4F7554;
      if ( v6 >= 0x80000 )
      {
        for ( ; v4; dword_4F7554 = v5 )
        {
          *(int *)((char *)spu_ram + v5) = *v3;
          v5 = (v5 + 4) & 0x7FFFF;
          ++v3;
          --v4;
        }
      }
      else
      {
        qmemcpy((char *)spu_ram + dword_4F7554, v3, 4 * ((unsigned int)(4 * v4) >> 2));
        dword_4F7554 = v6;
      }
    }
    else if ( (*(_DWORD *)dword_516518 & 0x1000000) != 0 )
    {
      fatal_error_with_message_box(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(_DWORD *)dword_516518,
        dword_516510,
        HIWORD(dword_516514),
        (unsigned __int16)dword_516514);
    }
  }
}
