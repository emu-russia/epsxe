#include "pch.h"
int __cdecl loader_pll_parse_section(int a1, unsigned int *a2, unsigned int a3, const char *a4, int a5)
{
  unsigned int v5; // eax
  int v6; // eax
  int v7; // edx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // edx
  unsigned int v12; // edx
  unsigned int v13; // edx

  if ( strncmp((const char *)(a1 + *a2), "DATA", 4u) )
  {
    do
    {
      if ( !strncmp((const char *)(a1 + *a2), "LOAD", 4u) )
        break;
      if ( *a2 >= a3 )
        return 0;
      v5 = *a2 + 1;
      *a2 = v5;
    }
    while ( strncmp((const char *)(a1 + v5), "DATA", 4u) );
  }
  if ( *a2 >= a3 )
    return 0;
  v6 = strncmp((const char *)(a1 + *a2), "DATA", 4u);
  v7 = *a2;
  if ( !v6 )
  {
    *a2 = v7 + 5;
    if ( *(_BYTE *)(v7 + 5 + a1) == 32 )
    {
      do
      {
        v8 = *a2 + 1;
        *a2 = v8;
      }
      while ( *(_BYTE *)(v8 + a1) == 32 );
    }
    sscanf((const char *const)(a1 + *a2), "%s ", a4);
    v9 = strlen(a4) + *a2;
    *a2 = v9;
    if ( *(_BYTE *)(v9 + a1) == 32 )
    {
      do
      {
        v10 = *a2 + 1;
        *a2 = v10;
      }
      while ( *(_BYTE *)(v10 + a1) == 32 );
    }
    sscanf((const char *const)(a1 + *a2), "%x", a5);
    return 1;
  }
  if ( strncmp((const char *)(a1 + v7), "LOAD", 4u) )
    return 0;
  v12 = *a2 + 5;
  *a2 = v12;
  if ( *(_BYTE *)(v12 + a1) == 32 )
  {
    do
    {
      v13 = *a2 + 1;
      *a2 = v13;
    }
    while ( *(_BYTE *)(v13 + a1) == 32 );
  }
  sscanf((const char *const)(a1 + *a2), "%s\n", a4);
  *a2 += strlen(a4);
  return 2;
}
