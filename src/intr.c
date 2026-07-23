#include "pch.h"
char clear_hw_regs()
{
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax

  for ( i = 0; i < 48; i += 3 )
  {
    dword_50C150[i] = 0;
    dword_50C154[i] = 0;
    dword_50C158[i] = 0;
  }
  for ( j = 0; j < 16; j += 4 )
  {
    dword_50BFD0[j] = 0;
    dword_50BFD4[j] = 0;
    dword_50BFD8[j] = 0;
    dword_50BFDC[j] = 0;
  }
  for ( k = 0; k < 80; k += 5 )
  {
    dword_50C010[k] = 0;
    dword_50C014[k] = 0;
    dword_50C018[k] = 0;
    dword_50C01C[k] = 0;
  }
  dword_50C210 = 0;
  byte_50C214 = -1;
  byte_50C215 = -1;
  sio_transfer_timeout = 0;
  dword_4FD868 = 0;
  sio_transfer_pending = 0;
  *(_DWORD *)dword_4FD870 = 0;
  *(_DWORD *)dword_4FD874 = 0;
  *(_DWORD *)dword_4FD878 = 0;
  return -1;
}

unsigned int irq_cpu_interrupt()
{
  unsigned int result; // eax

  result = *(_DWORD *)int_reg;
  if ( (*(_DWORD *)int_reg & int_mask) != 0 )
  {
    result = dword_50C2A4;
    if ( (dword_50C2A4 & 0x401) == 0x401 )
    {
      result = dword_50C2A4 & 0xFFFFFFC0;
      dword_50C2AC = *(_DWORD *)reg_pc;
      dword_50C2A8 = 1024;
      *(_DWORD *)reg_pc = 0x80000080;
      dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
    }
  }
  return result;
}

char __cdecl rcnt_write_reg(unsigned __int16 a1, int a2)
{
  int v2; // eax
  bool v3; // zf

  LOBYTE(v2) = a1;
  switch ( a1 )
  {
    case 0x1100u:
    case 0x1110u:
    case 0x1120u:
    case 0x1130u:
      if ( !a2 )
      {
        v2 = 16 * ((a1 >> 4) & 3);
        *(int *)((char *)dword_50BFD0 + v2) = 0;
      }
      break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)dword_50BFD0 + v2) = 0;
      *(int *)((char *)dword_50BFD4 + v2) = a2 & 0x3FF | 0x1000;
      if ( (a2 & 8) != 0 && *(int *)((char *)dword_50BFD8 + v2) )
      {
        *(int *)((char *)dword_50BFDC + v2) = (unsigned __int16)*(int *)((char *)dword_50BFD8 + v2);
        v3 = a1 == 4388;
      }
      else
      {
        *(int *)((char *)dword_50BFDC + v2) = 0xFFFF;
        v3 = a1 == 4388;
      }
      goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)dword_50BFD8 + v2) = a2;
      if ( (*((_BYTE *)dword_50BFD4 + v2) & 8) != 0 && a2 )
        *(int *)((char *)dword_50BFDC + v2) = (unsigned __int16)a2;
      else
        *(int *)((char *)dword_50BFDC + v2) = 0xFFFF;
      v3 = a1 == 4392;
LABEL_13:
      if ( v3 )
      {
        LOBYTE(v2) = parasite_eve_cheat;
        if ( parasite_eve_cheat )
          dword_50BFFC = (unsigned int)dword_50BFFC >> 2;
      }
      break;
    default:
      return v2;
  }
  return v2;
}

void cdrom_assert_int()
{
  *(_DWORD *)int_reg |= 4u;
}

void sio_assert_int()
{
  *(_DWORD *)int_reg |= 0x80u;
}

int sub_42AFD0()
{
  int result; // eax

  result = hw_update_counter;
  if ( hw_update_counter < 0 )
  {
    result = 0;
    hw_update_counter = 0;
LABEL_3:
    *(_DWORD *)dword_4FD874 = cpu_speed_scale + result - 535;
    *(_DWORD *)dword_4FD878 = 0;
    return result;
  }
  if ( (unsigned int)hw_update_counter <= 0x217 )
    goto LABEL_3;
  *(_DWORD *)dword_4FD870 = hw_update_counter - 535;
  *(_DWORD *)dword_4FD878 = 128;
  return hw_update_counter - 535;
}

