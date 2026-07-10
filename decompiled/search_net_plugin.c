#include "pch.h"
INT_PTR __userpurge sub_406510@<eax>(char a1@<dil>, HWND hDlg, UINT a3, WPARAM a4, LPARAM a5)
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
  CHAR v42; // cl
  int v43; // [esp-18h] [ebp-D68h]
  int v44; // [esp-14h] [ebp-D64h]
  char v46[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v46, "plugins\\");
  v5 = 0;
  do
  {
    v6 = v46[v5];
    FileName[v5++] = v6;
  }
  while ( v6 );
  v7 = &FileName[strlen(FileName) + 1];
  v8 = word_44E400;
  *(_DWORD *)--v7 = dword_44E3FC;
  *((_WORD *)v7 + 2) = v8;
  if ( a3 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      dbg_print(aNotNetPluginsF, a1);
    dword_45B8E4 = 0;
    sprintf(lParam, aDisabledNetpla);
    v21 = hDlg;
    v22 = SendDlgItemMessageA;
    v23 = SendDlgItemMessageA(hDlg, 1104, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)&byte_8B4180, aDisabled) )
      SendDlgItemMessageA(hDlg, 1104, 0x14Eu, v23, 0);
    v24 = dword_45B8E4;
    strcpy((char *)&byte_8A9540[256 * dword_45B8E4], "DISABLED");
    dword_45B8E4 = v24 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v46, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v26 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v26, aPsegetlibname);
        PSEgetLibVersion = GetProcAddress(v26, aPsegetlibversi);
        unk_8A94C4 = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v28 = PSEgetLibVersion();
              v29 = unk_8A94C4(v28);
              v30 = (const char *)PSEgetLibName(BYTE1(v29));
              sprintf(lParam, "%s %d.%d", v30, v43, v44);
              if ( PSEgetLibType() == 16 )
              {
                v31 = v22(v21, 1104, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)&byte_8B4180, FindFileData.cFileName) )
                  SendDlgItemMessageA(v21, 1104, 0x14Eu, v31, 0);
                v32 = dword_45B8E4;
                if ( v31 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v34 = (char *)byte_8A9540 + (dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName;
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
                    v36 = (char *)&byte_8A9140 + 1024 * dword_45B8E4;
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
                    v41[(_DWORD)byte_8A9540 + v40] = *v41;
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
  else if ( a3 == 273 )
  {
    switch ( (__int16)a4 )
    {
      case 1099:
        if ( !dword_45B8E4 )
          return 0;
        v11 = SendDlgItemMessageA(hDlg, 1104, 0x147u, 0, 0);
        if ( v11 == -1 )
          return 0;
        if ( v11 >= dword_45B8E4 )
          return 0;
        v12 = (const char *)&byte_8A9540[256 * v11];
        if ( !strcmp(v12, aDisabled) )
          return 0;
        sprintf(LibFileName, "%s%s", v46, v12);
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
        v16 = (const char *)&byte_8A9540[256 * v15];
        if ( !strcmp(v16, aDisabled) )
          return 0;
        sprintf(LibFileName, "%s%s", v46, v16);
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
            v19 = (const char *)&byte_8A9540[256 * v18];
            if ( strcmp(v19, aDisabled) )
            {
              sprintf(LibFileName, "%s%s", v46, v19);
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
            sprintf((char *const)&byte_8B4180, "%s", (const char *)&byte_8A9540[256 * v10]);
          EndDialog(hDlg, 1);
          save_settings();
          result = 1;
        }
        else
        {
          sprintf((char *const)&byte_8B4180, aNull);
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
          sprintf((char *const)&byte_8B4180, aNull);
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
