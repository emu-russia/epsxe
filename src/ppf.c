#include "pch.h"
static int ppf_parse_and_build(int a1, int a2, unsigned int a3)
{
  unsigned int i;
  unsigned int v4;
  bool v5;
  int v6;
  unsigned int v7;
  int v8;
  unsigned int v9;
  unsigned int v10;
  int v11;
  int v12;
  int j;
  uint32_t *v14;
  uint8_t *v15;
  int v16;
  int v17;
  int k;
  uint32_t *v19;
  unsigned int v21;
  uint8_t v22;

  ppf_sector_lists = malloc(0x145320u);
  for ( i = 0; i < 0x145320; i += 4 )
    *(uint32_t *)((char *)ppf_sector_lists + i) = 0;
  v4 = a3;
  v5 = a3 < a1 + a3;
  v21 = a1 + a3;
  if ( v5 )
  {
    do
    {
      v6 = a2;
      v7 = *(uint32_t *)(v4 + a2) / 0x930u;
      v8 = *((uint32_t *)ppf_sector_lists + v7);
      v9 = 2352 - *(uint32_t *)(v4 + a2) % 0x930u;
      v22 = *(uint8_t *)(v4 + a2 + 4);
      if ( v8 )
      {
        v12 = *((uint32_t *)ppf_sector_lists + v7);
        for ( j = *(uint32_t *)(v8 + 8); j; j = *(uint32_t *)(j + 8) )
          v12 = j;
        v14 = malloc(8u);
        *(uint32_t *)(v12 + 8) = v14;
        v14[1] = v4 + 5;
        *(uint16_t *)(*(uint32_t *)(v12 + 8) + 2) = *(uint32_t *)(v4 + a2) % 0x930u;
        v15 = *(uint8_t **)(v12 + 8);
        v10 = v22;
        if ( v22 > v9 )
          *v15 = v9;
        else
          *v15 = v22;
        v11 = *(uint32_t *)(v12 + 8);
        v6 = a2;
      }
      else
      {
        *((uint32_t *)ppf_sector_lists + v7) = malloc(8u);
        *(uint32_t *)(*((uint32_t *)ppf_sector_lists + v7) + 4) = v4 + 5;
        v10 = v22;
        *(uint16_t *)(*((uint32_t *)ppf_sector_lists + v7) + 2) = *(uint32_t *)(v4 + a2) % 0x930u;
        if ( v22 > v9 )
          **((uint8_t **)ppf_sector_lists + v7) = v9;
        else
          **((uint8_t **)ppf_sector_lists + v7) = *(uint8_t *)(v4 + a2 + 4);
        v11 = *((uint32_t *)ppf_sector_lists + v7);
      }
      *(uint32_t *)(v11 + 8) = 0;
      if ( v10 > v9 )
      {
        v16 = *((uint32_t *)ppf_sector_lists + v7 + 1);
        if ( v16 )
        {
          v17 = *((uint32_t *)ppf_sector_lists + v7 + 1);
          for ( k = *(uint32_t *)(v16 + 8); k; k = *(uint32_t *)(k + 8) )
            v17 = k;
          v19 = malloc(8u);
          *(uint32_t *)(v17 + 8) = v19;
          v19[1] = v9 + v4 + 5;
          *(uint16_t *)(*(uint32_t *)(v17 + 8) + 2) = 0;
          **(uint8_t **)(v17 + 8) = v22 - v9;
          *(uint32_t *)(*(uint32_t *)(v17 + 8) + 8) = 0;
        }
        else
        {
          *((uint32_t *)ppf_sector_lists + v7 + 1) = malloc(8u);
          *(uint32_t *)(*((uint32_t *)ppf_sector_lists + v7 + 1) + 4) = v9 + v4 + 5;
          *(uint16_t *)(*((uint32_t *)ppf_sector_lists + v7 + 1) + 2) = 0;
          **((uint8_t **)ppf_sector_lists + v7 + 1) = v22 - v9;
          *(uint32_t *)(*((uint32_t *)ppf_sector_lists + v7 + 1) + 8) = 0;
        }
      }
      v4 += *(uint8_t *)(v4 + v6 + 4) + 5;
    }
    while ( v4 < v21 );
  }
  return dbg_print("done.\n");
}

char ppf_load_patch()
{
  FILE *v0;
  FILE *v1;
  size_t v2;

  LOBYTE(v0) = ppf_enabled;
  if ( ppf_enabled )
  {
    if ( !strcmp(ppf_filename, "NULL") )
      sprintf(ppf_filename, "%s%s", "patches\\", default_filename);
    v0 = fopen(ppf_filename, "rb");
    v1 = v0;
    if ( v0 )
    {
      dbg_print(" * Patching game ... ");
      ppf_enabled = 1;
      fseek(v1, 0, 2);
      v2 = ftell(v1);
      fseek(v1, 0, 0);
      ppf_file_data = (char *)malloc(v2);
      fread(ppf_file_data, v2, 1u, v1);
      if ( !strncmp("PPF", ppf_file_data, 3u) )
      {
        if ( ppf_file_data[5] )
        {
          if ( ppf_file_data[5] == 1 )
          {
            dbg_print("ppf file v.2.0 ");
            if ( !strncmp(".DIZ", &ppf_file_data[v2 - 8], 4u) )
              ppf_parse_and_build(v2 - *(uint32_t *)&ppf_file_data[v2 - 4] - 1122, (int)ppf_file_data, 0x43Cu);
            else
              ppf_parse_and_build(v2 - 1084, (int)ppf_file_data, 0x43Cu);
            LOBYTE(v0) = fclose(v1);
          }
          else
          {
            ppf_enabled = 0;
            free(ppf_file_data);
            fclose(v1);
            LOBYTE(v0) = dbg_print("unk ppf format.\n");
          }
        }
        else
        {
          dbg_print("ppf file v.1.0 ");
          ppf_parse_and_build(v2 - 56, (int)ppf_file_data, 0x38u);
          LOBYTE(v0) = fclose(v1);
        }
      }
      else
      {
        ppf_enabled = 0;
        free(ppf_file_data);
        fclose(v1);
        LOBYTE(v0) = dbg_print("no ppf file.\n");
      }
    }
    else
    {
      ppf_enabled = 0;
    }
  }
  return (char)v0;
}

void ppf_free()
{
  if ( ppf_enabled )
  {
    free(ppf_file_data);
    free(ppf_sector_lists);
  }
}

void ppf_apply_patch_to_sector(int a1, int a2)
{
  uint8_t *v2;
  uint8_t *i;

  if ( ppf_enabled == 1 )
  {
    v2 = *((uint8_t **)ppf_sector_lists + a1);
    if ( v2 )
    {
      qmemcpy((void *)(a2 + *((uint16_t *)v2 + 1)), &ppf_file_data[*((uint32_t *)v2 + 1)], *v2);
      for ( i = *((uint8_t **)v2 + 2); i; i = *((uint8_t **)i + 2) )
        qmemcpy((void *)(a2 + *((uint16_t *)i + 1)), &ppf_file_data[*((uint32_t *)i + 1)], *i);
    }
  }
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char ppf_enabled = 0x1;
char *ppf_file_data;
unsigned char ppf_filename[0xc00];
unsigned int ppf_sector_lists;
