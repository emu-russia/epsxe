#include "pch.h"
int mdec_decode()
{
  int result; // eax
  char *v1; // ebx
  __m64 *v2; // esi
  int v3; // ebp
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  bool v7; // cc
  int v8; // [esp+0h] [ebp-4h]

  result = HIWORD(mdec_image_size) * (unsigned __int16)mdec_image_size;
  if ( mdec_dma_status == 0x1000200 )
  {
    v1 = (char *)mdec_in_ptr;
    if ( mdec_in_ptr )
    {
      if ( mdec_disable )
      {
        LOBYTE(mdec_disable_flag[0]) = 1;
        return result;
      }
      v2 = (__m64 *)((char *)ram + (mdec_dma_dest & 0x1FFFFF));
      v3 = *(_DWORD *)mdec_command & 0x8000000;
      v4 = 3 * result;
      if ( (*(_DWORD *)mdec_command & 0x8000000) == 0 )
        v4 = 2 * result;
      v5 = v4 / 384;
      if ( v4 / 384 < 31 )
        goto LABEL_15;
      v6 = v5 / 30;
      v7 = v5 / 30 <= 0;
      v5 %= 30;
      if ( !v7 )
      {
        v8 = v6;
        do
        {
          mdec_in_ptr = (int)mdec_rl_decode(v1, 30);
          mdec_idct_blocks(30);
          if ( v3 )
          {
            mdec_yuv_to_rgb((char *)mdec_idct_buffer, v2, (_WORD *)0x1E);
            v2 += 1920;
          }
          else
          {
            mdec_y_to_mono((unsigned int *)mdec_idct_buffer, v2, 30);
            v2 += 2880;
          }
          v1 = (char *)mdec_in_ptr;
          --v8;
        }
        while ( v8 );
      }
      if ( v5 )
      {
LABEL_15:
        mdec_in_ptr = (int)mdec_rl_decode(v1, v5);
        mdec_idct_blocks(v5);
        if ( v3 )
          mdec_yuv_to_rgb((char *)mdec_idct_buffer, v2, (_WORD *)v5);
        else
          mdec_y_to_mono((unsigned int *)mdec_idct_buffer, v2, v5);
      }
    }
    result = mdectiming;
    if ( mdectiming )
    {
      mdec_status = 0x44000000;
      mdec_timer_count = -65536;
      mdec_timer = 1;
    }
  }
  return result;
}
