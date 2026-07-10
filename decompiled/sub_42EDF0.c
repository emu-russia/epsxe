#include "pch.h"
int (__stdcall *sub_42EDF0())(_DWORD)
{
  int (__stdcall *result)(_DWORD); // eax

  result = GPUshowScreenPic;
  if ( GPUshowScreenPic )
    return (int (__stdcall *)(_DWORD))GPUshowScreenPic(0);
  return result;
}
