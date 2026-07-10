#include "pch.h"
char *__cdecl sub_4394A0(int a1, _DWORD *a2)
{
  int v3; // eax
  const char *v4; // ebp
  char *v5; // eax
  const char *v6; // edi

  if ( a1 )
  {
    v3 = *(_DWORD *)(a1 + 56);
    *a2 = v3;
    if ( v3 )
    {
      v4 = (const char *)&unk_4FF9FC;
      if ( v3 != -1 )
        v4 = *(const char **)(a1 + 24);
      if ( !v4 || !*v4 )
        v4 = (const char *)*(&off_4575A8 - *(_DWORD *)(a1 + 56));
      if ( *(_DWORD *)(a1 + 80) )
        free(*(LPVOID *)(a1 + 80));
      v5 = (char *)malloc(strlen(v4) + strlen(*(const char **)(a1 + 84)) + 3);
      v6 = *(const char **)(a1 + 84);
      *(_DWORD *)(a1 + 80) = v5;
      strcpy(v5, v6);
      strcat(*(char **)(a1 + 80), ": ");
      strcat(*(char **)(a1 + 80), v4);
      return *(char **)(a1 + 80);
    }
    else
    {
      return (char *)&unk_4FF9F8;
    }
  }
  else
  {
    *a2 = -2;
    return off_4575B0[0];
  }
}
