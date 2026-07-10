#include "pch.h"
HANDLE sub_407FF0()
{
  HANDLE FirstFileA; // edi
  HANDLE v1; // edi
  HANDLE result; // eax
  HANDLE v3; // edi
  char v4[12]; // [esp+10h] [ebp-94Ch] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+1Ch] [ebp-940h] BYREF
  CHAR FileName[1024]; // [esp+15Ch] [ebp-800h] BYREF
  CHAR NewFileName[1024]; // [esp+55Ch] [ebp-400h] BYREF

  strcpy(v4, "plugins\\");
  FileName[0] = byte_45B8CC;
  strcat(FileName, "gpu*.dll");
  FirstFileA = FindFirstFileA(FileName, &FindFileData);
  if ( FirstFileA != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(FirstFileA, &FindFileData) );
  }
  FileName[0] = byte_45B8CC;
  strcat(FileName, "spu*.dll");
  v1 = FindFirstFileA(FileName, &FindFileData);
  if ( v1 != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(v1, &FindFileData) );
  }
  FileName[0] = byte_45B8CC;
  strcat(FileName, "cdr*.dll");
  result = FindFirstFileA(FileName, &FindFileData);
  v3 = result;
  if ( result != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
      result = (HANDLE)FindNextFileA(v3, &FindFileData);
    }
    while ( result );
  }
  return result;
}
