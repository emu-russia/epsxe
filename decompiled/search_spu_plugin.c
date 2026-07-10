#include "pch.h"
INT_PTR __stdcall sub_407780(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
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
  HMODULE v15; // eax
  unsigned int v16; // eax
  const char *v17; // eax
  HMODULE v18; // eax
  HWND v19; // ebx
  LRESULT (__stdcall *v20)(HWND, int, UINT, WPARAM, LPARAM); // ebp
  LRESULT v21; // eax
  int v22; // eax
  int v23; // ecx
  HMODULE LibraryA; // eax
  HMODULE v25; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v27; // al
  int v28; // eax
  const char *v29; // eax
  signed int v30; // ebp
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
  int v42; // [esp-18h] [ebp-D68h]
  int v43; // [esp-14h] [ebp-D64h]
  char v44[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  char lParam[1024]; // [esp+550h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v44, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v44[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  v6 = &FileName[strlen(FileName) + 1];
  v7 = word_44E400;
  *(_DWORD *)--v6 = dword_44E3FC;
  *((_WORD *)v6 + 2) = v7;
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    dword_45B8E4 = 0;
    sprintf(lParam, aEpsxeSpuCore15);
    v19 = hDlg;
    v20 = SendDlgItemMessageA;
    v21 = SendDlgItemMessageA(hDlg, 1010, 0x143u, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)&byte_8B1D80, aSpucore) )
      SendDlgItemMessageA(hDlg, 1010, 0x14Eu, v21, 0);
    v22 = dword_45B8E4;
    v23 = dword_45B8E4 << 10;
    *(int *)((char *)byte_8A9540 + v23) = *(_DWORD *)aSpucore;
    *(int *)((char *)&unk_8A9544 + v23) = *(_DWORD *)&aSpucore[4];
    dword_45B8E4 = v22 + 1;
    do
    {
      sprintf(LibFileName, "%s%s", v44, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v25 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v25, aPsegetlibname);
        PSEgetLibVersion = GetProcAddress(v25, aPsegetlibversi);
        unk_8A94C4 = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v27 = PSEgetLibVersion();
              v28 = unk_8A94C4(v27);
              v29 = (const char *)PSEgetLibName(BYTE1(v28));
              sprintf(lParam, "%s %d.%d", v29, v42, v43);
              if ( PSEgetLibType() == 4 )
              {
                v30 = v20(v19, 1010, 0x143u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)&byte_8B1D80, FindFileData.cFileName) )
                  SendDlgItemMessageA(v19, 1010, 0x14Eu, v30, 0);
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
                v20 = SendDlgItemMessageA;
                dword_45B8E4 = v31 + 1;
                v19 = hDlg;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    v20(v19, 1005, 0xF1u, (unsigned __int8)sound_enabled, 0);
    v20(v19, 1006, 0xF1u, (unsigned __int8)sound_use_xa, 0);
    v20(v19, 1009, 0xF1u, (unsigned __int8)sound_use_cdda, 0);
    v20(v19, 1030, 0xF1u, (unsigned __int8)forcespu, 0);
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( (__int16)a3 )
    {
      case 1011:
        v10 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v10 == -1 )
          return 0;
        if ( v10 >= dword_45B8E4 )
          return 0;
        v11 = (const char *)&byte_8A9540[256 * v10];
        if ( !strcmp(v11, aSpucore) )
          return 0;
        sprintf(LibFileName, "%s%s", v44, v11);
        v12 = LoadLibraryA(LibFileName);
        GPUtest_0 = GetProcAddress(v12, aSputest);
        GPUtest_0();
        result = 0;
        break;
      case 1012:
        v13 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v13 == -1 || v13 >= dword_45B8E4 )
          return 0;
        v14 = (const char *)&byte_8A9540[256 * v13];
        if ( !strcmp(v14, aSpucore) )
        {
          DialogBoxParamA(g_hInstance, aIddSound9x, hDlg, spucore_configure_dialog_callback, 0);
        }
        else
        {
          sprintf(LibFileName, "%s%s", v44, v14);
          v15 = LoadLibraryA(LibFileName);
          GPUconfigure_0 = GetProcAddress(v15, aSpuconfigure);
          GPUconfigure_0();
        }
        result = 0;
        break;
      case 1013:
        v16 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v16 != -1 && v16 < dword_45B8E4 )
        {
          v17 = (const char *)&byte_8A9540[256 * v16];
          if ( strcmp(v17, aSpucore) )
          {
            sprintf(LibFileName, "%s%s", v44, v17);
            v18 = LoadLibraryA(LibFileName);
            GPUabout_0 = GetProcAddress(v18, aSpuabout);
            GPUabout_0();
          }
        }
        return 0;
      case 1014:
        v8 = SendDlgItemMessageA(hDlg, 1010, 0x147u, 0, 0);
        if ( v8 != -1 && v8 < dword_45B8E4 )
          sprintf((char *const)&byte_8B1D80, "%s", (const char *)&byte_8A9540[256 * v8]);
        sound_enabled = SendDlgItemMessageA(hDlg, 1005, 0xF0u, 0, 0);
        sound_use_xa = SendDlgItemMessageA(hDlg, 1006, 0xF0u, 0, 0);
        sound_use_cdda = SendDlgItemMessageA(hDlg, 1009, 0xF0u, 0, 0);
        forcespu = SendDlgItemMessageA(hDlg, 1030, 0xF0u, 0, 0);
        EndDialog(hDlg, 1);
        save_settings();
        result = 1;
        break;
      case 1015:
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
