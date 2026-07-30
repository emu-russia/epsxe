#include "pch.h"
char __cdecl gpu_pack_pixels(_BYTE *a1, char a2)
{
  char result; // al

  result = a2;
  if ( a2 )
  {
    if ( a2 == 1 )
    {
      *a1 = -1;
      a1[1] = -1;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
    else if ( a2 == 2 )
    {
      *a1 = 0;
      a1[1] = 0;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
  }
  else
  {
    *a1 = 0;
    a1[1] = 0;
    a1[2] = 0;
    return (_BYTE)a1 + 1;
  }
  return result;
}
