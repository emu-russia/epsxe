#include "pch.h"
int sub_40E240()
{
  if ( dword_4F75C8 && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 32))(dword_4F75C8);
  if ( dword_4F7A5C )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7A5C + 32))(dword_4F7A5C);
  if ( dword_4F776C[0] )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F776C[0] + 32))(dword_4F776C[0]);
  if ( dword_4F7770 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7770 + 32))(dword_4F7770);
  if ( dword_4F7774 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7774 + 32))(dword_4F7774);
  if ( dword_4F7778 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7778 + 32))(dword_4F7778);
  dword_4F82EC = 0;
  return 1;
}
