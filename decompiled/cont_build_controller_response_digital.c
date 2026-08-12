#include "pch.h"
_BYTE *__cdecl cont_build_controller_response_digital(char a1, _BYTE *a2)
{
  _BYTE *result; // eax

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad1_buttons_high;
      a2[4] = pad1_buttons_low;
      result = a2;
      break;
    case 1:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad2_buttons_high;
      a2[4] = pad2_buttons_low;
      result = a2;
      break;
    case 2:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad3_buttons_high;
      a2[4] = pad3_buttons_low;
      result = a2;
      break;
    case 3:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = pad4_buttons_high;
      a2[4] = pad4_buttons_low;
      result = a2;
      break;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = -1;
      a2[3] = -1;
      a2[4] = -1;
      result = a2;
      break;
  }
  return result;
}
