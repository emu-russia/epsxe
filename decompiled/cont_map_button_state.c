#include "pch.h"
__int16 __cdecl cont_map_button_state(unsigned __int16 a1, __int16 a2)
{
  __int16 result; // ax

  result = a2;
  if ( a2 != 1 )
    Keys1[a1] = a2;
  return result;
}
