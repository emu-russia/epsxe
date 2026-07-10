#include "pch.h"
char ext_CDRstop()
{
  char result; // al

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = (char)CDRstop;
    if ( CDRstop )
      return CDRstop();
  }
  return result;
}
