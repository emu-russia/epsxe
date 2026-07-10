#include "pch.h"
int sub_40E2C0()
{
  if ( dword_4F75C8 && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 28))(dword_4F75C8);
  return 1;
}
