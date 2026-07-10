#include "pch.h"
int (__stdcall *__cdecl sub_42EE20(int a1, int a2, int a3))(_DWORD, _DWORD, _DWORD)
{
  int (__stdcall *result)(_DWORD, _DWORD, _DWORD); // eax

  result = GPUcursor;
  if ( GPUcursor )
    return (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GPUcursor(a1, a2, a3);
  return result;
}
