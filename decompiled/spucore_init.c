#include "pch.h"
int init_core_spu()
{
  int v0; // eax
  int result; // eax

  dbg_print(aInitCoreSpu);
  dword_4EF12C = (int)&spu_ram;
  sub_40C560();
  v0 = spu_init_internal_core();
  if ( forcespu == 1 )
    forcespu = 0;
  dword_4E7114 = 0;
  if ( !v0 )
  {
    dbg_print(aErrorCanTOpenS);
    fatal_error_with_message_box(aErrorCanTOpenS_0);
  }
  result = dbg_print(aOk);
  dword_4F75C0 = 1;
  return result;
}
