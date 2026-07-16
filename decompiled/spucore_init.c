#include "pch.h"
int spucore_init()
{
  int inited; // eax
  int result; // eax

  dbg_print(" * Init core spu ... ");
  spu_ram_ptr = (int)spu_ram;
  spucore_init_gauss_table();
  inited = spucore_init_dsound();
  if ( forcespu == 1 )
    forcespu = 0;
  dword_4E7114 = 0;
  if ( !inited )
  {
    dbg_print("Error: can't open sound handler.\n");
    fatal_error_with_message_box(" * Error can't open sound handler. (try -nosound)\n");
  }
  result = dbg_print(" ok \n");
  spucore_init_flag = 1;
  return result;
}
