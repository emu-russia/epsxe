#include "pch.h"

static HANDLE setup_wizard_init()
{
  HANDLE hFindGpu;
  HANDLE hFindSpu;
  HANDLE hFindCdr;
  HANDLE hFindCdrCopy;
  char pluginPath[12];
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR FileName[1024];
  CHAR NewFileName[1024];

  strcpy(pluginPath, "plugins\\");
  FileName[0] = current_dir_path;
  strcat(FileName, "gpu*.dll");
  hFindGpu = FindFirstFileA(FileName, &FindFileData);
  if ( hFindGpu != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", pluginPath, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(hFindGpu, &FindFileData) );
  }
  FileName[0] = current_dir_path;
  strcat(FileName, "spu*.dll");
  hFindSpu = FindFirstFileA(FileName, &FindFileData);
  if ( hFindSpu != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", pluginPath, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
    }
    while ( FindNextFileA(hFindSpu, &FindFileData) );
  }
  FileName[0] = current_dir_path;
  strcat(FileName, "cdr*.dll");
  hFindCdr = FindFirstFileA(FileName, &FindFileData);
  hFindCdrCopy = hFindCdr;
  if ( hFindCdr != (HANDLE)-1 )
  {
    do
    {
      sprintf(NewFileName, "%s%s", pluginPath, FindFileData.cFileName);
      MoveFileA(FindFileData.cFileName, NewFileName);
      hFindCdr = (HANDLE)FindNextFileA(hFindCdrCopy, &FindFileData);
    }
    while ( hFindCdr );
  }
  return hFindCdr;
}

