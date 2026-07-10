#include "pch.h"
int mdec_decode()
{
  int result; // eax
  char *v1; // ebx
  __m64 *v2; // esi
  int v3; // ebp
  int v4; // ecx
  int v5; // edi
  int v6; // eax
  bool v7; // cc
  int v8; // [esp+0h] [ebp-4h]

  result = HIWORD(dword_5164F0) * (unsigned __int16)dword_5164F0;
  if ( dword_5164F4 == 0x1000200 )
  {
    v1 = (char *)dword_4FC4FC;
    if ( dword_4FC4FC )
    {
      if ( mdec_disable )
      {
        LOBYTE(dword_4FD888[0]) = 1;
        return result;
      }
      v2 = (__m64 *)((char *)ram_0 + (dword_5164EC & 0x1FFFFF));
      v3 = dword_4FC4F0 & 0x8000000;
      v4 = 3 * result;
      if ( (dword_4FC4F0 & 0x8000000) == 0 )
        v4 = 2 * result;
      v5 = v4 / 384;
      if ( v4 / 384 < 31 )
        goto LABEL_15;
      v6 = v5 / 30;
      v7 = v5 / 30 <= 0;
      v5 %= 30;
      if ( !v7 )
      {
        v8 = v6;
        do
        {
          dword_4FC4FC = (int)sub_429A70(v1, 30);
          sub_429B90(30);
          if ( v3 )
          {
            sub_429D20((char *)dword_512140, v2, 30);
            v2 += 1920;
          }
          else
          {
            sub_42A950((unsigned int *)dword_512140, v2, 30);
            v2 += 2880;
          }
          v1 = (char *)dword_4FC4FC;
          --v8;
        }
        while ( v8 );
      }
      if ( v5 )
      {
LABEL_15:
        dword_4FC4FC = (int)sub_429A70(v1, v5);
        sub_429B90(v5);
        if ( v3 )
          sub_429D20((char *)dword_512140, v2, v5);
        else
          sub_42A950((unsigned int *)dword_512140, v2, v5);
      }
    }
    result = mdectiming;
    if ( mdectiming )
    {
      dword_4FC504 = 0x44000000;
      dword_4FC4F8 = -65536;
      byte_4FC508 = 1;
    }
  }
  return result;
}
