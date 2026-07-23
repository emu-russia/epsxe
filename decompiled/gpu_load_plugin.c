#include "pch.h"
HWND gpu_load_plugin()
{
  HMODULE LibraryA; // eax
  FARPROC GPUclearDynarec; // eax
  int v2; // eax
  CHAR LibFileName[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( !strcmp((const char *)VideoPlugin, "NULL") )
    fatal_error_with_message_box(" * !Error video doesn't configurated \n * !Go Config->Video and choose a plugin. \n");
  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)VideoPlugin);
  LibraryA = LoadLibraryA(LibFileName);
  hGpuModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
  gpu_closed = 1;
  GPUinit = GetProcAddress(LibraryA, "GPUinit");
  if ( !GPUinit )
    ui_error(" * GetProcAddress error %s\n", "GPUinit");
  GPUshutdown = GetProcAddress(hGpuModule, "GPUshutdown");
  if ( !GPUshutdown )
    ui_error(" * GetProcAddress error %s\n", "GPUshutdown");
  GPUopen = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUopen");
  if ( !GPUopen )
    ui_error(" * GetProcAddress error %s\n", "GPUopen");
  GPUclose = GetProcAddress(hGpuModule, "GPUclose");
  if ( !GPUclose )
    ui_error(" * GetProcAddress error %s\n", "GPUclose");
  GPUconfigure = (int)GetProcAddress(hGpuModule, "GPUconfigure");
  if ( !GPUconfigure )
    ui_error(" * GetProcAddress error %s\n", "GPUconfigure");
  GPUabout = (int)GetProcAddress(hGpuModule, "GPUabout");
  if ( !GPUabout )
    ui_error(" * GetProcAddress error %s\n", "GPUabout");
  GPUtest = (int)GetProcAddress(hGpuModule, "GPUtest");
  if ( !GPUtest )
    ui_error(" * GetProcAddress error %s\n", "GPUtest");
  GPUwriteData = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUwriteData");
  if ( !GPUwriteData )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteData");
  GPUwriteStatus = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUwriteStatus");
  if ( !GPUwriteStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteStatus");
  GPUreadData = GetProcAddress(hGpuModule, "GPUreadData");
  if ( !GPUreadData )
    ui_error(" * GetProcAddress error %s\n", "GPUreadData");
  GPUreadStatus = GetProcAddress(hGpuModule, "GPUreadStatus");
  if ( !GPUreadStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUreadStatus");
  GPUdmaChain = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUdmaChain");
  if ( !GPUdmaChain )
    ui_error(" * GetProcAddress error %s\n", "GPUdmaChain");
  GPUgetMode = (int)GetProcAddress(hGpuModule, "GPUgetMode");
  if ( !GPUgetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUgetMode");
  GPUsetMode = (int)GetProcAddress(hGpuModule, "GPUsetMode");
  if ( !GPUsetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUsetMode");
  GPUupdateLace = (int (__fastcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUupdateLace");
  if ( !GPUupdateLace )
    ui_error(" * GetProcAddress error %s\n", "GPUupdateLace");
  GPUmakeSnapshot = (int (*(*)(void))(void))GetProcAddress(hGpuModule, "GPUmakeSnapshot");
  GPUwriteDataMem = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUwriteDataMem");
  GPUreadDataMem = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUreadDataMem");
  GPUdisplayFlags = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUdisplayFlags");
  GPUfreeze = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUfreeze");
  GPUgetScreenPic = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUgetScreenPic");
  GPUshowScreenPic = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUshowScreenPic");
  GPUcursor = (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUcursor");
  GPUclearDynarec = GetProcAddress(hGpuModule, "GPUclearDynarec");
  dword_50ADD4 = (int)GPUclearDynarec;
  if ( GPUclearDynarec )
    ((void (__stdcall *)(void (*)()))GPUclearDynarec)(gpu_sub_42DED0);
  v2 = GPUinit();
  dbg_print(" * Doing init gpu[%d]... \n", v2);
  net_load_plugin();
  net_open();
  net_netplay_handler();
  return gpu_create_output_window();
}
