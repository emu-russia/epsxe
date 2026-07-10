#include "pch.h"
int sub_40FA30()
{
  int result; // eax

  if ( !dword_4FD8DC )
    return 0;
  sub_40E2E0();
  result = dword_4F82F0;
  if ( dword_4F82F0 < dword_44F878 )
  {
    result = dword_44F878;
    dword_4F82F0 = dword_44F878;
  }
  if ( result > dword_44F87C )
  {
    dword_4F82F0 = dword_44F87C;
    return dword_44F87C;
  }
  return result;
}
