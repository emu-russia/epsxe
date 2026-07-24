#include "pch.h"
HANDLE setup_wizard_init()
{
  HANDLE FirstFileA; // edi
  HANDLE v1; // edi
  HANDLE result; // eax
  HANDLE v3; // edi
  char v4[12]; // [esp+10h] [ebp-94Ch] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+1Ch] [ebp-940h] BYREF
  CHAR FileName[1024]; // [esp+15Ch] [ebp-800h] BYREF
  CHAR NewFileName[1024]; // [esp+55Ch] [ebp-400h] BYREF

  strcpy(v4, "plugins\\");
  FileName[0] = byte_45B8CC;
  strcat(FileName, "gpu*.dll");
  FirstFileA = FindFirstFileA(FileName, &FindFileData);
  if ( FirstFileA != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(FirstFileA, &FindFileData) );
  }
  FileName[0] = byte_45B8CC;
  strcat(FileName, "spu*.dll");
  v1 = FindFirstFileA(FileName, &FindFileData);
  if ( v1 != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(v1, &FindFileData) );
  }
  FileName[0] = byte_45B8CC;
  strcat(FileName, "cdr*.dll");
  result = FindFirstFileA(FileName, &FindFileData);
  v3 = result;
  if ( result != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", v4, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
      result = (HANDLE)FindNextFileA(v3, &FindFileData);
    }
    while ( result );
  }
  return result;
}

INT_PTR __stdcall setup_wizard_search_bios(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  int v8; // ebx
  FILE *v9; // edi
  uint8_t *v10; // esi
  int v11; // edi
  uint32_t v12; // eax
  _BIOS_DESCR *v13; // ecx
  LRESULT v14; // eax
  int v15; // ebp
  char *v16; // eax
  char *v17; // edx
  char v18; // cl
  char *v19; // edi
  int v20; // ebx
  char *v21; // ecx
  char v22; // dl
  char *v23; // ecx
  char *v24; // edx
  char v25; // al
  char v26[8]; // [esp+0h] [ebp-D4Ch] BYREF
  HANDLE hFindFile; // [esp+8h] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+Ch] [ebp-D40h] BYREF
  char Buffer[1024]; // [esp+14Ch] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+54Ch] [ebp-800h] BYREF
  char lParam[1024]; // [esp+94Ch] [ebp-400h] BYREF

  strcpy(v26, "bios\\");
  v4 = 0;
  do
  {
    v5 = v26[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.bin");
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 != 272 )
  {
    if ( a2 == 273 )
    {
      if ( (unsigned __int16)a3 == 1107 )
      {
        --setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      if ( (unsigned __int16)a3 == 1108 )
      {
        v6 = SendDlgItemMessageA(hDlg, 1106, 0x188u, 0, 0);
        if ( v6 != -1 && v6 < dword_45B8E4 )
        {
          sprintf(byte_8A90C0, "%s", &byte_8A9540[1024 * v6]);
          ++setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        }
        MessageBoxA(
          nullptr,
          "ePSXe detected that you haven't selected a psx BIOS. Please, select some of the recommended psx BIOS and hit next button",
          "BIOS not selected",
          0x10u);
      }
    }
    return 0;
  }
  hFindFile = FindFirstFileA(FileName, &FindFileData);
  if ( hFindFile == (HANDLE)-1 )
    MessageBoxA(
      nullptr,
      "ePSXe wasn't able to find a psx bios in your epsxe\\bios directory. If you don't have a psx bios, enter either scp"
      "h1001.bin or scph7502 into your favorite internet search engine - but keep in mind that you can only have this fil"
      "e LEGALLY when you own a REAL Playstation",
      "psx bios not found",
      0x10u);
  dword_45B8E4 = 0;
  do
  {
    sprintf(Buffer, "%s%s", v26, FindFileData.cFileName);
    v8 = -1;
    v9 = fopen(Buffer, "rb");
    if ( v9 )
    {
      v10 = (uint8_t *)malloc(0x80000u);
      fread(v10, 0x80000u, 1u, v9);
      fclose(v9);
      v11 = calc_bios_checksum(v10, 0x80000);
      free(v10);
      v12 = 0;
      if ( debug_bios.crc )
      {
        v13 = retail_bioses;
        do
        {
          if ( v11 == v13->crc )
            v8 = v12;
          ++v12;
          ++v13;
        }
        while ( v12 < debug_bios.crc );
        if ( v8 != -1 )
        {
          sprintf(lParam, "%s", (const char *)(36 * v8 + 4513104));
          v14 = SendDlgItemMessageA(hDlg, 1106, 0x180u, 0, (LPARAM)lParam);
          v15 = dword_45B8E4;
          if ( v14 == dword_45B8E4 )
          {
            v16 = Buffer;
            v17 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)Buffer];
            do
            {
              v18 = *v16;
              v16[(_DWORD)v17] = *v16;
              ++v16;
            }
            while ( v18 );
          }
          else
          {
            if ( v14 < dword_45B8E4 )
            {
              v19 = &byte_8A9140[1024 * dword_45B8E4];
              v20 = dword_45B8E4 - v14;
              do
              {
                v21 = v19;
                do
                {
                  v22 = *v21;
                  v21[1024] = *v21;
                  ++v21;
                }
                while ( v22 );
                v19 -= 1024;
                --v20;
              }
              while ( v20 );
            }
            v23 = Buffer;
            v24 = &byte_8A9540[(v14 << 10) - (_DWORD)Buffer];
            do
            {
              v25 = *v23;
              v23[(_DWORD)v24] = *v23;
              ++v23;
            }
            while ( v25 );
          }
          dword_45B8E4 = v15 + 1;
        }
      }
    }
  }
  while ( FindNextFileA(hFindFile, &FindFileData) );
  if ( dword_45B8E4 == 1 )
  {
    SendDlgItemMessageA(hDlg, 1106, 0x186u, 0, 0);
    return 1;
  }
  return 1;
}

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

