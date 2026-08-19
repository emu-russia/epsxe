#include "pch.h"

static HANDLE setup_wizard_init()
{
  HANDLE FirstFileA;
  HANDLE v1;
  HANDLE result;
  HANDLE v3;
  char v4[12];
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR FileName[1024];
  CHAR NewFileName[1024];

  strcpy(v4, "plugins\\");
  FileName[0] = current_dir_path;
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
  FileName[0] = current_dir_path;
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
  FileName[0] = current_dir_path;
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

static INT_PTR __stdcall setup_wizard_search_bios(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4;
  char v5;
  unsigned int v6;
  int v8;
  FILE *v9;
  uint8_t *v10;
  int v11;
  uint32_t v12;
  _BIOS_DESCR *v13;
  LRESULT v14;
  int v15;
  char *v16;
  char *v17;
  char v18;
  char *v19;
  int v20;
  char *v21;
  char v22;
  char *v23;
  char *v24;
  char v25;
  char v26[8];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  char Buffer[1024];
  CHAR FileName[1024];
  char lParam[1024];

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
      if ( (uint16_t)a3 == 1107 )
      {
        --setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      if ( (uint16_t)a3 == 1108 )
      {
        v6 = SendDlgItemMessageA(hDlg, IDC_INSTALL_BIOS_LIST, 0x188u, 0, 0);
        if ( v6 != -1 && v6 < found_plugin_count )
        {
          sprintf(bios_search_path, "%s", &plugin_name_list[1024 * v6]);
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
  found_plugin_count = 0;
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
        v13 = &retail_bioses;
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
          v14 = SendDlgItemMessageA(hDlg, IDC_INSTALL_BIOS_LIST, 0x180u, 0, (LPARAM)lParam);
          v15 = found_plugin_count;
          if ( v14 == found_plugin_count )
          {
            v16 = Buffer;
            v17 = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)Buffer];
            do
            {
              v18 = *v16;
              v16[(uint32_t)v17] = *v16;
              ++v16;
            }
            while ( v18 );
          }
          else
          {
            if ( v14 < found_plugin_count )
            {
              v19 = &plugin_name_list_shift[1024 * found_plugin_count];
              v20 = found_plugin_count - v14;
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
            v24 = &plugin_name_list[(v14 << 10) - (uint32_t)Buffer];
            do
            {
              v25 = *v23;
              v23[(uint32_t)v24] = *v23;
              ++v23;
            }
            while ( v25 );
          }
          found_plugin_count = v15 + 1;
        }
      }
    }
  }
  while ( FindNextFileA(hFindFile, &FindFileData) );
  if ( found_plugin_count == 1 )
  {
    SendDlgItemMessageA(hDlg, IDC_INSTALL_BIOS_LIST, 0x186u, 0, 0);
    return 1;
  }
  return 1;
}

