#include "pch.h"
static int cdfs_read_le32(uint8_t *a1)
{
  return *a1 | ((a1[1] | ((a1[2] | ((char)a1[3] << 8)) << 8)) << 8);
}

static unsigned int cdfs_read_data(int a1, int a2, unsigned int a3, void *a4)
{
  uint8_t v5;
  uint8_t v6;
  uint8_t v7;
  uint8_t v8[4704];

  v7 = (a1 + 150) % 0x4Bu;
  v6 = (a1 + 150) / 0x4Bu / 0x3C;
  v5 = (a1 + 150) / 0x4Bu % 0x3C;
  if ( loaded_file_type == 3 )
  {
    iso_read_data(v6, v5, v7, (int)v8);
  }
  else if ( loaded_file_type == 1 )
  {
    cdrom_read_data_cb(v6, v5, v7, v8);
  }
  qmemcpy(a4, &v8[a2], a3);
  return a3;
}

static char *cdfs_read_root_directory()
{
  int le32;

  cdfs_read_data(16, 24, 0x800u, root_directory_buffer);
  le32 = cdfs_read_le32((uint8_t *)&root_directory_buffer[158]);
  cdfs_read_data(le32, 24, 0x800u, root_directory_buffer);
  cdfs_read_data(le32 + 1, 24, 0x800u, root_directory_buffer_2);
  return root_directory_buffer;
}

static int * cdfs_find_file(const char *a1, int *a2, int **a3)
{
  int v3;
  char *v4;
  int *result;

  v3 = 0;
  while ( 1 )
  {
    v4 = &root_directory_buffer[v3];
    if ( !root_directory_buffer[v3] )
    {
LABEL_8:
      *a2 = 0;
      return a2;
    }
    v3 += (uint8_t)root_directory_buffer[v3];
    if ( (uint8_t)v4[33] >= 2u && (!strncmp(a1, v4 + 33, 0xCu) || v4[44] == 59 && !strncmp(a1, v4 + 33, 0xBu)) )
      break;
    if ( v3 >= 4096 )
      goto LABEL_8;
  }
  *a2 = cdfs_read_le32((uint8_t *)v4 + 2);
  result = (int *)cdfs_read_le32((uint8_t *)v4 + 10);
  *a3 = result;
  return result;
}

static uint8_t cdfs_parse_system_cnf_for_exec(int a1, int a2, char *Buffer, int *a4, int **a5)
{
  int v5;
  uint8_t result;
  int v7;
  int v8;
  uint32_t v9[3];
  char v10;
  char v11;

  v5 = 0;
  result = cdfs_read_data(a1, 24, 0x800u, system_cnf_buffer);
  if ( a2 > 8 )
  {
    do
    {
      result = system_cnf_buffer[v5];
      if ( result == 'S' )
        break;
      if ( result == 's' )
        break;
      if ( system_cnf_buffer_8[v5] == '.' )
        break;
      result = ++v5 + 8;
    }
    while ( v5 + 8 < a2 );
  }
  if ( v5 + 8 == a2 )
  {
    *a4 = 0;
  }
  else
  {
    v7 = *(uint32_t *)&system_cnf_buffer[v5 + 4];
    v9[0] = *(uint32_t *)&system_cnf_buffer[v5];
    v8 = *(uint32_t *)&system_cnf_buffer[v5 + 8];
    v9[1] = v7;
    LOBYTE(v7) = system_cnf_buffer[v5 + 12];
    v9[2] = v8;
    v10 = v7;
    v11 = 0;
    sprintf(Buffer, "%s", (const char *)v9);
    return (uint8_t)cdfs_find_file((const char *)v9, a4, a5);
  }
  return result;
}

uint8_t cdfs_load_executable(char *Buffer)
{
  int v2;
  int v3;

  cdfs_read_root_directory();
  cdfs_find_file("SYSTEM.CNF;1", &v2, (int **)&v3);
  if ( v2 )
    return cdfs_parse_system_cnf_for_exec(v2, v3, Buffer, &v3, (int **)&Buffer);
  else
    return sprintf(Buffer, "SLUS_999.99");
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char system_cnf_buffer[1];
unsigned char system_cnf_buffer_8[0xff8];
unsigned char root_directory_buffer[0x800];
unsigned char root_directory_buffer_2[0x800];
