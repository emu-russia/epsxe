#include "pch.h"
char __cdecl ext_CDRplay(int a1, char a2)
{
  char result; // al
  int (__stdcall *v3)(int *); // esi

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v3 = (int (__stdcall *)(int *))CDRplay;
    if ( CDRplay )
    {
      BYTE1(a1) = a2;
      BYTE2(a1) = sub_430750(a1, a2);
      return v3(&a1);
    }
  }
  return result;
}
