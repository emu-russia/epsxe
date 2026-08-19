#include "pch.h"
int cdrom_fake_create_file(char *FileName)
{
  FILE *fp;

  cdrom_fake_data = malloc(0x145320u);
  memset(cdrom_fake_data, 0xFFu, 0x145320u);
  fp = fopen(FileName, "wb");
  FileHandle = fp;
  if ( !fp )
    fatal_error_with_message_box(" * Error saving %s\n", FileName);
  fake_file_version = 1;
  fake_file_version2 = 1;
  fseek(fp, 1332002, 0);
  fake_file_sector_offset = 0;
  return dbg_print(" * Creating fake file ... \n");
}

int cdrom_fake_load_file(char *FileName)
{
  FILE *fp;

  cdrom_fake_data = malloc(0x145320u);
  fp = fopen(FileName, "rb");
  FileHandle = fp;
  if ( !fp )
    fatal_error_with_message_box(" * Error loading %s\n", FileName);
  fread(&fake_file_version, 1u, 2u, fp);
  fread(cdrom_fake_data, 1u, 0x145320u, FileHandle);
  return dbg_print(" * Loading fake file ... \n");
}

void * cdrom_fake_write_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer)
{
  int lba;
  void *offset;

  lba = cdr_msf_to_lba(minute, second, frame);
  if ( !minute && second == 2 && frame == 18 )
    printf("saved \n");
  offset = cdrom_fake_data;
  if ( *((uint32_t *)cdrom_fake_data + lba) == -1 )
  {
    fwrite(Buffer, 1u, 0x930u, FileHandle);
    *((uint32_t *)cdrom_fake_data + lba) = fake_file_sector_offset;
    offset = (void *)(fake_file_sector_offset + 2352);
    fake_file_sector_offset += 2352;
  }
  return offset;
}

size_t cdrom_fake_read_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer)
{
  int offset;

  offset = *((uint32_t *)cdrom_fake_data + cdr_msf_to_lba(minute, second, frame));
  if ( offset == -1 )
  {
    _close((int)FileHandle);
    fatal_error_with_message_box(" * fake sector doesn't found \n");
  }
  fseek(FileHandle, offset + 1332002, 0);
  return fread(Buffer, 1u, 0x930u, FileHandle);
}

FILE *cdrom_fake_write()
{
  FILE *fp;

  if ( cd_savefake_flag == 1 )
  {
    fp = FileHandle;
    if ( !FileHandle )
      return fp;
    fseek(FileHandle, 0, 0);
    fwrite(&fake_file_version, 1u, 2u, FileHandle);
    fwrite(cdrom_fake_data, 1u, 0x145320u, FileHandle);
  }
  fp = FileHandle;
  if ( FileHandle )
    return (FILE *)_close((int)FileHandle);
  return fp;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int FileHandle;
unsigned char fake_file_version;
unsigned char fake_file_version2;
unsigned int cdrom_fake_data;
unsigned int fake_file_sector_offset;
