#include "pch.h"
int __cdecl sub_40E750(int a1, int a2, int a3, int a4)
{
  int result; // eax

  if ( a1 )
  {
    result = dword_4FD8CC[a4];
    if ( result == 1 )
    {
      return sub_40E5E0(dword_4F82F4[dword_4FD8AC[a4]], a2);
    }
    else if ( result == 2 )
    {
      return sub_40E670((_DWORD *)dword_4F82F4[dword_4FD8AC[a4]], a2);
    }
  }
  else
  {
    result = dword_4FD8BC[a4];
    if ( result == 1 )
    {
      return sub_40E5E0(dword_4F8304[dword_4FD8AC[a4]], a2);
    }
    else if ( result == 2 )
    {
      return sub_40E670((_DWORD *)dword_4F8304[dword_4FD8AC[a4]], a2);
    }
  }
  return result;
}
