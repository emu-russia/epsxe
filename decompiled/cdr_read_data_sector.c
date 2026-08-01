#include "pch.h"
char cdr_read_data_sector()
{
  __int16 v0; // bx
  int v1; // eax

  v0 = g_cdr_cur_msf_pos;
  v1 = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  if ( g_cdr_last_lba_read != v1 )
  {
    cdrom_read_data_cb((unsigned __int8)v0, HIBYTE(v0), BYTE2(g_cdr_cur_msf_pos), g_cdr_data_buffer);
    g_cdr_last_lba_read = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
    LOBYTE(v1) = g_cdr_status_regs[72];
    g_cdr_data_bytes_transferred = (g_cdr_status_regs[72] & 0x20) != 0 ? 12 : 24;
    if ( (g_cdr_xa_buffer[2] & 0xF) == 4 )
    {
      LOBYTE(v1) = g_cdr_status_regs[72] & 0x48;
      if ( (g_cdr_status_regs[72] & 0x48) == 0x40
        || (_BYTE)v1 == 72
        && g_cdr_xa_buffer[0] == (_BYTE)g_cdr_cur_track
        && (LOBYTE(v1) = g_cdr_xa_buffer[1], g_cdr_xa_buffer[1] == HIBYTE(g_cdr_cur_track)) )
      {
        LOBYTE(v1) = spu_play_adpcm_cb(g_cdr_xa_buffer);
      }
    }
  }
  return v1;
}
