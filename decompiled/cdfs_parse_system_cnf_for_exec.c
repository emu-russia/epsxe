#include "pch.h"
unsigned __int8 __cdecl cdfs_parse_system_cnf_for_exec(int a1, int a2, char *Buffer, int *a4, int **a5)
{
  int v5; // esi
  unsigned __int8 result; // al
  int v7; // edx
  int v8; // ecx
  _DWORD v9[3]; // [esp+4h] [ebp-100h] BYREF
  char v10; // [esp+10h] [ebp-F4h]
  char v11; // [esp+11h] [ebp-F3h]

  v5 = 0;
  result = cdfs_read_data(a1, 24, 0x800u, byte_4FD9E8);
  if ( a2 > 8 )
  {
    do
    {
      result = byte_4FD9E8[v5];
      if ( result == 'S' )
        break;
      if ( result == 's' )
        break;
      if ( byte_4FD9F0[v5] == '.' )
        break;
      result = ++v5 + 8;
    }
    while ( v5 + 8 < a2 );
  }
  if ( v5 + 8 == a2 )
  {
    *a4 = 0;
  }
  else
  {
    v7 = *(_DWORD *)&byte_4FD9E8[v5 + 4];
    v9[0] = *(_DWORD *)&byte_4FD9E8[v5];
    v8 = *(_DWORD *)&byte_4FD9E8[v5 + 8];
    v9[1] = v7;
    LOBYTE(v7) = byte_4FD9E8[v5 + 12];
    v9[2] = v8;
    v10 = v7;
    v11 = 0;
    sprintf(Buffer, "%s", (const char *)v9);
    return (unsigned __int8)cdfs_find_file((const char *)v9, a4, a5);
  }
  return result;
}
