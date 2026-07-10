#include "pch.h"
int sub_42F200()
{
  int result; // eax

  result = dword_4FD99C;
  if ( dword_4FD99C )
  {
    dbg_print(aNetpluginOpen);
    NETopen(dword_4FD98C);
    result = dbg_print(aOk);
    byte_45696C = 0;
  }
  return result;
}
