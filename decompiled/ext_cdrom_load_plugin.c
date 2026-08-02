#include "pch.h"
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
                            current_position_msf = 0;
                            current_position_low = 0;
                            ((void (__cdecl *)(int *))CDRgetTN)(&current_position_msf);
                            v0 = 0;
                            first_last_tracks = current_position_msf;
                            LOBYTE(v12) = 0;
                            if ( BYTE1(current_position_msf) )
                            {
                              v11 = v8;
                              do
                              {
                                v1 = (unsigned __int8)v12;
                                track_info_buffer = 0;
                                CDRgetTD((unsigned __int8)v12 + 1, &track_info_buffer, v11);
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
