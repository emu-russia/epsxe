#include "pch.h"
int spucore_init()
{
  int inited; // eax
  int result; // eax

  dbg_print(" * Init core spu ... ");
  dword_4EF12C = (int)spu_ram;
  sub_40C560();
  inited = spu_init_internal_core();
  if ( forcespu == 1 )
    forcespu = 0;
  dword_4E7114 = 0;
  if ( !inited )
  {
    dbg_print("Error: can't open sound handler.\n");
    fatal_error_with_message_box(" * Error can't open sound handler. (try -nosound)\n");
  }
  result = dbg_print(" ok \n");
  dword_4F75C0 = 1;
  return result;
}
