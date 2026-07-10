#include "pch.h"
char spu_close()
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
        result = SPUclose();
        byte_45B8F0 = 1;
      }
    }
  }
  return result;
}
