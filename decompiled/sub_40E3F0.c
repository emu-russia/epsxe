#include "pch.h"
unsigned int __cdecl sub_40E3F0(int a1, _DWORD *a2)
{
  int v3; // [esp+8h] [ebp-1Ch]
  _BYTE v4[16]; // [esp+14h] [ebp-10h] BYREF

  if ( *a2 )
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*a2 + 8))(*a2);
  v3 = a2[1];
  *a2 = 0;
  if ( (*(int (__stdcall **)(int, int (__stdcall *)(_DWORD *, _DWORD *), _BYTE *, int))(*(_DWORD *)a1 + 76))(
         a1,
         sub_40E3C0,
         v4,
         v3) >= 0 )
    return (*(int (__stdcall **)(int, _BYTE *, _DWORD *, _DWORD *, _DWORD))(*(_DWORD *)a1 + 72))(a1, v4, a2 + 2, a2, 0) >= 0
         ? 0
         : 0x80004005;
  else
    return 0x80004005;
}
