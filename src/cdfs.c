#include "pch.h"
static int cdfs_read_le32(uint8_t *data)
{
  return *data | ((data[1] | ((data[2] | ((char)data[3] << 8)) << 8)) << 8);
}

static unsigned int cdfs_read_data(int lba, int offset, unsigned int size, void *buffer)
{
  uint8_t frame;
  uint8_t minute;
  uint8_t second;
  uint8_t sector[4704];

  frame = (lba + 150) % 0x4Bu;
  minute = (lba + 150) / 0x4Bu / 0x3C;
  second = (lba + 150) / 0x4Bu % 0x3C;
  if ( loaded_file_type == 3 )
  {
    iso_read_data(minute, second, frame, (int)sector);
  }
  else if ( loaded_file_type == 1 )
  {
    cdrom_read_data_cb(minute, second, frame, sector);
  }
  qmemcpy(buffer, &sector[offset], size);
  return size;
}

static char *cdfs_read_root_directory()
{
  int lba;

  cdfs_read_data(16, 24, 0x800u, root_directory_buffer);
  lba = cdfs_read_le32((uint8_t *)&root_directory_buffer[158]);
  cdfs_read_data(lba, 24, 0x800u, root_directory_buffer);
  cdfs_read_data(lba + 1, 24, 0x800u, root_directory_buffer_2);
  return root_directory_buffer;
}

static int * cdfs_find_file(const char *name, int *sector_out, int **size_out)
{
  int pos;
  char *entry;
  int *size;

  pos = 0;
  while ( 1 )
  {
    entry = &root_directory_buffer[pos];
    if ( !root_directory_buffer[pos] )
    {
      *sector_out = 0;
      return sector_out;
    }
    pos += (uint8_t)root_directory_buffer[pos];
    if ( (uint8_t)entry[33] >= 2u && (!strncmp(name, entry + 33, 0xCu) || entry[44] == 59 && !strncmp(name, entry + 33, 0xBu)) )
      break;
    if ( pos >= 4096 )
    {
      *sector_out = 0;
      return sector_out;
    }
  }
  *sector_out = cdfs_read_le32((uint8_t *)entry + 2);
  size = (int *)cdfs_read_le32((uint8_t *)entry + 10);
  *size_out = size;
  return size;
}

static uint8_t cdfs_parse_system_cnf_for_exec(int sector, int size, char *out, int *sector_out, int **size_out)
{
  int pos;
  uint8_t ch;
  int name_part;
  int name_tail;
  uint32_t name[3];

  pos = 0;
  ch = cdfs_read_data(sector, 24, 0x800u, system_cnf_buffer);
  if ( size > 8 )
  {
    do
    {
      ch = system_cnf_buffer[pos];
      if ( ch == 'S' )
        break;
      if ( ch == 's' )
        break;
      if ( system_cnf_buffer_8[pos] == '.' )
        break;
      ch = ++pos + 8;
    }
    while ( pos + 8 < size );
  }
  if ( pos + 8 == size )
  {
    *sector_out = 0;
  }
  else
  {
    name_part = *(uint32_t *)&system_cnf_buffer[pos + 4];
    name[0] = *(uint32_t *)&system_cnf_buffer[pos];
    name_tail = *(uint32_t *)&system_cnf_buffer[pos + 8];
    name[1] = name_part;
    LOBYTE(name_part) = system_cnf_buffer[pos + 12];
    name[2] = name_tail;
    sprintf(out, "%s", (const char *)name);
    return (uint8_t)cdfs_find_file((const char *)name, sector_out, size_out);
  }
  return ch;
}

uint8_t cdfs_load_executable(char *Buffer)
{
  int sector;
  int size;

  cdfs_read_root_directory();
  cdfs_find_file("SYSTEM.CNF;1", &sector, (int **)&size);
  if ( sector )
    return cdfs_parse_system_cnf_for_exec(sector, size, Buffer, &size, (int **)&Buffer);
  else
    return sprintf(Buffer, "SLUS_999.99");
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char system_cnf_buffer[1];
unsigned char system_cnf_buffer_8[0xff8];
unsigned char root_directory_buffer[0x800];
unsigned char root_directory_buffer_2[0x800];
