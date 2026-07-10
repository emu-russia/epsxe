#include "pch.h"
char spu_close()
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
        result = SPUclose();
        byte_45B8F0 = 1;
      }
    }
  }
  return result;
}