int __cdecl irq_dma_assert_int(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( ((1 << (a1 + 16)) & dword_50BFC8) != 0 )
  {
    result = *(_DWORD *)int_reg | 8;
    dword_50BFC8 |= 1 << (a1 + 24);
    *(_DWORD *)int_reg |= 8u;
  }
  return result;
}

void irq_spu_registered_callback()
{
  ++dword_50C210;
}

int __cdecl sub_42B080(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 668;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD870, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD874, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_4FD878, 4u);
  dword_50C218 = sio_transfer_timeout;
  dword_50C21C = dword_4FD868;
  dword_50C220[0] = sio_transfer_pending;
  return gzwrite(a2, (unsigned __int8 *)int_reg, 0x290u);
}

int __cdecl irq_unfreeze(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dword_4FD870, 4);
  gzread(a2, dword_4FD874, 4);
  gzread(a2, dword_4FD878, 4);
  gzread(a2, int_reg, 656);
  sio_transfer_timeout = dword_50C218;
  dword_4FD868 = dword_50C21C;
  sio_transfer_pending = dword_50C220[0];
  return dword_50C220[0];
}

int clear_cpu_regs()
{
  *(_DWORD *)reg_pc = 0xBFC00000;
  memset(cpu_gpr, 0, 0x80u);
  memset(cop0_regs, 0, 0x40u);
  hw_update_counter = 0;
  dword_50C360 = 0;
  dword_50C364 = 0;
  cpu_LO = 0;
  cpu_HI = 0;
  return 0;
}

unsigned int sub_42B1E0()
{
  int v0; // ecx
  unsigned int result; // eax
  int v2; // eax

  v0 = *(_DWORD *)reg_pc;
  result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  for ( cpu_opcode = result; *(_DWORD *)reg_pc != 0x80030000; cpu_opcode = result )
  {
    *(_DWORD *)reg_pc = v0 + 4;
    cpu_main_table[result >> 26]();
    v2 = --hw_update_counter;
    if ( hw_update_counter < 0 )
    {
      hw_update_counter = cpu_speed_scale + v2;
      if ( ++dword_50C364 >= (unsigned int)dword_45593C )
      {
        dword_50C364 = 0;
        ++dword_50C360;
      }
    }
    v0 = *(_DWORD *)reg_pc;
    result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  }
  return result;
}

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
        irq_cpu_interrupt();
      v8 = --hw_update_counter;
      if ( hw_update_counter < 0 )
      {
        v9 = (((_BYTE)dword_4FC4EC + 1) & 0x1F) == 0;
        hw_update_counter = cpu_speed_scale + v8;
        ++dword_50C364;
        ++dword_4FC4EC;
        if ( v9 )
          spu_async_update_cb(32 * cpu_speed_scale);
        if ( mdectiming )
          mdec_timer_handler();
        gpu_sub_42E450();
        gpu_sub_42E650();
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
        if ( sio_transfer_pending )
        {
          sio_transfer_pending = 0;
          sio_trigger_rx_ready_irq();
        }
        else if ( dword_4FD868 )
        {
          sio_transfer_pending = 128;
          sio_transfer_timeout = dword_4FD868;
          dword_4FD868 = 0;
        }
        v10 = cpu_speed_scale;
        v11 = 512;
        if ( (dword_50BFD4[0] & 0x100) == 0 )
          v11 = cpu_speed_scale;
        dword_50BFD0[0] += v11;
        if ( dword_50BFD0[0] >= (unsigned int)dword_50BFDC[0] )
        {
          dword_50BFD0[0] = 0;
          if ( (dword_50BFD4[0] & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x10u;
        }
        v12 = 1;
        if ( (dword_50BFE4 & 0x100) == 0 )
          v12 = cpu_speed_scale;
        dword_50BFE0 += v12;
        if ( dword_50BFE0 >= (unsigned int)dword_50BFEC )
        {
          dword_50BFE0 = 0;
          if ( (dword_50BFE4 & 0x50) == 0x50 )
            *(_DWORD *)int_reg |= 0x20u;
        }
        if ( (dword_50BFF4 & 0x200) != 0 )
          v10 = (unsigned int)cpu_speed_scale >> 3;
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
          irq_cpu_interrupt();
        if ( dword_50C364 >= v13 )
          break;
      }
    }
    dword_50C364 = 0;
    ++dword_50C360;
    ++dword_50C000;
    gpu_frame_update();
    result = reset_flag;
    if ( reset_flag )
      break;
    if ( (dword_50C360 & 0x3F) == 0 )
      sub_42CE40();
    sio_memcard_auto_save();
  }
  return result;
}

