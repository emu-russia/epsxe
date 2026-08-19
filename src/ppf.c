#include "pch.h"
static int __cdecl ppf_parse_and_build(int a1, int a2, unsigned int a3)
{
  unsigned int i; // eax
  unsigned int v4; // edi
  bool v5; // cf
  int v6; // ebp
  unsigned int v7; // esi
  int v8; // eax
  unsigned int v9; // ebx
  unsigned int v10; // eax
  int v11; // edx
  int v12; // ebp
  int j; // eax
  _DWORD *v14; // eax
  unsigned __int8 *v15; // ecx
  int v16; // eax
  int v17; // esi
  int k; // eax
  _DWORD *v19; // eax
  unsigned int v21; // [esp+4h] [ebp+4h]
  unsigned __int8 v22; // [esp+Ch] [ebp+Ch]

  ppf_sector_lists = malloc(0x145320u);
  for ( i = 0; i < 0x145320; i += 4 )
    *(_DWORD *)((char *)ppf_sector_lists + i) = 0;
  v4 = a3;
  v5 = a3 < a1 + a3;
  v21 = a1 + a3;
  if ( v5 )
  {
    do
    {
      v6 = a2;
      v7 = *(_DWORD *)(v4 + a2) / 0x930u;
      v8 = *((_DWORD *)ppf_sector_lists + v7);
      v9 = 2352 - *(_DWORD *)(v4 + a2) % 0x930u;
      v22 = *(_BYTE *)(v4 + a2 + 4);
      if ( v8 )
      {
        v12 = *((_DWORD *)ppf_sector_lists + v7);
        for ( j = *(_DWORD *)(v8 + 8); j; j = *(_DWORD *)(j + 8) )
          v12 = j;
        v14 = malloc(8u);
        *(_DWORD *)(v12 + 8) = v14;
        v14[1] = v4 + 5;
        *(_WORD *)(*(_DWORD *)(v12 + 8) + 2) = *(_DWORD *)(v4 + a2) % 0x930u;
        v15 = *(unsigned __int8 **)(v12 + 8);
        v10 = v22;
        if ( v22 > v9 )
          *v15 = v9;
        else
          *v15 = v22;
        v11 = *(_DWORD *)(v12 + 8);
        v6 = a2;
      }
      else
      {
        *((_DWORD *)ppf_sector_lists + v7) = malloc(8u);
        *(_DWORD *)(*((_DWORD *)ppf_sector_lists + v7) + 4) = v4 + 5;
        v10 = v22;
        *(_WORD *)(*((_DWORD *)ppf_sector_lists + v7) + 2) = *(_DWORD *)(v4 + a2) % 0x930u;
        if ( v22 > v9 )
          **((_BYTE **)ppf_sector_lists + v7) = v9;
        else
          **((_BYTE **)ppf_sector_lists + v7) = *(_BYTE *)(v4 + a2 + 4);
        v11 = *((_DWORD *)ppf_sector_lists + v7);
      }
      *(_DWORD *)(v11 + 8) = 0;
      if ( v10 > v9 )
      {
        v16 = *((_DWORD *)ppf_sector_lists + v7 + 1);
        if ( v16 )
        {
          v17 = *((_DWORD *)ppf_sector_lists + v7 + 1);
          for ( k = *(_DWORD *)(v16 + 8); k; k = *(_DWORD *)(k + 8) )
            v17 = k;
          v19 = malloc(8u);
          *(_DWORD *)(v17 + 8) = v19;
          v19[1] = v9 + v4 + 5;
          *(_WORD *)(*(_DWORD *)(v17 + 8) + 2) = 0;
          **(_BYTE **)(v17 + 8) = v22 - v9;
          *(_DWORD *)(*(_DWORD *)(v17 + 8) + 8) = 0;
        }
        else
        {
          *((_DWORD *)ppf_sector_lists + v7 + 1) = malloc(8u);
          *(_DWORD *)(*((_DWORD *)ppf_sector_lists + v7 + 1) + 4) = v9 + v4 + 5;
          *(_WORD *)(*((_DWORD *)ppf_sector_lists + v7 + 1) + 2) = 0;
          **((_BYTE **)ppf_sector_lists + v7 + 1) = v22 - v9;
          *(_DWORD *)(*((_DWORD *)ppf_sector_lists + v7 + 1) + 8) = 0;
        }
      }
      v4 += *(unsigned __int8 *)(v4 + v6 + 4) + 5;
    }
    while ( v4 < v21 );
  }
  return dbg_print("done.\n");
}

char ppf_load_patch()
{
  FILE *v0; // eax
  FILE *v1; // esi
  size_t v2; // edi

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
              ppf_parse_and_build(v2 - *(_DWORD *)&ppf_file_data[v2 - 4] - 1122, (int)ppf_file_data, 0x43Cu);
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

void __cdecl ppf_apply_patch_to_sector(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *i; // eax

  if ( ppf_enabled == 1 )
  {
    v2 = *((unsigned __int8 **)ppf_sector_lists + a1);
    if ( v2 )
    {
      qmemcpy((void *)(a2 + *((unsigned __int16 *)v2 + 1)), &ppf_file_data[*((_DWORD *)v2 + 1)], *v2);
      for ( i = *((unsigned __int8 **)v2 + 2); i; i = *((unsigned __int8 **)i + 2) )
        qmemcpy((void *)(a2 + *((unsigned __int16 *)i + 1)), &ppf_file_data[*((_DWORD *)i + 1)], *i);
    }
  }
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char ppf_enabled = 0x1;
char *ppf_file_data;
unsigned char ppf_filename[0xc00];
unsigned int ppf_sector_lists;
