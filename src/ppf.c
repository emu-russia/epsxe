#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned char ppf_enabled = 0x1;
static char *ppf_file_data;
unsigned char ppf_filename[0xc00];
static unsigned int ppf_sector_lists;

static int ppf_parse_and_build(int size, int data, unsigned int offset)
{
  unsigned int i;
  unsigned int pos;
  bool has_entries;
  int base;
  unsigned int sector;
  int head;
  unsigned int remaining;
  unsigned int len;
  int node;
  int tail;
  int j;
  uint32_t *new_node;
  uint8_t *node_ptr;
  int next_head;
  int next_tail;
  int k;
  uint32_t *next_node;
  unsigned int end;
  uint8_t entry_len;

  ppf_sector_lists = malloc(0x145320u);
  for ( i = 0; i < 0x145320; i += 4 )
    *(uint32_t *)((char *)ppf_sector_lists + i) = 0;
  pos = offset;
  has_entries = offset < size + offset;
  end = size + offset;
  if ( has_entries )
  {
    do
    {
      base = data;
      sector = *(uint32_t *)(pos + data) / 0x930u;
      head = *((uint32_t *)ppf_sector_lists + sector);
      remaining = 2352 - *(uint32_t *)(pos + data) % 0x930u;
      entry_len = *(uint8_t *)(pos + data + 4);
      if ( head )
      {
        tail = *((uint32_t *)ppf_sector_lists + sector);
        for ( j = *(uint32_t *)(head + 8); j; j = *(uint32_t *)(j + 8) )
          tail = j;
        new_node = malloc(8u);
        *(uint32_t *)(tail + 8) = new_node;
        new_node[1] = pos + 5;
        *(uint16_t *)(*(uint32_t *)(tail + 8) + 2) = *(uint32_t *)(pos + data) % 0x930u;
        node_ptr = *(uint8_t **)(tail + 8);
        len = entry_len;
        if ( entry_len > remaining )
          *node_ptr = remaining;
        else
          *node_ptr = entry_len;
        node = *(uint32_t *)(tail + 8);
        base = data;
      }
      else
      {
        *((uint32_t *)ppf_sector_lists + sector) = malloc(8u);
        *(uint32_t *)(*((uint32_t *)ppf_sector_lists + sector) + 4) = pos + 5;
        len = entry_len;
        *(uint16_t *)(*((uint32_t *)ppf_sector_lists + sector) + 2) = *(uint32_t *)(pos + data) % 0x930u;
        if ( entry_len > remaining )
          **((uint8_t **)ppf_sector_lists + sector) = remaining;
        else
          **((uint8_t **)ppf_sector_lists + sector) = *(uint8_t *)(pos + data + 4);
        node = *((uint32_t *)ppf_sector_lists + sector);
      }
      *(uint32_t *)(node + 8) = 0;
      if ( len > remaining )
      {
        next_head = *((uint32_t *)ppf_sector_lists + sector + 1);
        if ( next_head )
        {
          next_tail = *((uint32_t *)ppf_sector_lists + sector + 1);
          for ( k = *(uint32_t *)(next_head + 8); k; k = *(uint32_t *)(k + 8) )
            next_tail = k;
          next_node = malloc(8u);
          *(uint32_t *)(next_tail + 8) = next_node;
          next_node[1] = remaining + pos + 5;
          *(uint16_t *)(*(uint32_t *)(next_tail + 8) + 2) = 0;
          **(uint8_t **)(next_tail + 8) = entry_len - remaining;
          *(uint32_t *)(*(uint32_t *)(next_tail + 8) + 8) = 0;
        }
        else
        {
          *((uint32_t *)ppf_sector_lists + sector + 1) = malloc(8u);
          *(uint32_t *)(*((uint32_t *)ppf_sector_lists + sector + 1) + 4) = remaining + pos + 5;
          *(uint16_t *)(*((uint32_t *)ppf_sector_lists + sector + 1) + 2) = 0;
          **((uint8_t **)ppf_sector_lists + sector + 1) = entry_len - remaining;
          *(uint32_t *)(*((uint32_t *)ppf_sector_lists + sector + 1) + 8) = 0;
        }
      }
      pos += *(uint8_t *)(pos + base + 4) + 5;
    }
    while ( pos < end );
  }
  return dbg_print("done.\n");
}

char ppf_load_patch()
{
  FILE *fp;
  FILE *fp2;
  size_t size;

  LOBYTE(fp) = ppf_enabled;
  if ( ppf_enabled )
  {
    if ( !strcmp(ppf_filename, "NULL") )
      sprintf(ppf_filename, "%s%s", "patches\\", default_filename);
    fp = fopen(ppf_filename, "rb");
    fp2 = fp;
    if ( fp )
    {
      dbg_print(" * Patching game ... ");
      ppf_enabled = 1;
      fseek(fp2, 0, 2);
      size = ftell(fp2);
      fseek(fp2, 0, 0);
      ppf_file_data = (char *)malloc(size);
      fread(ppf_file_data, size, 1u, fp2);
      if ( !strncmp("PPF", ppf_file_data, 3u) )
      {
        if ( ppf_file_data[5] )
        {
          if ( ppf_file_data[5] == 1 )
          {
            dbg_print("ppf file v.2.0 ");
            if ( !strncmp(".DIZ", &ppf_file_data[size - 8], 4u) )
              ppf_parse_and_build(size - *(uint32_t *)&ppf_file_data[size - 4] - 1122, (int)ppf_file_data, 0x43Cu);
            else
              ppf_parse_and_build(size - 1084, (int)ppf_file_data, 0x43Cu);
            LOBYTE(fp) = fclose(fp2);
          }
          else
          {
            ppf_enabled = 0;
            free(ppf_file_data);
            fclose(fp2);
            LOBYTE(fp) = dbg_print("unk ppf format.\n");
          }
        }
        else
        {
          dbg_print("ppf file v.1.0 ");
          ppf_parse_and_build(size - 56, (int)ppf_file_data, 0x38u);
          LOBYTE(fp) = fclose(fp2);
        }
      }
      else
      {
        ppf_enabled = 0;
        free(ppf_file_data);
        fclose(fp2);
        LOBYTE(fp) = dbg_print("no ppf file.\n");
      }
    }
    else
    {
      ppf_enabled = 0;
    }
  }
  return (char)fp;
}

void ppf_free()
{
  if ( ppf_enabled )
  {
    free(ppf_file_data);
    free(ppf_sector_lists);
  }
}

void ppf_apply_patch_to_sector(int sector, int buffer)
{
  uint8_t *entry;
  uint8_t *i;

  if ( ppf_enabled == 1 )
  {
    entry = *((uint8_t **)ppf_sector_lists + sector);
    if ( entry )
    {
      qmemcpy((void *)(buffer + *((uint16_t *)entry + 1)), &ppf_file_data[*((uint32_t *)entry + 1)], *entry);
      for ( i = *((uint8_t **)entry + 2); i; i = *((uint8_t **)i + 2) )
        qmemcpy((void *)(buffer + *((uint16_t *)i + 1)), &ppf_file_data[*((uint32_t *)i + 1)], *i);
    }
  }
}
