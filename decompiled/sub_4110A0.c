#include "pch.h"
char sub_4110A0()
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
  char result; // al

  v0 = word_8A7F02 * word_8A7FAE;
  v1 = (word_8A7F04 * word_8A7FA4 + word_8A7F02 * word_8A7FA2 + *(__int16 *)word_8A7F00 * word_8A7FA0) >> 12;
  v2 = (word_8A7F04 * word_8A7FAA + word_8A7F02 * word_8A7FA8 + *(__int16 *)word_8A7F00 * word_8A7FA6) >> 12;
  v3 = (word_8A7F04 * word_8A7FB0 + v0 + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
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
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
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
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (word_8A7F04 * word_8A7FB0 + v0 + *(__int16 *)word_8A7F00 * word_8A7FAC) >> 12;
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
  v4 = dword_8A7FB4
     + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v5 = dword_8A7FB8
     + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v6 = dword_8A7FBC
     + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  if ( (unsigned int)v4 >= 0x8000 )
    dword_8A7FFC |= 0x81000000;
  if ( (unsigned int)v5 >= 0x8000 )
    dword_8A7FFC |= 0x80800000;
  if ( (unsigned int)v6 >= 0x8000 )
    dword_8A7FFC |= 0x400000u;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  v9 = v6 >> 4;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      unk_8A7F58 = v7;
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
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      unk_8A7F59 = v8;
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
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      unk_8A7F5A = v9;
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
  byte_8A7F5B = byte_8A7F1B;
  v10 = word_8A7FAA * word_8A7F0C;
  v11 = (word_8A7FA4 * word_8A7F0C + word_8A7FA2 * word_8A7F0A + word_8A7FA0 * word_8A7F08) >> 12;
  v12 = (v10 + word_8A7FA8 * word_8A7F0A + word_8A7FA6 * word_8A7F08) >> 12;
  v13 = (word_8A7FB0 * word_8A7F0C + word_8A7FAE * word_8A7F0A + word_8A7FAC * word_8A7F08) >> 12;
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7FA4 * word_8A7F0C + word_8A7FA2 * word_8A7F0A + word_8A7FA0 * word_8A7F08) >> 12;
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
  if ( v12 >= 0 )
  {
    if ( v12 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (v10 + word_8A7FA8 * word_8A7F0A + word_8A7FA6 * word_8A7F08) >> 12;
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
  if ( v13 >= 0 )
  {
    if ( v13 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (word_8A7FB0 * word_8A7F0C + word_8A7FAE * word_8A7F0A + word_8A7FAC * word_8A7F08) >> 12;
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
  v14 = dword_8A7FB4
      + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v15 = dword_8A7FB8
      + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v16 = dword_8A7FBC
      + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  if ( (unsigned int)v14 >= 0x8000 )
    dword_8A7FFC |= 0x81000000;
  if ( (unsigned int)v15 >= 0x8000 )
    dword_8A7FFC |= 0x80800000;
  if ( (unsigned int)v16 >= 0x8000 )
    dword_8A7FFC |= 0x400000u;
  v17 = v14 >> 4;
  v18 = v15 >> 4;
  v19 = v16 >> 4;
  dword_8A7F54 = unk_8A7F58;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      unk_8A7F58 = v17;
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
  if ( v18 >= 0 )
  {
    if ( v18 <= 255 )
    {
      unk_8A7F59 = v18;
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
  if ( v19 >= 0 )
  {
    if ( v19 <= 255 )
    {
      unk_8A7F5A = v19;
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
  byte_8A7F5B = byte_8A7F1B;
  v20 = word_8A7FAA * word_8A7F14;
  v21 = (word_8A7FA4 * word_8A7F14 + word_8A7FA2 * word_8A7F12 + word_8A7FA0 * word_8A7F10) >> 12;
  v22 = (v20 + word_8A7FA8 * word_8A7F12 + word_8A7FA6 * word_8A7F10) >> 12;
  v23 = (word_8A7FB0 * word_8A7F14 + word_8A7FAE * word_8A7F12 + word_8A7FAC * word_8A7F10) >> 12;
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F24 = (word_8A7FA4 * word_8A7F14 + word_8A7FA2 * word_8A7F12 + word_8A7FA0 * word_8A7F10) >> 12;
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
  if ( v22 >= 0 )
  {
    if ( v22 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = (v20 + word_8A7FA8 * word_8A7F12 + word_8A7FA6 * word_8A7F10) >> 12;
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
  if ( v23 >= 0 )
  {
    if ( v23 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = (word_8A7FB0 * word_8A7F14 + word_8A7FAE * word_8A7F12 + word_8A7FAC * word_8A7F10) >> 12;
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
  v24 = dword_8A7FB4
      + ((word_8A7F2C[0] * word_8A7FC4 + word_8A7F28[0] * word_8A7FC2 + word_8A7F24[0] * word_8A7FC0) >> 12);
  v25 = dword_8A7FB8
      + ((word_8A7F2C[0] * word_8A7FCA + word_8A7F28[0] * word_8A7FC8 + word_8A7F24[0] * word_8A7FC6) >> 12);
  v26 = dword_8A7FBC
      + ((word_8A7F2C[0] * word_8A7FD0 + word_8A7F28[0] * word_8A7FCE + word_8A7F24[0] * word_8A7FCC) >> 12);
  dword_8A7F64 = v24;
  dword_8A7F68 = v25;
  dword_8A7F6C = v26;
  if ( v24 >= 0 )
  {
    if ( v24 <= 0x7FFF )
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
  if ( v25 >= 0 )
  {
    if ( v25 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F28 = v25;
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
  if ( v26 >= 0 )
  {
    if ( v26 <= 0x7FFF )
    {
      *(_DWORD *)word_8A7F2C = v26;
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
  v27 = v24 >> 4;
  unk_8A7F50 = dword_8A7F54;
  v28 = v25 >> 4;
  v29 = v26 >> 4;
  dword_8A7F54 = unk_8A7F58;
  dword_8A8004 = v27;
  dword_8A8008 = v28;
  dword_8A800C = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 255 )
    {
      unk_8A7F58 = v27;
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
      unk_8A7F59 = v28;
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
      result = byte_8A7F1B;
      unk_8A7F5A = v29;
    }
    else
    {
      result = dword_8A7FFC;
      unk_8A7F5A = -1;
      dword_8A7FFC |= 0x80000u;
    }
    byte_8A7F5B = byte_8A7F1B;
  }
  else
  {
    result = dword_8A7FFC;
    dword_8A7FFC |= 0x80000u;
    unk_8A7F5A = 0;
    byte_8A7F5B = byte_8A7F1B;
  }
  return result;
}
