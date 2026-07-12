#include "pch.h"
char spu_open()
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
        result = SPUopen(hOutputWnd);
        byte_45B8F0 = 0;
      }
    }
  }
  return result;
}
