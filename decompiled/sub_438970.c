#include "pch.h"
_DWORD *__cdecl sub_438970(int FileHandle, char *a2)
{
  char Buffer[20]; // [esp+4h] [ebp-14h] BYREF

  if ( FileHandle < 0 )
    return nullptr;
  sprintf(Buffer, "<fd:%d>", FileHandle);
  return sub_438710(Buffer, a2, FileHandle);
}
