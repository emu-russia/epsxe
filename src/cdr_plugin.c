#include "pch.h"
char ext_cdrom_load_plugin()
{
  uint8_t v0;
  int v1;
  char v2;
  char v3;
  int (*CDRconfigure)(void);
  HMODULE LibraryA;
  int v6;
  int v8;
  CHAR LibFileName[1004];
  int v10;
  int v11;
  int v12;
  int v13;

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)CdromPlugin);
  if ( cd_savefake_flag )
  {
    if ( cd_savefake_flag == 1 )
      cdrom_fake_create_file(cdrom_fake_filename);
    if ( loaded_file_type == 3 )
    {
      iso_load(bin_iso_file);
      sound_use_cdda = 0;
      track_msf_minutes[0] = 0;
      track_msf_sectors[0] = 0;
      first_last_tracks = 257;
      track_msf_seconds[0] = 2;
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
            CDRshutdown = (int ( *)(void))CDRconfigure;
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
                  CDRgetTN = (int ( *)(uint32_t, uint32_t, uint32_t))CDRconfigure;
                  if ( CDRconfigure )
                  {
                    CDRconfigure = GetProcAddress(hCdrModule, "CDRgetTD");
                    CDRgetTD = (int ( *)(uint32_t, uint32_t, uint32_t))CDRconfigure;
                    if ( CDRconfigure )
                    {
                      CDRconfigure = GetProcAddress(hCdrModule, "CDRreadTrack");
                      CDRreadTrack = (int ( *)(uint32_t))CDRconfigure;
                      if ( CDRconfigure )
                      {
                        CDRconfigure = GetProcAddress(hCdrModule, "CDRgetBuffer");
                        CDRgetBuffer = CDRconfigure;
                        if ( CDRconfigure )
                        {
                          CDRplay = (int ( *)(void))GetProcAddress(hCdrModule, "CDRplay");
                          CDRstop = (int ( *)(void))GetProcAddress(hCdrModule, "CDRstop");
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
                          LOBYTE(CDRconfigure) = (uint8_t)hCdrModule;
                          if ( hCdrModule )
                          {
                            current_position_msf = 0;
                            current_position_low = 0;
                            ((void ( *)(int *))CDRgetTN)(&current_position_msf);
                            v0 = 0;
                            first_last_tracks = current_position_msf;
                            LOBYTE(v12) = 0;
                            if ( BYTE1(current_position_msf) )
                            {
                              v11 = v8;
                              do
                              {
                                v1 = (uint8_t)v12;
                                track_info_buffer = 0;
                                CDRgetTD((uint8_t)v12 + 1, &track_info_buffer, v11);
                                track_msf_minutes[3 * v1] = BYTE2(track_info_buffer);
                                v2 = track_info_buffer;
                                track_msf_seconds[3 * v1] = BYTE1(track_info_buffer);
                                track_msf_sectors[3 * v1] = v2;
                                LOBYTE(v11) = ++v0;
                              }
                              while ( v0 < HIBYTE(first_last_tracks) );
                            }
                            track_info_buffer = 0;
                            CDRgetTD(0, &track_info_buffer, v10);
                            track_msf_minutes[3 * HIBYTE(first_last_tracks)] = BYTE2(track_info_buffer);
                            v3 = track_info_buffer;
                            track_msf_seconds[3 * HIBYTE(first_last_tracks)] = BYTE1(track_info_buffer);
                            LOBYTE(CDRconfigure) = HIBYTE(first_last_tracks);
                            track_msf_sectors[3 * HIBYTE(first_last_tracks)] = v3;
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

char ext_CDR_get_first_last_track(uint8_t *a1, uint8_t *a2)
{
  char result;

  *a1 = first_last_tracks;
  result = HIBYTE(first_last_tracks);
  *a2 = HIBYTE(first_last_tracks);
  return result;
}

char ext_CDR_track_to_msf(int16_t a1, uint8_t *a2, uint8_t *a3, uint8_t *a4)
{
  char result;

  if ( a1 <= (int)HIBYTE(first_last_tracks) )
  {
    if ( a1 )
    {
      *a2 = track_msf_table[3 * a1];
      *a3 = *((uint8_t *)&first_last_tracks + 3 * a1);
      result = *((uint8_t *)&first_last_tracks + 3 * a1 + 1);
      *a4 = result;
    }
    else
    {
      *a2 = track_msf_minutes[3 * HIBYTE(first_last_tracks)];
      *a3 = track_msf_seconds[3 * HIBYTE(first_last_tracks)];
      result = HIBYTE(first_last_tracks);
      *a4 = track_msf_sectors[3 * HIBYTE(first_last_tracks)];
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

int ext_CDR_read(uint8_t a1, uint8_t a2, uint8_t a3, char *Buffer)
{
  int v5;
  const void *v6;
  char *v7;
  int v8;
  uint8_t v9[16];

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
  int (*result)(void);

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

static char ext_CDR_bcd_to_binary(char a1, char a2)
{
  uint8_t v3;

  v3 = 0;
  if ( !HIBYTE(first_last_tracks) )
    return 0;
  while ( a1 != track_msf_minutes[3 * v3] || a2 != track_msf_seconds[3 * v3] )
  {
    if ( ++v3 >= HIBYTE(first_last_tracks) )
      return 0;
  }
  return track_msf_sectors[3 * v3];
}

char ext_CDRplay(int a1, char a2)
{
  char result;
  char (__stdcall *v3)(int *);

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v3 = (char (__stdcall *)(int *))CDRplay;
    if ( CDRplay )
    {
      BYTE1(a1) = a2;
      BYTE2(a1) = ext_CDR_bcd_to_binary(a1, a2);
      return v3(&a1);
    }
  }
  return result;
}

char ext_CDRstop()
{
  char result;

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = (char)CDRstop;
    if ( CDRstop )
      return CDRstop();
  }
  return result;
}


void ext_CDR_reset_state()
{
  cdr_spinup_motor();
}

static char ext_CDR_lba_to_msf_with_track(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6,
        uint8_t *a7)
{
  unsigned int v7;
  uint8_t v8;
  int v9;
  unsigned int v10;
  unsigned int v11;
  uint8_t v13;

  v7 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4) + (a3 & 0xF) - 150;
  v8 = HIBYTE(first_last_tracks);
  v13 = 0;
  v9 = (uint8_t)track_msf_sectors[3 * HIBYTE(first_last_tracks)];
  if ( 75
     * ((uint8_t)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (unsigned int)(uint8_t)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + v9
     - 150 > v7 )
  {
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        v10 = 75 * ((uint8_t)track_seconds_table[3 * v13] + 60 * (uint8_t)track_minutes_table[3 * v13])
            + (uint8_t)track_sectors_table[3 * v13]
            - 150;
        if ( v13 + 1 < HIBYTE(first_last_tracks) )
        {
          v10 -= v10 % 0x4B;
          v8 = HIBYTE(first_last_tracks);
        }
        if ( v10 > v7 )
          break;
        if ( ++v13 >= v8 )
          goto LABEL_8;
      }
      v11 = 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4))))
          + 10 * (a3 >> 4)
          + (a3 & 0xF)
          + (75 * ((uint8_t)track_msf_seconds[3 * v13] + 60 * (uint8_t)track_msf_minutes[3 * v13])
           + (unsigned int)(uint8_t)track_msf_sectors[3 * v13]
           - 150)
          % 0x4B
          - (75 * ((uint8_t)track_msf_seconds[3 * v13] + 60 * (uint8_t)track_msf_minutes[3 * v13])
           + (uint8_t)track_msf_sectors[3 * v13]);
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
      LOBYTE(v9) = (uint8_t)a4;
    }
  }
  else
  {
    *a4 = -86;
  }
  return v9;
}

uint8_t ext_CDR_lba_to_msf(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6)
{
  uint8_t v6;
  unsigned int v7;
  uint8_t result;
  unsigned int v9;
  uint8_t v10;

  v6 = 0;
  v7 = (a3 & 0xF) + 75 * ((a2 & 0xF) + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) + 10 * (a1 >> 4)))) + 10 * (a3 >> 4);
  v10 = 0;
  if ( 75
     * ((uint8_t)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (uint8_t)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + (unsigned int)(uint8_t)track_msf_sectors[3 * HIBYTE(first_last_tracks)]
     - 150 > v7 )
  {
    result = HIBYTE(first_last_tracks);
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        v9 = 75 * ((uint8_t)track_seconds_table[3 * v10] + 60 * (uint8_t)track_minutes_table[3 * v10])
           + (uint8_t)track_sectors_table[3 * v10]
           - 150;
        if ( v9 > v7 )
          break;
        result = HIBYTE(first_last_tracks);
        v10 = ++v6;
        if ( v6 >= HIBYTE(first_last_tracks) )
          return result;
      }
      *a4 = v9 / 0x4B / 0x3C;
      *a5 = v9 / 0x4B % 0x3C;
      *a6 = v9 % 0x4B;
      return (uint8_t)a5;
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

char ext_CDR_verify_subchannel_data(uint8_t a1, uint8_t a2, uint8_t a3, int a4)
{
  int v4;
  char v5;
  char v6;
  char result;
  char v8;
  uint8_t v9;
  uint8_t v10;
  uint8_t v11;
  char v12;
  uint8_t v13;

  *(uint32_t *)a4 = 0;
  *(uint32_t *)(a4 + 4) = 0;
  v8 = 0;
  if ( CDRgetBufferSub
    && ((v4 = CDRgetBufferSub(), !extsubchanhle) || (cop0_bpc_value[0] & 0x1F000000) != 0x1F000000 || a1 == 3)
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
    *(uint32_t *)a4 = *(uint32_t *)(v4 + 13);
    *(uint8_t *)(a4 + 4) = *(uint8_t *)(v4 + 17);
    *(uint16_t *)(a4 + 5) = *(uint16_t *)(v4 + 19);
    *(uint8_t *)(a4 + 7) = *(uint8_t *)(v4 + 21);
    if ( v5 != *(uint8_t *)(v4 + 19) )
      v8 = 1;
    if ( v5 != *(uint8_t *)(v4 + 15) )
      ++v8;
    if ( v9 != *(uint8_t *)(v4 + 20) )
      ++v8;
    v6 = v8;
    if ( (((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) % 10 + 16 * ((((v9 - 2) & 0xF) + 10 * ((v9 - 2) >> 4)) / 10) != *(uint8_t *)(v4 + 16) )
      v6 = v8 + 1;
    result = v12;
    if ( v12 != *(uint8_t *)(v4 + 21) )
      ++v6;
    if ( v12 != *(uint8_t *)(v4 + 17) )
      ++v6;
    if ( (uint8_t)v6 >= 2u )
    {
      result = 0;
      *(uint32_t *)(a4 + 2) = 0;
      *(uint16_t *)(a4 + 6) = 0;
      if ( v5 == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    v10 = a2 % 10 + 16 * (a2 / 10);
    v13 = a3 % 10 + 16 * (a3 / 10);
    ext_CDR_lba_to_msf_with_track(
      a1 % 10 + 16 * (a1 / 10),
      v10,
      v13,
      (uint8_t *)a4,
      (uint8_t *)(a4 + 2),
      (uint8_t *)(a4 + 3),
      (uint8_t *)(a4 + 4));
    *(uint8_t *)(a4 + 1) = 1;
    *(uint8_t *)(a4 + 5) = a1 % 10 + 16 * (a1 / 10);
    *(uint8_t *)(a4 + 6) = v10;
    *(uint8_t *)(a4 + 7) = v13;
    return v13;
  }
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
int ( *CDRclose)();
int ( *CDRgetBuffer)();
int ( *CDRgetBufferSub)();
int ( *CDRgetTD)();
unsigned int CDRgetTN;
int ( *CDRinit)();
int ( *CDRopen)();
unsigned int CDRplay;
int ( *CDRreadTrack)();
int ( *CDRshutdown)();
int ( *CDRstop)();
unsigned int CDRtest;
unsigned char cdrom_fake_filename[0x100];
unsigned short current_position_low;
unsigned int current_position_msf;
unsigned short first_last_tracks;
unsigned int hCdrModule;
unsigned int track_info_buffer;
unsigned char track_minutes_table[1];
unsigned char track_msf_minutes[1];
unsigned char track_msf_seconds[1];
unsigned char track_msf_sectors[1];
unsigned char track_msf_table[1];
unsigned char track_seconds_table[1];
unsigned char track_sectors_table[0x139];
