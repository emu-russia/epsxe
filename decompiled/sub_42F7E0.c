#include "pch.h"
int __cdecl sub_42F7E0(char *FileName)
{
  FILE *v1; // eax

  dword_50A1A0 = malloc(0x145320u);
  memset(dword_50A1A0, 0xFFu, 0x145320u);
  v1 = fopen(FileName, aWb);
  FileHandle = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * Error saving %s\n", FileName);
  byte_50A090 = 1;
  byte_50A091 = 1;
  fseek(v1, 1332002, 0);
  dword_5056E0 = 0;
  return dbg_print(aCreatingFakeFi);
}
