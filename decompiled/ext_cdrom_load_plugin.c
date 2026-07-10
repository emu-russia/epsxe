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

  sprintf(LibFileName, "%s%s", aPlugins, (const char *)CdromPlugin);
  if ( byte_456D70 )
  {
    if ( byte_456D70 == 1 )
      sub_42F7E0(byte_505420);
    if ( dword_50C37C == 3 )
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
            CDRshutdown = CDRconfigure;
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
                          CDRstop = GetProcAddress(hCdrModule, "CDRstop");
                          if ( use_subchannel )
                          {
                            CDRgetBufferSub = GetProcAddress(hCdrModule, "CDRgetBufferSub");
                            if ( CDRgetBufferSub )
                              BYTE1(dword_455945) = 0;
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
    LOBYTE(CDRconfigure) = sub_42F870(byte_505420);
  }
  return (char)CDRconfigure;
}
