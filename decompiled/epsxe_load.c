#include "pch.h"
void __cdecl epsxe_load(char *a1, size_t Size)
{
  char v2; // al
  int v3; // eax
  size_t v4; // eax
  char *v5; // ebp
  char *v6; // eax
  size_t v7; // eax
  char *Str2; // [esp+0h] [ebp-118h] BYREF
  LPVOID lpMem; // [esp+4h] [ebp-114h] BYREF
  int v10; // [esp+8h] [ebp-110h] BYREF
  int v11; // [esp+Ch] [ebp-10Ch] BYREF
  unsigned int v12; // [esp+10h] [ebp-108h] BYREF
  int v13; // [esp+14h] [ebp-104h] BYREF
  char ArgList[256]; // [esp+18h] [ebp-100h] BYREF

  lpMem = malloc(Size);
  v12 = 0;
  if ( sub_41FEB0(FileName, a1, &lpMem, (size_t *)&v11) )
    fatal_error_with_message_box(" * EPSX: error loading .pll file.");
  v2 = sub_41C220((int)lpMem, &v12, v11, ArgList, (int)&v10);
  if ( v2 )
  {
    while ( 1 )
    {
      v3 = v2 - 1;
      if ( !v3 )
        break;
      if ( v3 == 1 )
      {
        v4 = sub_41C390(ArgList);
        Str2 = (char *)malloc(v4);
        if ( sub_41FEB0(FileName, ArgList, (LPVOID *)&Str2, (size_t *)&v13) )
          fatal_error_with_message_box(" * EPSX: error loading .exe file in pll/zip.");
        v5 = Str2;
        if ( strncmp("PS-X EXE", Str2, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", ArgList);
        v6 = Str2;
        qmemcpy((char *)ram + (*((_DWORD *)v5 + 6) & 0x1FFFFF), Str2 + 2048, *((_DWORD *)v5 + 7));
        dword_50C350 = *((_DWORD *)v5 + 5);
        dword_50C354 = -2145386752;
        dword_50C358 = -2145386752;
        dword_50C35C = 0;
        *(_DWORD *)reg_pc = *((_DWORD *)v5 + 4);
LABEL_14:
        free(v6);
      }
      v2 = sub_41C220((int)lpMem, &v12, v11, ArgList, (int)&v10);
      if ( !v2 )
        goto LABEL_16;
    }
    v7 = sub_41C390(ArgList);
    Str2 = (char *)malloc(v7);
    if ( sub_41FEB0(FileName, ArgList, (LPVOID *)&Str2, (size_t *)&v13) )
      fatal_error_with_message_box(" * EPSX: error loading %s.", ArgList);
    v6 = Str2;
    qmemcpy((char *)ram + (v10 & 0x1FFFFF), Str2, v13);
    goto LABEL_14;
  }
LABEL_16:
  free(lpMem);
}
