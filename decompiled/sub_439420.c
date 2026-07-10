#include "pch.h"
int __cdecl sub_439420(LPVOID lpMem)
{
  if ( !lpMem )
    return -2;
  if ( *((_BYTE *)lpMem + 92) == 119 && !sub_439110(lpMem, 4) )
  {
    sub_439470(*((FILE **)lpMem + 16), *((_DWORD *)lpMem + 19));
    sub_439470(*((FILE **)lpMem + 16), *((_DWORD *)lpMem + 2));
  }
  return sub_438BF0(lpMem);
}
