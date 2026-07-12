#include "pch.h"
INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  INT_PTR result; // eax
  unsigned int v8; // eax
  const char *v9; // eax
  HMODULE v10; // eax
  unsigned int v11; // eax
  const char *v12; // eax
  HMODULE v13; // esi
  unsigned int v14; // eax
  const char *v15; // eax
  HMODULE v16; // eax
  HWND v17; // ebx
  LRESULT (__stdcall *v18)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v19; // eax
  int v20; // eax
  LRESULT v21; // eax
  int v22; // eax
  HMODULE LibraryA; // eax
  HMODULE v24; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v26; // al
  int v27; // eax
  const char *v28; // eax
  signed int v29; // ebp
  int v30; // ebx
  CHAR *cFileName; // eax
  char *v32; // edx
  CHAR v33; // cl
  char *v34; // esi
  int v35; // edi
  char *v36; // eax
  char v37; // cl
  int v38; // ebp
  CHAR *v39; // eax
  char v40; // cl
  int v41; // [esp-18h] [ebp-DFCh]
  int v42; // [esp-14h] [ebp-DF8h]
  char v43[12]; // [esp+0h] [ebp-DE4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-DD8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-DD4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+1E4h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+5E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+9E4h] [ebp-400h] BYREF

  strcpy(v43, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v43[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, "ePSXe CDR ASPI core 1.5.2.");
    v17 = hDlg;
    v18 = SendDlgItemMessageA;
    v19 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
      SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v19, 0);
    v20 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "W9XCDRCORE");
    dword_45B8E4 = v20 + 1;
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      sprintf(lParam, "ePSXe CDR WNT/W2K core 1.5.2.");
      v21 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
      if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
        SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v21, 0);
      v22 = dword_45B8E4;
      strcpy(&byte_8A9540[1024 * dword_45B8E4], "W2KCDRCORE");
      dword_45B8E4 = v22 + 1;
    }
    do
    {
      sprintf(LibFileName, "%s%s", v43, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v24 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v24, "PSEgetLibName");
        PSEgetLibVersion = GetProcAddress(v24, "PSEgetLibVersion");
        ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v26 = PSEgetLibVersion();
              v27 = ::PSEgetLibVersion(v26);
              v28 = (const char *)PSEgetLibName(BYTE1(v27));
              sprintf(lParam, "%s %d.%d", v28, v41, v42);
              if ( PSEgetLibType() == 1 )
              {
                v29 = v18(v17, 1000, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v17, 1000, 0x14Eu, v29, 0);
                v30 = dword_45B8E4;
                if ( v29 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v32 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v33 = *cFileName;
                    cFileName[(_DWORD)v32] = *cFileName;
                    ++cFileName;
                  }
                  while ( v33 );
                }
                else
                {
                  if ( v29 < dword_45B8E4 )
                  {
                    v34 = &byte_8A9140[1024 * dword_45B8E4];
                    v35 = dword_45B8E4 - v29;
                    do
                    {
                      v36 = v34;
                      do
                      {
                        v37 = *v36;
                        v36[1024] = *v36;
                        ++v36;
                      }
                      while ( v37 );
                      v34 -= 1024;
                      --v35;
                    }
                    while ( v35 );
                  }
                  v38 = (v29 << 10) - (_DWORD)FindFileData.cFileName;
                  v39 = FindFileData.cFileName;
                  do
                  {
                    v40 = *v39;
                    byte_8A9540[v38 + (_DWORD)v39] = *v39;
                    ++v39;
                  }
                  while ( v40 );
                }
                v18 = SendDlgItemMessageA;
                dword_45B8E4 = v30 + 1;
                v17 = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1001:
        v8 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v8 == -1 )
          return 0;
        if ( v8 >= dword_45B8E4 )
          return 0;
        v9 = &byte_8A9540[1024 * v8];
        if ( !strcmp(v9, "W9XCDRCORE") || !strcmp(v9, "W2KCDRCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", v43, v9);
        v10 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v10, "CDRtest");
        GPUtest_0();
        result = 0;
        break;
      case 1003:
        v11 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v11 == -1 || v11 >= dword_45B8E4 )
          return 0;
        v12 = &byte_8A9540[1024 * v11];
        if ( !strcmp(v12, "W9XCDRCORE") )
        {
          DialogBoxParamA(g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
          result = 0;
        }
        else
        {
          if ( !strcmp(v12, "W2KCDRCORE") )
          {
            DialogBoxParamA(g_hInstance, "IDD_CDROMCORE2K", hDlg, w2k_cdrom_settings, 0);
          }
          else
          {
            sprintf(LibFileName, "%s%s", v43, v12);
            v13 = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(v13, "CDRinit");
            GPUinit_0();
            PSEconfigure = GetProcAddress(v13, "CDRconfigure");
            PSEconfigure();
          }
          result = 0;
        }
        break;
      case 1004:
        v14 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v14 != -1 && v14 < dword_45B8E4 )
        {
          v15 = &byte_8A9540[1024 * v14];
          if ( strcmp(v15, "W9XCDRCORE") )
          {
            if ( strcmp(v15, "W2KCDRCORE") )
            {
              sprintf(LibFileName, "%s%s", v43, v15);
              v16 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v16, "CDRabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1023:
        v6 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v6 != -1 && v6 < dword_45B8E4 )
          sprintf((char *const)CdromPlugin, "%s", &byte_8A9540[1024 * v6]);
        EndDialog(hDlg, 1);
        save_settings();
        result = 1;
        break;
      case 1024:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}
