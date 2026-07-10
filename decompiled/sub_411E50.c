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
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // esi
  int v23; // edi
  int v24; // eax
  int v25; // edx
  int v26; // eax
  int v27; // edx
  int v28; // edx
  int v29; // eax
  int v30; // ebp
  int v31; // edi
  int v32; // eax
  int v33; // ecx
  int v34; // edx
  int v35; // eax
  int v36; // ecx
  int v37; // edx
  int v38; // esi
  int v39; // edi
  int v40; // eax
  int v41; // edx
  int v42; // eax
  int v43; // edx
  int v44; // eax

  v0 = (word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
  v1 = (word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
  v2 = (word_8A7F04 * word_8A7FB0 + word_8A7F02 * word_8A7FAE + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7F04 * word_8A7FA4
                              + word_8A7F02 * word_8A7FA2
                              + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (word_8A7F04 * word_8A7FAA
                              + word_8A7F02 * word_8A7FA8
                              + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (word_8A7F04 * word_8A7FB0
                              + word_8A7F02 * word_8A7FAE
                              + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v3 = dword_8A7FB4
     + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v4 = dword_8A7FB8
     + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v5 = dword_8A7FBC
     + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v3;
  dword_8A7F68 = v4;
  dword_8A7F6C = v5;
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7FB4
                             + ((word_8A7F2C[0] * word_8A7FC4
                               + word_8A7F28[0] * word_8A7FC2
                               + word_8A7F24[0] * word_8A7FC0) >> 12);
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v4;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v5;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v6 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
  v7 = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
  v8 = gte_clamp(-2130706432, dword_8A7FD4 - ((word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8));
  dword_8A7F64 = v9 + ((word_8A7F20 * v8) >> 12);
  dword_8A7F68 = v6 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v6)) >> 12);
  v10 = gte_clamp(0x400000, dword_8A7FDC - v7);
  v11 = unk_8A7F54;
  unk_8A7F54 = unk_8A7F58;
  unk_8A7F50 = v11;
  v12 = dword_8A7F68 >> 4;
  v13 = (v7 + ((word_8A7F20 * v10) >> 12)) >> 4;
  if ( dword_8A7F64 >> 4 >= 0 )
  {
    if ( dword_8A7F64 >> 4 <= 255 )
    {
      unk_8A7F58 = dword_8A7F64 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      unk_8A7F58 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    unk_8A7F58 = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      unk_8A7F59 = dword_8A7F68 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      unk_8A7F59 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    unk_8A7F59 = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 255 )
    {
      unk_8A7F5A = v13;
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      unk_8A7F5A = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80000u;
    unk_8A7F5A = 0;
  }
  unk_8A7F5B = byte_8A7F1B;
  v14 = word_8A7F0A * word_8A7FAE;
  v15 = word_8A7F0C * word_8A7FB0;
  v16 = (word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12;
  v17 = (word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12;
  v18 = (v15 + v14 + word_8A7F08 * word_8A7FAC) >> 12;
  if ( v16 >= 0 )
  {
    if ( v16 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7F0C * word_8A7FA4 + word_8A7F0A * word_8A7FA2 + word_8A7F08 * word_8A7FA0) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v17 >= 0 )
  {
    if ( v17 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (word_8A7F0C * word_8A7FAA + word_8A7F0A * word_8A7FA8 + word_8A7F08 * word_8A7FA6) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v18 >= 0 )
  {
    if ( v18 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (v15 + v14 + word_8A7F08 * word_8A7FAC) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v19 = dword_8A7FB4
      + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v20 = dword_8A7FB8
      + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v21 = dword_8A7FBC
      + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v19;
  dword_8A7F68 = v20;
  dword_8A7F6C = v21;
  if ( v19 >= 0 )
  {
    if ( v19 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7FB4
                             + ((word_8A7F2C[0] * word_8A7FC4
                               + word_8A7F28[0] * word_8A7FC2
                               + word_8A7F24[0] * word_8A7FC0) >> 12);
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v20 >= 0 )
  {
    if ( v20 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v20;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v21;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v22 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
  v23 = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
  v24 = gte_clamp(-2130706432, dword_8A7FD4 - ((word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8));
  dword_8A7F64 = v25 + ((word_8A7F20 * v24) >> 12);
  dword_8A7F68 = v22 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v22)) >> 12);
  v26 = gte_clamp(0x400000, dword_8A7FDC - v23);
  v27 = unk_8A7F54;
  unk_8A7F54 = unk_8A7F58;
  unk_8A7F50 = v27;
  v28 = dword_8A7F68 >> 4;
  v29 = (v23 + ((word_8A7F20 * v26) >> 12)) >> 4;
  if ( dword_8A7F64 >> 4 >= 0 )
  {
    if ( dword_8A7F64 >> 4 <= 255 )
    {
      unk_8A7F58 = dword_8A7F64 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      unk_8A7F58 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    unk_8A7F58 = 0;
  }
  if ( v28 >= 0 )
  {
    if ( v28 <= 255 )
    {
      unk_8A7F59 = dword_8A7F68 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      unk_8A7F59 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    unk_8A7F59 = 0;
  }
  if ( v29 >= 0 )
  {
    if ( v29 <= 255 )
    {
      unk_8A7F5A = v29;
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      unk_8A7F5A = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80000u;
    unk_8A7F5A = 0;
  }
  unk_8A7F5B = byte_8A7F1B;
  v30 = word_8A7F12 * word_8A7FAE;
  v31 = word_8A7F14 * word_8A7FB0;
  v32 = (word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12;
  v33 = (word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12;
  v34 = (v31 + v30 + word_8A7F10 * word_8A7FAC) >> 12;
  if ( v32 >= 0 )
  {
    if ( v32 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7F14 * word_8A7FA4 + word_8A7F12 * word_8A7FA2 + word_8A7F10 * word_8A7FA0) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v33 >= 0 )
  {
    if ( v33 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (word_8A7F14 * word_8A7FAA + word_8A7F12 * word_8A7FA8 + word_8A7F10 * word_8A7FA6) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v34 >= 0 )
  {
    if ( v34 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (v31 + v30 + word_8A7F10 * word_8A7FAC) >> 12;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v35 = dword_8A7FB4
      + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v36 = dword_8A7FB8
      + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v37 = dword_8A7FBC
      + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v35;
  dword_8A7F68 = v36;
  dword_8A7F6C = v37;
  if ( v35 >= 0 )
  {
    if ( v35 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7FB4
                             + ((word_8A7F2C[0] * word_8A7FC4
                               + word_8A7F28[0] * word_8A7FC2
                               + word_8A7F24[0] * word_8A7FC0) >> 12);
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( v36 >= 0 )
  {
    if ( v36 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v36;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v37 >= 0 )
  {
    if ( v37 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v37;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  v38 = (word_8A7F28[0] * HIBYTE(word_8A7F18)) >> 8;
  v39 = (word_8A7F2C[0] * (unsigned __int8)byte_8A7F1A) >> 8;
  v40 = gte_clamp(-2130706432, dword_8A7FD4 - ((word_8A7F24[0] * (unsigned __int8)word_8A7F18) >> 8));
  dword_8A7F64 = v41 + ((word_8A7F20 * v40) >> 12);
  dword_8A7F68 = v38 + ((word_8A7F20 * gte_clamp(-2139095040, dword_8A7FD8 - v38)) >> 12);
  v42 = v39 + ((word_8A7F20 * gte_clamp(0x400000, dword_8A7FDC - v39)) >> 12);
  dword_8A7F6C = v42;
  if ( dword_8A7F64 >= 0 )
  {
    if ( dword_8A7F64 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = dword_8A7F64;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      *(_DWORD *)word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    *(_DWORD *)word_8A7F24 = 0;
  }
  if ( dword_8A7F68 >= 0 )
  {
    if ( dword_8A7F68 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = dword_8A7F68;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      *(_DWORD *)word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    *(_DWORD *)word_8A7F28 = 0;
  }
  if ( v42 >= 0 )
  {
    if ( v42 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v42;
    }
    else
    {
      dword_8A7FFC |= 0x400000u;
      *(_DWORD *)word_8A7F2C = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x400000u;
    *(_DWORD *)word_8A7F2C = 0;
  }
  unk_8A7F50 = unk_8A7F54;
  v43 = dword_8A7F68 >> 4;
  v44 = v42 >> 4;
  unk_8A7F54 = unk_8A7F58;
  unk_8A8004 = dword_8A7F64 >> 4;
  unk_8A8008 = dword_8A7F68 >> 4;
  unk_8A800C = v44;
  if ( dword_8A7F64 >> 4 >= 0 )
  {
    if ( dword_8A7F64 >> 4 <= 255 )
    {
      unk_8A7F58 = dword_8A7F64 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x200000u;
      unk_8A7F58 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x200000u;
    unk_8A7F58 = 0;
  }
  if ( v43 >= 0 )
  {
    if ( v43 <= 255 )
    {
      unk_8A7F59 = dword_8A7F68 >> 4;
    }
    else
    {
      dword_8A7FFC |= 0x100000u;
      unk_8A7F59 = -1;
    }
  }
  else
  {
    dword_8A7FFC |= 0x100000u;
    unk_8A7F59 = 0;
  }
  if ( v44 >= 0 )
  {
    if ( v44 <= 255 )
    {
      unk_8A7F5A = v44;
    }
    else
    {
      dword_8A7FFC |= 0x80000u;
      LOBYTE(v44) = byte_8A7F1B;
      unk_8A7F5A = -1;
    }
    unk_8A7F5B = byte_8A7F1B;
  }
  else
  {
    LOBYTE(v44) = dword_8A7FFC;
    unk_8A7F5A = 0;
    dword_8A7FFC |= 0x80000u;
    unk_8A7F5B = byte_8A7F1B;
  }
  return v44;
}
