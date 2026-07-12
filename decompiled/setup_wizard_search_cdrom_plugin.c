#include "pch.h"
INT_PTR __stdcall setup_wizard_search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  LRESULT v8; // eax
  unsigned int v9; // eax
  const char *v10; // eax
  HMODULE v11; // eax
  unsigned int v12; // eax
  const char *v13; // eax
  HMODULE v14; // esi
  unsigned int v15; // eax
  const char *v16; // eax
  HMODULE v17; // eax
  LRESULT v18; // eax
  int v19; // eax
  LRESULT v20; // eax
  int v21; // eax
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v25; // al
  int v26; // eax
  const char *v27; // eax
  LRESULT v28; // ebp
  int v29; // ebx
  CHAR *cFileName; // eax
  char *v31; // edx
  CHAR v32; // cl
  char *v33; // esi
  int v34; // edi
  char *v35; // eax
  char v36; // cl
  int v37; // ebp
  CHAR *v38; // eax
  char v39; // cl
  LRESULT v40; // eax
  int i; // esi
  LRESULT v42; // eax
  int v43; // [esp-18h] [ebp-11FCh]
  int v44; // [esp-14h] [ebp-11F8h]
  char v45[12]; // [esp+0h] [ebp-11E4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-11D8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-11D4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-1140h] BYREF
  CHAR lParam[1024]; // [esp+1E4h] [ebp-1000h] BYREF
  CHAR LibFileName[1024]; // [esp+5E4h] [ebp-C00h] BYREF
  char v51[1024]; // [esp+9E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+DE4h] [ebp-400h] BYREF

  strcpy(v45, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v45[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  switch ( a2 )
  {
    case 0x10u:
      setup_wizard_step = 8;
      EndDialog(hDlg, 1);
      break;
    case 0x110u:
      hFindFile = FindFirstFileA(FileName, &FindFileData);
      dword_45B8E4 = 0;
      sprintf(v51, "ePSXe CDR ASPI core 1.5.2.");
      v18 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
      if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
        SendDlgItemMessageA(hDlg, 1119, 0x186u, v18, 0);
      v19 = dword_45B8E4;
      strcpy(&byte_8A9540[1024 * dword_45B8E4], "W9XCDRCORE");
      dword_45B8E4 = v19 + 1;
      memset(&VersionInformation, 0, sizeof(VersionInformation));
      VersionInformation.dwOSVersionInfoSize = 148;
      GetVersionExA(&VersionInformation);
      if ( VersionInformation.dwPlatformId == 2 )
      {
        sprintf(v51, "ePSXe CDR WNT/W2K core 1.5.2.");
        v20 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
        if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
          SendDlgItemMessageA(hDlg, 1119, 0x186u, v20, 0);
        v21 = dword_45B8E4;
        strcpy(&byte_8A9540[1024 * dword_45B8E4], "W2KCDRCORE");
        dword_45B8E4 = v21 + 1;
      }
      do
      {
        sprintf(LibFileName, "%s%s", v45, FindFileData.cFileName);
        LibraryA = LoadLibraryA(LibFileName);
        v23 = LibraryA;
        if ( LibraryA )
        {
          PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
          PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v23, "PSEgetLibName");
          PSEgetLibVersion = GetProcAddress(v23, "PSEgetLibVersion");
          ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
          if ( PSEgetLibType )
          {
            if ( PSEgetLibName )
            {
              if ( PSEgetLibVersion )
              {
                v25 = PSEgetLibVersion();
                v26 = ::PSEgetLibVersion(v25);
                v27 = (const char *)PSEgetLibName(BYTE1(v26));
                sprintf(v51, "%s %d.%d", v27, v43, v44);
                if ( PSEgetLibType() == 1 )
                {
                  v28 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
                  if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                    SendDlgItemMessageA(hDlg, 1119, 0x186u, v28, 0);
                  v29 = dword_45B8E4;
                  if ( v28 == dword_45B8E4 )
                  {
                    cFileName = FindFileData.cFileName;
                    v31 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                    do
                    {
                      v32 = *cFileName;
                      cFileName[(_DWORD)v31] = *cFileName;
                      ++cFileName;
                    }
                    while ( v32 );
                  }
                  else
                  {
                    if ( v28 < dword_45B8E4 )
                    {
                      v33 = &byte_8A9140[1024 * dword_45B8E4];
                      v34 = dword_45B8E4 - v28;
                      do
                      {
                        v35 = v33;
                        do
                        {
                          v36 = *v35;
                          v35[1024] = *v35;
                          ++v35;
                        }
                        while ( v36 );
                        v33 -= 1024;
                        --v34;
                      }
                      while ( v34 );
                    }
                    v37 = (v28 << 10) - (_DWORD)FindFileData.cFileName;
                    v38 = FindFileData.cFileName;
                    do
                    {
                      v39 = *v38;
                      byte_8A9540[v37 + (_DWORD)v38] = *v38;
                      ++v38;
                    }
                    while ( v39 );
                  }
                  dword_45B8E4 = v29 + 1;
                }
              }
            }
          }
        }
      }
      while ( FindNextFileA(hFindFile, &FindFileData) );
      sprintf(lParam, "FirstCdrom");
      v40 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
      if ( !cdrom_letter )
        SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v40, 0);
      for ( i = 65; i <= 90; ++i )
      {
        sprintf(lParam, "%c:\\", i);
        if ( GetDriveTypeA(lParam) == 5 )
        {
          sprintf(lParam, "--%c:--", i);
          v42 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
          if ( i == cdrom_letter )
            SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v42, 0);
        }
      }
      if ( dword_45B8E4 == 1 )
      {
        SendDlgItemMessageA(hDlg, 1119, 0x186u, 0, 0);
        return 1;
      }
      break;
    case 0x111u:
      switch ( (__int16)a3 )
      {
        case 1120:
          v12 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v12 == -1 || v12 >= dword_45B8E4 )
            return 0;
          v13 = &byte_8A9540[1024 * v12];
          byte_8A94C0 = 1;
          if ( !strcmp(v13, "W9XCDRCORE") )
          {
            DialogBoxParamA(g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
            return 0;
          }
          if ( !strcmp(v13, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", v45, v13);
          v14 = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(v14, "CDRinit");
          GPUinit_0();
          PSEconfigure = GetProcAddress(v14, "CDRconfigure");
          PSEconfigure();
          return 0;
        case 1121:
          v9 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v9 == -1 )
            return 0;
          if ( v9 >= dword_45B8E4 )
            return 0;
          v10 = &byte_8A9540[1024 * v9];
          if ( !strcmp(v10, "W9XCDRCORE") || !strcmp(v10, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", v45, v10);
          v11 = LoadLibraryA(LibFileName);
          GPUtest_0 = GetProcAddress(v11, "CDRtest");
          GPUtest_0();
          return 0;
        case 1122:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case 1123:
          v6 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v6 == -1 || v6 >= dword_45B8E4 )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that you haven't selected a CDROM plugin. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not selected",
              0x10u);
            return 0;
          }
          if ( !byte_8A94C0 && strcmp(&byte_8A9540[1024 * v6], "W2KCDRCORE") )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that CDROM plugin hasn't been configured. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not configured",
              0x10u);
            return 0;
          }
          sprintf(byte_8A8CC0, "%s", &byte_8A9540[1024 * v6]);
          ++setup_wizard_step;
          v8 = SendDlgItemMessageA(hDlg, 1062, 0x147u, 0, 0);
          if ( v8 != -1 )
          {
            SendDlgItemMessageA(hDlg, 1062, 0x148u, v8, (LPARAM)lParam);
            if ( strncmp(lParam, "FirstCdrom", 4u) )
            {
              sscanf(lParam, "--%c:--", &cdrom_letter);
              EndDialog(hDlg, 1);
              return 1;
            }
            cdrom_letter = 0;
          }
          EndDialog(hDlg, 1);
          break;
        case 1124:
          v15 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v15 != -1 && v15 < dword_45B8E4 )
          {
            v16 = &byte_8A9540[1024 * v15];
            if ( strcmp(v16, "W9XCDRCORE") )
            {
              if ( strcmp(v16, "W2KCDRCORE") )
              {
                sprintf(LibFileName, "%s%s", v45, v16);
                v17 = LoadLibraryA(LibFileName);
                GPUabout_0 = GetProcAddress(v17, "CDRabout");
                GPUabout_0();
              }
            }
          }
          return 0;
        default:
          return 0;
      }
      break;
    default:
      return 0;
  }
  return 1;
}
