#include "pch.h"
void sub_437060(char *Format, ...)
{
  char *v1; // esi
  DWORD NumberOfCharsWritten; // [esp+4h] [ebp-4h] BYREF
  va_list va; // [esp+10h] [ebp+8h] BYREF

  va_start(va, Format);
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, va);
  fprintf(&stru_458A00, "%s", v1);
  if ( console_allocated )
    WriteConsoleA(hConsoleOutput, v1, strlen(v1), &NumberOfCharsWritten, nullptr);
  free(v1);
}
