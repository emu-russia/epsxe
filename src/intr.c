#include "pch.h"
char irq_clear_hw_regs()
{
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax

  for ( i = 0; i < 48; i += 3 )
  {
    irq_hw_regs_e[i] = 0;
    irq_hw_regs_f[i] = 0;
    irq_hw_regs_g[i] = 0;
  }
  for ( j = 0; j < 16; j += 4 )
  {
    rcnt_counter[j] = 0;
    rcnt_mode[j] = 0;
    rcnt_target[j] = 0;
    rcnt_compare[j] = 0;
  }
  for ( k = 0; k < 80; k += 5 )
  {
    irq_hw_regs_a[k] = 0;
    irq_hw_regs_b[k] = 0;
    irq_hw_regs_c[k] = 0;
    irq_hw_regs_d[k] = 0;
  }
  spu_irq_pending_count = 0;
  gpu_dma2_delay_counter = -1;
  gpu_dma6_delay_counter = -1;
  sio_transfer_timeout = 0;
  sio_scheduled_transfer_timeout = 0;
  sio_transfer_pending = 0;
  *(_DWORD *)sio_irq_timeout = 0;
  *(_DWORD *)sio_irq_delay_time = 0;
  *(_DWORD *)sio_irq_pending = 0;
  return -1;
}

unsigned int irq_cpu_interrupt()
{
  unsigned int result; // eax

  result = *(_DWORD *)int_reg;
  if ( (*(_DWORD *)int_reg & int_mask) != 0 )
  {
    result = cop0_sr;
    if ( (cop0_sr & 0x401) == 0x401 )
    {
      result = cop0_sr & 0xFFFFFFC0;
      cop0_epc = *(_DWORD *)reg_pc;
      cop0_cause = 1024;
      *(_DWORD *)reg_pc = 0x80000080;
      cop0_sr = cop0_sr & 0xFFFFFFC0 | (4 * (cop0_sr & 0xF));
    }
  }
  return result;
}

static char __cdecl rcnt_write_reg(unsigned __int16 a1, int a2)
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
        *(int *)((char *)rcnt_counter + v2) = 0;
      }
      break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)rcnt_counter + v2) = 0;
      *(int *)((char *)rcnt_mode + v2) = a2 & 0x3FF | 0x1000;
      if ( (a2 & 8) != 0 && *(int *)((char *)rcnt_target + v2) )
      {
        *(int *)((char *)rcnt_compare + v2) = (unsigned __int16)*(int *)((char *)rcnt_target + v2);
        v3 = a1 == 4388;
      }
      else
      {
        *(int *)((char *)rcnt_compare + v2) = 0xFFFF;
        v3 = a1 == 4388;
      }
      goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)rcnt_target + v2) = a2;
      if ( (*((_BYTE *)rcnt_mode + v2) & 8) != 0 && a2 )
        *(int *)((char *)rcnt_compare + v2) = (unsigned __int16)a2;
      else
        *(int *)((char *)rcnt_compare + v2) = 0xFFFF;
      v3 = a1 == 4392;
LABEL_13:
      if ( v3 )
      {
        LOBYTE(v2) = parasite_eve_cheat;
        if ( parasite_eve_cheat )
          rcnt2_compare = (unsigned int)rcnt2_compare >> 2;
      }
      break;
    default:
      return v2;
  }
  return v2;
}

static void cdrom_assert_int()
{
  *(_DWORD *)int_reg |= 4u;
}

static void sio_assert_int()
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
    *(_DWORD *)sio_irq_delay_time = cpu_speed_scale + result - 535;
    *(_DWORD *)sio_irq_pending = 0;
    return result;
  }
  if ( (unsigned int)hw_update_counter <= 0x217 )
    goto LABEL_3;
  *(_DWORD *)sio_irq_timeout = hw_update_counter - 535;
  *(_DWORD *)sio_irq_pending = 128;
  return hw_update_counter - 535;
}

int __cdecl irq_dma_assert_int(unsigned __int8 a1)
{
  int result; // eax

  result = a1;
  if ( ((1 << (a1 + 16)) & dma_int_ctrl) != 0 )
  {
    result = *(_DWORD *)int_reg | 8;
    dma_int_ctrl |= 1 << (a1 + 24);
    *(_DWORD *)int_reg |= 8u;
  }
  return result;
}

void irq_spu_registered_callback()
{
  ++spu_irq_pending_count;
}

static int __cdecl sub_42B080(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
  int v4; // [esp+7h] [ebp-3Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 668;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)sio_irq_timeout, 4u);
  gzwrite(a2, (unsigned __int8 *)sio_irq_delay_time, 4u);
  gzwrite(a2, (unsigned __int8 *)sio_irq_pending, 4u);
  sio_transfer_timeout_saved = sio_transfer_timeout;
  sio_pending_time_saved = sio_scheduled_transfer_timeout;
  sio_transfer_pending_saved[0] = sio_transfer_pending;
  return gzwrite(a2, (unsigned __int8 *)int_reg, 0x290u);
}

int __cdecl irq_unfreeze(int a1, _DWORD *a2)
{
  char v3[64]; // [esp+4h] [ebp-40h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, sio_irq_timeout, 4);
  gzread(a2, sio_irq_delay_time, 4);
  gzread(a2, sio_irq_pending, 4);
  gzread(a2, int_reg, 656);
  sio_transfer_timeout = sio_transfer_timeout_saved;
  sio_scheduled_transfer_timeout = sio_pending_time_saved;
  sio_transfer_pending = sio_transfer_pending_saved[0];
  return sio_transfer_pending_saved[0];
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int sio_irq_timeout;
unsigned int sio_irq_delay_time;
unsigned int rcnt_target[1];
unsigned int rcnt_compare[1];
unsigned int irq_hw_regs_a[1];
unsigned int irq_hw_regs_b[1];
unsigned int irq_hw_regs_c[1];
unsigned int irq_hw_regs_d[0x4d];
unsigned int irq_hw_regs_e[1];
unsigned int irq_hw_regs_f[1];
unsigned int irq_hw_regs_g[0x2e];
unsigned int sio_transfer_timeout_saved;
unsigned int sio_pending_time_saved;
unsigned int sio_transfer_pending_saved[0x10];
