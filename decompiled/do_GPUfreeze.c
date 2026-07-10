#include "pch.h"
int (__stdcall *__cdecl sub_42EE00(int a1))(_DWORD, DWORD)
{
  int (__stdcall *result)(DWORD, DWORD); // eax

  result = GPUfreeze;
  if ( GPUfreeze )
    return (int (__stdcall *)(DWORD, DWORD))GPUfreeze(2, &a1);
  return result;
}
