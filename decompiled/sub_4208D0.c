#include "pch.h"
int __cdecl sub_4208D0(const char *a1, const char *a2)
{
  const char *v2; // esi
  const char *i; // eax
  bool v4; // cf
  unsigned __int8 v5; // dl
  unsigned __int8 v6; // bl
  char *v8; // eax
  char *v9; // edi
  const char *v10; // eax
  unsigned __int8 v11; // dl
  unsigned __int8 v12; // bl
  char String[256]; // [esp+Ch] [ebp-100h] BYREF

  v2 = a2;
  if ( strlen(a1) == strlen(a2) )
  {
    for ( i = a1; ; i += 2 )
    {
      v4 = *i < (unsigned int)*v2;
      if ( *i != *v2 )
        break;
      if ( !*i )
        return 0;
      v5 = i[1];
      v6 = v2[1];
      v4 = v5 < v6;
      if ( v5 != v6 )
        break;
      v2 += 2;
      if ( !v5 )
        return 0;
    }
  }
  else
  {
    if ( a1[strlen(a1) - 1] == 47 )
      return 1;
    strcpy(String, a1);
    v8 = strtok(String, "/");
    if ( !v8 )
      return 1;
    do
    {
      v9 = v8;
      v8 = strtok(nullptr, "/");
    }
    while ( v8 );
    v10 = v9;
    while ( 1 )
    {
      v4 = *v10 < (unsigned int)*v2;
      if ( *v10 != *v2 )
        break;
      if ( *v10 )
      {
        v11 = v10[1];
        v12 = v2[1];
        v4 = v11 < v12;
        if ( v11 != v12 )
          return -v4 - (v4 - 1);
        v10 += 2;
        v2 += 2;
        if ( v11 )
          continue;
      }
      return 0;
    }
  }
  return -v4 - (v4 - 1);
}
