#include "pch.h"
INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v5; // eax
  char v6; // cl
  CHAR *v7; // edi
  __int16 v8; // cx
  INT_PTR result; // eax
  unsigned int v10; // eax
  unsigned int v11; // eax
  const char *v12; // eax
  HMODULE v13; // eax
  char v14; // al
  unsigned int v15; // eax
  const char *v16; // eax
  HMODULE v17; // eax
  unsigned int v18; // eax
  const char *v19; // eax
  HMODULE v20; // eax
  HWND v21; // ebx
  LRESULT (__stdcall *v22)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v23; // eax
  int v24; // eax
  HMODULE LibraryA; // eax
  HMODULE v26; // esi
  FARPROC PSEgetLibVersion_ptr; // eax
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
  int v43; // [esp-18h] [ebp-D68h]
  int v44; // [esp-14h] [ebp-D64h]
  char v45[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v45, "plugins\\");
  v5 = 0;
  do
  {
    v6 = v45[v5];
    FileName[v5++] = v6;
  }
  while ( v6 );
  v7 = &FileName[strlen(FileName) + 1];
  v8 = MEMORY[0x44E400];
  *(_DWORD *)--v7 = aDll;
  *((_WORD *)v7 + 2) = v8;
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print(aNotNetPluginsF);
    dword_45B8E4 = 0;
    sprintf(lParam, aDisabledNetpla);
    v21 = hDlg;
    v22 = SendDlgItemMessageA;
    v23 = SendDlgItemMessageA(hDlg, 1104, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)NetPlugin, "DISABLED") )
      SendDlgItemMessageA(hDlg, 1104, 0x14Eu, v23, 0);
    v24 = dword_45B8E4;
    strcpy(&byte_8A9540[1024 * dword_45B8E4], "DISABLED");
    dword_45B8E4 = v24 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v45, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v26 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v26, aPsegetlibname);
        PSEgetLibVersion_ptr = GetProcAddress(v26, aPsegetlibversi);
        PSEgetLibVersion = (int (__cdecl *)(_DWORD))PSEgetLibVersion_ptr;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion_ptr )
            {
              v28 = PSEgetLibVersion_ptr();
              v29 = PSEgetLibVersion(v28);
              v30 = (const char *)PSEgetLibName(BYTE1(v29));
              sprintf(lParam, "%s %d.%d", v30, v43, v44);
              if ( PSEgetLibType() == 16 )
              {
                v31 = v22(v21, 1104, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)NetPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v21, 1104, 0x14Eu, v31, 0);
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
                dword_45B8E4 = v32 + 1;
                v21 = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      v22 = SendDlgItemMessageA;
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
        v11 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
        if ( v11 == -1 )
          return 0;
        if ( v11 >= dword_45B8E4 )
          return 0;
        v12 = &byte_8A9540[1024 * v11];
        if ( !strcmp(v12, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v45, v12);
        v13 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v13, aNettest);
        v14 = GPUtest_0();
        if ( v14 )
        {
          if ( v14 == -1 )
            MessageBoxA(nullptr, aPluginNotWorki, aTestingNetPlug, 0x10u);
          else
            MessageBoxA(nullptr, aUnkValue, aTestingNetPlug, 0x40u);
          result = 0;
        }
        else
        {
          MessageBoxA(nullptr, aPluginWorkingC, aTestingNetPlug, 0x40u);
          result = 0;
        }
        break;
      case 1100:
        if ( !dword_45B8E4 )
          return 0;
        v15 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
        if ( v15 == -1 )
          return 0;
        if ( v15 >= dword_45B8E4 )
          return 0;
        v16 = &byte_8A9540[1024 * v15];
        if ( !strcmp(v16, "DISABLED") )
          return 0;
        sprintf(LibFileName, "%s%s", v45, v16);
        v17 = LoadLibraryA(LibFileName);
        GPUconfigure_0 = GetProcAddress(v17, aNetconfigure);
        GPUconfigure_0();
        result = 0;
        break;
      case 1101:
        if ( dword_45B8E4 )
        {
          v18 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v18 != -1 && v18 < dword_45B8E4 )
          {
            v19 = &byte_8A9540[1024 * v18];
            if ( strcmp(v19, "DISABLED") )
            {
              sprintf(LibFileName, "%s%s", v45, v19);
              v20 = LoadLibraryA(LibFileName);
              GPUabout_0 = GetProcAddress(v20, aNetabout);
              GPUabout_0();
            }
          }
        }
        return 0;
      case 1102:
        if ( dword_45B8E4 )
        {
          v10 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
          if ( v10 != -1 && v10 < dword_45B8E4 )
            sprintf((char *const)NetPlugin, "%s", &byte_8A9540[1024 * v10]);
          EndDialog(hDlg, 1);
          save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)NetPlugin, "NULL");
          EndDialog(hDlg, 1);
          save_settings();
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
          save_settings();
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
