#include "pch.h"
BOOL __cdecl zip_check_signature_PK(int a1, int a2, _DWORD *a3)
{
  int v3; // esi
  int v4; // ebx

  v3 = a2 - 22;
  v4 = 0;
  if ( a2 - 22 >= 0 )
  {
    while ( strncmp((const char *)(v3 + a1), zip_signature, 4u) )
    {
      if ( --v3 < 0 )
        return 1;
    }
    v4 = 1;
    *a3 = v3;
  }
  return v4 == 0;
}
