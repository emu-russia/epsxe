#include "pch.h"
bool __cdecl sio_controller_init(__int16 a1)
{
  bool result; // al

  if ( (a1 & 2) != 0 )
  {
    result = (a1 & 0x2000) != 0;
    sio_controller_state[0] = result;
  }
  else
  {
    sio_controller_slot_index = 0;
    sio_controller_state[2] = 0;
    sio_controller_state[0] = 0x80;
    return 0;
  }
  return result;
}
