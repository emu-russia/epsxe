#include "pch.h"
char spu_load_plugin()
{
  char result; // al
  HMODULE LibraryA; // eax
  CHAR LibFileName[1024]; // [esp+4h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", aPlugins, (const char *)SoundPlugin);
  result = sound_enabled;
  spu_need_to_be_closed = 0;
  if ( sound_enabled )
  {
    spu_need_to_be_closed = 1;
    LibraryA = LoadLibraryA(LibFileName);
    hSpuModule = LibraryA;
    if ( !LibraryA )
      fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
    SPUinit = GetProcAddress(LibraryA, "SPUinit");
    if ( !SPUinit )
      ui_error(" * GetProcAddress error %s\n", "SPUinit");
    SPUshutdown = GetProcAddress(hSpuModule, "SPUshutdown");
    if ( !SPUshutdown )
      ui_error(" * GetProcAddress error %s\n", "SPUshutdown");
    SPUopen = (int (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUopen");
    if ( !SPUopen )
      ui_error(" * GetProcAddress error %s\n", "SPUopen");
    SPUclose = GetProcAddress(hSpuModule, "SPUclose");
    if ( !SPUclose )
      ui_error(" * GetProcAddress error %s\n", "SPUclose");
    SPUconfigure = GetProcAddress(hSpuModule, "SPUconfigure");
    if ( !SPUconfigure )
      ui_error(" * GetProcAddress error %s\n", "SPUconfigure");
    SPUabout = GetProcAddress(hSpuModule, "SPUabout");
    if ( !SPUabout )
      ui_error(" * GetProcAddress error %s\n", "SPUabout");
    SPUtest = GetProcAddress(hSpuModule, "SPUtest");
    if ( !SPUtest )
      ui_error(" * GetProcAddress error %s\n", "SPUtest");
    SPUplaySample = GetProcAddress(hSpuModule, "SPUplaySample");
    if ( !SPUplaySample )
      ui_error(" * GetProcAddress error %s\n", "SPUplaySample");
    SPUstartChannels1 = GetProcAddress(hSpuModule, "SPUstartChannels1");
    if ( !SPUstartChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels1");
    SPUstartChannels2 = GetProcAddress(hSpuModule, "SPUstartChannels2");
    if ( !SPUstartChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels2");
    SPUstopChannels1 = GetProcAddress(hSpuModule, "SPUstopChannels1");
    if ( !SPUstopChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels1");
    SPUstopChannels2 = GetProcAddress(hSpuModule, "SPUstopChannels2");
    if ( !SPUstopChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels2");
    *(_DWORD *)&SPUputOne = GetProcAddress(hSpuModule, "SPUputOne");
    if ( !*(_DWORD *)&SPUputOne )
      ui_error(" * GetProcAddress error %s\n", "SPUputOne");
    *(_DWORD *)&SPUgetOne = GetProcAddress(hSpuModule, "SPUgetOne");
    if ( !*(_DWORD *)&SPUgetOne )
      ui_error(" * GetProcAddress error %s\n", "SPUgetOne");
    *(_DWORD *)&SPUsetAddr = GetProcAddress(hSpuModule, "SPUsetAddr");
    if ( !*(_DWORD *)&SPUsetAddr )
      ui_error(" * GetProcAddress error %s\n", "SPUsetAddr");
    SPUsetPitch = GetProcAddress(hSpuModule, "SPUsetPitch");
    if ( !SPUsetPitch )
      ui_error(" * GetProcAddress error %s\n", "SPUsetPitch");
    SPUsetVolumeL = GetProcAddress(hSpuModule, "SPUsetVolumeL");
    if ( !SPUsetVolumeL )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeL");
    SPUsetVolumeR = GetProcAddress(hSpuModule, "SPUsetVolumeR");
    if ( !SPUsetVolumeR )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeR");
    SPUplayADPCMchannel = GetProcAddress(hSpuModule, "SPUplayADPCMchannel");
    if ( !SPUplayADPCMchannel )
      ui_error(" * GetProcAddress error %s\n", "SPUplayADPCMchannel");
    SPUwriteRegister = GetProcAddress(hSpuModule, "SPUwriteRegister");
    if ( !SPUwriteRegister )
      spu_use_external_plugin = 0;
    *(_DWORD *)&SPUreadRegister = GetProcAddress(hSpuModule, "SPUreadRegister");
    if ( !*(_DWORD *)&SPUreadRegister )
      spu_use_external_plugin = 0;
    *(_DWORD *)&SPUwriteDMA = GetProcAddress(hSpuModule, "SPUwriteDMA");
    if ( !*(_DWORD *)&SPUwriteDMA )
      spu_use_external_plugin = 0;
    SPUreadDMA = GetProcAddress(hSpuModule, "SPUreadDMA");
    if ( !SPUreadDMA )
      spu_use_external_plugin = 0;
    SPUregisterCallback = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUregisterCallback");
    SPUfreeze = GetProcAddress(hSpuModule, "SPUfreeze");
    SPUupdate = GetProcAddress(hSpuModule, "SPUupdate");
    SPUasync = GetProcAddress(hSpuModule, "SPUasync");
    *(_DWORD *)&SPUreadDMAMem = GetProcAddress(hSpuModule, "SPUreadDMAMem");
    SPUwriteDMAMem = GetProcAddress(hSpuModule, "SPUwriteDMAMem");
    dbg_print(" * Doing spu init... \n");
    SPUinit();
    dbg_print(" * Spu open... \n");
    SPUopen(hSaveLoadWnd);
    result = (char)SPUregisterCallback;
    if ( SPUregisterCallback )
      return SPUregisterCallback(spu_registered_callback);
  }
  else
  {
    spu_use_external_plugin = 0;
  }
  return result;
}
