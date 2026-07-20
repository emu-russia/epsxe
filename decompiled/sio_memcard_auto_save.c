#include "pch.h"
char sio_memcard_auto_save()
{
  int v0; // eax

  v0 = sio_memcard1_dirty_counter;
  if ( sio_memcard1_dirty_counter )
    v0 = ++sio_memcard1_dirty_counter;
  if ( sio_memcard2_dirty_counter )
    ++sio_memcard2_dirty_counter;
  if ( v0 == 120 )
  {
    sio_memcard1_dirty_counter = 0;
    LOBYTE(v0) = sio_memcard1_save();
  }
  if ( sio_memcard2_dirty_counter == 120 )
  {
    sio_memcard2_dirty_counter = 0;
    LOBYTE(v0) = sio_memcard2_save();
  }
  return v0;
}
