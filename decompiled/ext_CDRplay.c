#include "pch.h"
char __cdecl ext_CDRplay(int a1, char a2)
{
  char result; // al
  char (__stdcall *v3)(int *); // esi

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v3 = (char (__stdcall *)(int *))CDRplay;
    if ( CDRplay )
    {
      BYTE1(a1) = a2;
      BYTE2(a1) = ext_CDR_bcd_to_binary(a1, a2);
      return v3(&a1);
    }
  }
  return result;
}
