#include "pch.h"
_DWORD *__cdecl sub_438710(char *FileName, char *a2, int FileHandle)
{
  char *v4; // ebx
  _DWORD *v5; // eax
  _DWORD *v6; // ebp
  char *v7; // edx
  char v8; // al
  char v9; // al
  int v10; // esi
  void *v11; // eax
  void *v13; // eax
  FILE *v14; // eax
  int v15; // [esp+10h] [ebp-58h]
  int v16; // [esp+14h] [ebp-54h]
  char Mode[80]; // [esp+18h] [ebp-50h] BYREF
  _UNKNOWN *retaddr; // [esp+68h] [ebp+0h] BYREF
  char *v19; // [esp+70h] [ebp+8h]

  v16 = -1;
  v15 = 0;
  v4 = a2;
  v19 = Mode;
  if ( !FileName )
    return nullptr;
  if ( !a2 )
    return nullptr;
  v5 = malloc(0x64u);
  v6 = v5;
  if ( !v5 )
    return nullptr;
  v5[8] = 0;
  v5[9] = 0;
  v5[10] = 0;
  v5[17] = 0;
  *v5 = 0;
  v5[18] = 0;
  v5[3] = 0;
  v5[4] = 0;
  v5[1] = 0;
  v5[16] = 0;
  v5[14] = 0;
  v5[15] = 0;
  v5[19] = crc32_calc(0, nullptr, 0);
  v6[20] = 0;
  v6[22] = 0;
  v7 = (char *)malloc(strlen(FileName) + 1);
  v6[21] = v7;
  if ( !v7 )
    goto LABEL_25;
  strcpy(v7, FileName);
  *((_BYTE *)v6 + 92) = 0;
  do
  {
    if ( *v4 == 114 )
      *((_BYTE *)v6 + 92) = 114;
    if ( *v4 == 119 || *v4 == 97 )
      *((_BYTE *)v6 + 92) = 119;
    v8 = *v4;
    if ( *v4 < 48 || v8 > 57 )
    {
      if ( v8 == 102 )
      {
        v15 = 1;
      }
      else if ( v8 == 104 )
      {
        v15 = 2;
      }
      else
      {
        *v19++ = v8;
      }
    }
    else
    {
      v16 = v8 - 48;
    }
    ++v4;
  }
  while ( v8 && v19 != (char *)&retaddr );
  v9 = *((_BYTE *)v6 + 92);
  if ( !v9 )
  {
LABEL_25:
    sub_438BF0(v6);
    return nullptr;
  }
  if ( v9 == 119 )
  {
    v10 = sub_439D60(v6, v16, 8, -15, 8, v15, a113, 56);
    v11 = malloc(0x4000u);
    v6[18] = v11;
    v6[3] = v11;
    if ( v10 || !v11 )
      goto LABEL_25;
  }
  else
  {
    v13 = malloc(0x4000u);
    v6[17] = v13;
    *v6 = v13;
    if ( sub_439640(v6, -15, a113_0, 56) || !v6[17] )
      goto LABEL_25;
  }
  v6[4] = 0x4000;
  dword_4FFA10 = 0;
  if ( FileHandle >= 0 )
    v14 = _fdopen(FileHandle, Mode);
  else
    v14 = fopen(FileName, Mode);
  v6[16] = v14;
  if ( !v14 )
    goto LABEL_25;
  if ( *((_BYTE *)v6 + 92) == 119 )
  {
    fprintf(v14, "%c%c%c%c%c%c%c%c%c%c", dword_4574E0, dword_4574E4, 8, 0, 0, 0, 0, 0, 0, 11);
    v6[24] = 10;
  }
  else
  {
    sub_438A20(v6);
    v6[24] = ftell((FILE *)v6[16]) - v6[1];
  }
  return v6;
}