static INT_PTR __stdcall setup_wizard_search_video_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4;
  char v5;
  unsigned int v6;
  INT_PTR result;
  unsigned int v8;
  HMODULE v9;
  char v10;
  unsigned int v11;
  HMODULE v12;
  unsigned int v13;
  HMODULE v14;
  HMODULE LibraryA;
  HMODULE v16;
  FARPROC PSEgetLibVersionProc;
  uint8_t v18;
  int v19;
  const char *v20;
  LRESULT v21;
  int v22;
  CHAR *cFileName;
  char *v24;
  CHAR v25;
  char *v26;
  int v27;
  char *v28;
  char v29;
  int v30;
  CHAR *v31;
  char v32;
  int v33;
  int v34;
  char v35[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  CHAR FileName[1024];
  char lParam[1024];

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
    found_plugin_count = 0;
    do
    {
      sprintf(LibFileName, "%s%s", v35, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v16 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(v16, "PSEgetLibName");
        PSEgetLibVersionProc = GetProcAddress(v16, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersionProc )
            {
              v18 = PSEgetLibVersionProc();
              v19 = PSEgetLibVersion(v18);
              v20 = (const char *)PSEgetLibName(BYTE1(v19));
              sprintf(lParam, "%s %d.%d", v20, v33, v34);
              if ( PSEgetLibType() == 2 )
              {
                v21 = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x180u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x186u, v21, 0);
                v22 = found_plugin_count;
                if ( v21 == found_plugin_count )
                {
                  cFileName = FindFileData.cFileName;
                  v24 = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    v25 = *cFileName;
                    cFileName[(uint32_t)v24] = *cFileName;
                    ++cFileName;
                  }
                  while ( v25 );
                }
                else
                {
                  if ( v21 < found_plugin_count )
                  {
                    v26 = &plugin_name_list_shift[1024 * found_plugin_count];
                    v27 = found_plugin_count - v21;
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
                  v30 = (v21 << 10) - (uint32_t)FindFileData.cFileName;
                  v31 = FindFileData.cFileName;
                  do
                  {
                    v32 = *v31;
                    plugin_name_list[v30 + (uint32_t)v31] = *v31;
                    ++v31;
                  }
                  while ( v32 );
                }
                found_plugin_count = v22 + 1;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    if ( found_plugin_count == 1 )
    {
      SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x186u, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( a2 != 273 )
    return 0;
  switch ( (int16_t)a3 )
  {
    case IDC_INSTALL_GPU_CONFIG:
      if ( !found_plugin_count )
        return 0;
      v11 = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( v11 == -1 || v11 >= found_plugin_count )
        return 0;
      sprintf(LibFileName, "%s%s", v35, &plugin_name_list[1024 * v11]);
      v12 = LoadLibraryA(LibFileName);
      GPUinit_0 = GetProcAddress(v12, "GPUinit");
      PSEconfigure = GetProcAddress(v12, "GPUconfigure");
      GPUshutdown_0 = GetProcAddress(v12, "GPUshutdown");
      GPUinit_0();
      PSEconfigure();
      GPUshutdown_0();
      return 0;
    case IDC_INSTALL_GPU_TEST:
      if ( !found_plugin_count )
        return 0;
      v8 = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( v8 == -1 || v8 >= found_plugin_count )
        return 0;
      sprintf(LibFileName, "%s%s", v35, &plugin_name_list[1024 * v8]);
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
    case IDC_INSTALL_GPU_BACK:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case IDC_INSTALL_GPU_NEXT:
      if ( !found_plugin_count )
        return 1;
      v6 = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( v6 != -1 && v6 < found_plugin_count )
      {
        sprintf(video_plugin_search_path, "%s", &plugin_name_list[1024 * v6]);
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
    case IDC_INSTALL_GPU_ABOUT:
      if ( found_plugin_count )
      {
        v13 = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
        if ( v13 != -1 && v13 < found_plugin_count )
        {
          sprintf(LibFileName, "%s%s", v35, &plugin_name_list[1024 * v13]);
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

static INT_PTR __stdcall setup_wizard_search_spu_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4;
  char v5;
  unsigned int v6;
  INT_PTR result;
  unsigned int v8;
  const char *v9;
  HMODULE v10;
  unsigned int v11;
  const char *v12;
  HMODULE v13;
  unsigned int v14;
  const char *v15;
  HMODULE v16;
  HWND v17;
  LRESULT (__stdcall *v18)(HWND, int, UINT, WPARAM, LPARAM);
  LRESULT v19;
  int v20;
  int v21;
  HMODULE LibraryA;
  HMODULE v23;
  FARPROC PSEgetLibVersionProc;
  uint8_t v25;
  int v26;
  const char *v27;
  signed int v28;
  int v29;
  CHAR *cFileName;
  char *v31;
  CHAR v32;
  char *v33;
  int v34;
  char *v35;
  char v36;
  int v37;
  CHAR *v38;
  char v39;
  int v40;
  int v41;
  char v42[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  char lParam[1024];
  CHAR FileName[1024];

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
    found_plugin_count = 0;
    sprintf(lParam, "ePSXe SPU core 1.5.2.");
    v17 = hDlg;
    v18 = SendDlgItemMessageA;
    v19 = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_ADDSTRING, 0, (LPARAM)lParam);
    if ( !strcmp((const char *)SoundPlugin, "SPUCORE") )
      SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_SETCURSEL, v19, 0);
    v20 = found_plugin_count;
    v21 = found_plugin_count << 10;
    *(uint32_t *)&plugin_name_list[v21] = *(uint32_t *)"SPUCORE";
    strcpy(&plugin_name_list_tail[v21], "ORE");
    found_plugin_count = v20 + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", v42, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v23 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(v23, "PSEgetLibName");
        PSEgetLibVersionProc = GetProcAddress(v23, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersionProc )
            {
              v25 = PSEgetLibVersionProc();
              v26 = PSEgetLibVersion(v25);
              v27 = (const char *)PSEgetLibName(BYTE1(v26));
              sprintf(lParam, "%s %d.%d", v27, v40, v41);
              if ( PSEgetLibType() == 4 )
              {
                v28 = v18(v17, IDC_INSTALL_SPU_LIST, 0x180u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)SoundPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(v17, IDC_INSTALL_SPU_LIST, 0x186u, v28, 0);
                v29 = found_plugin_count;
                if ( v28 == found_plugin_count )
                {
                  cFileName = FindFileData.cFileName;
                  v31 = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    v32 = *cFileName;
                    cFileName[(uint32_t)v31] = *cFileName;
                    ++cFileName;
                  }
                  while ( v32 );
                }
                else
                {
                  if ( (unsigned int)v28 < found_plugin_count )
                  {
                    v33 = &plugin_name_list_shift[1024 * found_plugin_count];
                    v34 = found_plugin_count - v28;
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
                  v37 = (v28 << 10) - (uint32_t)FindFileData.cFileName;
                  v38 = FindFileData.cFileName;
                  do
                  {
                    v39 = *v38;
                    plugin_name_list[v37 + (uint32_t)v38] = *v38;
                    ++v38;
                  }
                  while ( v39 );
                }
                found_plugin_count = v29 + 1;
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
    if ( found_plugin_count == 1 )
    {
      SendDlgItemMessageA(v17, IDC_INSTALL_SPU_LIST, LB_SETCURSEL, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( a2 != 273 )
    return 0;
  switch ( (int16_t)a3 )
  {
    case IDC_INSTALL_SPU_CONFIG:
      v11 = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_GETCURSEL, 0, 0);
      if ( v11 == -1 || v11 >= found_plugin_count )
        return 0;
      v12 = &plugin_name_list[1024 * v11];
      if ( !strcmp(v12, "SPUCORE") )
      {
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_SOUND9X", hDlg, spucore_configure_dialog_callback, 0);
      }
      else
      {
        sprintf(LibFileName, "%s%s", v42, v12);
        v13 = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(v13, "SPUconfigure");
        PSEconfigure();
      }
      return 0;
    case IDC_INSTALL_SPU_TEST:
      v8 = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_GETCURSEL, 0, 0);
      if ( v8 == -1 )
        return 0;
      if ( v8 >= found_plugin_count )
        return 0;
      v9 = &plugin_name_list[1024 * v8];
      if ( !strcmp(v9, "SPUCORE") )
        return 0;
      sprintf(LibFileName, "%s%s", v42, v9);
      v10 = LoadLibraryA(LibFileName);
      GPUtest_0 = GetProcAddress(v10, "SPUtest");
      GPUtest_0();
      return 0;
    case IDC_INSTALL_SPU_ABOUT:
      v14 = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, 0x188u, 0, 0);
      if ( v14 != -1 && v14 < found_plugin_count )
      {
        v15 = &plugin_name_list[1024 * v14];
        if ( strcmp(v15, "SPUCORE") )
        {
          sprintf(LibFileName, "%s%s", v42, v15);
          v16 = LoadLibraryA(LibFileName);
          GPUabout_0 = GetProcAddress(v16, "SPUabout");
          GPUabout_0();
        }
      }
      return 0;
    case IDC_INSTALL_SPU_BACK:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case IDC_INSTALL_SPU_NEXT:
      v6 = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, 0x188u, 0, 0);
      if ( v6 != -1 && v6 < found_plugin_count )
      {
        sprintf(spu_plugin_search_path, "%s", &plugin_name_list[1024 * v6]);
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

static INT_PTR __stdcall setup_wizard_search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4;
  char v5;
  unsigned int v6;
  LRESULT v8;
  unsigned int v9;
  const char *v10;
  HMODULE v11;
  unsigned int v12;
  const char *v13;
  HMODULE v14;
  unsigned int v15;
  const char *v16;
  HMODULE v17;
  LRESULT v18;
  int v19;
  LRESULT v20;
  int v21;
  HMODULE LibraryA;
  HMODULE v23;
  FARPROC PSEgetLibVersionProc;
  uint8_t v25;
  int v26;
  const char *v27;
  LRESULT v28;
  int v29;
  CHAR *cFileName;
  char *v31;
  CHAR v32;
  char *v33;
  int v34;
  char *v35;
  char v36;
  int v37;
  CHAR *v38;
  char v39;
  LRESULT v40;
  int i;
  LRESULT v42;
  int v43;
  int v44;
  char v45[12];
  HANDLE hFindFile;
  struct _OSVERSIONINFOA VersionInformation;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR lParam[1024];
  CHAR LibFileName[1024];
  char v51[1024];
  CHAR FileName[1024];

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
      found_plugin_count = 0;
      sprintf(v51, "ePSXe CDR ASPI core 1.5.2.");
      v18 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)v51);
      if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, v18, 0);
      v19 = found_plugin_count;
      strcpy(&plugin_name_list[1024 * found_plugin_count], "W9XCDRCORE");
      found_plugin_count = v19 + 1;
      memset(&VersionInformation, 0, sizeof(VersionInformation));
      VersionInformation.dwOSVersionInfoSize = 148;
      GetVersionExA(&VersionInformation);
      if ( VersionInformation.dwPlatformId == 2 )
      {
        sprintf(v51, "ePSXe CDR WNT/W2K core 1.5.2.");
        v20 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)v51);
        if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
          SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, v20, 0);
        v21 = found_plugin_count;
        strcpy(&plugin_name_list[1024 * found_plugin_count], "W2KCDRCORE");
        found_plugin_count = v21 + 1;
      }
      do
      {
        sprintf(LibFileName, "%s%s", v45, FindFileData.cFileName);
        LibraryA = LoadLibraryA(LibFileName);
        v23 = LibraryA;
        if ( LibraryA )
        {
          PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
          PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(v23, "PSEgetLibName");
          PSEgetLibVersionProc = GetProcAddress(v23, "PSEgetLibVersion");
          PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
          if ( PSEgetLibType )
          {
            if ( PSEgetLibName )
            {
              if ( PSEgetLibVersionProc )
              {
                v25 = PSEgetLibVersionProc();
                v26 = PSEgetLibVersion(v25);
                v27 = (const char *)PSEgetLibName(BYTE1(v26));
                sprintf(v51, "%s %d.%d", v27, v43, v44);
                if ( PSEgetLibType() == 1 )
                {
                  v28 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)v51);
                  if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                    SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, v28, 0);
                  v29 = found_plugin_count;
                  if ( v28 == found_plugin_count )
                  {
                    cFileName = FindFileData.cFileName;
                    v31 = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                    do
                    {
                      v32 = *cFileName;
                      cFileName[(uint32_t)v31] = *cFileName;
                      ++cFileName;
                    }
                    while ( v32 );
                  }
                  else
                  {
                    if ( (unsigned int)v28 < found_plugin_count )
                    {
                      v33 = &plugin_name_list_shift[1024 * found_plugin_count];
                      v34 = found_plugin_count - v28;
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
                    v37 = (v28 << 10) - (uint32_t)FindFileData.cFileName;
                    v38 = FindFileData.cFileName;
                    do
                    {
                      v39 = *v38;
                      plugin_name_list[v37 + (uint32_t)v38] = *v38;
                      ++v38;
                    }
                    while ( v39 );
                  }
                  found_plugin_count = v29 + 1;
                }
              }
            }
          }
        }
      }
      while ( FindNextFileA(hFindFile, &FindFileData) );
      sprintf(lParam, "FirstCdrom");
      v40 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x143u, 0, (LPARAM)lParam);
      if ( !cdrom_letter )
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x14Eu, v40, 0);
      for ( i = 65; i <= 90; ++i )
      {
        sprintf(lParam, "%c:\\", i);
        if ( GetDriveTypeA(lParam) == 5 )
        {
          sprintf(lParam, "--%c:--", i);
          v42 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x143u, 0, (LPARAM)lParam);
          if ( i == cdrom_letter )
            SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x14Eu, v42, 0);
        }
      }
      if ( found_plugin_count == 1 )
      {
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, 0, 0);
        return 1;
      }
      break;
    case 0x111u:
      switch ( (int16_t)a3 )
      {
        case IDC_INSTALL_CDROM_CONFIG:
          v12 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( v12 == -1 || v12 >= found_plugin_count )
            return 0;
          v13 = &plugin_name_list[1024 * v12];
          cdrom_plugin_configured_flag = 1;
          if ( !strcmp(v13, "W9XCDRCORE") )
          {
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
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
        case IDC_INSTALL_CDROM_TEST:
          v9 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( v9 == -1 )
            return 0;
          if ( v9 >= found_plugin_count )
            return 0;
          v10 = &plugin_name_list[1024 * v9];
          if ( !strcmp(v10, "W9XCDRCORE") || !strcmp(v10, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", v45, v10);
          v11 = LoadLibraryA(LibFileName);
          GPUtest_0 = GetProcAddress(v11, "CDRtest");
          GPUtest_0();
          return 0;
        case IDC_INSTALL_CDROM_BACK:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case IDC_INSTALL_CDROM_NEXT:
          v6 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( v6 == -1 || v6 >= found_plugin_count )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that you haven't selected a CDROM plugin. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not selected",
              0x10u);
            return 0;
          }
          if ( !cdrom_plugin_configured_flag && strcmp(&plugin_name_list[1024 * v6], "W2KCDRCORE") )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that CDROM plugin hasn't been configured. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not configured",
              0x10u);
            return 0;
          }
          sprintf(cdrom_plugin_search_path, "%s", &plugin_name_list[1024 * v6]);
          ++setup_wizard_step;
          v8 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER_ALT, 0x147u, 0, 0);
          if ( v8 != -1 )
          {
            SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER_ALT, 0x148u, v8, (LPARAM)lParam);
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
        case IDC_INSTALL_CDROM_ABOUT:
          v15 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( v15 != -1 && v15 < found_plugin_count )
          {
            v16 = &plugin_name_list[1024 * v15];
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

static INT_PTR __stdcall setup_wizard_controllers(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  HDC DC;
  int DeviceCaps;
  HDC v7;
  int v8;

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
      switch ( (int16_t)a3 )
      {
        case IDC_INSTALL_PAD_BACK:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case IDC_INSTALL_PAD_NEXT:
          ++setup_wizard_step;
          goto LABEL_16;
        case IDC_INSTALL_PAD_1:
          pad_number_menu_selection = 1;
          DC = GetDC(hDlg);
          DeviceCaps = GetDeviceCaps(DC, 88);
          ReleaseDC(hDlg, DC);
          if ( DeviceCaps > 96 )
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          else
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
          return 0;
        case IDC_INSTALL_PAD_2:
          pad_number_menu_selection = 2;
          v7 = GetDC(hDlg);
          v8 = GetDeviceCaps(v7, 88);
          ReleaseDC(hDlg, v7);
          if ( v8 <= 96 )
          {
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
            return 0;
          }
          DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          break;
        default:
          return 0;
      }
      break;
  }
  return 0;
}

