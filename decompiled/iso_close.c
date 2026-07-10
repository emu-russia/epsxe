#include "pch.h"
int iso_close()
{
  if ( dword_50A098 )
    _close((int)dword_50A098);
  if ( dword_505400 )
    _close((int)dword_505400);
  return dbg_print(" * Closing ISO system. \n");
}
