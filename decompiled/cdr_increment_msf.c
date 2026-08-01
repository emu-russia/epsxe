#include "pch.h"
char cdr_increment_msf()
{
  char result; // al
  bool v1; // zf

  result = ++BYTE2(g_cdr_cur_msf_pos);
  if ( BYTE2(g_cdr_cur_msf_pos) == 75 )
  {
    result = BYTE1(g_cdr_cur_msf_pos) + 1;
    v1 = BYTE1(g_cdr_cur_msf_pos)++ == 59;
    *(_WORD *)((char *)&g_cdr_cur_msf_pos + 1) = BYTE1(g_cdr_cur_msf_pos);
    if ( v1 )
    {
      result = g_cdr_cur_msf_pos + 1;
      LOBYTE(g_cdr_cur_msf_pos) = g_cdr_cur_msf_pos + 1;
      LOWORD(g_cdr_cur_msf_pos) = (unsigned __int8)g_cdr_cur_msf_pos;
    }
  }
  return result;
}
