#include "pch.h"
int (__stdcall *__cdecl gpu_display_flags(int a1))(_DWORD)
{
  int (__stdcall *result)(_DWORD); // eax

  result = GPUdisplayFlags;
  if ( GPUdisplayFlags )
    return (int (__stdcall *)(_DWORD))GPUdisplayFlags(a1);
  return result;
}
