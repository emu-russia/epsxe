#include "pch.h"
char sub_40D250()
{
  int *v0; // eax
  unsigned int v1; // esi
  int v2; // ebx
  int v3; // edi
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ebx
  int v7; // edi
  int v8; // ebx
  unsigned __int16 v9; // ax

  LOBYTE(v0) = sound_enabled;
  v1 = dword_516510;
  v2 = HIWORD(dword_516514);
  v3 = (unsigned __int16)dword_516514;
  if ( sound_enabled )
  {
    dword_4F75A0 = 0;
    if ( *(_DWORD *)dword_516518 == 16777728 )
    {
      v7 = HIWORD(dword_516514) * (unsigned __int16)dword_516514;
      LOBYTE(v0) = 2 * BYTE2(dword_516514) * dword_516514;
      if ( 2 * v7 )
      {
        v8 = 2 * v7;
        do
        {
          v9 = sub_40CDD0();
          LOBYTE(v0) = hw_reg_write_half(v1, v9);
          v1 += 2;
          --v8;
        }
        while ( v8 );
      }
      if ( dword_50C36C == 1 && v7 )
        LOBYTE(v0) = sub_4281B0(dword_516510, v7);
    }
    else
    {
      LOBYTE(v0) = dword_516518[0] - 1;
      if ( *(_DWORD *)dword_516518 == 16777729 )
      {
        v0 = (int *)dma_mem_read(dword_516510);
        v4 = v2 * v3;
        v5 = dword_4F7554;
        v6 = 4 * v4 + dword_4F7554;
        if ( v6 >= 0x80000 )
        {
          for ( ; v4; dword_4F7554 = v5 )
          {
            *(int *)((char *)&spu_ram + v5) = *v0;
            v5 = (v5 + 4) & 0x7FFFF;
            ++v0;
            --v4;
          }
        }
        else
        {
          qmemcpy((char *)&spu_ram + dword_4F7554, v0, 4 * ((unsigned int)(4 * v4) >> 2));
          dword_4F7554 = v6;
          LOBYTE(v0) = 4 * v4;
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
  return (char)v0;
}
