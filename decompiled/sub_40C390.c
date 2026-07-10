#include "pch.h"
int sub_40C390()
{
  int result; // eax
  int v1; // esi
  int v2; // ebx
  int v3; // edi
  char *v4; // ecx
  _WORD *v5; // eax
  int v6; // edx
  int v7; // edi
  char v8; // dl
  unsigned int v9; // ecx
  char *v10; // esi

  if ( dword_4F75A0 == 1 )
  {
    result = ++dword_4F75A4;
    dword_4F75A0 = (unsigned int)dword_4F75A4 <= 0x40;
  }
  else
  {
    dword_4F75A4 = 0;
    (*(void (__stdcall **)(int, int *, void *))(*(_DWORD *)dword_45B8FC + 16))(dword_45B8FC, &dword_465534, &unk_4EF134);
    v1 = dword_4F7598;
    result = dword_465534;
    if ( dword_4F7598 > (unsigned int)dword_465534 )
    {
      v2 = dword_465534 + dword_44F708 - dword_4F7598;
    }
    else
    {
      result = dword_465534 - dword_4F7598;
      v2 = dword_465534 - dword_4F7598;
    }
    for ( ; v2 >= 256; v2 -= 256 )
    {
      if ( dword_4F75A0 == 1 )
        break;
      v3 = dword_4F7594;
      if ( !dword_4F7594 )
      {
        sub_40C8B0();
        v1 = dword_4F7598;
        v3 = dword_4F7594;
      }
      v4 = byte_463910;
      v5 = &unk_4F7150;
      do
      {
        *(_WORD *)v4 = *v5;
        v6 = *(_DWORD *)v5;
        if ( *(int *)v5 > 0x7FFF )
          *(_WORD *)v4 = 0x7FFF;
        if ( v6 < -32767 )
          *(_WORD *)v4 = -32767;
        if ( v3 )
          *(_WORD *)v4 = 0;
        v5 += 2;
        v4 += 2;
      }
      while ( (int)v5 < (int)MEMORY[0x4F7350] );
      result = (*(int (__stdcall **)(int, int, int, int *, int *, int *, int *, _DWORD))(*(_DWORD *)dword_45B8FC + 44))(
                 dword_45B8FC,
                 v1,
                 256,
                 &dword_463908,
                 &dword_4F7590,
                 &dword_46390C,
                 &dword_4F758C,
                 0);
      if ( result )
        break;
      qmemcpy((void *)dword_463908, byte_463910, dword_4F7590);
      v7 = dword_46390C;
      if ( dword_46390C )
      {
        v8 = dword_4F758C;
        v9 = (unsigned int)dword_4F758C >> 2;
        v10 = (char *)(2 * dword_4F7590 + 4602128);
        qmemcpy((void *)dword_46390C, v10, 4 * ((unsigned int)dword_4F758C >> 2));
        qmemcpy((void *)(v7 + 4 * v9), &v10[4 * v9], v8 & 3);
        v7 = dword_46390C;
      }
      result = (*(int (__stdcall **)(int, int, int, int, int))(*(_DWORD *)dword_45B8FC + 76))(
                 dword_45B8FC,
                 dword_463908,
                 dword_4F7590,
                 v7,
                 dword_4F758C);
      if ( result )
        break;
      result = dword_44F708;
      v1 = dword_4F7598 + 256;
      dword_4F7598 += 256;
      if ( dword_4F7598 >= (unsigned int)dword_44F708 )
      {
        v1 = 0;
        dword_4F7598 = 0;
      }
    }
  }
  return result;
}
