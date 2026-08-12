#include "pch.h"
unsigned int __cdecl sio_build_multitap_response(_BYTE *a1, _DWORD *a2)
{
  int *v2; // ecx
  int *v3; // esi
  int v4; // edi
  unsigned int result; // eax

  sio_multitap_state = 0;
  *a2 = 3;
  v2 = &sio_multitap_state;
  v3 = controller_port_modes;
  v4 = 4;
  do
  {
    *(_BYTE *)v2 = *(_BYTE *)a2;
    ++v3;
    v2 = (int *)((char *)v2 + 1);
    --v4;
    *a2 += 8;
  }
  while ( v4 );
  *a1 = 1;
  a1[1] = 0x80;
  result = *a2 - 3;
  a1[2] = 90;
  if ( result < 0x20 )
  {
    result >>= 1;
    LOBYTE(result) = result | 0x80;
    a1[1] = result;
  }
  return result;
}
