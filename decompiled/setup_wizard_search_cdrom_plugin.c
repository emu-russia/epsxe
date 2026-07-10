#include "pch.h"
INT_PTR __stdcall search_cdrom_plugin2(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  CHAR *v6; // edi
  __int16 v7; // cx
  unsigned int v8; // eax
  LRESULT v10; // eax
  unsigned int v11; // eax
  const char *v12; // eax
  HMODULE v13; // eax
  unsigned int v14; // eax
  const char *v15; // eax
  HMODULE v16; // esi
  unsigned int v17; // eax
  const char *v18; // eax
  HMODULE v19; // eax
  LRESULT v20; // eax
  int v21; // eax
  LRESULT v22; // eax
  int v23; // eax
  HMODULE LibraryA; // eax
  HMODULE v25; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v27; // al
  int v28; // eax
  const char *v29; // eax
  LRESULT v30; // ebp
  int v31; // ebx
  CHAR *cFileName; // eax
  char *v33; // edx
  CHAR v34; // cl
  char *v35; // esi
  int v36; // edi
  char *v37; // eax
  char v38; // cl
  int v39; // ebp
  CHAR *v40; // eax
  CHAR v41; // cl
  LRESULT v42; // eax
  int i; // esi
  LRESULT v44; // eax
  int v45; // [esp-18h] [ebp-11FCh]
  int v46; // [esp-14h] [ebp-11F8h]
  char v47[12]; // [esp+0h] [ebp-11E4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-11D8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-11D4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-1140h] BYREF
  CHAR lParam[1024]; // [esp+1E4h] [ebp-1000h] BYREF
  CHAR LibFileName[1024]; // [esp+5E4h] [ebp-C00h] BYREF
  char v53[1024]; // [esp+9E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+DE4h] [ebp-400h] BYREF

  strcpy(v47, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v47[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  v6 = &FileName[strlen(FileName) + 1];
  v7 = MEMORY[0x44E400];
  *(_DWORD *)--v6 = aDll;
  *((_WORD *)v6 + 2) = v7;
  switch ( a2 )
  {
    case 0x10u:
      setup_wizard_step = 8;
      EndDialog(hDlg, 1);
      break;
    case 0x110u:
      hFindFile = FindFirstFileA(FileName, &FindFileData);
      dword_45B8E4 = 0;
      sprintf(v53, aEpsxeCdrAspiCo);
      v20 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v53);
      if ( !strcmp((const char *)&CdromPlugin, aW9xcdrcore) )
        SendDlgItemMessageA(hDlg, 1119, 0x186u, v20, 0);
      v21 = dword_45B8E4;
      strcpy((char *)&byte_8A9540[256 * dword_45B8E4], "W9XCDRCORE");
      dword_45B8E4 = v21 + 1;
      memset(&VersionInformation, 0, sizeof(VersionInformation));
      VersionInformation.dwOSVersionInfoSize = 148;
      GetVersionExA(&VersionInformation);
      if ( VersionInformation.dwPlatformId == 2 )
      {
        sprintf(v53, aEpsxeCdrWntW2k);
        v22 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v53);
        if ( !strcmp((const char *)&CdromPlugin, aW2kcdrcore) )
          SendDlgItemMessageA(hDlg, 1119, 0x186u, v22, 0);
        v23 = dword_45B8E4;
        strcpy((char *)&byte_8A9540[256 * dword_45B8E4], "W2KCDRCORE");
        dword_45B8E4 = v23 + 1;
      }
      do
      {
        sprintf(LibFileName, "%s%s", v47, FindFileData.cFileName);
        LibraryA = LoadLibraryA(LibFileName);
        v25 = LibraryA;
        if ( LibraryA )
        {
          PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
          PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v25, aPsegetlibname);
          PSEgetLibVersion = GetProcAddress(v25, aPsegetlibversi);
          ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
          if ( PSEgetLibType )
          {
            if ( PSEgetLibName )
            {
              if ( PSEgetLibVersion )
              {
                v27 = PSEgetLibVersion();
                v28 = ::PSEgetLibVersion(v27);
                v29 = (const char *)PSEgetLibName(BYTE1(v28));
                sprintf(v53, "%s %d.%d", v29, v45, v46);
                if ( PSEgetLibType() == 1 )
                {
                  v30 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v53);
                  if ( !strcmp((const char *)&CdromPlugin, FindFileData.cFileName) )
                    SendDlgItemMessageA(hDlg, 1119, 0x186u, v30, 0);
                  v31 = dword_45B8E4;
                  if ( v30 == dword_45B8E4 )
                  {
                    cFileName = FindFileData.cFileName;
                    v33 = (char *)byte_8A9540 + (dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName;
                    do
                    {
                      v34 = *cFileName;
                      cFileName[(_DWORD)v33] = *cFileName;
                      ++cFileName;
                    }
                    while ( v34 );
                  }
                  else
                  {
                    if ( v30 < dword_45B8E4 )
                    {
                      v35 = (char *)&byte_8A9140 + 1024 * dword_45B8E4;
                      v36 = dword_45B8E4 - v30;
                      do
                      {
                        v37 = v35;
                        do
                        {
                          v38 = *v37;
                          v37[1024] = *v37;
                          ++v37;
                        }
                        while ( v38 );
                        v35 -= 1024;
                        --v36;
                      }
                      while ( v36 );
                    }
                    v39 = (v30 << 10) - (_DWORD)FindFileData.cFileName;
                    v40 = FindFileData.cFileName;
                    do
                    {
                      v41 = *v40;
                      v40[(_DWORD)byte_8A9540 + v39] = *v40;
                      ++v40;
                    }
                    while ( v41 );
                  }
                  dword_45B8E4 = v31 + 1;
                }
              }
            }
          }
        }
      }
      while ( FindNextFileA(hFindFile, &FindFileData) );
      sprintf(lParam, aFirstcdrom);
      v42 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
      if ( !cdrom_letter )
        SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v42, 0);
      for ( i = 65; i <= 90; ++i )
      {
        sprintf(lParam, "%c:\\", i);
        if ( GetDriveTypeA(lParam) == 5 )
        {
          sprintf(lParam, "--%c:--", i);
          v44 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
          if ( i == cdrom_letter )
            SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v44, 0);
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
          v14 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v14 == -1 || v14 >= dword_45B8E4 )
            return 0;
          v15 = (const char *)&byte_8A9540[256 * v14];
          unk_8A94C0 = 1;
          if ( !strcmp(v15, aW9xcdrcore) )
          {
            DialogBoxParamA(g_hInstance, TemplateName, hDlg, w9x_cdrom_settings, 0);
            return 0;
          }
          if ( !strcmp(v15, aW2kcdrcore) )
            return 0;
          sprintf(LibFileName, "%s%s", v47, v15);
          v16 = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(v16, aCdrinit);
          GPUinit_0();
          GPUconfigure_0 = GetProcAddress(v16, aCdrconfigure);
          GPUconfigure_0();
          return 0;
        case 1121:
          v11 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v11 == -1 )
            return 0;
          if ( v11 >= dword_45B8E4 )
            return 0;
          v12 = (const char *)&byte_8A9540[256 * v11];
          if ( !strcmp(v12, aW9xcdrcore) || !strcmp(v12, aW2kcdrcore) )
            return 0;
          sprintf(LibFileName, "%s%s", v47, v12);
          v13 = LoadLibraryA(LibFileName);
          GPUtest_0 = GetProcAddress(v13, aCdrtest);
          GPUtest_0();
          return 0;
        case 1122:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case 1123:
          v8 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v8 == -1 || v8 >= dword_45B8E4 )
          {
            MessageBoxA(nullptr, aEpsxeDetectedT_3, aCdromPluginNot_0, 0x10u);
            return 0;
          }
          if ( !unk_8A94C0 && strcmp((const char *)&byte_8A9540[256 * v8], aW2kcdrcore) )
          {
            MessageBoxA(nullptr, aEpsxeDetectedT_2, aCdromPluginNot, 0x10u);
            return 0;
          }
          sprintf(byte_8A8CC0, "%s", (const char *)&byte_8A9540[256 * v8]);
          ++setup_wizard_step;
          v10 = SendDlgItemMessageA(hDlg, 1062, 0x147u, 0, 0);
          if ( v10 != -1 )
          {
            SendDlgItemMessageA(hDlg, 1062, 0x148u, v10, (LPARAM)lParam);
            if ( strncmp(lParam, aFirstcdrom, 4u) )
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
          v17 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v17 != -1 && v17 < dword_45B8E4 )
          {
            v18 = (const char *)&byte_8A9540[256 * v17];
            if ( strcmp(v18, aW9xcdrcore) )
            {
              if ( strcmp(v18, aW2kcdrcore) )
              {
                sprintf(LibFileName, "%s%s", v47, v18);
                v19 = LoadLibraryA(LibFileName);
                GPUabout_0 = GetProcAddress(v19, aCdrabout);
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
