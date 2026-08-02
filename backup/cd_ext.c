char ext_cdrom_load_plugin()
{
  unsigned __int8 v0; // bl
  int v1; // esi
  char v2; // al
  char v3; // cl
  int (*CDRconfigure)(void); // eax
  HMODULE LibraryA; // eax
  int v6; // ecx
  int v8; // [esp+0h] [ebp-408h]
  CHAR LibFileName[1004]; // [esp+8h] [ebp-400h] BYREF
  int v10; // [esp+3F4h] [ebp-14h]
  int v11; // [esp+3F8h] [ebp-10h]
  int v12; // [esp+400h] [ebp-8h]
  int v13; // [esp+404h] [ebp-4h]

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)CdromPlugin);
  if ( cd_savefake_flag )
  {
    if ( cd_savefake_flag == 1 )
      cdrom_fake_create_file(cdrom_fake_filename);
    if ( loaded_file_type == 3 )
    {
      iso_load(bin_iso_file);
      sound_use_cdda = 0;
      byte_505542[0] = 0;
      byte_505544[0] = 0;
      word_505540 = 257;
      byte_505543[0] = 2;
      LOBYTE(CDRconfigure) = 1;
    }
    else
    {
      if ( !strcmp((const char *)CdromPlugin, "NULL") )
        fatal_error_with_message_box(" * !Error cdrom doesn't configurated \n"
                                     " * !Go Config->Cdrom and choose a plugin. \n");
      LibraryA = LoadLibraryA(LibFileName);
      hCdrModule = LibraryA;
      if ( !LibraryA )
        fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
      CDRconfigure = GetProcAddress(LibraryA, "CDRconfigure");
      ::CDRconfigure = (int)CDRconfigure;
      if ( CDRconfigure )
      {
        CDRconfigure = GetProcAddress(hCdrModule, "CDRtest");
        CDRtest = (int)CDRconfigure;
        if ( CDRconfigure )
        {
          CDRconfigure = GetProcAddress(hCdrModule, "CDRinit");
          CDRinit = CDRconfigure;
          if ( CDRconfigure )
          {
            CDRconfigure = GetProcAddress(hCdrModule, "CDRshutdown");
            CDRshutdown = (int (*(*)(void))(void))CDRconfigure;
            if ( CDRconfigure )
            {
              CDRconfigure = GetProcAddress(hCdrModule, "CDRopen");
              CDRopen = CDRconfigure;
              if ( CDRconfigure )
              {
                CDRconfigure = GetProcAddress(hCdrModule, "CDRclose");
                CDRclose = CDRconfigure;
                if ( CDRconfigure )
                {
                  CDRconfigure = GetProcAddress(hCdrModule, "CDRgetTN");
                  CDRgetTN = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))CDRconfigure;
                  if ( CDRconfigure )
                  {
                    CDRconfigure = GetProcAddress(hCdrModule, "CDRgetTD");
                    CDRgetTD = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))CDRconfigure;
                    if ( CDRconfigure )
                    {
                      CDRconfigure = GetProcAddress(hCdrModule, "CDRreadTrack");
                      CDRreadTrack = (int (__stdcall *)(_DWORD))CDRconfigure;
                      if ( CDRconfigure )
                      {
                        CDRconfigure = GetProcAddress(hCdrModule, "CDRgetBuffer");
                        CDRgetBuffer = CDRconfigure;
                        if ( CDRconfigure )
                        {
                          CDRplay = (int)GetProcAddress(hCdrModule, "CDRplay");
                          CDRstop = (char (*)(void))GetProcAddress(hCdrModule, "CDRstop");
                          if ( use_subchannel )
                          {
                            CDRgetBufferSub = GetProcAddress(hCdrModule, "CDRgetBufferSub");
                            if ( CDRgetBufferSub )
                              cpu_overclock_setting = 0;
                          }
                          else
                          {
                            CDRgetBufferSub = nullptr;
                          }
                          dbg_print(" * Init cdrom ... ");
                          CDRinit();
                          dbg_print("ok\n");
                          if ( nocd )
                          {
                            dbg_print(" * Cdrom open... ");
                            ShowCursor(1);
                            CDRopen();
                            ShowCursor(0);
                            dbg_print(" ok \n");
                          }
                          v13 = v6;
                          LOBYTE(CDRconfigure) = (_BYTE)hCdrModule;
                          if ( hCdrModule )
                          {
                            dword_505528 = 0;
                            word_50552C = 0;
                            ((void (__cdecl *)(int *))CDRgetTN)(&dword_505528);
                            v0 = 0;
                            word_505540 = dword_505528;
                            LOBYTE(v12) = 0;
                            if ( BYTE1(dword_505528) )
                            {
                              v11 = v8;
                              do
                              {
                                v1 = (unsigned __int8)v12;
                                dword_505524 = 0;
                                CDRgetTD((unsigned __int8)v12 + 1, &dword_505524, v11);
                                byte_505542[3 * v1] = BYTE2(dword_505524);
                                v2 = dword_505524;
                                byte_505543[3 * v1] = BYTE1(dword_505524);
                                byte_505544[3 * v1] = v2;
                                LOBYTE(v11) = ++v0;
                              }
                              while ( v0 < HIBYTE(word_505540) );
                            }
                            dword_505524 = 0;
                            CDRgetTD(0, &dword_505524, v10);
                            byte_505542[3 * HIBYTE(word_505540)] = BYTE2(dword_505524);
                            v3 = dword_505524;
                            byte_505543[3 * HIBYTE(word_505540)] = BYTE1(dword_505524);
                            LOBYTE(CDRconfigure) = HIBYTE(word_505540);
                            byte_505544[3 * HIBYTE(word_505540)] = v3;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else
  {
    LOBYTE(CDRconfigure) = cdrom_fake_load_file(cdrom_fake_filename);
  }
  return (char)CDRconfigure;
}

char __cdecl ext_CDR_get_first_last_track(_BYTE *a1, _BYTE *a2)
{
  char result; // al

  *a1 = word_505540;
  result = HIBYTE(word_505540);
  *a2 = HIBYTE(word_505540);
  return result;
}

char __cdecl ext_CDR_tarck_to_msf(__int16 a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  char result; // al

  if ( a1 <= (int)HIBYTE(word_505540) )
  {
    if ( a1 )
    {
      *a2 = byte_50553F[3 * a1];
      *a3 = *((_BYTE *)&word_505540 + 3 * a1);
      result = *((_BYTE *)&word_505540 + 3 * a1 + 1);
      *a4 = result;
    }
    else
    {
      *a2 = byte_505542[3 * HIBYTE(word_505540)];
      *a3 = byte_505543[3 * HIBYTE(word_505540)];
      result = HIBYTE(word_505540);
      *a4 = byte_505544[3 * HIBYTE(word_505540)];
    }
  }
  else
  {
    *a2 = 0;
    *a3 = 2;
    *a4 = 0;
    return (char)a2;
  }
  return result;
}

int __cdecl ext_CDR_read(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, char *Buffer)
{
  int v5; // eax
  const void *v6; // eax
  char *v7; // edx
  int v8; // eax
  _BYTE v9[16]; // [esp+14h] [ebp-10h] BYREF

  if ( !cd_savefake_flag )
  {
    cdrom_fake_read_portion(a1, a2, a3, Buffer);
    return 0;
  }
  if ( loaded_file_type == 3 )
  {
    iso_read_data(a1, a2, a3, (int)Buffer);
    if ( ppf_enabled )
    {
      v5 = cdr_msf_to_lba(a1, a2, a3);
      ppf_apply_patch_to_sector(v5, (int)Buffer);
    }
    if ( cd_savefake_flag == 1 )
    {
      cdrom_fake_write_portion(a1, a2, a3, Buffer);
      return 0;
    }
  }
  else
  {
    v9[0] = a1 % 10 + 16 * (a1 / 10);
    v9[1] = a2 % 10 + 16 * (a2 / 10);
    v9[2] = a3 % 10 + 16 * (a3 / 10);
    CDRreadTrack(v9);
    v6 = (const void *)CDRgetBuffer();
    v7 = Buffer;
    qmemcpy(Buffer + 12, v6, 0x930u);
    if ( ppf_enabled )
    {
      v8 = cdr_msf_to_lba(a1, a2, a3);
      ppf_apply_patch_to_sector(v8, (int)Buffer);
      v7 = Buffer;
    }
    if ( cd_savefake_flag == 1 )
      cdrom_fake_write_portion(a1, a2, a3, v7);
  }
  return 0;
}

int (*ext_cdrom_deinit())(void)
{
  int (*result)(void); // eax

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  ext_CDRstop();
  if ( CDRclose )
    CDRclose();
  result = (int (*)(void))CDRshutdown;
  if ( CDRshutdown )
    return CDRshutdown();
  return result;
}

char __cdecl sub_430750(char a1, char a2)
{
  unsigned __int8 v3; // [esp+4h] [ebp-4h]

  v3 = 0;
  if ( !HIBYTE(word_505540) )
    return 0;
  while ( a1 != byte_505542[3 * v3] || a2 != byte_505543[3 * v3] )
  {
    if ( ++v3 >= HIBYTE(word_505540) )
      return 0;
  }
  return byte_505544[3 * v3];
}

char __cdecl ext_CDRplay(int a1, char a2)
{
  char result; // al
  char (__stdcall *v3)(int *); // esi

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v3 = (char (__stdcall *)(int *))CDRplay;
    if ( CDRplay )
    {
      BYTE1(a1) = a2;
      BYTE2(a1) = sub_430750(a1, a2);
      return v3(&a1);
    }
  }
  return result;
}

char ext_CDRstop()
{
  char result; // al

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = (char)CDRstop;
    if ( CDRstop )
      return CDRstop();
  }
  return result;
}

// attributes: thunk
void ext_CDR_reset_state()
{
  cdr_spinup_motor();
}

char __cdecl sub_430820(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  unsigned int v7; // ebp
  unsigned __int8 v8; // dl
  int v9; // eax
  unsigned int v10; // edi
  unsigned int v11; // esi
  unsigned __int8 v13; // [esp+Ch] [ebp-4h]

  v7 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4) + (a3 & 0xF) - 150;
  v8 = HIBYTE(word_505540);
  v13 = 0;
  v9 = (unsigned __int8)byte_505544[3 * HIBYTE(word_505540)];
  if ( 75
     * ((unsigned __int8)byte_505543[3 * HIBYTE(word_505540)]
      + 60 * (unsigned int)(unsigned __int8)byte_505542[3 * HIBYTE(word_505540)])
     + v9
     - 150 > v7 )
  {
    if ( HIBYTE(word_505540) )
    {
      while ( 1 )
      {
        v10 = 75 * ((unsigned __int8)byte_505546[3 * v13] + 60 * (unsigned __int8)byte_505545[3 * v13])
            + (unsigned __int8)byte_505547[3 * v13]
            - 150;
        if ( v13 + 1 < HIBYTE(word_505540) )
        {
          v10 -= v10 % 0x4B;
          v8 = HIBYTE(word_505540);
        }
        if ( v10 > v7 )
          break;
        if ( ++v13 >= v8 )
          goto LABEL_8;
      }
      v11 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4))))
          + 10 * (a3 >> 4)
          + (a3 & 0xF)
          + (75 * ((unsigned __int8)byte_505543[3 * v13] + 60 * (unsigned __int8)byte_505542[3 * v13])
           + (unsigned int)(unsigned __int8)byte_505544[3 * v13]
           - 150)
          % 0x4B
          - (75 * ((unsigned __int8)byte_505543[3 * v13] + 60 * (unsigned __int8)byte_505542[3 * v13])
           + (unsigned __int8)byte_505544[3 * v13]);
      *a4 = (v13 + 1) % 10 + 16 * ((v13 + 1) / 10);
      *a5 = v11 / 0x4B / 0x3C % 0xA + 16 * (v11 / 0x4B / 0x3C / 0xA);
      *a6 = v11 / 0x4B % 0x3C % 0xA + 16 * (v11 / 0x4B % 0x3C / 0xA);
      LOBYTE(v9) = v11 % 0x4B % 0xA + 16 * (v11 % 0x4B / 0xA);
      *a7 = v9;
    }
    else
    {
LABEL_8:
      *a4 = -86;
      LOBYTE(v9) = (_BYTE)a4;
    }
  }
  else
  {
    *a4 = -86;
  }
  return v9;
}

unsigned __int8 __cdecl ext_CDR_lba_to_msf(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  unsigned __int8 v6; // bl
  unsigned int v7; // ecx
  unsigned __int8 result; // al
  unsigned int v9; // eax
  unsigned __int8 v10; // [esp+8h] [ebp-8h]

  v6 = 0;
  v7 = (a3 & 0xF) + 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4);
  v10 = 0;
  if ( 75
     * ((unsigned __int8)byte_505543[3 * HIBYTE(word_505540)]
      + 60 * (unsigned __int8)byte_505542[3 * HIBYTE(word_505540)])
     + (unsigned int)(unsigned __int8)byte_505544[3 * HIBYTE(word_505540)]
     - 150 > v7 )
  {
    result = HIBYTE(word_505540);
    if ( HIBYTE(word_505540) )
    {
      while ( 1 )
      {
        v9 = 75 * ((unsigned __int8)byte_505546[3 * v10] + 60 * (unsigned __int8)byte_505545[3 * v10])
           + (unsigned __int8)byte_505547[3 * v10]
           - 150;
        if ( v9 > v7 )
          break;
        result = HIBYTE(word_505540);
        v10 = ++v6;
        if ( v6 >= HIBYTE(word_505540) )
          return result;
      }
      *a4 = v9 / 0x4B / 0x3C;
      *a5 = v9 / 0x4B % 0x3C;
      *a6 = v9 % 0x4B;
      return (unsigned __int8)a5;
    }
  }
  else
  {
    *a4 = a1;
    *a5 = a2;
    *a6 = a3;
    return a2;
  }
  return result;
}

