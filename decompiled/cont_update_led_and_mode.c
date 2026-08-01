#include "pch.h"
int (__stdcall *__cdecl cont_update_led_and_mode(unsigned __int8 a1))(_DWORD)
{
  int v1; // eax
  int (__stdcall *result)(_DWORD); // eax

  v1 = dword_456048[a1];
  if ( v1 == 4 || v1 == 5 || v1 == 6 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0) << 8));
  if ( dword_456048[a1] == 2 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0 ? 2 : 0) << 8));
  if ( dword_456048[a1] == 3 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0 ? 3 : 0) << 8));
  result = (int (__stdcall *)(_DWORD))dword_456048[a1];
  if ( (unsigned int)result <= 1 )
    return gpu_display_flags((a1 + 1) << 12);
  return result;
}
