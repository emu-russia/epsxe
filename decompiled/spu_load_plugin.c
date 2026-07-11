#include "pch.h"
char spu_load_plugin()
{
  char result; // al
  HMODULE LibraryA; // eax
  CHAR LibFileName[1024]; // [esp+4h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)SoundPlugin);
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
    SPUconfigure = (int)GetProcAddress(hSpuModule, "SPUconfigure");
    if ( !SPUconfigure )
      ui_error(" * GetProcAddress error %s\n", "SPUconfigure");
    SPUabout = (int)GetProcAddress(hSpuModule, "SPUabout");
    if ( !SPUabout )
      ui_error(" * GetProcAddress error %s\n", "SPUabout");
    SPUtest = (int)GetProcAddress(hSpuModule, "SPUtest");
    if ( !SPUtest )
      ui_error(" * GetProcAddress error %s\n", "SPUtest");
    SPUplaySample = (int)GetProcAddress(hSpuModule, "SPUplaySample");
    if ( !SPUplaySample )
      ui_error(" * GetProcAddress error %s\n", "SPUplaySample");
    SPUstartChannels1 = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUstartChannels1");
    if ( !SPUstartChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels1");
    SPUstartChannels2 = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUstartChannels2");
    if ( !SPUstartChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels2");
    SPUstopChannels1 = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUstopChannels1");
    if ( !SPUstopChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels1");
    SPUstopChannels2 = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUstopChannels2");
    if ( !SPUstopChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels2");
    SPUputOne = (int)GetProcAddress(hSpuModule, "SPUputOne");
    if ( !SPUputOne )
      ui_error(" * GetProcAddress error %s\n", "SPUputOne");
    SPUgetOne = (int)GetProcAddress(hSpuModule, "SPUgetOne");
    if ( !SPUgetOne )
      ui_error(" * GetProcAddress error %s\n", "SPUgetOne");
    SPUsetAddr = (int)GetProcAddress(hSpuModule, "SPUsetAddr");
    if ( !SPUsetAddr )
      ui_error(" * GetProcAddress error %s\n", "SPUsetAddr");
    SPUsetPitch = (char (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUsetPitch");
    if ( !SPUsetPitch )
      ui_error(" * GetProcAddress error %s\n", "SPUsetPitch");
    SPUsetVolumeL = (char (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUsetVolumeL");
    if ( !SPUsetVolumeL )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeL");
    SPUsetVolumeR = (char (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUsetVolumeR");
    if ( !SPUsetVolumeR )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeR");
    SPUplayADPCMchannel = (int (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUplayADPCMchannel");
    if ( !SPUplayADPCMchannel )
      ui_error(" * GetProcAddress error %s\n", "SPUplayADPCMchannel");
    SPUwriteRegister = (char (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUwriteRegister");
    if ( !SPUwriteRegister )
      spu_use_external_plugin = 0;
    SPUreadRegister = (int)GetProcAddress(hSpuModule, "SPUreadRegister");
    if ( !SPUreadRegister )
      spu_use_external_plugin = 0;
    SPUwriteDMA = (int)GetProcAddress(hSpuModule, "SPUwriteDMA");
    if ( !SPUwriteDMA )
      spu_use_external_plugin = 0;
    SPUreadDMA = GetProcAddress(hSpuModule, "SPUreadDMA");
    if ( !SPUreadDMA )
      spu_use_external_plugin = 0;
    SPUregisterCallback = (char (__stdcall *)(_DWORD))GetProcAddress(hSpuModule, "SPUregisterCallback");
    SPUfreeze = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUfreeze");
    SPUupdate = (int)GetProcAddress(hSpuModule, "SPUupdate");
    SPUasync = (int)GetProcAddress(hSpuModule, "SPUasync");
    SPUreadDMAMem = (int)GetProcAddress(hSpuModule, "SPUreadDMAMem");
    SPUwriteDMAMem = (char (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hSpuModule, "SPUwriteDMAMem");
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
