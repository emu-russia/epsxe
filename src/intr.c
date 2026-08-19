#include "pch.h"
char irq_clear_hw_regs()
{
  unsigned int i;
  unsigned int j;
  unsigned int k;

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
  *(uint32_t *)sio_irq_timeout = 0;
  *(uint32_t *)sio_irq_delay_time = 0;
  *(uint32_t *)sio_irq_pending = 0;
  return -1;
}

unsigned int irq_cpu_interrupt()
{
  unsigned int status;

  status = *(uint32_t *)int_reg;
  if ( (*(uint32_t *)int_reg & int_mask) != 0 )
  {
    status = cop0_sr;
    if ( (cop0_sr & 0x401) == 0x401 )
    {
      status = cop0_sr & 0xFFFFFFC0;
      cop0_epc = *(uint32_t *)reg_pc;
      cop0_cause = 1024;
      *(uint32_t *)reg_pc = 0x80000080;
      cop0_sr = cop0_sr & 0xFFFFFFC0 | (4 * (cop0_sr & 0xF));
    }
  }
  return status;
}

static char rcnt_write_reg(uint16_t reg, int value)
{
  int offset;
  bool is_rcnt2;

  LOBYTE(offset) = reg;
  switch ( reg )
  {
    case 0x1100u:
    case 0x1110u:
    case 0x1120u:
    case 0x1130u:
      if ( !value )
      {
        offset = 16 * ((reg >> 4) & 3);
        *(int *)((char *)rcnt_counter + offset) = 0;
      }
      break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
      offset = 16 * ((reg >> 4) & 3);
      *(int *)((char *)rcnt_counter + offset) = 0;
      *(int *)((char *)rcnt_mode + offset) = value & 0x3FF | 0x1000;
      if ( (value & 8) != 0 && *(int *)((char *)rcnt_target + offset) )
      {
        *(int *)((char *)rcnt_compare + offset) = (uint16_t)*(int *)((char *)rcnt_target + offset);
        is_rcnt2 = reg == 4388;
      }
      else
      {
        *(int *)((char *)rcnt_compare + offset) = 0xFFFF;
        is_rcnt2 = reg == 4388;
      }
      goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
      offset = 16 * ((reg >> 4) & 3);
      *(int *)((char *)rcnt_target + offset) = value;
      if ( (*((uint8_t *)rcnt_mode + offset) & 8) != 0 && value )
        *(int *)((char *)rcnt_compare + offset) = (uint16_t)value;
      else
        *(int *)((char *)rcnt_compare + offset) = 0xFFFF;
      is_rcnt2 = reg == 4392;
LABEL_13:
      if ( is_rcnt2 )
      {
        LOBYTE(offset) = parasite_eve_cheat;
        if ( parasite_eve_cheat )
          rcnt2_compare = (unsigned int)rcnt2_compare >> 2;
      }
      break;
    default:
      return offset;
  }
  return offset;
}

static void cdrom_assert_int()
{
  *(uint32_t *)int_reg |= 4u;
}

static void sio_assert_int()
{
  *(uint32_t *)int_reg |= 0x80u;
}

int irq_sio_update()
{
  int delay;

  delay = hw_update_counter;
  if ( hw_update_counter < 0 )
  {
    delay = 0;
    hw_update_counter = 0;
LABEL_3:
    *(uint32_t *)sio_irq_delay_time = cpu_speed_scale + delay - 535;
    *(uint32_t *)sio_irq_pending = 0;
    return delay;
  }
  if ( (unsigned int)hw_update_counter <= 0x217 )
    goto LABEL_3;
  *(uint32_t *)sio_irq_timeout = hw_update_counter - 535;
  *(uint32_t *)sio_irq_pending = 128;
  return hw_update_counter - 535;
}

int irq_dma_assert_int(uint8_t channel)
{
  int status;

  status = channel;
  if ( ((1 << (channel + 16)) & dma_int_ctrl) != 0 )
  {
    status = *(uint32_t *)int_reg | 8;
    dma_int_ctrl |= 1 << (channel + 24);
    *(uint32_t *)int_reg |= 8u;
  }
  return status;
}

