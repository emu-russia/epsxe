#include "pch.h"
FILE *loader_load_cheats()
{
  FILE *v0; // eax
  FILE *v1; // edi
  int v2; // esi
  FILE *result; // eax
  FILE *v4; // esi
  int v5; // eax

  v0 = fopen("cheats\\database.dat", "rb");
  v1 = v0;
  if ( v0 )
  {
    if ( (v0->_flag & 0x10) == 0 )
    {
      v2 = dword_44F9A8;
      do
      {
        if ( v2 >= 200 )
          break;
        fread((void *)(24 * v2 + 4520368), 1u, 0x18u, v1);
        v2 = dword_44F9A8;
        if ( !sub_41BC30(dword_44F9C0[6 * dword_44F9A8], dword_44F9C4[6 * dword_44F9A8]) )
          dword_44F9A8 = ++v2;
      }
      while ( (v1->_flag & 0x10) == 0 );
    }
    fclose(v1);
  }
  result = fopen("cheats\\dataconf.dat", "rb");
  v4 = result;
  if ( result )
  {
    if ( (result->_flag & 0x10) == 0 )
    {
      v5 = dword_450C70;
      do
      {
        if ( v5 >= 200 )
          break;
        fread(&aSces02105[81 * v5], 1u, 0x51u, v4);
        v5 = ++dword_450C70;
      }
      while ( (v4->_flag & 0x10) == 0 );
    }
    return (FILE *)fclose(v4);
  }
  return result;
}
