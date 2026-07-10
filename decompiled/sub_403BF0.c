#include "pch.h"
int __cdecl sub_403BF0(_DWORD *a1, int a2, int a3)
{
  if ( sub_403C30(a2) == 2 )
    return -(sub_403C60(a1, a2, a2 + 8, a3) != 0);
  else
    return -1;
}
