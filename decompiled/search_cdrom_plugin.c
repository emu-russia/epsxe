#include "pch.h"
INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  CHAR *v6; // edi
  __int16 v7; // cx
  unsigned int v8; // eax
  INT_PTR result; // eax
  unsigned int v10; // eax
  const char *v11; // eax
  HMODULE v12; // eax
  unsigned int v13; // eax
  const char *v14; // eax
  HMODULE v15; // esi
  unsigned int v16; // eax
  const char *v17; // eax
  HMODULE v18; // eax
  HWND v19; // ebx
  LRESULT (__stdcall *v20)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v21; // eax
  int v22; // eax
  LRESULT v23; // eax
  int v24; // eax
  HMODULE LibraryA; // eax
  HMODULE v26; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v28; // al
  int v29; // eax
  const char *v30; // eax
  signed int v31; // ebp
  int v32; // ebx
  CHAR *cFileName; // eax
  char *v34; // edx
  CHAR v35; // cl
  char *v36; // esi
  int v37; // edi
  char *v38; // eax
  char v39; // cl
  int v40; // ebp
  CHAR *v41; // eax
  char v42; // cl
  int v43; // [esp-18h] [ebp-DFCh]
  int v44; // [esp-14h] [ebp-DF8h]
  char v45[12]; // [esp+0h] [ebp-DE4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-DD8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-DD4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+1E4h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+5E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+9E4h] [ebp-400h] BYREF

  strcpy(v45, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v45[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  v6 = &FileName[strlen(FileName) + 1];
  v7 = MEMORY[0x44E400];
  *(_DWORD *)--v6 = aDll;
  *((_WORD *)v6 + 2) = v7;
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, "ePSXe CDR ASPI core 1.5.2.");
    v19 = hDlg;
    v20 = SendDlgItemMessageA;
    v21 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
      SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v21, 0);
    v22 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "W9XCDRCORE");
    dword_45B8E4 = v22 + 1;
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      sprintf(lParam, "ePSXe CDR WNT/W2K core 1.5.2.");
      v23 = SendDlgItemMessageA(hDlg, 1000, 0x143u, 0, (LPARAM)lParam);
      if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
        SendDlgItemMessageA(hDlg, 1000, 0x14Eu, v23, 0);
      v24 = dword_45B8E4;
      strcpy(&byte_8A9540[1024 * dword_45B8E4], "W2KCDRCORE");
      dword_45B8E4 = v24 + 1;
    }
    do
    {
      sprintf(LibFileName, "%s%s", v45, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v26 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v26, aPsegetlibname);
        PSEgetLibVersion = GetProcAddress(v26, aPsegetlibversi);
        ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v28 = PSEgetLibVersion();
              v29 = ::PSEgetLibVersion(v28);
              v30 = (const char *)PSEgetLibName(BYTE1(v29));
              sprintf(lParam, "%s %d.%d", v30, v43, v44);
              if ( PSEgetLibType() == 1 )
              {
                v31 = v20(v19, 1000, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v19, 1000, 0x14Eu, v31, 0);
                v32 = dword_45B8E4;
                if ( v31 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v34 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v35 = *cFileName;
                    cFileName[(_DWORD)v34] = *cFileName;
                    ++cFileName;
                  }
                  while ( v35 );
                }
                else
                {
                  if ( v31 < dword_45B8E4 )
                  {
                    v36 = &byte_8A9140[1024 * dword_45B8E4];
                    v37 = dword_45B8E4 - v31;
                    do
                    {
                      v38 = v36;
                      do
                      {
                        v39 = *v38;
                        v38[1024] = *v38;
                        ++v38;
                      }
                      while ( v39 );
                      v36 -= 1024;
                      --v37;
                    }
                    while ( v37 );
                  }
                  v40 = (v31 << 10) - (_DWORD)FindFileData.cFileName;
                  v41 = FindFileData.cFileName;
                  do
                  {
                    v42 = *v41;
                    byte_8A9540[v40 + (_DWORD)v41] = *v41;
                    ++v41;
                  }
                  while ( v42 );
                }
                v20 = SendDlgItemMessageA;
                dword_45B8E4 = v32 + 1;
                v19 = hDlg;
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
        v10 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v10 == -1 )
          return 0;
        if ( v10 >= dword_45B8E4 )
          return 0;
        v11 = &byte_8A9540[1024 * v10];
        if ( !strcmp(v11, "W9XCDRCORE") || !strcmp(v11, "W2KCDRCORE") )
          return 0;
        sprintf(LibFileName, "%s%s", v45, v11);
        v12 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v12, "CDRtest");
        GPUtest_0();
        result = 0;
        break;
      case 1003:
        v13 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v13 == -1 || v13 >= dword_45B8E4 )
          return 0;
        v14 = &byte_8A9540[1024 * v13];
        if ( !strcmp(v14, "W9XCDRCORE") )
        {
          DialogBoxParamA(g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
          result = 0;
        }
        else
        {
          if ( !strcmp(v14, "W2KCDRCORE") )
          {
            DialogBoxParamA(g_hInstance, "IDD_CDROMCORE2K", hDlg, w2k_cdrom_settings, 0);
          }
          else
          {
            sprintf(LibFileName, "%s%s", v45, v14);
            v15 = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(v15, "CDRinit");
            GPUinit_0();
            GPUconfigure_0 = GetProcAddress(v15, "CDRconfigure");
            GPUconfigure_0();
          }
          result = 0;
        }
        break;
      case 1004:
        v16 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v16 != -1 && v16 < dword_45B8E4 )
        {
          v17 = &byte_8A9540[1024 * v16];
          if ( strcmp(v17, "W9XCDRCORE") )
          {
            if ( strcmp(v17, "W2KCDRCORE") )
            {
              sprintf(LibFileName, "%s%s", v45, v17);
              v18 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v18, "CDRabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1023:
        v8 = SendDlgItemMessageA(hDlg, 1000, 0x147u, 0, 0);
        if ( v8 != -1 && v8 < dword_45B8E4 )
          sprintf((char *const)CdromPlugin, "%s", &byte_8A9540[1024 * v8]);
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
