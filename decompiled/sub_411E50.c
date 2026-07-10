#include "pch.h"
char sub_411E50()
{
  int v0; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // esi
  int v7; // edi
  __int64 v8; // rax
  int v9; // eax
  int v10; // edx
  int v11; // edx
  int v12; // eax
  int v13; // ebp
  int v14; // edi
  int v15; // eax
  int v16; // ecx
  int v17; // edx
  int v18; // eax
  int v19; // ecx
  int v20; // edx
  int v21; // esi
  int v22; // edi
  __int64 v23; // rax
  int v24; // eax
  int v25; // edx
  int v26; // edx
  int v27; // eax
  int v28; // ebp
  int v29; // edi
  int v30; // eax
  int v31; // ecx
  int v32; // edx
  int v33; // eax
  int v34; // ecx
  int v35; // edx
  int v36; // esi
  int v37; // edi
  __int64 v38; // rax
  int v39; // eax
  int v40; // edx
  int v41; // eax

  v0 = (unk_8A7F04 * unk_8A7FA4 + SHIWORD(unk_8A7F00[0]) * unk_8A7FA2 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA0) >> 12;
  v1 = (unk_8A7F04 * unk_8A7FAA + SHIWORD(unk_8A7F00[0]) * unk_8A7FA8 + SLOWORD(unk_8A7F00[0]) * unk_8A7FA6) >> 12;
  v2 = (unk_8A7F04 * unk_8A7FB0 + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
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
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F2C = (unk_8A7F04 * unk_8A7FB0 + SHIWORD(unk_8A7F00[0]) * unk_8A7FAE + SLOWORD(unk_8A7F00[0]) * unk_8A7FAC) >> 12;
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
  v3 = unk_8A7FB4
     + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v4 = unk_8A7FB8
     + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v5 = unk_8A7FBC
     + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  unk_8A7F64 = v3;
  unk_8A7F68 = v4;
  unk_8A7F6C = v5;
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
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
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      word_8A7F28 = v4;
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
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      word_8A7F2C = v5;
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
  v6 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  v7 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  v8 = gte_clamp(-2130706432, unk_8A7FD4 - (((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8));
  unk_8A7F64 = HIDWORD(v8) + ((unk_8A7F20 * (int)v8) >> 12);
  unk_8A7F68 = v6 + ((int)(unk_8A7F20 * (unsigned int)gte_clamp(-2139095040, unk_8A7FD8 - v6)) >> 12);
  v9 = gte_clamp(0x400000, unk_8A7FDC - v7);
  v10 = unk_8A7F54;
  unk_8A7F54 = unk_8A7F58;
  unk_8A7F50 = v10;
  v11 = unk_8A7F68 >> 4;
  v12 = (v7 + ((unk_8A7F20 * v9) >> 12)) >> 4;
  if ( unk_8A7F64 >> 4 >= 0 )
  {
    if ( unk_8A7F64 >> 4 <= 255 )
    {
      LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
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
  if ( v11 >= 0 )
  {
    if ( v11 <= 255 )
    {
      BYTE1(unk_8A7F58) = unk_8A7F68 >> 4;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      BYTE2(unk_8A7F58) = v12;
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
  v13 = unk_8A7F0A * unk_8A7FAE;
  v14 = unk_8A7F0C * unk_8A7FB0;
  v15 = (unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12;
  v16 = (unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12;
  v17 = (v14 + v13 + unk_8A7F08 * unk_8A7FAC) >> 12;
  if ( v15 >= 0 )
  {
    if ( v15 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7F0C * unk_8A7FA4 + unk_8A7F0A * unk_8A7FA2 + unk_8A7F08 * unk_8A7FA0) >> 12;
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
  if ( v16 >= 0 )
  {
    if ( v16 <= 0x7FFF )
    {
      word_8A7F28 = (unk_8A7F0C * unk_8A7FAA + unk_8A7F0A * unk_8A7FA8 + unk_8A7F08 * unk_8A7FA6) >> 12;
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
  if ( v17 >= 0 )
  {
    if ( v17 <= 0x7FFF )
    {
      word_8A7F2C = (v14 + v13 + unk_8A7F08 * unk_8A7FAC) >> 12;
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
  v18 = unk_8A7FB4
      + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v19 = unk_8A7FB8
      + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v20 = unk_8A7FBC
      + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  unk_8A7F64 = v18;
  unk_8A7F68 = v19;
  unk_8A7F6C = v20;
  if ( v18 >= 0 )
  {
    if ( v18 <= 0x7FFF )
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
  if ( v19 >= 0 )
  {
    if ( v19 <= 0x7FFF )
    {
      word_8A7F28 = v19;
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
  if ( v20 >= 0 )
  {
    if ( v20 <= 0x7FFF )
    {
      word_8A7F2C = v20;
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
  v21 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  v22 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  v23 = gte_clamp(-2130706432, unk_8A7FD4 - (((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8));
  unk_8A7F64 = HIDWORD(v23) + ((unk_8A7F20 * (int)v23) >> 12);
  unk_8A7F68 = v21 + ((int)(unk_8A7F20 * (unsigned int)gte_clamp(-2139095040, unk_8A7FD8 - v21)) >> 12);
  v24 = gte_clamp(0x400000, unk_8A7FDC - v22);
  v25 = unk_8A7F54;
  unk_8A7F54 = unk_8A7F58;
  unk_8A7F50 = v25;
  v26 = unk_8A7F68 >> 4;
  v27 = (v22 + ((unk_8A7F20 * v24) >> 12)) >> 4;
  if ( unk_8A7F64 >> 4 >= 0 )
  {
    if ( unk_8A7F64 >> 4 <= 255 )
    {
      LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
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
  if ( v26 >= 0 )
  {
    if ( v26 <= 255 )
    {
      BYTE1(unk_8A7F58) = unk_8A7F68 >> 4;
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
  if ( v27 >= 0 )
  {
    if ( v27 <= 255 )
    {
      BYTE2(unk_8A7F58) = v27;
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
  v28 = unk_8A7F12 * unk_8A7FAE;
  v29 = unk_8A7F14 * unk_8A7FB0;
  v30 = (unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12;
  v31 = (unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12;
  v32 = (v29 + v28 + unk_8A7F10 * unk_8A7FAC) >> 12;
  if ( v30 >= 0 )
  {
    if ( v30 <= 0x7FFF )
    {
      word_8A7F24 = (unk_8A7F14 * unk_8A7FA4 + unk_8A7F12 * unk_8A7FA2 + unk_8A7F10 * unk_8A7FA0) >> 12;
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
  if ( v31 >= 0 )
  {
    if ( v31 <= 0x7FFF )
    {
      word_8A7F28 = (unk_8A7F14 * unk_8A7FAA + unk_8A7F12 * unk_8A7FA8 + unk_8A7F10 * unk_8A7FA6) >> 12;
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
  if ( v32 >= 0 )
  {
    if ( v32 <= 0x7FFF )
    {
      word_8A7F2C = (v29 + v28 + unk_8A7F10 * unk_8A7FAC) >> 12;
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
  v33 = unk_8A7FB4
      + (((__int16)word_8A7F2C * unk_8A7FC4 + (__int16)word_8A7F28 * unk_8A7FC2 + (__int16)word_8A7F24 * unk_8A7FC0) >> 12);
  v34 = unk_8A7FB8
      + (((__int16)word_8A7F2C * unk_8A7FCA + (__int16)word_8A7F28 * unk_8A7FC8 + (__int16)word_8A7F24 * unk_8A7FC6) >> 12);
  v35 = unk_8A7FBC
      + (((__int16)word_8A7F2C * unk_8A7FD0 + (__int16)word_8A7F28 * unk_8A7FCE + (__int16)word_8A7F24 * unk_8A7FCC) >> 12);
  unk_8A7F64 = v33;
  unk_8A7F68 = v34;
  unk_8A7F6C = v35;
  if ( v33 >= 0 )
  {
    if ( v33 <= 0x7FFF )
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
  if ( v34 >= 0 )
  {
    if ( v34 <= 0x7FFF )
    {
      word_8A7F28 = v34;
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
  if ( v35 >= 0 )
  {
    if ( v35 <= 0x7FFF )
    {
      word_8A7F2C = v35;
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
  v36 = ((__int16)word_8A7F28 * BYTE1(unk_8A7F18)) >> 8;
  v37 = ((__int16)word_8A7F2C * BYTE2(unk_8A7F18)) >> 8;
  v38 = gte_clamp(-2130706432, unk_8A7FD4 - (((__int16)word_8A7F24 * (unsigned __int8)unk_8A7F18) >> 8));
  unk_8A7F64 = HIDWORD(v38) + ((unk_8A7F20 * (int)v38) >> 12);
  unk_8A7F68 = v36 + ((int)(unk_8A7F20 * (unsigned int)gte_clamp(-2139095040, unk_8A7FD8 - v36)) >> 12);
  v39 = v37 + ((int)(unk_8A7F20 * (unsigned int)gte_clamp(0x400000, unk_8A7FDC - v37)) >> 12);
  unk_8A7F6C = v39;
  if ( unk_8A7F64 >= 0 )
  {
    if ( unk_8A7F64 <= 0x7FFF )
    {
      word_8A7F24 = unk_8A7F64;
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
  if ( unk_8A7F68 >= 0 )
  {
    if ( unk_8A7F68 <= 0x7FFF )
    {
      word_8A7F28 = unk_8A7F68;
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
  if ( v39 >= 0 )
  {
    if ( v39 <= 0x7FFF )
    {
      word_8A7F2C = v39;
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
  unk_8A7F50 = unk_8A7F54;
  v40 = unk_8A7F68 >> 4;
  v41 = v39 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = unk_8A7F64 >> 4;
  unk_8A8008 = unk_8A7F68 >> 4;
  unk_8A800C = v41;
  if ( unk_8A7F64 >> 4 >= 0 )
  {
    if ( unk_8A7F64 >> 4 <= 255 )
    {
      LOBYTE(unk_8A7F58) = unk_8A7F64 >> 4;
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
  if ( v40 >= 0 )
  {
    if ( v40 <= 255 )
    {
      BYTE1(unk_8A7F58) = unk_8A7F68 >> 4;
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
  if ( v41 >= 0 )
  {
    if ( v41 <= 255 )
    {
      BYTE2(unk_8A7F58) = v41;
    }
    else
    {
      unk_8A7FFC |= 0x80000u;
      LOBYTE(v41) = HIBYTE(unk_8A7F18);
      BYTE2(unk_8A7F58) = -1;
    }
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  else
  {
    LOBYTE(v41) = unk_8A7FFC;
    BYTE2(unk_8A7F58) = 0;
    unk_8A7FFC |= 0x80000u;
    HIBYTE(unk_8A7F58) = HIBYTE(unk_8A7F18);
  }
  return v41;
}
