#include "pch.h"
INT_PTR __stdcall search_video_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  INT_PTR result; // eax
  unsigned int v7; // eax
  unsigned int v8; // eax
  HMODULE v9; // esi
  char v10; // al
  unsigned int v11; // eax
  HMODULE v12; // esi
  unsigned int v13; // eax
  HMODULE v14; // esi
  HMODULE LibraryA; // eax
  HMODULE v16; // esi
  FARPROC PSEgetLibVersion_ptr; // eax
  unsigned __int8 v18; // al
  int v19; // eax
  const char *v20; // eax
  LRESULT v21; // ebp
  int v22; // ebx
  CHAR *cFileName; // eax
  char *v24; // edx
  CHAR v25; // cl
  char *v26; // esi
  int v27; // edi
  char *v28; // eax
  char v29; // cl
  int v30; // ebp
  CHAR *v31; // eax
  char v32; // cl
  int v33; // [esp-18h] [ebp-D68h]
  int v34; // [esp-14h] [ebp-D64h]
  char v35[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+550h] [ebp-800h] BYREF
  char lParam[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v35, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v35[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print("not video plugins found\n");
    dword_45B8E4 = 0;
    do
    {
      sprintf(LibFileName, "%s%s", v35, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v16 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v16, "PSEgetLibName");
        PSEgetLibVersion_ptr = GetProcAddress(v16, "PSEgetLibVersion");
        PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              v18 = PSEgetLibVersion_ptr();
              v19 = PSEgetLibVersion(v18);
              v20 = (const char *)PSEgetLibName(BYTE1(v19));
              sprintf(lParam, "%s %d.%d", v20, v33, v34);
              if ( PSEgetLibType() == 2 )
              {
                v21 = SendDlgItemMessageA(hDlg, 1017, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, 1017, 0x14Eu, v21, 0);
                v22 = dword_45B8E4;
                if ( v21 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v24 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName];
                  do
                  {
                    v25 = *cFileName;
                    cFileName[(_DWORD)v24] = *cFileName;
                    ++cFileName;
                  }
                  while ( v25 );
                }
                else
                {
                  if ( v21 < dword_45B8E4 )
                  {
                    v26 = &byte_8A9140[1024 * dword_45B8E4];
                    v27 = dword_45B8E4 - v21;
                    do
                    {
                      v28 = v26;
                      do
                      {
                        v29 = *v28;
                        v28[1024] = *v28;
                        ++v28;
                      }
                      while ( v29 );
                      v26 -= 1024;
                      --v27;
                    }
                    while ( v27 );
                  }
                  v30 = (v21 << 10) - (_DWORD)FindFileData.cFileName;
                  v31 = FindFileData.cFileName;
                  do
                  {
                    v32 = *v31;
                    byte_8A9540[v30 + (_DWORD)v31] = *v31;
                    ++v31;
                  }
                  while ( v32 );
                }
                dword_45B8E4 = v22 + 1;
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
      case 1018:
        if ( !dword_45B8E4 )
          return 0;
        v8 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
        if ( v8 == -1 || v8 >= dword_45B8E4 )
          return 0;
        sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v8]);
        v9 = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(v9, "GPUinit");
        GPUtest_0 = GetProcAddress(v9, "GPUtest");
        GPUshutdown_0 = GetProcAddress(v9, "GPUshutdown");
        GPUinit_0();
        v10 = GPUtest_0();
        if ( v10 )
        {
          if ( v10 == -1 )
            MessageBoxA(nullptr, "   Plugin NOT working, try configuring it.  ", "Testing GPU Plugin", 0x10u);
          else
            MessageBoxA(nullptr, "UNK value", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          result = 0;
        }
        else
        {
          MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing GPU Plugin", 0x40u);
          GPUshutdown_0();
          result = 0;
        }
        break;
      case 1019:
        if ( !dword_45B8E4 )
          return 0;
        v11 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
        if ( v11 == -1 || v11 >= dword_45B8E4 )
          return 0;
        sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v11]);
        v12 = LoadLibraryA(LibFileName);
        GPUinit_0 = GetProcAddress(v12, "GPUinit");
        PSEconfigure = GetProcAddress(v12, "GPUconfigure");
        GPUshutdown_0 = GetProcAddress(v12, "GPUshutdown");
        GPUinit_0();
        PSEconfigure();
        GPUshutdown_0();
        result = 0;
        break;
      case 1020:
        if ( dword_45B8E4 )
        {
          v13 = SendDlgItemMessageA(hDlg, 1017, CB_GETCURSEL, 0, 0);
          if ( v13 != -1 && v13 < dword_45B8E4 )
          {
            sprintf(LibFileName, "%s%s", v35, &byte_8A9540[1024 * v13]);
            v14 = LoadLibraryA(LibFileName);
            GPUinit_0 = GetProcAddress(v14, "GPUinit");
            GPUabout_0 = GetProcAddress(v14, "GPUabout");
            GPUshutdown_0 = GetProcAddress(v14, "GPUshutdown");
            GPUinit_0();
            GPUabout_0();
            GPUshutdown_0();
          }
        }
        return 0;
      case 1021:
        if ( dword_45B8E4 )
        {
          v7 = SendDlgItemMessageA(hDlg, 1017, 0x147u, 0, 0);
          if ( v7 != -1 && v7 < dword_45B8E4 )
            sprintf((char *const)VideoPlugin, "%s", &byte_8A9540[1024 * v7]);
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
          EndDialog(hDlg, 1);
          cfg_save_settings();
          result = 1;
        }
        break;
      case 1022:
        if ( dword_45B8E4 )
        {
          EndDialog(hDlg, 1);
        }
        else
        {
          sprintf((char *const)VideoPlugin, "NULL");
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
