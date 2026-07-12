#include "pch.h"
int (__stdcall *__cdecl do_GPUfreeze(int a1))(_DWORD, _DWORD)
{
  int (__stdcall *result)(_DWORD, _DWORD); // eax

  result = GPUfreeze;
  if ( GPUfreeze )
    return (int (__stdcall *)(_DWORD, _DWORD))GPUfreeze(2, &a1);
  return result;
}
