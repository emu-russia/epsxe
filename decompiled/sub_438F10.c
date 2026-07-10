#include "pch.h"
char *__cdecl sub_438F10(int a1, char *a2, int a3)
{
  char *v3; // esi
  int i; // edi
  char v5; // al

  v3 = a2;
  if ( !a2 || a3 <= 0 )
    return nullptr;
  for ( i = a3 - 1; i > 0; --i )
  {
    if ( sub_438CA0(a1, v3, 1) != 1 )
      break;
    v5 = *v3++;
    if ( v5 == 10 )
      break;
  }
  *v3 = 0;
  if ( a2 == v3 && i > 0 )
    return nullptr;
  else
    return a2;
}
