#include "pch.h"
void sub_42CA70()
{
  char v0; // cl

  if ( byte_50AF07[70] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      v0 = byte_50AF07[72];
      if ( (byte_50AF07[72] & 4) == 4 )
      {
        if ( byte_50AF07[62] )
        {
          if ( byte_50AF07[62] != 1 )
          {
            if ( (byte_50AF07[72] & 2) != 0 )
              byte_50AF07[63] = 1;
            LOBYTE(dword_50AF03) = byte_50AF07[70] | 0x22;
            byte_50AF07[60] = 1;
          }
        }
        else
        {
          byte_50AF07[62] = 1;
          dword_50AE80[0] = byte_50AF07[70] | 0x22;
          if ( (byte_50AF07[72] & 2) != 0 )
          {
            byte_50AEC0 = 1;
          }
          else
          {
            dword_50AE80[1] = 1;
            dword_50AE80[2] = 0x80;
            if ( byte_455FA5 )
              dword_50AE80[3] = cdr_sub_42B680(dword_50AF50);
            else
              dword_50AE80[3] = 0;
            LOBYTE(dword_50AE84) = cdr_sub_42B680(BYTE1(dword_50AF50));
            BYTE1(dword_50AE84) = cdr_sub_42B680(BYTE2(dword_50AF50));
            byte_50AEC0 = 6;
          }
          byte_50AEC1 = 0;
          byte_50AEC2 = 1;
          cdrom_assert_int();
          v0 = byte_50AF07[72];
        }
      }
      if ( (v0 & 2) == 2
        && word_50BF7A == (_BYTE)dword_50AF50
        && MEMORY[0x50BF7B] == *(_WORD *)((char *)&dword_50AF50 + 1)
        && loaded_file_type != 3 )
      {
        byte_50AF07[62] = 4;
        dword_50AE80[0] = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50AEC2 = 1;
        cdrom_stop_cb();
        byte_50AF07[68] = 1;
        byte_50AF07[65] &= 0x3Fu;
        byte_50AF07[67] = 0;
        byte_50AF07[70] = 0;
      }
      word_50BF82 = 0;
      sub_42C7E0();
    }
  }
  else if ( byte_50AF07[67] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      word_50BF82 = 0;
      if ( !byte_50BF7D )
      {
        sub_42C710();
        dword_50BF5C = (byte_50AF07[72] & 0x20) != 0 ? 12 : 24;
        sub_42C7E0();
        word_50BF80 = word_50BF7E;
        if ( (byte_50AF66[2] & 0xF) != 4 || (byte_50AF07[72] & 0x40) != 0x40 )
        {
          if ( byte_50AF07[62] )
          {
            if ( byte_50AF07[62] == 1 )
              return;
            if ( !byte_50AF07[63] )
            {
              byte_50AF07[63] = 1;
              LOBYTE(dword_50AF03) = 34;
              byte_50AF07[60] = 1;
              ++byte_50BF7D;
              return;
            }
          }
          else if ( !byte_50AF07[63] )
          {
            byte_50AF07[62] = 1;
            dword_50AE80[0] = 34;
            byte_50AEC0 = 1;
            byte_50AEC1 = 0;
            byte_50AEC2 = 1;
            cdrom_assert_int();
            ++byte_50BF7D;
            return;
          }
          byte_50BF6A = 1;
          byte_50BF6B = 1;
          LOBYTE(dword_50BF6C) = 34;
          ++byte_50BF7D;
        }
      }
    }
  }
}
