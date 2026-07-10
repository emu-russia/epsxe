#include "pch.h"
char __cdecl sub_42D0E0(char a1, _BYTE *a2)
{
  char result; // al
  __int16 v3; // ax
  char v4; // al
  int v5; // eax
  int v6; // eax

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB0);
      a2[4] = dword_455FB0;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      if ( dword_456048[0] == 4 )
      {
        a2[7] = LOBYTE(dword_4FD900[0]) + 0x80;
        a2[8] = LOBYTE(dword_4FD910[0]) + 0x80;
        a2[5] = LOBYTE(dword_4FD920[0]) + 0x80;
        result = LOBYTE(dword_4FD930[0]) + 0x80;
        a2[6] = LOBYTE(dword_4FD930[0]) + 0x80;
        return result;
      }
      if ( dword_456048[0] != 5 )
      {
        result = LOBYTE(dword_456048[0]) - 6;
        if ( dword_456048[0] != 6 )
          return result;
        if ( (dword_50AB60 & 3) != 0 )
        {
          word_4FD8FA += dword_4FD8F0 / 3;
          LOBYTE(v3) = word_4FD8FA;
          if ( word_4FD8FA <= 127 )
          {
            if ( word_4FD8FA >= -128 )
              goto LABEL_12;
            v3 = -128;
          }
          else
          {
            v3 = 127;
          }
        }
        else
        {
          v3 = 0;
        }
        word_4FD8FA = v3;
LABEL_12:
        a2[7] = v3 + 0x80;
        if ( (dword_50AB60 & 3) != 0 )
        {
          word_4FD8FC += dword_4FD8F4 / 3;
          v4 = word_4FD8FC;
          if ( word_4FD8FC <= 127 )
          {
            if ( word_4FD8FC < -128 )
            {
              v4 = 0x80;
              word_4FD8FC = -128;
            }
            result = v4 + 0x80;
            a2[8] = result;
          }
          else
          {
            word_4FD8FC = 127;
            a2[8] = -1;
            return -1;
          }
        }
        else
        {
          word_4FD8FC = 0;
          a2[8] = 0x80;
          return 0x80;
        }
        return result;
      }
      v5 = 3 * dword_4FD8F0;
      dword_4FD8F0 *= 3;
      if ( dword_4FD8F0 <= 127 )
      {
        if ( v5 >= -128 )
          goto LABEL_24;
        v5 = -128;
      }
      else
      {
        v5 = 127;
      }
      dword_4FD8F0 = v5;
LABEL_24:
      a2[7] = v5 + 0x80;
      v6 = 3 * dword_4FD8F4;
      dword_4FD8F4 *= 3;
      if ( dword_4FD8F4 <= 127 )
      {
        if ( v6 < -128 )
        {
          LOBYTE(v6) = 0x80;
          dword_4FD8F4 = -128;
        }
        result = v6 + 0x80;
        a2[8] = result;
      }
      else
      {
        dword_4FD8F4 = 127;
        a2[8] = -1;
        return -1;
      }
      return result;
    case 1:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB4);
      a2[4] = dword_455FB4;
      a2[7] = byte_4FD904 + 0x80;
      a2[8] = byte_4FD914 + 0x80;
      a2[5] = byte_4FD924 + 0x80;
      a2[6] = byte_4FD934 + 0x80;
      return (char)a2;
    case 2:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = byte_455FB9;
      a2[4] = byte_455FB8;
      a2[7] = byte_4FD908 + 0x80;
      a2[8] = byte_4FD918 + 0x80;
      a2[5] = byte_4FD928 + 0x80;
      a2[6] = byte_4FD938 + 0x80;
      return (char)a2;
    case 3:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = byte_455FBD;
      a2[4] = byte_455FBC;
      a2[7] = byte_4FD90C + 0x80;
      a2[8] = byte_4FD91C + 0x80;
      a2[5] = byte_4FD92C + 0x80;
      a2[6] = byte_4FD93C + 0x80;
      return (char)a2;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = 90;
      a2[3] = -1;
      a2[4] = -1;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      return (char)a2;
  }
}
