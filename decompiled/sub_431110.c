#include "pch.h"
_DWORD *__cdecl sub_431110(_DWORD *a1, unsigned __int8 *a2)
{
  *a1 = a2[3] + ((a2[2] + ((a2[1] + (*a2 << 8)) << 8)) << 8);
  return a1;
}
