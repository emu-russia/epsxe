#include "pch.h"
int (*ext_cdrom_deinit())(void)
{
  int (*result)(void); // eax

  if ( byte_456D70 >= 0 )
    sub_42FA10();
  if ( dword_50C37C == 3 )
    iso_close();
  ext_CDRstop();
  if ( CDRclose )
    CDRclose();
  result = CDRshutdown;
  if ( CDRshutdown )
    return (int (*)(void))CDRshutdown();
  return result;
}
