#include "pch.h"
int __stdcall diEnumEffectsCallback(_DWORD *a1, _DWORD *a2)
{
  if ( a2 )
  {
    *a2 = a1[1];
    a2[1] = a1[2];
    a2[2] = a1[3];
    a2[3] = a1[4];
  }
  return 0;
}
