#include "pch.h"
int (__stdcall *gpu_hide_screen_pic())(_DWORD)
{
  int (__stdcall *result)(_DWORD); // eax

  result = GPUshowScreenPic;
  if ( GPUshowScreenPic )
    return (int (__stdcall *)(_DWORD))GPUshowScreenPic(0);
  return result;
}
