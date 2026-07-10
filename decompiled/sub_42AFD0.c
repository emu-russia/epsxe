#include "pch.h"
int sub_42AFD0()
{
  int result; // eax

  result = dword_50C270;
  if ( dword_50C270 < 0 )
  {
    result = 0;
    dword_50C270 = 0;
LABEL_3:
    dword_4FD874 = dword_455940 + result - 535;
    dword_4FD878 = 0;
    return result;
  }
  if ( (unsigned int)dword_50C270 <= 0x217 )
    goto LABEL_3;
  dword_4FD870 = dword_50C270 - 535;
  dword_4FD878 = 128;
  return dword_50C270 - 535;
}
