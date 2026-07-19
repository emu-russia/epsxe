#include "pch.h"
INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  INT_PTR result; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  const char *v9; // eax
  HMODULE v10; // eax
  char v11; // al
  unsigned int v12; // eax
  const char *v13; // eax
  HMODULE v14; // eax
  unsigned int v15; // eax
  const char *v16; // eax
  HMODULE v17; // eax
  HWND v18; // ebx
  LRESULT (__stdcall *v19)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v20; // eax
  int v21; // eax
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion_ptr; // eax
  unsigned __int8 v25; // al
  int v26; // eax
  const char *v27; // eax
  signed int v28; // ebp
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
  int v40; // [esp-18h] [ebp-D68h]
  int v41; // [esp-14h] [ebp-D64h]
  char v42[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v42, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v42[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not net plugins found\n");
    dword_45B8E4 = 0;
    sprintf(lParam, "Disabled Netplay");
    v18 = hDlg;
    v19 = SendDlgItemMessageA;
    v20 = SendDlgItemMessageA(hDlg, 1104, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)NetPlugin, "DISABLED") )
      SendDlgItemMessageA(hDlg, 1104, 0x14Eu, v20, 0);
    v21 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "DISABLED");
    dword_45B8E4 = v21 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v42, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v23 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v23, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(v23, "PSEgetLibVersion");
        PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              v25 = PSEgetLibVersion_ptr();
              v26 = PSEgetLibVersion(v25);
              v27 = (const char *)PSEgetLibName(BYTE1(v26));
              sprintf(lParam, "%s %d.%d", v27, v40, v41);
              if ( PSEgetLibType() == 16 )
              {
                v28 = v19(v18, 1104, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)NetPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v18, 1104, CB_SETCURSEL, v28, 0);
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
                v18 = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      v19 = SendDlgItemMessageA;
    }
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1099:
        if ( !dword_45B8E4 )
          return 0;
        v8 = SendDlgItemMessageA(hDlg, 1104, CB_GETCURSEL, 0, 0);
        if ( v8 == -1 )
          return 0;
        if ( v8 >= dword_45B8E4 )
          return 0;
        v9 = &byte_8A9540[1024 * v8];
        if ( !strcmp(v9, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v42, v9);
        v10 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v10, "NETtest");
        v11 = GPUtest_0();
        if ( v11 )
        {
          if ( v11 == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing NET Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing NET Plugin", 0x40u);
          result = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing NET Plugin", 0x40u);
          result = 0;
        }
        break;
      case 1100:
        if ( !dword_45B8E4 )
          return 0;
        v12 = SendDlgItemMessageA(hDlg, 1104, CB_GETCURSEL, 0, 0);
        if ( v12 == -1 )
          return 0;
        if ( v12 >= dword_45B8E4 )
          return 0;
        v13 = &byte_8A9540[1024 * v12];
        if ( !strcmp(v13, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v42, v13);
        v14 = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(v14, "NETconfigure");
        PSEconfigure();
        result = 0;
        break;
      case 1101:
        if ( dword_45B8E4 )
        {
          v15 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v15 != -1 && v15 < dword_45B8E4 )
          {
            v16 = &byte_8A9540[1024 * v15];
            if ( strcmp(v16, "DISABLED") )
            {
              sprintf(LibFileName, "%s%s", v42, v16);
              v17 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v17, "NETabout");
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1102:
        if ( dword_45B8E4 )
        {
          v7 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v7 != -1 && v7 < dword_45B8E4 )
            sprintf((char *const)NetPlugin, "%s", &byte_8A9540[1024 * v7]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        break;
      case 1103:
        if ( dword_45B8E4 )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
        }
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
