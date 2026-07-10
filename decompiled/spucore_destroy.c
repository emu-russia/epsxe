#include "pch.h"
int spu_close_core()
{
  int result; // eax

  result = dword_4F75C0;
  if ( dword_4F75C0 )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_45B8FC + 72))(dword_45B8FC);
    while ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_45B8FC + 8))(dword_45B8FC) )
      ;
    while ( ppDS->lpVtbl->Release(ppDS) )
      ;
    return dbg_print(aClosingCoreSpu);
  }
  return result;
}
