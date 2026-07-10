#include "pch.h"
char spu_destroy()
{
  char result; // al

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      result = (char)hSpuModule;
      if ( hSpuModule )
      {
        dbg_print(" * Closing spu ... \n");
        if ( !byte_45B8F0 )
        {
          SPUclose();
          byte_45B8F0 = 1;
        }
        result = SPUshutdown();
        hSpuModule = nullptr;
      }
    }
  }
  return result;
}
