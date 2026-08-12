#include "pch.h"
_BYTE *__cdecl cont_build_mouse_response(char a1, _BYTE *a2)
{
  _BYTE *result; // eax

  if ( a1 )
  {
    result = a2;
    a2[3] = -1;
    a2[2] = 90;
    a2[1] = 18;
    *a2 = 0;
    if ( a1 != 1 )
    {
      a2[4] = -1;
      a2[6] = -1;
      a2[5] = -1;
      return result;
    }
  }
  else
  {
    result = a2;
    *a2 = 0;
    a2[1] = 18;
    a2[2] = 90;
    a2[3] = -1;
  }
  result[4] = -4;
  if ( (mouse_buttons_state & 1) != 0 )
    result[4] = -12;
  if ( (mouse_buttons_state & 2) != 0 )
    result[4] &= ~4u;
  result[5] = mouse_delta_x;
  result[6] = mouse_delta_y;
  return result;
}