void irq_spu_registered_callback()
{
  ++spu_irq_pending_count;
}

static int sub_42B080(const char *magic, int fp)
{
  char Buffer[3];

  sprintf(Buffer, "%s", magic);
  gzwrite(fp, (uint8_t *)Buffer, 7u);
  gzwrite(fp, (uint8_t *)sio_irq_timeout, 4u);
  gzwrite(fp, (uint8_t *)sio_irq_delay_time, 4u);
  gzwrite(fp, (uint8_t *)sio_irq_pending, 4u);
  sio_transfer_timeout_saved = sio_transfer_timeout;
  sio_pending_time_saved = sio_scheduled_transfer_timeout;
  sio_transfer_pending_saved[0] = sio_transfer_pending;
  return gzwrite(fp, (uint8_t *)int_reg, 0x290u);
}

int irq_unfreeze(int magic, uint32_t *fp)
{
  char buffer[64];

  gzread(fp, buffer, 7);
  gzread(fp, sio_irq_timeout, 4);
  gzread(fp, sio_irq_delay_time, 4);
  gzread(fp, sio_irq_pending, 4);
  gzread(fp, int_reg, 656);
  sio_transfer_timeout = sio_transfer_timeout_saved;
  sio_scheduled_transfer_timeout = sio_pending_time_saved;
  sio_transfer_pending = sio_transfer_pending_saved[0];
  return sio_transfer_pending_saved[0];
}

void irq_cdrom_assert_int()
{
    *(uint32_t*)int_reg |= 4u;
}

void irq_sio_assert_int()
{
    *(uint32_t*)int_reg |= 0x80u;
}

char irq_rcnt_write_reg(uint16_t reg, int value)
{
    int offset;
    bool is_rcnt2;

    LOBYTE(offset) = reg;
    switch (reg)
    {
    case 0x1100u:
    case 0x1110u:
    case 0x1120u:
    case 0x1130u:
        if (!value)
        {
            offset = 16 * ((reg >> 4) & 3);
            *(int*)((char*)rcnt_counter + offset) = 0;
        }
        break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
        offset = 16 * ((reg >> 4) & 3);
        *(int*)((char*)rcnt_counter + offset) = 0;
        *(int*)((char*)rcnt_mode + offset) = value & 0x3FF | 0x1000;
        if ((value & 8) != 0 && *(int*)((char*)rcnt_target + offset))
        {
            *(int*)((char*)rcnt_compare + offset) = (uint16_t)*(int*)((char*)rcnt_target + offset);
            is_rcnt2 = reg == 4388;
        }
        else
        {
            *(int*)((char*)rcnt_compare + offset) = 0xFFFF;
            is_rcnt2 = reg == 4388;
        }
        goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
        offset = 16 * ((reg >> 4) & 3);
        *(int*)((char*)rcnt_target + offset) = value;
        if ((*((uint8_t*)rcnt_mode + offset) & 8) != 0 && value)
            *(int*)((char*)rcnt_compare + offset) = (uint16_t)value;
        else
            *(int*)((char*)rcnt_compare + offset) = 0xFFFF;
        is_rcnt2 = reg == 4392;
    LABEL_13:
        if (is_rcnt2)
        {
            LOBYTE(offset) = parasite_eve_cheat;
            if (parasite_eve_cheat)
                rcnt2_compare = (unsigned int)rcnt2_compare >> 2;
        }
        break;
    default:
        return offset;
    }
    return offset;
}

int irq_freeze(const char* magic, int fp)
{
    char Buffer[3];

    sprintf(Buffer, "%s", magic);
    gzwrite(fp, (uint8_t*)Buffer, 7u);
    gzwrite(fp, (uint8_t*)sio_irq_timeout, 4u);
    gzwrite(fp, (uint8_t*)sio_irq_delay_time, 4u);
    gzwrite(fp, (uint8_t*)sio_irq_pending, 4u);
    sio_transfer_timeout_saved = sio_transfer_timeout;
    sio_pending_time_saved = sio_scheduled_transfer_timeout;
    sio_transfer_pending_saved[0] = sio_transfer_pending;
    return gzwrite(fp, (uint8_t*)int_reg, 0x290u);
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
