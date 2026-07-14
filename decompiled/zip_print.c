#include "pch.h"
int zip_print(char *Format, ...)
{
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF
  va_list ArgList; // [esp+108h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  vsprintf(Buffer, Format, ArgList);
  return printf(Buffer);
}
