#include "pch.h"
int sub_40E2E0()
{
  int v1; // eax
  int v2; // eax
  _DWORD v3[3]; // [esp+Ch] [ebp-14h] BYREF
  _BYTE v4[8]; // [esp+18h] [ebp-8h]

  if ( !point_device_enabled )
    return 0;
  v1 = dword_4F75C8;
  dword_4F82F0 = 0;
  dword_4F82F4[0] = 0;
  if ( dword_4F75C8 && dword_4F82EC == 1 )
  {
    while ( 1 )
    {
      v2 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v1 + 36))(v1, 16, v3);
      if ( v2 != 0x8007001E )
        break;
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 28))(dword_4F75C8) < 0 )
        return 0;
      v1 = dword_4F75C8;
    }
    if ( v2 < 0 )
      return 0;
    dword_4F82F0 = 3 * v3[0];
    dword_4F82F4[0] = 3 * v3[1];
    dword_4F7784 = (v4[3] | ((v4[2] | ((unsigned int)(v4[1] | (v4[0] >> 1)) >> 1)) >> 1)) >> 4;
  }
  return 1;
}
