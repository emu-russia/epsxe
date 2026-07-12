#include "pch.h"
INT_PTR __stdcall setup_wizard_search_video_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  INT_PTR result; // eax
  unsigned int v8; // eax
  HMODULE v9; // esi
  char v10; // al
  unsigned int v11; // eax
  HMODULE v12; // esi
  unsigned int v13; // eax
  HMODULE v14; // esi
  HMODULE LibraryA; // eax
  HMODULE v16; // esi
  FARPROC PSEgetLibVersion; // eax
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
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      MessageBoxA(
        nullptr,
        "ePSXe wasn't able to find a GPU plugin in your epsxe\\plugins directory. Take a look at the list of recommended "
        "plugins and download the latest version from pages like www.psxemu.com or www.emulatronia.com",
        "GPU plugin not found",
        0x10u);
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
        PSEgetLibVersion = GetProcAddress(v16, "PSEgetLibVersion");
        ::PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v18 = PSEgetLibVersion();
              v19 = ::PSEgetLibVersion(v18);
              v20 = (const char *)PSEgetLibName(BYTE1(v19));
              sprintf(lParam, "%s %d.%d", v20, v33, v34);
              if ( PSEgetLibType() == 2 )
              {
                v21 = SendDlgItemMessageA(hDlg, 1124, 0x180u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, 1124, 0x186u, v21, 0);
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
    if ( dword_45B8E4 == 1 )
    {
      SendDlgItemMessageA(hDlg, 1124, 0x186u, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( a2 != 273 )
    return 0;
  switch ( (__int16)a3 )
  {
    case 1125:
      if ( !dword_45B8E4 )
        return 0;
      v11 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
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
      return 0;
    case 1126:
      if ( !dword_45B8E4 )
        return 0;
      v8 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
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
        return 0;
      }
      else
      {
        MessageBoxA(nullptr, "   Plugin working correctly.  ", "Testing GPU Plugin", 0x40u);
        GPUshutdown_0();
        return 0;
      }
    case 1127:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case 1128:
      if ( !dword_45B8E4 )
        return 1;
      v6 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
      if ( v6 != -1 && v6 < dword_45B8E4 )
      {
        sprintf(byte_8A84C0, "%s", &byte_8A9540[1024 * v6]);
        ++setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      MessageBoxA(
        nullptr,
        "ePSXe detected that you haven't selected a GPU plugin. Please, select your favourite plugin and hit on config button",
        "GPU plugin not selected",
        0x10u);
      result = 0;
      break;
    case 1129:
      if ( dword_45B8E4 )
      {
        v13 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
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
    default:
      return 0;
  }
  return result;
}
