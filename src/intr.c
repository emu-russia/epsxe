#include "pch.h"
char irq_clear_hw_regs()
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
  gpu_dma2_delay_counter = -1;
  gpu_dma6_delay_counter = -1;
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

int irq_sio_update()
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


/* Decompiled globals (previously generated in src/_gen) */
unsigned int dword_4FD870;
unsigned int dword_4FD874;
unsigned int dword_50BFD8[1];
unsigned int dword_50BFDC[1];
unsigned int dword_50C010[1];
unsigned int dword_50C014[1];
unsigned int dword_50C018[1];
unsigned int dword_50C01C[0x4d];
unsigned int dword_50C150[1];
unsigned int dword_50C154[1];
unsigned int dword_50C158[0x2e];
unsigned int dword_50C218;
unsigned int dword_50C21C;
unsigned int dword_50C220[0x10];
