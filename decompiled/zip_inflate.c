#include "pch.h"
int zip_inflate()
{
  unsigned int v0; // esi
  int result; // eax
  int v2; // [esp+8h] [ebp-4h] BYREF

  dword_4F8324 = 0;
  dword_4F832C = 0;
  dword_4F8328 = 0;
  v0 = 0;
  while ( 1 )
  {
    dword_4F8340 = 0;
    result = sub_41F1F0(&v2);
    if ( result )
      break;
    if ( dword_4F8340 > v0 )
      v0 = dword_4F8340;
    if ( v2 )
    {
      sub_41FE70(dword_576984, dword_4F8324);
      return 0;
    }
  }
  return result;
}
