#include "pch.h"
char spu_open()
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
        result = SPUopen(dword_4FD98C);
        byte_45B8F0 = 0;
      }
    }
  }
  return result;
}
