#include "pch.h"
void dbg_print_no_flush(char *Format, ...)
{
  char *v1; // esi
  DWORD NumberOfCharsWritten; // [esp+4h] [ebp-4h] BYREF
  va_list ArgList; // [esp+10h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, ArgList);
  fprintf(&stru_458A00, "%s", v1);
  if ( console_allocated )
    WriteConsoleA(hConsoleOutput, v1, strlen(v1), &NumberOfCharsWritten, nullptr);
  free(v1);
}
