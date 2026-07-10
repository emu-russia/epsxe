#include "pch.h"
HANDLE sub_407FF0()
{
  char v0; // al
  int v1; // edx
  CHAR *v2; // edi
  HANDLE FirstFileA; // edi
  int v4; // edx
  char v5; // al
  CHAR *v6; // edi
  HANDLE v7; // edi
  int v8; // edx
  char v9; // al
  CHAR *v10; // edi
  HANDLE result; // eax
  void *v12; // edi
  char v13[12]; // [esp+10h] [ebp-94Ch] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+1Ch] [ebp-940h] BYREF
  CHAR FileName[1024]; // [esp+15Ch] [ebp-800h] BYREF
  CHAR NewFileName[1024]; // [esp+55Ch] [ebp-400h] BYREF

  strcpy(v13, "plugins\\");
  FileName[0] = byte_45B8CC;
  v0 = MEMORY[0x44E64C];
  v1 = MEMORY[0x44E648];
  v2 = &FileName[strlen(FileName)];
  *(_DWORD *)v2 = aGpuDll;
  *((_DWORD *)v2 + 1) = v1;
  v2[8] = v0;
  FirstFileA = FindFirstFileA(FileName, &FindFileData);
  if ( FirstFileA != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v13, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(FirstFileA, &FindFileData) );
  }
  v4 = MEMORY[0x44E63C];
  FileName[0] = byte_45B8CC;
  v5 = MEMORY[0x44E640];
  v6 = &FileName[strlen(FileName)];
  *(_DWORD *)v6 = aSpuDll;
  *((_DWORD *)v6 + 1) = v4;
  v6[8] = v5;
  v7 = FindFirstFileA(FileName, &FindFileData);
  if ( v7 != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v13, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(v7, &FindFileData) );
  }
  v8 = MEMORY[0x44E630];
  FileName[0] = byte_45B8CC;
  v9 = MEMORY[0x44E634];
  v10 = &FileName[strlen(FileName)];
  *(_DWORD *)v10 = aCdrDll;
  *((_DWORD *)v10 + 1) = v8;
  v10[8] = v9;
  result = FindFirstFileA(FileName, &FindFileData);
  v12 = result;
  if ( result != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v13, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
      result = (HANDLE)FindNextFileA(v12, &FindFileData);
    }
    while ( result );
  }
  return result;
}
