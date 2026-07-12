#include "pch.h"
void sub_429380()
{
  int v0; // esi
  int v1; // eax

  v0 = dword_5164E0[0];
  if ( dword_5164E8[0] == 0x1000201 )
  {
    if ( mdec_disable )
      LOBYTE(dword_4FD888[0]) = 1;
    v1 = *(_DWORD *)dword_4FC4F0;
    if ( *(_DWORD *)dword_4FC4F0 == 0x40000001 )
    {
      sub_429540((int)ram + (dword_5164E0[0] & 0x1FFFFF));
      v1 = *(_DWORD *)dword_4FC4F0;
    }
    if ( (v1 & 0xF5FF0000) == 0x30000000 )
    {
      dword_4FC4FC = (int)ram + (v0 & 0x1FFFFF);
      dword_4FC500 = (int)ram + (v0 & 0x1FFFFF);
    }
  }
}
