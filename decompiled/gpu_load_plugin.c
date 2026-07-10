#include "pch.h"
int sub_42DFE0()
{
  HMODULE LibraryA; // eax
  FARPROC GPUclearDynarec; // eax
  char v2; // al
  char v4; // [esp-8h] [ebp-408h]
  CHAR LibFileName[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( !strcmp((const char *)&byte_8B1980, aNull) )
    fatal_error_with_message_box(aErrorVideoDoes, v4);
  sprintf(LibFileName, "%s%s", aPlugins, (const char *)&byte_8B1980);
  LibraryA = LoadLibraryA(LibFileName);
  dword_4FD990 = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(aErrorLoadingS, (char)LibFileName);
  gpu_closed = 1;
  GPUinit = GetProcAddress(LibraryA, ProcName);
  if ( !GPUinit )
    ui_error(aGetprocaddress, (char)ProcName);
  GPUshutdown = (int)GetProcAddress(dword_4FD990, aGpushutdown);
  if ( !GPUshutdown )
    ui_error(aGetprocaddress, (char)aGpushutdown);
  GPUopen = (int)GetProcAddress(dword_4FD990, aGpuopen);
  if ( !GPUopen )
    ui_error(aGetprocaddress, (char)aGpuopen);
  GPUclose = (int)GetProcAddress(dword_4FD990, aGpuclose);
  if ( !GPUclose )
    ui_error(aGetprocaddress, (char)aGpuclose);
  GPUconfigure = (int)GetProcAddress(dword_4FD990, aGpuconfigure);
  if ( !GPUconfigure )
    ui_error(aGetprocaddress, (char)aGpuconfigure);
  GPUabout = (int)GetProcAddress(dword_4FD990, aGpuabout);
  if ( !GPUabout )
    ui_error(aGetprocaddress, (char)aGpuabout);
  GPUtest = (int)GetProcAddress(dword_4FD990, aGputest);
  if ( !GPUtest )
    ui_error(aGetprocaddress, (char)aGputest);
  GPUwriteData = (int)GetProcAddress(dword_4FD990, aGpuwritedata);
  if ( !GPUwriteData )
    ui_error(aGetprocaddress, (char)aGpuwritedata);
  GPUwriteStatus = (int)GetProcAddress(dword_4FD990, aGpuwritestatus);
  if ( !GPUwriteStatus )
    ui_error(aGetprocaddress, (char)aGpuwritestatus);
  GPUreadData = (int)GetProcAddress(dword_4FD990, aGpureaddata);
  if ( !GPUreadData )
    ui_error(aGetprocaddress, (char)aGpureaddata);
  GPUreadStatus = (int)GetProcAddress(dword_4FD990, aGpureadstatus);
  if ( !GPUreadStatus )
    ui_error(aGetprocaddress, (char)aGpureadstatus);
  GPUdmaChain = (int)GetProcAddress(dword_4FD990, aGpudmachain);
  if ( !GPUdmaChain )
    ui_error(aGetprocaddress, (char)aGpudmachain);
  GPUgetMode = (int)GetProcAddress(dword_4FD990, aGpugetmode);
  if ( !GPUgetMode )
    ui_error(aGetprocaddress, (char)aGpugetmode);
  GPUsetMode = (int)GetProcAddress(dword_4FD990, aGpusetmode);
  if ( !GPUsetMode )
    ui_error(aGetprocaddress, (char)aGpusetmode);
  GPUupdateLace = (int)GetProcAddress(dword_4FD990, aGpuupdatelace);
  if ( !GPUupdateLace )
    ui_error(aGetprocaddress, (char)aGpuupdatelace);
  GPUmakeSnapshot = (int)GetProcAddress(dword_4FD990, aGpumakesnapsho);
  GPUwriteDataMem = (int)GetProcAddress(dword_4FD990, aGpuwritedatame);
  GPUreadDataMem = (int)GetProcAddress(dword_4FD990, aGpureaddatamem);
  GPUdisplayFlags = (int)GetProcAddress(dword_4FD990, aGpudisplayflag);
  GPUfreeze = (int)GetProcAddress(dword_4FD990, aGpufreeze);
  GPUgetScreenPic = (int)GetProcAddress(dword_4FD990, aGpugetscreenpi);
  GPUshowScreenPic = (int)GetProcAddress(dword_4FD990, aGpushowscreenp);
  GPUcursor = (int)GetProcAddress(dword_4FD990, aGpucursor);
  GPUclearDynarec = GetProcAddress(dword_4FD990, aGpucleardynare);
  dword_50ADD4 = (int)GPUclearDynarec;
  if ( GPUclearDynarec )
    ((void (__stdcall *)(int (*)()))GPUclearDynarec)(sub_42DED0);
  v2 = GPUinit();
  dbg_print(aDoingInitGpuD, v2);
  net_load_plugin();
  net_open();
  netplay_handler();
  return create_save_load_window();
}
