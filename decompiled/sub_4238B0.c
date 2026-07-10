#include "pch.h"
char *sub_4238B0()
{
  int v0; // eax
  unsigned int v2; // ecx
  int v3; // eax
  int v4; // eax
  unsigned int v5; // edx
  char v6; // al
  int v7; // edx
  int v8; // eax
  int v9; // eax

  dword_50C2B4 = 0;
  if ( (dword_50C270 & 0xC0000000) == 0x80000000 )
  {
    if ( (int_reg & int_mask) != 0 )
      cpu_interrupt();
    if ( (reg_pc & 0xFFF00000) == 0xBFC00000 )
      v0 = (reg_pc & 0x7FFFF) + 0x200000;
    else
      v0 = reg_pc & 0x1FFFFF;
    return (char *)dword_5164C4 + v0;
  }
  else
  {
    if ( (++dword_4FC4EC & 0x1F) == 0 )
      spu_async_update_cb(32 * dword_455940);
    sub_429310();
    sub_42E450();
    sub_42E650();
    dword_50C270 = dword_455940;
    ++dword_50C364;
    sub_42CA70();
    sub_42C9A0();
    if ( (int_reg & 4) == 0 && sub_42C8B0() )
      int_reg |= 4u;
    if ( dword_50C210 && (int_reg & 0x200) == 0 )
    {
      int_reg |= 0x200u;
      --dword_50C210;
    }
    if ( dword_4FD878 )
    {
      int_reg |= dword_4FD878;
      dword_4FD878 = 0;
    }
    else if ( dword_4FD874 )
    {
      dword_4FD878 = 128;
      dword_4FD870 = dword_4FD874;
      dword_4FD874 = 0;
    }
    if ( dword_4FD86C )
    {
      dword_4FD86C = 0;
      sub_421FD0();
    }
    else if ( dword_4FD868 )
    {
      dword_4FD86C = 128;
      dword_4FD864 = dword_4FD868;
      dword_4FD868 = 0;
    }
    v2 = dword_455940;
    v3 = 512;
    if ( (dword_50BFD4[0] & 0x100) == 0 )
      v3 = dword_455940;
    dword_50BFD0[0] += v3;
    if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
    {
      dword_50BFD0[0] = 0;
      if ( (dword_50BFD4[0] & 0x50) == 0x50 )
        int_reg |= 0x10u;
    }
    v4 = 1;
    if ( (dword_50BFE4 & 0x100) == 0 )
      v4 = dword_455940;
    dword_50BFE0 += v4;
    if ( dword_50BFE0 >= (unsigned int)dword_50BFEC )
    {
      dword_50BFE0 = 0;
      if ( (dword_50BFE4 & 0x50) == 0x50 )
        int_reg |= 0x20u;
    }
    if ( (dword_50BFF4 & 1) == 0 && byte_455944 )
    {
      if ( (dword_50BFF4 & 0x200) != 0 )
        v2 = (unsigned int)dword_455940 >> 3;
      v5 = v2 + dword_50BFF0;
      dword_50BFF0 = v5;
      if ( v5 >= dword_50BFFC )
      {
        dword_50BFF0 = v5 - dword_50BFFC;
        if ( (dword_50BFF4 & 0x50) == 0x50 )
          int_reg |= 0x40u;
      }
    }
    v6 = int_mask;
    if ( dword_50C364 == dword_45593C - (byte_4FC4E6 != 0 ? 32 : 1) )
    {
      v7 = int_reg | 1;
      int_reg |= 1u;
      if ( (int_mask & 0x200) != 0 && forcespu && (dword_50C360 & 3) == 0 )
        int_reg = v7 | 0x200;
    }
    if ( (int_mask & int_reg) != 0 )
    {
      cpu_interrupt();
      v6 = int_mask;
    }
    if ( dword_50C364 >= (unsigned int)dword_45593C )
    {
      dword_50C364 = 0;
      ++dword_50C360;
      ++dword_50C000;
      int_reg |= 1u;
      if ( (v6 & 1) != 0 )
        cpu_interrupt();
      frame_update();
      if ( dword_50C380 )
      {
        if ( (reg_pc & 0xFFF00000) == 0xBFC00000 )
          v8 = (reg_pc & 0x7FFFF) + 0x200000;
        else
          v8 = reg_pc & 0x1FFFFF;
        **(_DWORD **)((char *)dword_5164C4 + v8) = 195;
      }
      if ( byte_4FC4E4 )
      {
        byte_4FC4E4 = 0;
        sub_4291E0();
      }
      if ( (dword_50C360 & 0x3F) == 0 )
        sub_42CE40();
      memcard_all_save();
    }
    if ( (reg_pc & 0xFFF00000) == 0xBFC00000 )
      v9 = (reg_pc & 0x7FFFF) + 0x200000;
    else
      v9 = reg_pc & 0x1FFFFF;
    return (char *)dword_5164C4 + v9;
  }
}
