#include "pch.h"
int spucore_destroy()
{
  int result; // eax

  result = spucore_init_flag;
  if ( spucore_init_flag )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_45B8FC + 72))(dword_45B8FC);
    while ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_45B8FC + 8))(dword_45B8FC) )
      ;
    while ( ppDS->lpVtbl->Release(ppDS) )
      ;
    return dbg_print(" * Closing core spu...\n");
  }
  return result;
}
