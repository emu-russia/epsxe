#include "pch.h"
int __cdecl cdrom_create_fake_file(char *FileName)
{
  FILE *v1; // eax

  cdrom_fake_data = malloc(0x145320u);
  memset(cdrom_fake_data, 0xFFu, 0x145320u);
  v1 = fopen(FileName, "wb");
  FileHandle = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * Error saving %s\n", FileName);
  byte_50A090 = 1;
  byte_50A091 = 1;
  fseek(v1, 1332002, 0);
  dword_5056E0 = 0;
  return dbg_print(" * Creating fake file ... \n");
}
