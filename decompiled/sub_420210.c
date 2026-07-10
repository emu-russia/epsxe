#include "pch.h"
int sub_420210(char *Format, ...)
{
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF
  va_list va; // [esp+108h] [ebp+8h] BYREF

  va_start(va, Format);
  vsprintf(Buffer, Format, va);
  return printf(Buffer);
}