char __cdecl ext_CD_verify_subchannel_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  int v4; // ecx
  char v5; // bl
  char v6; // dl
  char result; // al
  char v8; // [esp+Bh] [ebp-1h]
  unsigned __int8 v9; // [esp+14h] [ebp+8h]
  unsigned __int8 v10; // [esp+14h] [ebp+8h]
  unsigned __int8 v11; // [esp+18h] [ebp+Ch]
  char v12; // [esp+18h] [ebp+Ch]
  unsigned __int8 v13; // [esp+18h] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  v8 = 0;
  if ( CDRgetBufferSub
    && ((v4 = CDRgetBufferSub(), !extsubchanhle) || (dword_50C280[0] & 0x1F000000) != 0x1F000000 || a1 == 3)
    && v4 )
  {
    if ( a3 )
    {
      v11 = a3 - 1;
    }
    else
    {
      v11 = 74;
      if ( a2 )
      {
        --a2;
      }
      else
      {
        a2 = 59;
        --a1;
      }
    }
    v5 = a1 % 10 + 16 * (a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v12 = v11 % 10 + 16 * (v11 / 10);
    *(_DWORD *)a4 = *(_DWORD *)(v4 + 13);
    *(_BYTE *)(a4 + 4) = *(_BYTE *)(v4 + 17);
    *(_WORD *)(a4 + 5) = *(_WORD *)(v4 + 19);
    *(_BYTE *)(a4 + 7) = *(_BYTE *)(v4 + 21);
    if ( v5 != *(_BYTE *)(v4 + 19) )
      v8 = 1;
    if ( v5 != *(_BYTE *)(v4 + 15) )
      ++v8;
    if ( v9 != *(_BYTE *)(v4 + 20) )
      ++v8;
    v6 = v8;
    if ( (((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) % 10 + 16 * ((((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) / 10) != *(unsigned __int8 *)(v4 + 16) )
      v6 = v8 + 1;
    result = v12;
    if ( v12 != *(_BYTE *)(v4 + 21) )
      ++v6;
    if ( v12 != *(_BYTE *)(v4 + 17) )
      ++v6;
    if ( (unsigned __int8)v6 >= 2u )
    {
      result = 0;
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      if ( v5 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    v10 = a2 % 10 + 16 * (a2 / 10);
    v13 = a3 % 10 + 16 * (a3 / 10);
    sub_430820(a1 % 10 + 16 * (a1 / 10), v10, v13, (_BYTE *)a4, (_BYTE *)(a4 + 2), (_BYTE *)(a4 + 3), (_BYTE *)(a4 + 4));
    *(_BYTE *)(a4 + 1) = 1;
    *(_BYTE *)(a4 + 5) = a1 % 10 + 16 * (a1 / 10);
    *(_BYTE *)(a4 + 6) = v10;
    *(_BYTE *)(a4 + 7) = v13;
    return v13;
  }
  return result;
}