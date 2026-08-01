#include "pch.h"
int __cdecl cdr_unfreeze_new(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, g_cdr_response_fifo, 4396);
  word_4FD87C = (unsigned __int8)g_cdr_idle_counter;
  if ( g_cdr_status_regs[70] )
    return cdrom_play_cdda_cb((unsigned __int8)g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  else
    return cdrom_stop_cb();
}
