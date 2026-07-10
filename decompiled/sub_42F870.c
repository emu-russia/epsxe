#include "pch.h"
int __cdecl sub_42F870(char *FileName)
{
  FILE *v1; // eax

  dword_50A1A0 = malloc(0x145320u);
  v1 = fopen(FileName, "rb");
  FileHandle = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * Error loading %s\n", FileName);
  fread(&byte_50A090, 1u, 2u, v1);
  fread(dword_50A1A0, 1u, 0x145320u, FileHandle);
  return dbg_print(" * Loading fake file ... \n");
}
