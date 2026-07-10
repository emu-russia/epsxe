#include "pch.h"
int sub_40FA70()
{
  int result; // eax

  if ( !dword_4FD8DC )
    return 0;
  result = dword_4F82F4[0];
  if ( dword_4F82F4[0] < dword_44F880 )
  {
    result = dword_44F880;
    dword_4F82F4[0] = dword_44F880;
  }
  if ( result > dword_44F884 )
  {
    dword_4F82F4[0] = dword_44F884;
    return dword_44F884;
  }
  return result;
}
