#include "pch.h"
int spucore_destroy()
{
  int result; // eax

  result = spucore_init_flag;
  if ( spucore_init_flag )
  {
    pDSBuffer->lpVtbl->Stop(pDSBuffer);
    while ( pDSBuffer->lpVtbl->Release(pDSBuffer) )
      ;
    while ( ppDS->lpVtbl->Release(ppDS) )
      ;
    return dbg_print(" * Closing core spu...\n");
  }
  return result;
}
