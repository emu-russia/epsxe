#include "pch.h"
int __cdecl sub_436960(const char *a1, int *a2, int *a3)
{
  int v3; // ebp
  char *v4; // edi
  int result; // eax

  v3 = 0;
  while ( 1 )
  {
    v4 = (char *)&byte_4FE9E8[v3];
    if ( !byte_4FE9E8[v3] )
    {
LABEL_8:
      *a2 = 0;
      return (int)a2;
    }
    v3 += byte_4FE9E8[v3];
    if ( (unsigned __int8)v4[33] >= 2u && (!strncmp(a1, v4 + 33, 0xCu) || v4[44] == 59 && !strncmp(a1, v4 + 33, 0xBu)) )
      break;
    if ( v3 >= 4096 )
      goto LABEL_8;
  }
  *a2 = sub_436800((unsigned __int8 *)v4 + 2);
  result = sub_436800((unsigned __int8 *)v4 + 10);
  *a3 = result;
  return result;
}
