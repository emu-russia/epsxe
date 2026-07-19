#include "pch.h"
int net_load_plugin()
{
  int result; // eax
  HMODULE LibraryA; // eax
  CHAR LibFileName[1024]; // [esp+8h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)NetPlugin);
  if ( !strcmp((const char *)NetPlugin, "DISABLED") )
  {
    result = network_enabled;
    if ( !network_enabled )
      return result;
  }
  else
  {
    network_enabled = 1;
  }
  LibraryA = LoadLibraryA(LibFileName);
  hNetModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
  NETinit = GetProcAddress(LibraryA, "NETinit");
  if ( !NETinit )
    ui_error(" * GetProcAddress error NETinit\n");
  NETshutdown = (HMODULE (*)(void))GetProcAddress(hNetModule, "NETshutdown");
  if ( !NETshutdown )
    ui_error(" * GetProcAddress error NETshutdoww\n");
  NETopen = (int (__stdcall *)(_DWORD))GetProcAddress(hNetModule, "NETopen");
  if ( !NETopen )
    ui_error(" * GetProcAddress error NETopen\n");
  NETclose = GetProcAddress(hNetModule, "NETclose");
  if ( !NETclose )
    ui_error(" * GetProcAddress error NETclose\n");
  NETpause = (HMODULE (*)(void))GetProcAddress(hNetModule, "NETpause");
  if ( !NETpause )
    ui_error(" * GetProcAddress error NETpause\n");
  NETresume = (int (__stdcall *)(_DWORD))GetProcAddress(hNetModule, "NETresume");
  if ( !NETresume )
    ui_error(" * GetProcAddress error NETresume\n");
  NETpadState = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hNetModule, "NETpadState");
  if ( !NETpadState )
    ui_error(" * GetProcAddress error NETpadState\n");
  NETcompareData = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hNetModule, "NETcompareData");
  if ( !NETcompareData )
    ui_error(" * GetProcAddress error NETcompareData\n");
  NETqueryPlayer = GetProcAddress(hNetModule, "NETqueryPlayer");
  if ( !NETqueryPlayer )
    ui_error(" * GetProcAddress error NETqueryPlayer\n");
  NETtransferData = (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GetProcAddress(hNetModule, "NETtransferData");
  if ( !NETtransferData )
    ui_error(" * GetProcAddress error NETtransferData\n");
  dbg_print(" * Init netplugin ... ");
  NETinit();
  return dbg_print(" ok \n");
}