INT_PTR __stdcall setup_wizard_search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  LRESULT v8; // eax
  unsigned int v9; // eax
  const char *v10; // eax
  HMODULE v11; // eax
  unsigned int v12; // eax
  const char *v13; // eax
  HMODULE v14; // esi
  unsigned int v15; // eax
  const char *v16; // eax
  HMODULE v17; // eax
  LRESULT v18; // eax
  int v19; // eax
  LRESULT v20; // eax
  int v21; // eax
  HMODULE LibraryA; // eax
  HMODULE v23; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v25; // al
  int v26; // eax
  const char *v27; // eax
  LRESULT v28; // ebp
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
  LRESULT v40; // eax
  int i; // esi
  LRESULT v42; // eax
  int v43; // [esp-18h] [ebp-11FCh]
  int v44; // [esp-14h] [ebp-11F8h]
  char v45[12]; // [esp+0h] [ebp-11E4h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-11D8h]
  struct _OSVERSIONINFOA VersionInformation; // [esp+10h] [ebp-11D4h] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+A4h] [ebp-1140h] BYREF
  CHAR lParam[1024]; // [esp+1E4h] [ebp-1000h] BYREF
  CHAR LibFileName[1024]; // [esp+5E4h] [ebp-C00h] BYREF
  char v51[1024]; // [esp+9E4h] [ebp-800h] BYREF
  CHAR FileName[1024]; // [esp+DE4h] [ebp-400h] BYREF

  strcpy(v45, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v45[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.dll");
  switch ( a2 )
  {
    case 0x10u:
      setup_wizard_step = 8;
      EndDialog(hDlg, 1);
      break;
    case 0x110u:
      hFindFile = FindFirstFileA(FileName, &FindFileData);
      dword_45B8E4 = 0;
      sprintf(v51, "ePSXe CDR ASPI core 1.5.2.");
      v18 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
      if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
        SendDlgItemMessageA(hDlg, 1119, 0x186u, v18, 0);
      v19 = dword_45B8E4;
      strcpy(&byte_8A9540[1024 * dword_45B8E4], "W9XCDRCORE");
      dword_45B8E4 = v19 + 1;
      memset(&VersionInformation, 0, sizeof(VersionInformation));
      VersionInformation.dwOSVersionInfoSize = 148;
      GetVersionExA(&VersionInformation);
      if ( VersionInformation.dwPlatformId == 2 )
      {
        sprintf(v51, "ePSXe CDR WNT/W2K core 1.5.2.");
        v20 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
        if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
          SendDlgItemMessageA(hDlg, 1119, 0x186u, v20, 0);
        v21 = dword_45B8E4;
        strcpy(&byte_8A9540[1024 * dword_45B8E4], "W2KCDRCORE");
        dword_45B8E4 = v21 + 1;
      }
      do
      {
        sprintf(LibFileName, "%s%s", v45, FindFileData.cFileName);
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
                sprintf(v51, "%s %d.%d", v27, v43, v44);
                if ( PSEgetLibType() == 1 )
                {
                  v28 = SendDlgItemMessageA(hDlg, 1119, 0x180u, 0, (LPARAM)v51);
                  if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                    SendDlgItemMessageA(hDlg, 1119, 0x186u, v28, 0);
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
                }
              }
            }
          }
        }
      }
      while ( FindNextFileA(hFindFile, &FindFileData) );
      sprintf(lParam, "FirstCdrom");
      v40 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
      if ( !cdrom_letter )
        SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v40, 0);
      for ( i = 65; i <= 90; ++i )
      {
        sprintf(lParam, "%c:\\", i);
        if ( GetDriveTypeA(lParam) == 5 )
        {
          sprintf(lParam, "--%c:--", i);
          v42 = SendDlgItemMessageA(hDlg, 1113, 0x143u, 0, (LPARAM)lParam);
          if ( i == cdrom_letter )
            SendDlgItemMessageA(hDlg, 1113, 0x14Eu, v42, 0);
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
          v12 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v12 == -1 || v12 >= dword_45B8E4 )
            return 0;
          v13 = &byte_8A9540[1024 * v12];
          byte_8A94C0 = 1;
          if ( !strcmp(v13, "W9XCDRCORE") )
          {
            DialogBoxParamA(g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
            return 0;
          }
          if ( !strcmp(v13, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", v45, v13);
          v14 = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(v14, "CDRinit");
          GPUinit_0();
          PSEconfigure = GetProcAddress(v14, "CDRconfigure");
          PSEconfigure();
          return 0;
        case 1121:
          v9 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v9 == -1 )
            return 0;
          if ( v9 >= dword_45B8E4 )
            return 0;
          v10 = &byte_8A9540[1024 * v9];
          if ( !strcmp(v10, "W9XCDRCORE") || !strcmp(v10, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", v45, v10);
          v11 = LoadLibraryA(LibFileName);
          GPUtest_0 = GetProcAddress(v11, "CDRtest");
          GPUtest_0();
          return 0;
        case 1122:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case 1123:
          v6 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v6 == -1 || v6 >= dword_45B8E4 )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that you haven't selected a CDROM plugin. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not selected",
              0x10u);
            return 0;
          }
          if ( !byte_8A94C0 && strcmp(&byte_8A9540[1024 * v6], "W2KCDRCORE") )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that CDROM plugin hasn't been configured. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not configured",
              0x10u);
            return 0;
          }
          sprintf(byte_8A8CC0, "%s", &byte_8A9540[1024 * v6]);
          ++setup_wizard_step;
          v8 = SendDlgItemMessageA(hDlg, 1062, 0x147u, 0, 0);
          if ( v8 != -1 )
          {
            SendDlgItemMessageA(hDlg, 1062, 0x148u, v8, (LPARAM)lParam);
            if ( strncmp(lParam, "FirstCdrom", 4u) )
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
          v15 = SendDlgItemMessageA(hDlg, 1119, 0x188u, 0, 0);
          if ( v15 != -1 && v15 < dword_45B8E4 )
          {
            v16 = &byte_8A9540[1024 * v15];
            if ( strcmp(v16, "W9XCDRCORE") )
            {
              if ( strcmp(v16, "W2KCDRCORE") )
              {
                sprintf(LibFileName, "%s%s", v45, v16);
                v17 = LoadLibraryA(LibFileName);
                GPUabout_0 = GetProcAddress(v17, "CDRabout");
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

INT_PTR __stdcall setup_wizard_controllers(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  HDC DC; // esi
  int DeviceCaps; // ebx
  HDC v7; // esi
  int v8; // ebx

  switch ( a2 )
  {
    case 0x10u:
      setup_wizard_step = 8;
LABEL_16:
      EndDialog(hDlg, 1);
      return 1;
    case 0x110u:
      return 1;
    case 0x111u:
      switch ( (__int16)a3 )
      {
        case 1115:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case 1116:
          ++setup_wizard_step;
          goto LABEL_16;
        case 1117:
          pad_number_menu_selection = 1;
          DC = GetDC(hDlg);
          DeviceCaps = GetDeviceCaps(DC, 88);
          ReleaseDC(hDlg, DC);
          if ( DeviceCaps > 96 )
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          else
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
          return 0;
        case 1118:
          pad_number_menu_selection = 2;
          v7 = GetDC(hDlg);
          v8 = GetDeviceCaps(v7, 88);
          ReleaseDC(hDlg, v7);
          if ( v8 <= 96 )
          {
            DialogBoxParamA(g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
            return 0;
          }
          DialogBoxParamA(g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          break;
        default:
          return 0;
      }
      break;
  }
  return 0;
}

INT_PTR __stdcall setup_wizard_end(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
    return 1;
  if ( a2 != 273 || (_WORD)a3 != 1114 )
    return 0;
  ++setup_wizard_step;
  EndDialog(hDlg, 1);
  return 1;
}

INT_PTR __stdcall setup_wizard_begin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
    return 1;
  if ( a2 != 273 )
    return 0;
  if ( (unsigned __int16)a3 == 1109 )
  {
    --setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
  else
  {
    if ( (unsigned __int16)a3 != 1110 )
      return 0;
    ++setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
}

int __cdecl setup_wizard_callback(HWND hWndParent)
{
  int result; // eax

  byte_8A94C0 = 0;
  while ( 2 )
  {
    result = setup_wizard_step;
    switch ( setup_wizard_step )
    {
      case 0:
        setup_wizard_init();
        DialogBoxParamA(g_hInstance, "IDD_INSTALL", hWndParent, setup_wizard_begin, 0);
        continue;
      case 1:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_BIOS", hWndParent, setup_wizard_search_bios, 0);
        continue;
      case 2:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_GPU", hWndParent, setup_wizard_search_video_plugin, 0);
        continue;
      case 3:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_SPU", hWndParent, setup_wizard_search_spu_plugin, 0);
        continue;
      case 4:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_CDROM", hWndParent, setup_wizard_search_cdrom_plugin, 0);
        continue;
      case 5:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_PAD", hWndParent, setup_wizard_controllers, 0);
        continue;
      case 6:
        DialogBoxParamA(g_hInstance, "IDD_INSTALL_END", hWndParent, setup_wizard_end, 0);
        continue;
      case 7:
        sprintf((char *const)VideoPlugin, "%s", byte_8A84C0);
        sprintf((char *const)SoundPlugin, "%s", byte_8A88C0);
        sprintf((char *const)CdromPlugin, "%s", byte_8A8CC0);
        sprintf((char *const)bios_name, "%s", byte_8A90C0);
        result = cfg_save_settings();
        break;
      default:
        return result;
    }
    break;
  }
  return result;
}