static INT_PTR __stdcall setup_wizard_end(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
    return 1;
  if ( a2 != 273 || (uint16_t)a3 != 1114 )
    return 0;
  ++setup_wizard_step;
  EndDialog(hDlg, 1);
  return 1;
}

static INT_PTR __stdcall setup_wizard_begin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
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
  if ( (uint16_t)a3 == 1109 )
  {
    --setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
  else
  {
    if ( (uint16_t)a3 != 1110 )
      return 0;
    ++setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
}

int setup_wizard_callback(HWND hWndParent)
{
  int result;

  cdrom_plugin_configured_flag = 0;
  while ( 2 )
  {
    result = setup_wizard_step;
    switch ( setup_wizard_step )
    {
      case 0:
        setup_wizard_init();
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL", hWndParent, setup_wizard_begin, 0);
        continue;
      case 1:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_BIOS", hWndParent, setup_wizard_search_bios, 0);
        continue;
      case 2:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_GPU", hWndParent, setup_wizard_search_video_plugin, 0);
        continue;
      case 3:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_SPU", hWndParent, setup_wizard_search_spu_plugin, 0);
        continue;
      case 4:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_CDROM", hWndParent, setup_wizard_search_cdrom_plugin, 0);
        continue;
      case 5:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_PAD", hWndParent, setup_wizard_controllers, 0);
        continue;
      case 6:
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_INSTALL_END", hWndParent, setup_wizard_end, 0);
        continue;
      case 7:
        sprintf((char *const)VideoPlugin, "%s", video_plugin_search_path);
        sprintf((char *const)SoundPlugin, "%s", spu_plugin_search_path);
        sprintf((char *const)CdromPlugin, "%s", cdrom_plugin_search_path);
        sprintf((char *const)bios_name, "%s", bios_search_path);
        result = cfg_save_settings();
        break;
      default:
        return result;
    }
    break;
  }
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
char FileName[256];
unsigned char video_plugin_search_path[0x400];
unsigned char spu_plugin_search_path[0x400];
unsigned char cdrom_plugin_search_path[0x400];
unsigned char bios_search_path[0x80];
unsigned char cdrom_plugin_configured_flag;
BIOS_DESCR debug_bios = {0x0D, "dtlh3002 - PAL"};
BIOS_DESCR retail_bioses = {0x0C8EC73C0, "scph1000 - JAP"};
unsigned int setup_wizard_step = 0xffffffff;
