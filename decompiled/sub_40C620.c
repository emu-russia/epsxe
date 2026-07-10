#include "pch.h"
char __cdecl sub_40C620(int a1)
{
  unsigned __int16 v1; // cx
  int v2; // edi
  char v3; // bl
  int v4; // edx
  int v5; // eax
  unsigned __int8 v6; // cl
  int v7; // eax
  char result; // al
  __int16 v9; // di
  int v10; // eax
  int v11; // ebp
  int v12; // ebx
  int v13; // eax
  int v14; // [esp+10h] [ebp-14h]
  unsigned __int8 v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+18h] [ebp-Ch]
  char v17; // [esp+1Ch] [ebp-8h]
  int v18; // [esp+20h] [ebp-4h]

  v1 = dword_463904;
  v2 = dword_4655BC[74 * a1];
  v3 = BYTE1(spu_ram[2 * v2]);
  v18 = v2;
  if ( (unsigned __int16)dword_463904 == v2 && (word_4F7550 & 0x40) != 0 && !dword_4F75A0 )
  {
    dword_4F75A0 = 1;
    spu_registered_callback();
    v1 = dword_463904;
  }
  if ( v1 == dword_4655BC[74 * a1] + 1 && (word_4F7550 & 0x40) != 0 && !dword_4F75A0 )
  {
    dword_4F75A0 = 1;
    spu_registered_callback();
    v1 = dword_463904;
  }
  v4 = dword_4655BC[74 * a1] + 2;
  dword_4655BC[74 * a1] = v4;
  dword_465638[74 * a1] = 1;
  if ( (v3 & 1) == 0 || (v5 = dword_4655A0[74 * a1]) == 0 || v1 != v5 )
  {
    switch ( v3 )
    {
      case 1:
      case 7:
        dword_465638[74 * a1] = 2;
        result = 0;
        goto LABEL_26;
      case 3:
        dword_4655BC[74 * a1] = dword_4655A0[74 * a1];
        goto LABEL_13;
      case 6:
        dword_4655A0[74 * a1] = v4 - 2;
        goto LABEL_13;
      default:
        goto LABEL_13;
    }
  }
  dword_4655BC[74 * a1] = v5;
LABEL_13:
  v6 = spu_ram[2 * v2];
  v7 = 2 * (v6 >> 4);
  v16 = dword_44F7A4[v7];
  v15 = 0;
  v14 = dword_44F7A8[v7];
  v17 = v6 & 0xF;
  while ( 1 )
  {
    v9 = *((unsigned __int8 *)&spu_ram[2 * v2] + v15 + 2);
    v10 = ((__int16)(v9 << 12) >> v17) + (v16 * dword_4655C0[74 * a1] + v14 * dword_4655C4[74 * a1]) / 64;
    if ( v10 > 0x7FFF )
      break;
    if ( v10 < -32768 )
      break;
    dword_4655C4[74 * a1] = dword_4655C0[74 * a1];
    dword_4655C0[74 * a1] = v10;
    v11 = 2 * (v15 + 37 * a1);
    dword_4655C8[v11] = v10;
    v12 = dword_4655C0[74 * a1];
    v13 = ((__int16)((v9 & 0xFFF0) << 8) >> v17) + (v16 * v12 + v14 * dword_4655C4[74 * a1]) / 64;
    if ( v13 > 0x7FFF || v13 < -32768 )
      break;
    dword_4655C0[74 * a1] = v13;
    dword_4655C4[74 * a1] = v12;
    dword_4655CC[v11] = v13;
    result = ++v15;
    if ( v15 >= 0xEu )
      return result;
    v2 = v18;
  }
  result = 0;
  ++word_4F75B4;
LABEL_26:
  memset(&dword_4655C8[74 * a1], 0, 0x70u);
  return result;
}
