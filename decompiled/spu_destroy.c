#include "pch.h"
char spu_destroy()
{
  char result; // al

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = unk_8A8484;
    if ( unk_8A8484 )
    {
      result = (char)hModule;
      if ( hModule )
      {
        dbg_print(aClosingSpu);
        if ( !byte_45B8F0 )
        {
          SPUclose();
          byte_45B8F0 = 1;
        }
        result = SPUshutdown();
        hModule = nullptr;
      }
    }
  }
  return result;
}
