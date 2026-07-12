#include "pch.h"
INT_PTR __stdcall setup_wizard_search_spu_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
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
  HMODULE v13; // eax
  unsigned int v14; // eax
  const char *v15; // eax
  HMODULE v16; // eax
  HWND v17; // ebx
  LRESULT (__stdcall *v18)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v19; // eax
  int v20; // eax
  int v21; // ecx
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion; // eax
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
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, "ePSXe SPU core 1.5.2.");
    v17 = hDlg;
    v18 = SendDlgItemMessageA;
    v19 = SendDlgItemMessageA(hDlg, 1129, LB_ADDSTRING, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)SoundPlugin, "SPUCORE") )
      SendDlgItemMessageA(hDlg, 1129, LB_SETCURSEL, v19, 0);
    v20 = dword_45B8E4;
    v21 = dword_45B8E4 << 10;
    *(_DWORD *)&byte_8A9540[v21] = *(_DWORD *)"SPUCORE";
    strcpy(&byte_8A9544[v21], "ORE");
    dword_45B8E4 = v20 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v42, FindFileData.cFileName);
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
              sprintf(lParam, "%s %d.%d", v27, v40, v41);
              if ( PSEgetLibType() == 4 )
              {
                v28 = v18(v17, 1129, 0x180u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)SoundPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v17, 1129, 0x186u, v28, 0);
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
                v17 = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      v18 = SendDlgItemMessageA;
    }
    if ( dword_45B8E4 == 1 )
    {
      SendDlgItemMessageA(v17, 1129, LB_SETCURSEL, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( a2 != 273 )
    return 0;
  switch ( (__int16)a3 )
  {
    case 1111:
      v11 = SendDlgItemMessageA(hDlg, 1129, LB_GETCURSEL, 0, 0);
      if ( v11 == -1 || v11 >= dword_45B8E4 )
        return 0;
      v12 = &byte_8A9540[1024 * v11];
      if ( !strcmp(v12, "SPUCORE") )
      {
        DialogBoxParamA(g_hInstance, "IDD_SOUND9X", hDlg, spucore_configure_dialog_callback, 0);
      }
      else
      {
        sprintf(LibFileName, "%s%s", v42, v12);
        v13 = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(v13, "SPUconfigure");
        PSEconfigure();
      }
      return 0;
    case 1112:
      v8 = SendDlgItemMessageA(hDlg, 1129, LB_GETCURSEL, 0, 0);
      if ( v8 == -1 )
        return 0;
      if ( v8 >= dword_45B8E4 )
        return 0;
      v9 = &byte_8A9540[1024 * v8];
      if ( !strcmp(v9, "SPUCORE") )
        return 0;
      sprintf(LibFileName, "%s%s", v42, v9);
      v10 = LoadLibraryA(LibFileName);
      GPUtest_0 = GetProcAddress(v10, "SPUtest");
      GPUtest_0();
      return 0;
    case 1113:
      v14 = SendDlgItemMessageA(hDlg, 1129, 0x188u, 0, 0);
      if ( v14 != -1 && v14 < dword_45B8E4 )
      {
        v15 = &byte_8A9540[1024 * v14];
        if ( strcmp(v15, "SPUCORE") )
        {
          sprintf(LibFileName, "%s%s", v42, v15);
          v16 = LoadLibraryA(LibFileName);
          GPUabout_0 = GetProcAddress(v16, "SPUabout");
          GPUabout_0();
        }
      }
      return 0;
    case 1130:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case 1131:
      v6 = SendDlgItemMessageA(hDlg, 1129, 0x188u, 0, 0);
      if ( v6 != -1 && v6 < dword_45B8E4 )
      {
        sprintf(byte_8A88C0, "%s", &byte_8A9540[1024 * v6]);
        ++setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      MessageBoxA(
        nullptr,
        "ePSXe detected that you haven't selected a SPU plugin. Please, select your favourite plugin and hit on config button",
        "SPU plugin not selected",
        0x10u);
      result = 0;
      break;
    default:
      return 0;
  }
  return result;
}
