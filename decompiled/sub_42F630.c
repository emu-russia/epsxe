#include "pch.h"
int sub_42F630()
{
  int result; // eax

  result = 0;
  if ( network_enabled )
  {
    HIWORD(dword_50A1D0) = dword_455FB0;
    byte_50A1D4 = dword_4FD900[0];
    byte_50A1D5 = dword_4FD910[0];
    byte_50A1D6 = dword_4FD920[0];
    byte_50A1D7 = dword_4FD930[0];
    LOBYTE(dword_50A1D8) = dword_50AB60;
    BYTE1(dword_50A1D8) = dword_4FD8F0;
    HIWORD(dword_50A1C0) = dword_455FB4;
    BYTE2(dword_50A1D8) = dword_4FD8F4;
    LOBYTE(dword_50A1D0) = dword_456048[0];
    LOBYTE(dword_50A1C0) = dword_45604C;
    byte_50A1C4 = 0;
    byte_50A1C5 = 0;
    byte_50A1C6 = 0;
    byte_50A1C7 = 0;
    byte_50A1C8 = 0;
    byte_50A1C9 = 0;
    byte_50A1CA = 0;
    if ( dword_4FD9A0 )
    {
      LOBYTE(dword_50A1D0) = LOBYTE(dword_456048[0]) | 0x80;
      LOBYTE(dword_50A1C0) = dword_45604C | 0x80;
    }
    NETpadState(&dword_50A1D0, &dword_50A1C0);
    if ( (dword_50A1D0 & 0x80u) != 0 || (dword_50A1C0 & 0x80u) != 0 )
    {
      return 1;
    }
    else
    {
      dword_456048[0] = (unsigned __int8)dword_50A1D0;
      dword_4FD910[0] = byte_50A1D5;
      dword_455FB0 = HIWORD(dword_50A1D0);
      dword_4FD920[0] = byte_50A1D6;
      dword_4FD8F0 = SBYTE1(dword_50A1D8);
      dword_4FD900[0] = byte_50A1D4;
      dword_50AB60 = (unsigned __int8)dword_50A1D8;
      dword_4FD930[0] = byte_50A1D7;
      dword_45604C = (unsigned __int8)dword_50A1C0;
      dword_4FD8F4 = SBYTE2(dword_50A1D8);
      dword_455FB4 = HIWORD(dword_50A1C0);
      return 0;
    }
  }
  return result;
}
