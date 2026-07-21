int __cdecl sub_436B50(int a1, int a2, unsigned int a3)
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

  dword_4FFC24 = malloc(0x145320u);
  for ( i = 0; i < 0x145320; i += 4 )
    *(_DWORD *)((char *)dword_4FFC24 + i) = 0;
  v4 = a3;
  v5 = a3 < a1 + a3;
  v21 = a1 + a3;
  if ( v5 )
  {
    do
    {
      v6 = a2;
      v7 = *(_DWORD *)(v4 + a2) / 0x930u;
      v8 = *((_DWORD *)dword_4FFC24 + v7);
      v9 = 2352 - *(_DWORD *)(v4 + a2) % 0x930u;
      v22 = *(_BYTE *)(v4 + a2 + 4);
      if ( v8 )
      {
        v12 = *((_DWORD *)dword_4FFC24 + v7);
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
        *((_DWORD *)dword_4FFC24 + v7) = malloc(8u);
        *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7) + 4) = v4 + 5;
        v10 = v22;
        *(_WORD *)(*((_DWORD *)dword_4FFC24 + v7) + 2) = *(_DWORD *)(v4 + a2) % 0x930u;
        if ( v22 > v9 )
          **((_BYTE **)dword_4FFC24 + v7) = v9;
        else
          **((_BYTE **)dword_4FFC24 + v7) = *(_BYTE *)(v4 + a2 + 4);
        v11 = *((_DWORD *)dword_4FFC24 + v7);
      }
      *(_DWORD *)(v11 + 8) = 0;
      if ( v10 > v9 )
      {
        v16 = *((_DWORD *)dword_4FFC24 + v7 + 1);
        if ( v16 )
        {
          v17 = *((_DWORD *)dword_4FFC24 + v7 + 1);
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
          *((_DWORD *)dword_4FFC24 + v7 + 1) = malloc(8u);
          *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 4) = v9 + v4 + 5;
          *(_WORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 2) = 0;
          **((_BYTE **)dword_4FFC24 + v7 + 1) = v22 - v9;
          *(_DWORD *)(*((_DWORD *)dword_4FFC24 + v7 + 1) + 8) = 0;
        }
      }
      v4 += *(unsigned __int8 *)(v4 + v6 + 4) + 5;
    }
    while ( v4 < v21 );
  }
  return dbg_print("done.\n");
}

char patch_game()
{
  FILE *v0; // eax
  FILE *v1; // esi
  size_t v2; // edi

  LOBYTE(v0) = auto_ppf_load;
  if ( auto_ppf_load )
  {
    if ( !strcmp(ppf_filename, "NULL") )
      sprintf(ppf_filename, "%s%s", "patches\\", byte_8B3D80);
    v0 = fopen(ppf_filename, "rb");
    v1 = v0;
    if ( v0 )
    {
      dbg_print(" * Patching game ... ");
      auto_ppf_load = 1;
      fseek(v1, 0, 2);
      v2 = ftell(v1);
      fseek(v1, 0, 0);
      dword_4FFC28 = (char *)malloc(v2);
      fread(dword_4FFC28, v2, 1u, v1);
      if ( !strncmp("PPF", dword_4FFC28, 3u) )
      {
        if ( dword_4FFC28[5] )
        {
          if ( dword_4FFC28[5] == 1 )
          {
            dbg_print("ppf file v.2.0 ");
            if ( !strncmp(".DIZ", &dword_4FFC28[v2 - 8], 4u) )
              sub_436B50(v2 - *(_DWORD *)&dword_4FFC28[v2 - 4] - 1122, (int)dword_4FFC28, 0x43Cu);
            else
              sub_436B50(v2 - 1084, (int)dword_4FFC28, 0x43Cu);
            LOBYTE(v0) = fclose(v1);
          }
          else
          {
            auto_ppf_load = 0;
            free(dword_4FFC28);
            fclose(v1);
            LOBYTE(v0) = dbg_print("unk ppf format.\n");
          }
        }
        else
        {
          dbg_print("ppf file v.1.0 ");
          sub_436B50(v2 - 56, (int)dword_4FFC28, 0x38u);
          LOBYTE(v0) = fclose(v1);
        }
      }
      else
      {
        auto_ppf_load = 0;
        free(dword_4FFC28);
        fclose(v1);
        LOBYTE(v0) = dbg_print("no ppf file.\n");
      }
    }
    else
    {
      auto_ppf_load = 0;
    }
  }
  return (char)v0;
}

void ppf_free()
{
  if ( auto_ppf_load )
  {
    free(dword_4FFC28);
    free(dword_4FFC24);
  }
}

void __cdecl sub_436F60(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *i; // eax

  if ( auto_ppf_load == 1 )
  {
    v2 = *((unsigned __int8 **)dword_4FFC24 + a1);
    if ( v2 )
    {
      qmemcpy((void *)(a2 + *((unsigned __int16 *)v2 + 1)), &dword_4FFC28[*((_DWORD *)v2 + 1)], *v2);
      for ( i = *((unsigned __int8 **)v2 + 2); i; i = *((unsigned __int8 **)i + 2) )
        qmemcpy((void *)(a2 + *((unsigned __int16 *)i + 1)), &dword_4FFC28[*((_DWORD *)i + 1)], *i);
    }
  }
}