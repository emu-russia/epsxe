#include "pch.h"
char sub_4131C0()
{
  int v0; // ebp
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  int v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // edx
  int v30; // eax
  int v31; // ecx
  int v32; // edx
  char result; // al

  v0 = SHIWORD(unk_8A7F00[0]) * unk_8A7FAE;
  v1 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
  v2 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
  v3 = (unk_8A7F04 * unk_8A7FB0 + v0 + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F28 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      word_8A7F2C = (unk_8A7F04 * unk_8A7FB0 + v0 + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v4 = unk_8A7FB4
     + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v5 = unk_8A7FB8
     + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v6 = unk_8A7FBC
     + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      word_8A7F28 = v5;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v6 >= 0 )
  {
    if ( v6 <= 0x7FFF )
    {
      word_8A7F2C = v6;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v7 = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 12;
  v8 = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 12;
  v9 = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 12;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(unk_8A7F58) = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x200000u;
      LOBYTE(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x200000u;
    LOBYTE(unk_8A7F58) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      BYTE1(unk_8A7F58) = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x100000u;
      BYTE1(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x100000u;
    BYTE1(unk_8A7F58) = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      BYTE2(unk_8A7F58) = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      BYTE2(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80000u;
    BYTE2(unk_8A7F58) = 0;
  }
  HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  v10 = unk_8A7FAA * unk_8A7F0C;
  v11 = (unk_8A7FA4 * unk_8A7F0C + unk_8A7FA2 * unk_8A7F0A + unk_8A7FA0 * unk_8A7F08) >> 12;
  v12 = (v10 + unk_8A7FA8 * unk_8A7F0A + unk_8A7FA6 * unk_8A7F08) >> 12;
  v13 = (unk_8A7FB0 * unk_8A7F0C + unk_8A7FAE * unk_8A7F0A + unk_8A7FAC * unk_8A7F08) >> 12;
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7FA4 * unk_8A7F0C + unk_8A7FA2 * unk_8A7F0A + unk_8A7FA0 * unk_8A7F08) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 0x7FFF )
    {
      word_8A7F28 = (v10 + unk_8A7FA8 * unk_8A7F0A + unk_8A7FA6 * unk_8A7F08) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 0x7FFF )
    {
      word_8A7F2C = (unk_8A7FB0 * unk_8A7F0C + unk_8A7FAE * unk_8A7F0A + unk_8A7FAC * unk_8A7F08) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v14 = unk_8A7FB4
      + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v15 = unk_8A7FB8
      + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v16 = unk_8A7FBC
      + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  if ( v14 >= 0 )
  {
    if ( v14 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v15 >= 0 )
  {
    if ( v15 <= 0x7FFF )
    {
      word_8A7F28 = v15;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v16 >= 0 )
  {
    if ( v16 <= 0x7FFF )
    {
      word_8A7F2C = v16;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v17 = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 12;
  v18 = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 12;
  v19 = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 12;
  unk_8A7F54 = unk_8A7F58;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      LOBYTE(unk_8A7F58) = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x200000u;
      LOBYTE(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x200000u;
    LOBYTE(unk_8A7F58) = 0;
  }
  if ( v18 >= 0 )
  {
    if ( v18 <= 255 )
    {
      BYTE1(unk_8A7F58) = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x100000u;
      BYTE1(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x100000u;
    BYTE1(unk_8A7F58) = 0;
  }
  if ( v19 >= 0 )
  {
    if ( v19 <= 255 )
    {
      BYTE2(unk_8A7F58) = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      BYTE2(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80000u;
    BYTE2(unk_8A7F58) = 0;
  }
  HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  v20 = unk_8A7FAA * unk_8A7F14;
  v21 = (unk_8A7FA4 * unk_8A7F14 + unk_8A7FA2 * unk_8A7F12 + unk_8A7FA0 * unk_8A7F10) >> 12;
  v22 = (v20 + unk_8A7FA8 * unk_8A7F12 + unk_8A7FA6 * unk_8A7F10) >> 12;
  v23 = (unk_8A7FB0 * unk_8A7F14 + unk_8A7FAE * unk_8A7F12 + unk_8A7FAC * unk_8A7F10) >> 12;
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7FA4 * unk_8A7F14 + unk_8A7FA2 * unk_8A7F12 + unk_8A7FA0 * unk_8A7F10) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v22 >= 0 )
  {
    if ( v22 <= 0x7FFF )
    {
      word_8A7F28 = (v20 + unk_8A7FA8 * unk_8A7F12 + unk_8A7FA6 * unk_8A7F10) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v23 >= 0 )
  {
    if ( v23 <= 0x7FFF )
    {
      word_8A7F2C = (unk_8A7FB0 * unk_8A7F14 + unk_8A7FAE * unk_8A7F12 + unk_8A7FAC * unk_8A7F10) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v24 = unk_8A7FB4
      + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v25 = unk_8A7FB8
      + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v26 = unk_8A7FBC
      + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  if ( v24 >= 0 )
  {
    if ( v24 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7FB4
                  + (((__int16)word_8A7F2C * unk_8A7FC4
                    + (__int16)word_8A7F28 * unk_8A7FC2
                    + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = 0;
  }
  if ( v25 >= 0 )
  {
    if ( v25 <= 0x7FFF )
    {
      word_8A7F28 = v25;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v26 >= 0 )
  {
    if ( v26 <= 0x7FFF )
    {
      word_8A7F2C = v26;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v27 = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 8;
  v28 = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 8;
  v29 = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 8;
  unk_8A7F64 = v27;
  unk_8A7F68 = v28;
  unk_8A7F6C = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 0x7FFF )
    {
      word_8A7F24 = ((unsigned __int8)unk_8A7F18 * (__int16)word_8A7F24) >> 8;
    }
    else
    {
      HIBYTE(unk_8A7FFC) |= 0x81u;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    HIBYTE(unk_8A7FFC) |= 0x81u;
    word_8A7F24 = 0;
  }
  if ( v28 >= 0 )
  {
    if ( v28 <= 0x7FFF )
    {
      word_8A7F28 = (BYTE1(unk_8A7F18) * (__int16)word_8A7F28) >> 8;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = 0;
  }
  if ( v29 >= 0 )
  {
    if ( v29 <= 0x7FFF )
    {
      word_8A7F2C = (BYTE2(unk_8A7F18) * (__int16)word_8A7F2C) >> 8;
    }
    else
    {
      unk_8A7FFC |= 0x400000u;
      word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x400000u;
    word_8A7F2C = 0;
  }
  v30 = v27 >> 4;
  unk_8A7F50 = unk_8A7F54;
  v31 = v28 >> 4;
  v32 = v29 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = v30;
  unk_8A8008 = v31;
  unk_8A800C = v32;
  if ( v30 >= 0 )
  {
    if ( v30 <= 255 )
    {
      LOBYTE(unk_8A7F58) = v30;
    }
    else
    {
      unk_8A7FFC |= 0x200000u;
      LOBYTE(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x200000u;
    LOBYTE(unk_8A7F58) = 0;
  }
  if ( v31 >= 0 )
  {
    if ( v31 <= 255 )
    {
      BYTE1(unk_8A7F58) = v31;
    }
    else
    {
      unk_8A7FFC |= 0x100000u;
      BYTE1(unk_8A7F58) = -1;
    }
  }
  else
  {
    unk_8A7FFC |= 0x100000u;
    BYTE1(unk_8A7F58) = 0;
  }
  if ( v32 >= 0 )
  {
    if ( v32 <= 255 )
    {
      result = HIBYTE(unk_8A7F18);
      BYTE2(unk_8A7F58) = v32;
    }
    else
    {
      result = unk_8A7FFC;
      BYTE2(unk_8A7F58) = -1;
      unk_8A7FFC |= 0x80000u;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    result = unk_8A7FFC;
    unk_8A7FFC |= 0x80000u;
    BYTE2(unk_8A7F58) = 0;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  return result;
}
