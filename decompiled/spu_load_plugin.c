#include "pch.h"
char spu_load_plugin()
{
  char result; // al
  HMODULE LibraryA; // eax
  CHAR LibFileName[1024]; // [esp+4h] [ebp-400h] BYREF

  sprintf(LibFileName, "%s%s", aPlugins, (const char *)byte_8B1D80);
  result = sound_enabled;
  unk_8A8484 = 0;
  if ( sound_enabled )
  {
    unk_8A8484 = 1;
    LibraryA = LoadLibraryA(LibFileName);
    hModule = LibraryA;
    if ( !LibraryA )
      fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
    SPUinit = GetProcAddress(LibraryA, aSpuinit);
    if ( !SPUinit )
      ui_error(" * GetProcAddress error %s\n", aSpuinit);
    SPUshutdown = GetProcAddress(hModule, aSpushutdown);
    if ( !SPUshutdown )
      ui_error(" * GetProcAddress error %s\n", aSpushutdown);
    SPUopen = (int (__stdcall *)(_DWORD))GetProcAddress(hModule, aSpuopen);
    if ( !SPUopen )
      ui_error(" * GetProcAddress error %s\n", aSpuopen);
    SPUclose = GetProcAddress(hModule, aSpuclose);
    if ( !SPUclose )
      ui_error(" * GetProcAddress error %s\n", aSpuclose);
    SPUconfigure = GetProcAddress(hModule, aSpuconfigure);
    if ( !SPUconfigure )
      ui_error(" * GetProcAddress error %s\n", aSpuconfigure);
    SPUabout = GetProcAddress(hModule, aSpuabout);
    if ( !SPUabout )
      ui_error(" * GetProcAddress error %s\n", aSpuabout);
    SPUtest = GetProcAddress(hModule, aSputest);
    if ( !SPUtest )
      ui_error(" * GetProcAddress error %s\n", aSputest);
    SPUplaySample = GetProcAddress(hModule, aSpuplaysample);
    if ( !SPUplaySample )
      ui_error(" * GetProcAddress error %s\n", aSpuplaysample);
    SPUstartChannels1 = GetProcAddress(hModule, aSpustartchanne);
    if ( !SPUstartChannels1 )
      ui_error(" * GetProcAddress error %s\n", aSpustartchanne);
    SPUstartChannels2 = GetProcAddress(hModule, aSpustartchanne_0);
    if ( !SPUstartChannels2 )
      ui_error(" * GetProcAddress error %s\n", aSpustartchanne_0);
    SPUstopChannels1 = GetProcAddress(hModule, aSpustopchannel);
    if ( !SPUstopChannels1 )
      ui_error(" * GetProcAddress error %s\n", aSpustopchannel);
    SPUstopChannels2 = GetProcAddress(hModule, aSpustopchannel_0);
    if ( !SPUstopChannels2 )
      ui_error(" * GetProcAddress error %s\n", aSpustopchannel_0);
    *(_DWORD *)&SPUputOne = GetProcAddress(hModule, aSpuputone);
    if ( !*(_DWORD *)&SPUputOne )
      ui_error(" * GetProcAddress error %s\n", aSpuputone);
    *(_DWORD *)&SPUgetOne = GetProcAddress(hModule, aSpugetone);
    if ( !*(_DWORD *)&SPUgetOne )
      ui_error(" * GetProcAddress error %s\n", aSpugetone);
    SPUsetAddr = GetProcAddress(hModule, aSpusetaddr);
    if ( !SPUsetAddr )
      ui_error(" * GetProcAddress error %s\n", aSpusetaddr);
    SPUsetPitch = GetProcAddress(hModule, aSpusetpitch);
    if ( !SPUsetPitch )
      ui_error(" * GetProcAddress error %s\n", aSpusetpitch);
    SPUsetVolumeL = GetProcAddress(hModule, aSpusetvolumel);
    if ( !SPUsetVolumeL )
      ui_error(" * GetProcAddress error %s\n", aSpusetvolumel);
    SPUsetVolumeR = GetProcAddress(hModule, aSpusetvolumer);
    if ( !SPUsetVolumeR )
      ui_error(" * GetProcAddress error %s\n", aSpusetvolumer);
    SPUplayADPCMchannel = GetProcAddress(hModule, aSpuplayadpcmch);
    if ( !SPUplayADPCMchannel )
      ui_error(" * GetProcAddress error %s\n", aSpuplayadpcmch);
    SPUwriteRegister = GetProcAddress(hModule, aSpuwriteregist);
    if ( !SPUwriteRegister )
      spu_use_external_plugin = 0;
    SPUreadRegister = GetProcAddress(hModule, aSpureadregiste);
    if ( !SPUreadRegister )
      spu_use_external_plugin = 0;
    SPUwriteDMA = GetProcAddress(hModule, aSpuwritedma);
    if ( !SPUwriteDMA )
      spu_use_external_plugin = 0;
    SPUreadDMA = GetProcAddress(hModule, aSpureaddma);
    if ( !SPUreadDMA )
      spu_use_external_plugin = 0;
    SPUregisterCallback = (char (__stdcall *)(_DWORD))GetProcAddress(hModule, aSpuregistercal);
    SPUfreeze = GetProcAddress(hModule, aSpufreeze);
    SPUupdate = GetProcAddress(hModule, aSpuupdate);
    SPUasync = GetProcAddress(hModule, aSpuasync);
    SPUreadDMAMem = GetProcAddress(hModule, aSpureaddmamem);
    SPUwriteDMAMem = GetProcAddress(hModule, aSpuwritedmamem);
    dbg_print(aDoingSpuInit);
    SPUinit();
    dbg_print(aSpuOpen);
    SPUopen(dword_4FD98C);
    result = (char)SPUregisterCallback;
    if ( SPUregisterCallback )
      return SPUregisterCallback(sub_42B070);
  }
  else
  {
    spu_use_external_plugin = 0;
  }
  return result;
}