static INT_PTR __stdcall setup_wizard_search_bios(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int index;
  char ch;
  unsigned int selection;
  int matchIndex;
  FILE *file;
  uint8_t *biosData;
  int checksum;
  uint32_t count;
  _BIOS_DESCR *biosDesc;
  LRESULT itemIndex;
  int pluginCount;
  char *src;
  char *dstOffset;
  char ch2;
  char *shiftPtr;
  int shiftCount;
  char *p;
  char ch3;
  char *insSrc;
  char *insOffset;
  char ch4;
  char biosPath[8];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  char Buffer[1024];
  CHAR FileName[1024];
  char strBuf[1024];

  strcpy(biosPath, "bios\\");
  index = 0;
  do
  {
    ch = biosPath[index];
    FileName[index++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.bin");
  if ( msg == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( msg != 272 )
  {
    if ( msg == 273 )
    {
      if ( (uint16_t)wParam == 1107 )
      {
        --setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      if ( (uint16_t)wParam == 1108 )
      {
        selection = SendDlgItemMessageA(hDlg, IDC_INSTALL_BIOS_LIST, 0x188u, 0, 0);
        if ( selection != -1 && selection < found_plugin_count )
        {
          sprintf(bios_search_path, "%s", &plugin_name_list[1024 * selection]);
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
    sprintf(Buffer, "%s%s", biosPath, FindFileData.cFileName);
    matchIndex = -1;
    file = fopen(Buffer, "rb");
    if ( file )
    {
      biosData = (uint8_t *)malloc(0x80000u);
      fread(biosData, 0x80000u, 1u, file);
      fclose(file);
      checksum = calc_bios_checksum(biosData, 0x80000);
      free(biosData);
      count = 0;
      if ( debug_bios.crc )
      {
        biosDesc = &retail_bioses;
        do
        {
          if ( checksum == biosDesc->crc )
            matchIndex = count;
          ++count;
          ++biosDesc;
        }
        while ( count < debug_bios.crc );
        if ( matchIndex != -1 )
        {
          sprintf(strBuf, "%s", (const char *)(36 * matchIndex + 4513104));
          itemIndex = SendDlgItemMessageA(hDlg, IDC_INSTALL_BIOS_LIST, 0x180u, 0, (LPARAM)strBuf);
          pluginCount = found_plugin_count;
          if ( itemIndex == found_plugin_count )
          {
            src = Buffer;
            dstOffset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)Buffer];
            do
            {
              ch2 = *src;
              src[(uint32_t)dstOffset] = *src;
              ++src;
            }
            while ( ch2 );
          }
          else
          {
            if ( itemIndex < found_plugin_count )
            {
              shiftPtr = &plugin_name_list_shift[1024 * found_plugin_count];
              shiftCount = found_plugin_count - itemIndex;
              do
              {
                p = shiftPtr;
                do
                {
                  ch3 = *p;
                  p[1024] = *p;
                  ++p;
                }
                while ( ch3 );
                shiftPtr -= 1024;
                --shiftCount;
              }
              while ( shiftCount );
            }
            insSrc = Buffer;
            insOffset = &plugin_name_list[(itemIndex << 10) - (uint32_t)Buffer];
            do
            {
              ch4 = *insSrc;
              insSrc[(uint32_t)insOffset] = *insSrc;
              ++insSrc;
            }
            while ( ch4 );
          }
          found_plugin_count = pluginCount + 1;
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

static INT_PTR __stdcall setup_wizard_search_video_plugin(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int index;
  char ch;
  unsigned int selection;
  INT_PTR ret;
  unsigned int testSelection;
  HMODULE hTestLib;
  char testResult;
  unsigned int configSelection;
  HMODULE hConfigLib;
  unsigned int aboutSelection;
  HMODULE hAboutLib;
  HMODULE LibraryA;
  HMODULE hLib;
  FARPROC PSEgetLibVersionProc;
  uint8_t versionByte;
  int version;
  const char *libName;
  LRESULT itemIndex;
  int pluginCount;
  CHAR *cFileName;
  char *dstOffset;
  CHAR ch2;
  char *shiftPtr;
  int shiftCount;
  char *p;
  CHAR ch3;
  int insOffset;
  CHAR *insSrc;
  char ch4;
  int versionMajor;
  int versionMinor;
  char pluginPath[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  CHAR FileName[1024];
  char strBuf[1024];

  strcpy(pluginPath, "plugins\\");
  index = 0;
  do
  {
    ch = pluginPath[index];
    FileName[index++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( msg == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( msg == 272 )
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
      sprintf(LibFileName, "%s%s", pluginPath, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      hLib = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(hLib, "PSEgetLibName");
        PSEgetLibVersionProc = GetProcAddress(hLib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersionProc )
            {
              versionByte = PSEgetLibVersionProc();
              version = PSEgetLibVersion(versionByte);
              libName = (const char *)PSEgetLibName(BYTE1(version));
              sprintf(strBuf, "%s %d.%d", libName, versionMajor, versionMinor);
              if ( PSEgetLibType() == 2 )
              {
                itemIndex = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x180u, 0, (LPARAM)strBuf);
                if ( !strcmp((const char *)VideoPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x186u, itemIndex, 0);
                pluginCount = found_plugin_count;
                if ( itemIndex == found_plugin_count )
                {
                  cFileName = FindFileData.cFileName;
                  dstOffset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *cFileName;
                    cFileName[(uint32_t)dstOffset] = *cFileName;
                    ++cFileName;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( itemIndex < found_plugin_count )
                  {
                    shiftPtr = &plugin_name_list_shift[1024 * found_plugin_count];
                    shiftCount = found_plugin_count - itemIndex;
                    do
                    {
                      p = shiftPtr;
                      do
                      {
                        ch3 = *p;
                        p[1024] = *p;
                        ++p;
                      }
                      while ( ch3 );
                      shiftPtr -= 1024;
                      --shiftCount;
                    }
                    while ( shiftCount );
                  }
                  insOffset = (itemIndex << 10) - (uint32_t)FindFileData.cFileName;
                  insSrc = FindFileData.cFileName;
                  do
                  {
                    ch4 = *insSrc;
                    plugin_name_list[insOffset + (uint32_t)insSrc] = *insSrc;
                    ++insSrc;
                  }
                  while ( ch4 );
                }
                found_plugin_count = pluginCount + 1;
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
  if ( msg != 273 )
    return 0;
  switch ( (int16_t)wParam )
  {
    case IDC_INSTALL_GPU_CONFIG:
      if ( !found_plugin_count )
        return 0;
      configSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( configSelection == -1 || configSelection >= found_plugin_count )
        return 0;
      sprintf(LibFileName, "%s%s", pluginPath, &plugin_name_list[1024 * configSelection]);
      hConfigLib = LoadLibraryA(LibFileName);
      GPUinit_0 = GetProcAddress(hConfigLib, "GPUinit");
      PSEconfigure = GetProcAddress(hConfigLib, "GPUconfigure");
      GPUshutdown_0 = GetProcAddress(hConfigLib, "GPUshutdown");
      GPUinit_0();
      PSEconfigure();
      GPUshutdown_0();
      return 0;
    case IDC_INSTALL_GPU_TEST:
      if ( !found_plugin_count )
        return 0;
      testSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( testSelection == -1 || testSelection >= found_plugin_count )
        return 0;
      sprintf(LibFileName, "%s%s", pluginPath, &plugin_name_list[1024 * testSelection]);
      hTestLib = LoadLibraryA(LibFileName);
      GPUinit_0 = GetProcAddress(hTestLib, "GPUinit");
      GPUtest_0 = GetProcAddress(hTestLib, "GPUtest");
      GPUshutdown_0 = GetProcAddress(hTestLib, "GPUshutdown");
      GPUinit_0();
      testResult = GPUtest_0();
      if ( testResult )
      {
        if ( testResult == -1 )
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
      selection = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
      if ( selection != -1 && selection < found_plugin_count )
      {
        sprintf(video_plugin_search_path, "%s", &plugin_name_list[1024 * selection]);
        ++setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      MessageBoxA(
        nullptr,
        "ePSXe detected that you haven't selected a GPU plugin. Please, select your favourite plugin and hit on config button",
        "GPU plugin not selected",
        0x10u);
      ret = 0;
      break;
    case IDC_INSTALL_GPU_ABOUT:
      if ( found_plugin_count )
      {
        aboutSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_GPU_LIST, 0x188u, 0, 0);
        if ( aboutSelection != -1 && aboutSelection < found_plugin_count )
        {
          sprintf(LibFileName, "%s%s", pluginPath, &plugin_name_list[1024 * aboutSelection]);
          hAboutLib = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(hAboutLib, "GPUinit");
          GPUabout_0 = GetProcAddress(hAboutLib, "GPUabout");
          GPUshutdown_0 = GetProcAddress(hAboutLib, "GPUshutdown");
          GPUinit_0();
          GPUabout_0();
          GPUshutdown_0();
        }
      }
      return 0;
    default:
      return 0;
  }
  return ret;
}

static INT_PTR __stdcall setup_wizard_search_spu_plugin(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int index;
  char ch;
  unsigned int selection;
  INT_PTR ret;
  unsigned int testSelection;
  const char *testLibName;
  HMODULE hTestLib;
  unsigned int configSelection;
  const char *configLibName;
  HMODULE hConfigLib;
  unsigned int aboutSelection;
  const char *aboutLibName;
  HMODULE hAboutLib;
  HWND hwnd;
  LRESULT (__stdcall *sendDlgItemMsg)(HWND, int, UINT, WPARAM, LPARAM);
  LRESULT coreItem;
  int coreCount;
  int nameOffset;
  HMODULE LibraryA;
  HMODULE hLib;
  FARPROC PSEgetLibVersionProc;
  uint8_t versionByte;
  int version;
  const char *libName;
  signed int itemIndex;
  int pluginCount;
  CHAR *cFileName;
  char *dstOffset;
  CHAR ch2;
  char *shiftPtr;
  int shiftCount;
  char *p;
  char ch3;
  int insOffset;
  CHAR *insSrc;
  char ch4;
  int versionMajor;
  int versionMinor;
  char pluginPath[12];
  HANDLE hFindFile;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR LibFileName[1024];
  char strBuf[1024];
  CHAR FileName[1024];

  strcpy(pluginPath, "plugins\\");
  index = 0;
  do
  {
    ch = pluginPath[index];
    FileName[index++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  if ( msg == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( msg == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    found_plugin_count = 0;
    sprintf(strBuf, "ePSXe SPU core 1.5.2.");
    hwnd = hDlg;
    sendDlgItemMsg = SendDlgItemMessageA;
    coreItem = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_ADDSTRING, 0, (LPARAM)strBuf);
    if ( !strcmp((const char *)SoundPlugin, "SPUCORE") )
      SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_SETCURSEL, coreItem, 0);
    coreCount = found_plugin_count;
    nameOffset = found_plugin_count << 10;
    *(uint32_t *)&plugin_name_list[nameOffset] = *(uint32_t *)"SPUCORE";
    strcpy(&plugin_name_list_tail[nameOffset], "ORE");
    found_plugin_count = coreCount + 1;
    while ( 1 )
    {
      sprintf(LibFileName, "%s%s", pluginPath, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      hLib = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
        PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(hLib, "PSEgetLibName");
        PSEgetLibVersionProc = GetProcAddress(hLib, "PSEgetLibVersion");
        PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersionProc )
            {
              versionByte = PSEgetLibVersionProc();
              version = PSEgetLibVersion(versionByte);
              libName = (const char *)PSEgetLibName(BYTE1(version));
              sprintf(strBuf, "%s %d.%d", libName, versionMajor, versionMinor);
              if ( PSEgetLibType() == 4 )
              {
                itemIndex = sendDlgItemMsg(hwnd, IDC_INSTALL_SPU_LIST, 0x180u, 0, (LPARAM)strBuf);
                if ( !strcmp((const char *)SoundPlugin, FindFileData.cFileName) )
                  SendDlgItemMessageA(hwnd, IDC_INSTALL_SPU_LIST, 0x186u, itemIndex, 0);
                pluginCount = found_plugin_count;
                if ( itemIndex == found_plugin_count )
                {
                  cFileName = FindFileData.cFileName;
                  dstOffset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                  do
                  {
                    ch2 = *cFileName;
                    cFileName[(uint32_t)dstOffset] = *cFileName;
                    ++cFileName;
                  }
                  while ( ch2 );
                }
                else
                {
                  if ( (unsigned int)itemIndex < found_plugin_count )
                  {
                    shiftPtr = &plugin_name_list_shift[1024 * found_plugin_count];
                    shiftCount = found_plugin_count - itemIndex;
                    do
                    {
                      p = shiftPtr;
                      do
                      {
                        ch3 = *p;
                        p[1024] = *p;
                        ++p;
                      }
                      while ( ch3 );
                      shiftPtr -= 1024;
                      --shiftCount;
                    }
                    while ( shiftCount );
                  }
                  insOffset = (itemIndex << 10) - (uint32_t)FindFileData.cFileName;
                  insSrc = FindFileData.cFileName;
                  do
                  {
                    ch4 = *insSrc;
                    plugin_name_list[insOffset + (uint32_t)insSrc] = *insSrc;
                    ++insSrc;
                  }
                  while ( ch4 );
                }
                found_plugin_count = pluginCount + 1;
                hwnd = hDlg;
              }
            }
          }
        }
      }
      if ( !FindNextFileA(hFindFile, &FindFileData) )
        break;
      sendDlgItemMsg = SendDlgItemMessageA;
    }
    if ( found_plugin_count == 1 )
    {
      SendDlgItemMessageA(hwnd, IDC_INSTALL_SPU_LIST, LB_SETCURSEL, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( msg != 273 )
    return 0;
  switch ( (int16_t)wParam )
  {
    case IDC_INSTALL_SPU_CONFIG:
      configSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_GETCURSEL, 0, 0);
      if ( configSelection == -1 || configSelection >= found_plugin_count )
        return 0;
      configLibName = &plugin_name_list[1024 * configSelection];
      if ( !strcmp(configLibName, "SPUCORE") )
      {
        DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_SOUND9X", hDlg, spucore_configure_dialog_callback, 0);
      }
      else
      {
        sprintf(LibFileName, "%s%s", pluginPath, configLibName);
        hConfigLib = LoadLibraryA(LibFileName);
        PSEconfigure = GetProcAddress(hConfigLib, "SPUconfigure");
        PSEconfigure();
      }
      return 0;
    case IDC_INSTALL_SPU_TEST:
      testSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, LB_GETCURSEL, 0, 0);
      if ( testSelection == -1 )
        return 0;
      if ( testSelection >= found_plugin_count )
        return 0;
      testLibName = &plugin_name_list[1024 * testSelection];
      if ( !strcmp(testLibName, "SPUCORE") )
        return 0;
      sprintf(LibFileName, "%s%s", pluginPath, testLibName);
      hTestLib = LoadLibraryA(LibFileName);
      GPUtest_0 = GetProcAddress(hTestLib, "SPUtest");
      GPUtest_0();
      return 0;
    case IDC_INSTALL_SPU_ABOUT:
      aboutSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, 0x188u, 0, 0);
      if ( aboutSelection != -1 && aboutSelection < found_plugin_count )
      {
        aboutLibName = &plugin_name_list[1024 * aboutSelection];
        if ( strcmp(aboutLibName, "SPUCORE") )
        {
          sprintf(LibFileName, "%s%s", pluginPath, aboutLibName);
          hAboutLib = LoadLibraryA(LibFileName);
          GPUabout_0 = GetProcAddress(hAboutLib, "SPUabout");
          GPUabout_0();
        }
      }
      return 0;
    case IDC_INSTALL_SPU_BACK:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case IDC_INSTALL_SPU_NEXT:
      selection = SendDlgItemMessageA(hDlg, IDC_INSTALL_SPU_LIST, 0x188u, 0, 0);
      if ( selection != -1 && selection < found_plugin_count )
      {
        sprintf(spu_plugin_search_path, "%s", &plugin_name_list[1024 * selection]);
        ++setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      MessageBoxA(
        nullptr,
        "ePSXe detected that you haven't selected a SPU plugin. Please, select your favourite plugin and hit on config button",
        "SPU plugin not selected",
        0x10u);
      ret = 0;
      break;
    default:
      return 0;
  }
  return ret;
}

static INT_PTR __stdcall setup_wizard_search_cdrom_plugin(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int index;
  char ch;
  unsigned int selection;
  LRESULT letterSel;
  unsigned int testSelection;
  const char *testLibName;
  HMODULE hTestLib;
  unsigned int configSelection;
  const char *configLibName;
  HMODULE hConfigLib;
  unsigned int aboutSelection;
  const char *aboutLibName;
  HMODULE hAboutLib;
  LRESULT coreItem;
  int coreCount;
  LRESULT coreItem2;
  int coreCount2;
  HMODULE LibraryA;
  HMODULE hLib;
  FARPROC PSEgetLibVersionProc;
  uint8_t versionByte;
  int version;
  const char *libName;
  LRESULT itemIndex;
  int pluginCount;
  CHAR *cFileName;
  char *dstOffset;
  CHAR ch2;
  char *shiftPtr;
  int shiftCount;
  char *p;
  char ch3;
  int insOffset;
  CHAR *insSrc;
  char ch4;
  LRESULT firstCdromItem;
  int i;
  LRESULT driveItem;
  int versionMajor;
  int versionMinor;
  char pluginPath[12];
  HANDLE hFindFile;
  struct _OSVERSIONINFOA VersionInformation;
  struct _WIN32_FIND_DATAA FindFileData;
  CHAR driveBuf[1024];
  CHAR LibFileName[1024];
  char coreBuf[1024];
  CHAR FileName[1024];

  strcpy(pluginPath, "plugins\\");
  index = 0;
  do
  {
    ch = pluginPath[index];
    FileName[index++] = ch;
  }
  while ( ch );
  strcat(FileName, "*.dll");
  switch ( msg )
  {
    case 0x10u:
      setup_wizard_step = 8;
      EndDialog(hDlg, 1);
      break;
    case 0x110u:
      hFindFile = FindFirstFileA(FileName, &FindFileData);
      found_plugin_count = 0;
      sprintf(coreBuf, "ePSXe CDR ASPI core 1.5.2.");
      coreItem = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)coreBuf);
      if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, coreItem, 0);
      coreCount = found_plugin_count;
      strcpy(&plugin_name_list[1024 * found_plugin_count], "W9XCDRCORE");
      found_plugin_count = coreCount + 1;
      memset(&VersionInformation, 0, sizeof(VersionInformation));
      VersionInformation.dwOSVersionInfoSize = 148;
      GetVersionExA(&VersionInformation);
      if ( VersionInformation.dwPlatformId == 2 )
      {
        sprintf(coreBuf, "ePSXe CDR WNT/W2K core 1.5.2.");
        coreItem2 = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)coreBuf);
        if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
          SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, coreItem2, 0);
        coreCount2 = found_plugin_count;
        strcpy(&plugin_name_list[1024 * found_plugin_count], "W2KCDRCORE");
        found_plugin_count = coreCount2 + 1;
      }
      do
      {
        sprintf(LibFileName, "%s%s", pluginPath, FindFileData.cFileName);
        LibraryA = LoadLibraryA(LibFileName);
        hLib = LibraryA;
        if ( LibraryA )
        {
          PSEgetLibType = GetProcAddress(LibraryA, "PSEgetLibType");
          PSEgetLibName = (int ( *)(uint32_t))GetProcAddress(hLib, "PSEgetLibName");
          PSEgetLibVersionProc = GetProcAddress(hLib, "PSEgetLibVersion");
          PSEgetLibVersion = (int ( *)(uint32_t))PSEgetLibVersionProc;
          if ( PSEgetLibType )
          {
            if ( PSEgetLibName )
            {
              if ( PSEgetLibVersionProc )
              {
                versionByte = PSEgetLibVersionProc();
                version = PSEgetLibVersion(versionByte);
                libName = (const char *)PSEgetLibName(BYTE1(version));
                sprintf(coreBuf, "%s %d.%d", libName, versionMajor, versionMinor);
                if ( PSEgetLibType() == 1 )
                {
                  itemIndex = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x180u, 0, (LPARAM)coreBuf);
                  if ( !strcmp((const char *)CdromPlugin, FindFileData.cFileName) )
                    SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, itemIndex, 0);
                  pluginCount = found_plugin_count;
                  if ( itemIndex == found_plugin_count )
                  {
                    cFileName = FindFileData.cFileName;
                    dstOffset = &plugin_name_list[(found_plugin_count << 10) - (uint32_t)FindFileData.cFileName];
                    do
                    {
                      ch2 = *cFileName;
                      cFileName[(uint32_t)dstOffset] = *cFileName;
                      ++cFileName;
                    }
                    while ( ch2 );
                  }
                  else
                  {
                    if ( (unsigned int)itemIndex < found_plugin_count )
                    {
                      shiftPtr = &plugin_name_list_shift[1024 * found_plugin_count];
                      shiftCount = found_plugin_count - itemIndex;
                      do
                      {
                        p = shiftPtr;
                        do
                        {
                          ch3 = *p;
                          p[1024] = *p;
                          ++p;
                        }
                        while ( ch3 );
                        shiftPtr -= 1024;
                        --shiftCount;
                      }
                      while ( shiftCount );
                    }
                    insOffset = (itemIndex << 10) - (uint32_t)FindFileData.cFileName;
                    insSrc = FindFileData.cFileName;
                    do
                    {
                      ch4 = *insSrc;
                      plugin_name_list[insOffset + (uint32_t)insSrc] = *insSrc;
                      ++insSrc;
                    }
                    while ( ch4 );
                  }
                  found_plugin_count = pluginCount + 1;
                }
              }
            }
          }
        }
      }
      while ( FindNextFileA(hFindFile, &FindFileData) );
      sprintf(driveBuf, "FirstCdrom");
      firstCdromItem = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x143u, 0, (LPARAM)driveBuf);
      if ( !cdrom_letter )
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x14Eu, firstCdromItem, 0);
      for ( i = 65; i <= 90; ++i )
      {
        sprintf(driveBuf, "%c:\\", i);
        if ( GetDriveTypeA(driveBuf) == 5 )
        {
          sprintf(driveBuf, "--%c:--", i);
          driveItem = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x143u, 0, (LPARAM)driveBuf);
          if ( i == cdrom_letter )
            SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER, 0x14Eu, driveItem, 0);
        }
      }
      if ( found_plugin_count == 1 )
      {
        SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x186u, 0, 0);
        return 1;
      }
      break;
    case 0x111u:
      switch ( (int16_t)wParam )
      {
        case IDC_INSTALL_CDROM_CONFIG:
          configSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( configSelection == -1 || configSelection >= found_plugin_count )
            return 0;
          configLibName = &plugin_name_list[1024 * configSelection];
          cdrom_plugin_configured_flag = 1;
          if ( !strcmp(configLibName, "W9XCDRCORE") )
          {
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CDROMCORE9X", hDlg, w9x_cdrom_settings, 0);
            return 0;
          }
          if ( !strcmp(configLibName, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", pluginPath, configLibName);
          hConfigLib = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(hConfigLib, "CDRinit");
          GPUinit_0();
          PSEconfigure = GetProcAddress(hConfigLib, "CDRconfigure");
          PSEconfigure();
          return 0;
        case IDC_INSTALL_CDROM_TEST:
          testSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( testSelection == -1 )
            return 0;
          if ( testSelection >= found_plugin_count )
            return 0;
          testLibName = &plugin_name_list[1024 * testSelection];
          if ( !strcmp(testLibName, "W9XCDRCORE") || !strcmp(testLibName, "W2KCDRCORE") )
            return 0;
          sprintf(LibFileName, "%s%s", pluginPath, testLibName);
          hTestLib = LoadLibraryA(LibFileName);
          GPUtest_0 = GetProcAddress(hTestLib, "CDRtest");
          GPUtest_0();
          return 0;
        case IDC_INSTALL_CDROM_BACK:
          --setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        case IDC_INSTALL_CDROM_NEXT:
          selection = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( selection == -1 || selection >= found_plugin_count )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that you haven't selected a CDROM plugin. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not selected",
              0x10u);
            return 0;
          }
          if ( !cdrom_plugin_configured_flag && strcmp(&plugin_name_list[1024 * selection], "W2KCDRCORE") )
          {
            MessageBoxA(
              nullptr,
              "ePSXe detected that CDROM plugin hasn't been configured. Please, select your favourite plugin and hit on config button",
              "CDROM plugin not configured",
              0x10u);
            return 0;
          }
          sprintf(cdrom_plugin_search_path, "%s", &plugin_name_list[1024 * selection]);
          ++setup_wizard_step;
          letterSel = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER_ALT, 0x147u, 0, 0);
          if ( letterSel != -1 )
          {
            SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LETTER_ALT, 0x148u, letterSel, (LPARAM)driveBuf);
            if ( strncmp(driveBuf, "FirstCdrom", 4u) )
            {
              sscanf(driveBuf, "--%c:--", &cdrom_letter);
              EndDialog(hDlg, 1);
              return 1;
            }
            cdrom_letter = 0;
          }
          EndDialog(hDlg, 1);
          break;
        case IDC_INSTALL_CDROM_ABOUT:
          aboutSelection = SendDlgItemMessageA(hDlg, IDC_INSTALL_CDROM_LIST, 0x188u, 0, 0);
          if ( aboutSelection != -1 && aboutSelection < found_plugin_count )
          {
            aboutLibName = &plugin_name_list[1024 * aboutSelection];
            if ( strcmp(aboutLibName, "W9XCDRCORE") )
            {
              if ( strcmp(aboutLibName, "W2KCDRCORE") )
              {
                sprintf(LibFileName, "%s%s", pluginPath, aboutLibName);
                hAboutLib = LoadLibraryA(LibFileName);
                GPUabout_0 = GetProcAddress(hAboutLib, "CDRabout");
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

static INT_PTR __stdcall setup_wizard_controllers(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  int deviceCaps;
  HDC hdc2;
  int deviceCaps2;

  switch ( msg )
  {
    case 0x10u:
      setup_wizard_step = 8;
LABEL_16:
      EndDialog(hDlg, 1);
      return 1;
    case 0x110u:
      return 1;
    case 0x111u:
      switch ( (int16_t)wParam )
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
          hdc = GetDC(hDlg);
          deviceCaps = GetDeviceCaps(hdc, 88);
          ReleaseDC(hDlg, hdc);
          if ( deviceCaps > 96 )
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER_LARGE", hDlg, controller_setup_callback, 0);
          else
            DialogBoxParamA((HINSTANCE)g_hInstance, "IDD_CONTROLLER", hDlg, controller_setup_callback, 0);
          return 0;
        case IDC_INSTALL_PAD_2:
          pad_number_menu_selection = 2;
          hdc2 = GetDC(hDlg);
          deviceCaps2 = GetDeviceCaps(hdc2, 88);
          ReleaseDC(hDlg, hdc2);
          if ( deviceCaps2 <= 96 )
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

static INT_PTR __stdcall setup_wizard_end(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if ( msg == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( msg == 272 )
    return 1;
  if ( msg != 273 || (uint16_t)wParam != 1114 )
    return 0;
  ++setup_wizard_step;
  EndDialog(hDlg, 1);
  return 1;
}

static INT_PTR __stdcall setup_wizard_begin(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if ( msg == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( msg == 272 )
    return 1;
  if ( msg != 273 )
    return 0;
  if ( (uint16_t)wParam == 1109 )
  {
    --setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
  else
  {
    if ( (uint16_t)wParam != 1110 )
      return 0;
    ++setup_wizard_step;
    EndDialog(hDlg, 1);
    return 1;
  }
}

int setup_wizard_callback(HWND hWndParent)
{
  int ret;

  cdrom_plugin_configured_flag = 0;
  while ( 2 )
  {
    ret = setup_wizard_step;
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
        ret = cfg_save_settings();
        break;
      default:
        return ret;
    }
    break;
  }
  return ret;
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
