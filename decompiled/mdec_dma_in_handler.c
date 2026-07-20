#include "pch.h"
void mdec_dma_in_handler()
{
  int v0; // esi
  int v1; // eax

  v0 = mdec_dma_src[0];
  if ( mdec_dma_control[0] == 0x1000201 )
  {
    if ( mdec_disable )
      LOBYTE(mdec_disable_flag[0]) = 1;
    v1 = *(_DWORD *)mdec_command;
    if ( *(_DWORD *)mdec_command == 0x40000001 )
    {
      mdec_set_scale_table((int)ram + (mdec_dma_src[0] & 0x1FFFFF));
      v1 = *(_DWORD *)mdec_command;
    }
    if ( (v1 & 0xF5FF0000) == 0x30000000 )
    {
      mdec_in_ptr = (int)ram + (v0 & 0x1FFFFF);
      mdec_out_addr = (int)ram + (v0 & 0x1FFFFF);
    }
  }
}
