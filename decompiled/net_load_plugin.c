#include "pch.h"
int sub_42EFF0()
{
  int result; // eax
  HMODULE LibraryA; // eax
  char v2; // [esp+0h] [ebp-408h]
  CHAR LibFileName[1024]; // [esp+8h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", aPlugins, (const char *)&byte_8B4180);
  if ( !strcmp((const char *)&byte_8B4180, aDisabled) )
  {
    result = dword_4FD99C;
    if ( !dword_4FD99C )
      return result;
  }
  else
  {
    dword_4FD99C = 1;
  }
  LibraryA = LoadLibraryA(LibFileName);
  dword_4FD998 = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(aErrorLoadingS, (char)LibFileName);
  NETinit = GetProcAddress(LibraryA, aNetinit);
  if ( !NETinit )
    ui_error(aGetprocaddress_0, v2);
  NETshutdown = (int)GetProcAddress(dword_4FD998, aNetshutdown);
  if ( !NETshutdown )
    ui_error(aGetprocaddress_1, v2);
  NETopen = (int)GetProcAddress(dword_4FD998, aNetopen);
  if ( !NETopen )
    ui_error(aGetprocaddress_2, v2);
  NETclose = (int)GetProcAddress(dword_4FD998, aNetclose);
  if ( !NETclose )
    ui_error(aGetprocaddress_3, v2);
  NETpause = (int)GetProcAddress(dword_4FD998, aNetpause);
  if ( !NETpause )
    ui_error(aGetprocaddress_4, v2);
  NETresume = (int)GetProcAddress(dword_4FD998, aNetresume);
  if ( !NETresume )
    ui_error(aGetprocaddress_5, v2);
  NETpadState = (int)GetProcAddress(dword_4FD998, aNetpadstate);
  if ( !NETpadState )
    ui_error(aGetprocaddress_6, v2);
  NETcompareData = (int)GetProcAddress(dword_4FD998, aNetcomparedata);
  if ( !NETcompareData )
    ui_error(aGetprocaddress_7, v2);
  NETqueryPlayer = (int)GetProcAddress(dword_4FD998, aNetqueryplayer);
  if ( !NETqueryPlayer )
    ui_error(aGetprocaddress_8, v2);
  NETtransferData = (int)GetProcAddress(dword_4FD998, aNettransferdat);
  if ( !NETtransferData )
    ui_error(aGetprocaddress_9, v2);
  dbg_print(aInitNetplugin);
  NETinit();
  return dbg_print(aOk);
}
