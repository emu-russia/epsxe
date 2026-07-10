#include "pch.h"
int __cdecl sub_41FE40(int a1)
{
  int v1; // eax
  int v2; // esi

  v1 = a1;
  if ( a1 )
  {
    do
    {
      v2 = *(_DWORD *)(v1 - 4);
      free((LPVOID)(v1 - 8));
      v1 = v2;
    }
    while ( v2 );
  }
  return 0;
}
