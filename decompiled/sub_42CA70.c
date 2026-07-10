#include "pch.h"
void sub_42CA70()
{
  char v0; // cl

  if ( byte_50AF4D )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      v0 = byte_50AF4F;
      if ( (byte_50AF4F & 4) == 4 )
      {
        if ( byte_50AF44[1] )
        {
          if ( byte_50AF44[1] != 1 )
          {
            if ( (byte_50AF4F & 2) != 0 )
              byte_50AF44[2] = 1;
            LOBYTE(dword_50AF03) = byte_50AF4D | 0x22;
            byte_50AF43 = 1;
          }
        }
        else
        {
          byte_50AF44[1] = 1;
          LOBYTE(dword_50AE80) = byte_50AF4D | 0x22;
          if ( (byte_50AF4F & 2) != 0 )
          {
            byte_50AEC0 = 1;
          }
          else
          {
            *(_WORD *)((char *)&dword_50AE80 + 1) = -32767;
            if ( byte_455FA5 )
              HIBYTE(dword_50AE80) = sub_42B680(dword_50AF50);
            else
              HIBYTE(dword_50AE80) = 0;
            LOBYTE(dword_50AE84) = sub_42B680(BYTE1(dword_50AF50));
            BYTE1(dword_50AE84) = sub_42B680(BYTE2(dword_50AF50));
            byte_50AEC0 = 6;
          }
          byte_50AEC1 = 0;
          byte_50AEC2 = 1;
          cdrom_assert_int();
          v0 = byte_50AF4F;
        }
      }
      if ( (v0 & 2) == 2
        && word_50BF7A == (_BYTE)dword_50AF50
        && MEMORY[0x50BF7B] == *(_WORD *)((char *)&dword_50AF50 + 1)
        && dword_50C37C != 3 )
      {
        byte_50AF44[1] = 4;
        LOBYTE(dword_50AE80) = 2;
        byte_50AEC0 = 1;
        byte_50AEC1 = 0;
        byte_50AEC2 = 1;
        cdrom_stop_cb();
        byte_50AF4B = 1;
        byte_50AF48 &= 0x3Fu;
        byte_50AF4A = 0;
        byte_50AF4D = 0;
      }
      word_50BF82 = 0;
      sub_42C7E0();
    }
  }
  else if ( byte_50AF4A )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)word_50BF80 )
    {
      word_50BF82 = 0;
      if ( !byte_50BF7D )
      {
        sub_42C710();
        dword_50BF5C = (byte_50AF4F & 0x20) != 0 ? 12 : 24;
        sub_42C7E0();
        word_50BF80 = word_50BF7E;
        if ( (BYTE2(dword_50AF66) & 0xF) != 4 || (byte_50AF4F & 0x40) != 0x40 )
        {
          if ( byte_50AF44[1] )
          {
            if ( byte_50AF44[1] == 1 )
              return;
            if ( !byte_50AF44[2] )
            {
              byte_50AF44[2] = 1;
              LOBYTE(dword_50AF03) = 34;
              byte_50AF43 = 1;
              ++byte_50BF7D;
              return;
            }
          }
          else if ( !byte_50AF44[2] )
          {
            byte_50AF44[1] = 1;
            LOBYTE(dword_50AE80) = 34;
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
