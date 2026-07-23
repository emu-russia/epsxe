#include "pch.h"
int __cdecl cdrom_fake_create_file(char *FileName)
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

int __cdecl cdrom_fake_load_file(char *FileName)
{
  FILE *v1; // eax

  cdrom_fake_data = malloc(0x145320u);
  v1 = fopen(FileName, "rb");
  FileHandle = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * Error loading %s\n", FileName);
  fread(&byte_50A090, 1u, 2u, v1);
  fread(cdrom_fake_data, 1u, 0x145320u, FileHandle);
  return dbg_print(" * Loading fake file ... \n");
}

void *__cdecl cdrom_fake_write_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer)
{
  int v4; // esi
  void *result; // eax

  v4 = sub_42C6D0(a1, a2, a3);
  if ( !a1 && a2 == 2 && a3 == 18 )
    printf("saved \n");
  result = cdrom_fake_data;
  if ( *((_DWORD *)cdrom_fake_data + v4) == -1 )
  {
    fwrite(Buffer, 1u, 0x930u, FileHandle);
    *((_DWORD *)cdrom_fake_data + v4) = dword_5056E0;
    result = (void *)(dword_5056E0 + 2352);
    dword_5056E0 += 2352;
  }
  return result;
}

size_t __cdecl cdrom_fake_read_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer)
{
  int v4; // eax

  v4 = *((_DWORD *)cdrom_fake_data + sub_42C6D0(a1, a2, a3));
  if ( v4 == -1 )
  {
    _close((int)FileHandle);
    fatal_error_with_message_box(" * fake sector doesn't found \n");
  }
  fseek(FileHandle, v4 + 1332002, 0);
  return fread(Buffer, 1u, 0x930u, FileHandle);
}

FILE *cdrom_fake_write()
{
  FILE *result; // eax

  if ( cd_savefake_flag == 1 )
  {
    result = FileHandle;
    if ( !FileHandle )
      return result;
    fseek(FileHandle, 0, 0);
    fwrite(&byte_50A090, 1u, 2u, FileHandle);
    fwrite(cdrom_fake_data, 1u, 0x145320u, FileHandle);
  }
  result = FileHandle;
  if ( FileHandle )
    return (FILE *)_close((int)FileHandle);
  return result;
}

