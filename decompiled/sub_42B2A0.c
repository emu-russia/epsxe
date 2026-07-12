#include "pch.h"
int sub_42B2A0()
{
  unsigned int v0; // esi
  unsigned __int8 v1; // dl
  unsigned __int8 v2; // bl
  int v3; // edi
  int v4; // ecx
  unsigned __int8 v5; // cl
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // eax
  bool v9; // zf
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // ecx
  unsigned int v13; // esi
  int v14; // edx
  int result; // eax
  unsigned __int8 v16; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    while ( 1 )
    {
      v0 = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
      v1 = dword_4F831C;
      cpu_opcode = v0;
      if ( (_BYTE)dword_4F831C )
      {
        v2 = 0;
        v16 = 0;
        v3 = *(_DWORD *)reg_pc & 0x1FFFFF;
        do
        {
          v4 = dword_5B6DC4[2 * v16];
          if ( (v4 & 0x1FFFFF) == v3 )
          {
            v0 = dword_5B6DC0[2 * v16];
            if ( (v4 & 0xF0000000) == 0 )
            {
              v5 = v2 + 1;
              if ( (unsigned __int8)(v2 + 1) < v1 )
              {
                v6 = (_DWORD *)(8 * v5 + 5991868);
                v7 = (unsigned __int8)(v1 - v5);
                do
                {
                  *(v6 - 1) = v6[1];
                  *v6 = v6[2];
                  v6 += 2;
                  --v7;
                }
                while ( v7 );
                v2 = v16;
              }
              --v1;
            }
          }
          v16 = ++v2;
        }
        while ( v2 < v1 );
        LOBYTE(dword_4F831C) = v1;
        cpu_opcode = v0;
      }
      if ( (*(_DWORD *)reg_pc & 0xFFF00000) == 0x1F800000 )
        ui_error("out of line\n");
      *(_DWORD *)reg_pc += 4;
      cpu_main_table[v0 >> 26]();
      cpu_gpr[0] = 0;
      if ( (*(_DWORD *)int_reg & int_mask & 0x3FB) != 0 && (dword_50C2A4 & 0x401) == 0x401 )
        cpu_interrupt();
      v8 = --hw_update_counter;
      if ( hw_update_counter < 0 )
      {
        v9 = (((_BYTE)dword_4FC4EC + 1) & 0x1F) == 0;
        hw_update_counter = dword_455940 + v8;
        ++dword_50C364;
        ++dword_4FC4EC;
        if ( v9 )
          spu_async_update_cb(32 * dword_455940);
        if ( mdectiming )
          sub_429310();
        sub_42E450();
        sub_42E650();
        sub_42CA70();
        sub_42C9A0();
        if ( (int_reg[0] & 4) == 0 && sub_42C8B0() )
          *(_DWORD *)int_reg |= 4u;
        if ( dword_50C210 && (*(_WORD *)int_reg & 0x200) == 0 )
        {
          *(_DWORD *)int_reg |= 0x200u;
          --dword_50C210;
        }
        if ( *(_DWORD *)dword_4FD878 )
        {
          *(_DWORD *)int_reg |= *(_DWORD *)dword_4FD878;
          *(_DWORD *)dword_4FD878 = 0;
        }
        else if ( *(_DWORD *)dword_4FD874 )
        {
          *(_DWORD *)dword_4FD878 = 128;
          *(_DWORD *)dword_4FD870 = *(_DWORD *)dword_4FD874;
          *(_DWORD *)dword_4FD874 = 0;
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
        v10 = dword_455940;
        v11 = 512;
        if ( (dword_50BFD4[0] & 0x100) == 0 )
          v11 = dword_455940;
        dword_50BFD0[0] += v11;
        if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
        {
          dword_50BFD0[0] = 0;
          if ( (dword_50BFD4[0] & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x10u;
        }
        v12 = 1;
        if ( (dword_50BFE4 & 0x100) == 0 )
          v12 = dword_455940;
        dword_50BFE0 += v12;
        if ( dword_50BFE0 >= (unsigned int)dword_50BFEC )
        {
          dword_50BFE0 = 0;
          if ( (dword_50BFE4 & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x20u;
        }
        if ( (dword_50BFF4 & 0x200) != 0 )
          v10 = (unsigned int)dword_455940 >> 3;
        dword_50BFF0 += v10;
        if ( dword_50BFF0 >= (unsigned int)dword_50BFFC )
        {
          dword_50BFF0 = 0;
          if ( (dword_50BFF4 & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x40u;
        }
        v13 = dword_45593C;
        if ( dword_50C364 == dword_45593C - 22 )
        {
          v14 = *(_DWORD *)int_reg | 1;
          *(_DWORD *)int_reg |= 1u;
          if ( (int_mask & 0x200) != 0 && forcespu && (dword_50C360 & 3) == 0 )
            *(_DWORD *)int_reg = v14 | 0x200;
        }
        if ( (int_mask & *(_DWORD *)int_reg) != 0 )
          cpu_interrupt();
        if ( dword_50C364 >= v13 )
          break;
      }
    }
    dword_50C364 = 0;
    ++dword_50C360;
    ++dword_50C000;
    frame_update();
    result = reset_flag;
    if ( reset_flag )
      break;
    if ( (dword_50C360 & 0x3F) == 0 )
      sub_42CE40();
    memcard_all_save();
  }
  return result;
}
