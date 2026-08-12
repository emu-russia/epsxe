#include "pch.h"
char sio_reset_controller_state()
{
  unsigned int i; // eax

  sio_controller_state[0] = 0;
  sio_controller_slot_index = 0;
  sio_controller_state[2] = 0;
  sio_controller_state[1] = 0;
  for ( i = 3; i < 6; ++i )
  {
    sio_controller_state[i + 3] = -1;
    sio_controller_response_alt[i] = -1;
  }
  sio_controller_state[3] = 0;
  sio_controller_response_buffer[0] = 65;
  sio_response_buffer_id[0] = 90;
  sio_controller_response_alt[0] = 0;
  byte_5165A5 = 65;
  byte_5165A6 = 90;
  return 90;
}
