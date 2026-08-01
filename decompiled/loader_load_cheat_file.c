#include "pch.h"
FILE *__cdecl loader_load_cheat_file(char *FileName)
{
  FILE *result; // eax
  FILE *v2; // esi
  int v3; // edx
  int v4; // eax
  int v5; // [esp+4h] [ebp-408h] BYREF
  int v6; // [esp+8h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+Ch] [ebp-400h] BYREF

  LOBYTE(byte_4F831C) = 0;
  result = fopen(FileName, "r");
  v2 = result;
  if ( result )
  {
    if ( (result->_flag & 0x10) == 0 )
    {
      do
      {
        sprintf(Buffer, asc_44E24C);
        fgets(Buffer, 1024, v2);
        if ( Buffer[0] != '#' && sscanf(Buffer, "%x %x", &v6, &v5) == 2 )
        {
          v3 = v5;
          v4 = 2 * (unsigned __int8)byte_4F831C;
          dword_5B6DC4[v4] = v6;
          dword_5B6DC0[v4] = v3;
          LOBYTE(byte_4F831C) = byte_4F831C + 1;
        }
      }
      while ( (v2->_flag & 0x10) == 0 );
    }
    return (FILE *)fclose(v2);
  }
  return result;
}
