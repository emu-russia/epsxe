#include "pch.h"
char __cdecl sub_431760(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, BYTE *a5)
{
  char v6; // [esp+4h] [ebp-Ch] BYREF
  __int16 v7; // [esp+5h] [ebp-Bh]
  char v8; // [esp+7h] [ebp-9h]
  char v9; // [esp+8h] [ebp-8h]
  __int16 v10; // [esp+9h] [ebp-7h]
  char v11; // [esp+Bh] [ebp-5h]
  int v12; // [esp+Ch] [ebp-4h]

  if ( !byte_4FD9C8 )
  {
    if ( sub_4315A0() != 1 )
      return 1;
    byte_4FD9C8 = 1;
  }
  v11 = 0;
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = 40;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  return W9x_exec_scsi_cmd(&v6, 0xAu, a5, 2352 * a4);
}
