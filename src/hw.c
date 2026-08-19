#include "pch.h"
void hw_reg_write_word(unsigned int addr, unsigned int value)
{
  int madr;
  unsigned int bcr;
  int data;
  int count;
  int data24;
  int addr24;

  if ( addr <= 0x1F801020 && addr >= 0x1F801000 )
  {
    *(uint32_t *)&hw_regs[(uint16_t)addr] = value;
    return;
  }
  if ( addr <= 0x1F801138 && addr >= 0x1F801100 )
  {
    irq_rcnt_write_reg(addr, value);
    return;
  }
  if ( addr <= 0x1F801E0F && addr >= 0x1F801C00 )
  {
    spu_write_register_cb(addr, (uint16_t)value);
    spu_write_register_cb(addr + 2, HIWORD(value));
    return;
  }
  if ( addr <= 0x1F8010B8 )
  {
    if ( addr == 0x1F8010B8 )
    {
      g_cdr_dma_channel_control = value;
      if ( dma_channel_status[1] < 0 )
      {
        cdr_dma();
        g_cdr_dma_channel_control = value & 0xFEFFFFFF;
        irq_dma_assert_int(3u);
      }
    }
    else
    {
      switch ( addr )
      {
        case 0x1F801040u:
          sio_write_data_byte(addr, value);
          sio_write_data_byte(addr, SBYTE1(value));
          sio_write_data_byte(addr, SBYTE2(value));
          sio_write_data_byte(addr, SHIBYTE(value));
          break;
        case 0x1F801060u:
          *(uint32_t *)&hw_regs[(uint16_t)addr] = value;
          break;
        case 0x1F801070u:
          if ( *(uint32_t *)sio_irq_pending )
          {
            if ( (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
            {
              *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
              *(uint32_t *)sio_irq_pending = 0;
            }
          }
          *(uint32_t *)int_reg &= value & int_mask;
          break;
        case 0x1F801074u:
          int_mask = value;
          break;
        case 0x1F801080u:
        case 0x1F801090u:
        case 0x1F8010A0u:
        case 0x1F8010B0u:
          goto LABEL_32;
        case 0x1F801084u:
        case 0x1F801094u:
        case 0x1F8010A4u:
        case 0x1F8010B4u:
          goto LABEL_37;
        case 0x1F801088u:
          mdec_dma_control[0] = value;
          if ( (dma_channel_status[0] & 8) != 0 )
          {
            mdec_dma_in_handler();
            mdec_dma_control[0] = value & 0xFEFFFFFF;
            irq_dma_assert_int(0);
          }
          break;
        case 0x1F801098u:
          mdec_dma_status = value;
          if ( dma_channel_status[0] < 0 )
          {
            mdec_decode();
            if ( !mdectiming )
            {
              mdec_dma_status = value & 0xFEFFFFFF;
              irq_dma_assert_int(1u);
            }
          }
          break;
        case 0x1F8010A8u:
          *(uint32_t *)gpu_dma_channel_status = value;
          if ( (dma_channel_status[1] & 8) != 0 )
            gpu_dma();
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( addr <= 0x1F8010E4 )
  {
    if ( addr == 528486628 )
    {
LABEL_37:
      mdec_dma_bcr[3 * ((uint8_t)addr >> 4) - 24] = value;
    }
    else
    {
      switch ( addr )
      {
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
LABEL_32:
          mdec_dma_src[3 * ((uint8_t)addr >> 4) - 24] = value;
          break;
        case 0x1F8010C4u:
        case 0x1F8010D4u:
          goto LABEL_37;
        case 0x1F8010C8u:
          *(uint32_t *)spu_dma_chcr_ptr = value;
          if ( (*(uint32_t *)dma_channel_status & 0x80000) != 0 )
          {
            spu_dma_cb();
            *(uint32_t *)spu_dma_chcr_ptr = value & 0xFEFFFFFF;
            irq_dma_assert_int(4u);
          }
          break;
        case 0x1F8010D8u:
          pio_dma_chcr = value;
          if ( ((unsigned int)&bios_image[37248] & *(uint32_t *)dma_channel_status) != 0 )
          {
            pio_dma_chcr = value & 0xFEFFFFFF;
            irq_dma_assert_int(5u);
          }
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( addr > 0x1F801810 )
  {
    switch ( addr )
    {
      case 0x1F801814u:
        gpu_writeStatus(value);
        return;
      case 0x1F801820u:
        mdec_write_command(value);
        return;
      case 0x1F801824u:
        mdec_handle_special_command(value);
        return;
    }
LABEL_51:
    dump_log(console_log_handle, "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n", "UNK", addr, value, 4, *(uint32_t *)reg_pc);
    return;
  }
  if ( addr == 528488464 )
  {
    gpu_writeData(value);
    return;
  }
  if ( addr != 528486632 )
  {
    if ( addr == 528486640 )
    {
      *(uint32_t *)dma_channel_status = value;
      return;
    }
    if ( addr == 528486644 )
    {
      dma_int_ctrl = value & 0xFFFFFF | dma_int_ctrl & ~(value | 0xFFFFFF);
      return;
    }
    goto LABEL_51;
  }
  *(uint32_t *)gpu_dma6_status = value;
  if ( (*(uint32_t *)dma_channel_status & 0x8000000) != 0 )
  {
    madr = dma6_madr;
    bcr = dma6_bcr;
    if ( *(uint32_t *)gpu_dma6_status == 285212674 )
    {
      if ( dma6_bcr )
      {
        data = dma6_madr - 4;
        count = dma6_bcr;
        do
        {
          data24 = data & 0xFFFFFF;
          addr24 = madr & 0x1FFFFF;
          madr -= 4;
          data -= 4;
          --count;
          *(int *)((char *)ram + addr24) = data24;
        }
        while ( count );
      }
      *(int *)((char *)&ram[1] + (madr & 0x1FFFFF)) = 0xFFFFFF;
      if ( bcr <= 0x40 )
      {
        *(uint32_t *)gpu_dma6_status = 268435458;
        irq_dma_assert_int(6u);
      }
      else
      {
        gpu_dma6_delay_counter = 1;
      }
    }
    else if ( (*(uint32_t *)gpu_dma6_status & 0x1000000) != 0 )
    {
      ui_error("DMA[6] mode NOT implemented (%08x)\n", *(uint32_t *)gpu_dma6_status);
    }
  }
}

int16_t hw_reg_read_half(unsigned int addr)
{
  int value;
  int counter;
  char sio_byte;
  int16_t sio_val;
  unsigned int index;
  int flag;
  int freq;
  int total;
  unsigned int freq2;
  unsigned int index2;
  int16_t counter2;
  int flag2;
  int16_t total2;

  if ( addr < 0x1F801C00 || addr > 0x1F801EEF )
  {
    if ( addr > 0x1F801108 )
    {
      switch ( addr )
      {
        case 0x1F801110u:
          LOWORD(value) = LOWORD(rcnt_counter[4 * ((addr >> 4) & 3)])
                         + ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                         - ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter);
          return value;
        case 0x1F801114u:
        case 0x1F801124u:
        case 0x1F801134u:
LABEL_33:
          LOWORD(value) = rcnt_mode[4 * ((addr >> 4) & 3)];
          return value;
        case 0x1F801118u:
        case 0x1F801128u:
        case 0x1F801138u:
          goto LABEL_34;
        case 0x1F801120u:
          LOWORD(freq2) = cpu_speed_scale;
          index2 = 4 * ((addr >> 4) & 3);
          counter2 = rcnt_counter[index2];
          flag2 = rcnt_mode[index2] & 0x200;
          if ( flag2 )
            freq2 = (unsigned int)cpu_speed_scale >> 3;
          total2 = freq2 + counter2;
          LOWORD(freq2) = hw_update_counter;
          if ( flag2 )
            freq2 = (unsigned int)hw_update_counter >> 3;
          LOWORD(value) = total2 - freq2;
          return value;
        case 0x1F801130u:
          goto LABEL_36;
        default:
LABEL_35:
          dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", addr, 0, 2);
LABEL_36:
          LOWORD(value) = 0;
          break;
      }
    }
    else if ( addr == 0x1F801108 )
    {
LABEL_34:
      LOWORD(value) = rcnt_target[4 * ((addr >> 4) & 3)];
    }
    else
    {
      HIWORD(counter) = 0;
      switch ( addr )
      {
        case 0x1F801014u:
          LOWORD(value) = *(uint16_t *)&hw_regs[(uint16_t)addr];
          break;
        case 0x1F801040u:
          sio_read_data_byte();
          HIBYTE(sio_val) = sio_byte;
          sio_read_data_byte();
          LOBYTE(sio_val) = value;
          LOWORD(value) = sio_val;
          break;
        case 0x1F801044u:
          if ( sio_transfer_pending && hw_update_counter < (unsigned int)sio_transfer_timeout )
          {
            sio_transfer_pending = 0;
            sio_trigger_rx_ready_irq();
          }
          LOWORD(value) = sio0_mode_reg;
          break;
        case 0x1F801048u:
          LOWORD(value) = HIWORD(sio0_mode_reg);
          break;
        case 0x1F80104Au:
          LOWORD(value) = sio0_control_reg;
          break;
        case 0x1F80104Eu:
          LOWORD(value) = HIWORD(sio0_control_reg);
          break;
        case 0x1F801070u:
          if ( *(uint32_t *)sio_irq_pending && (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
          {
            *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
            *(uint32_t *)sio_irq_pending = 0;
          }
          LOWORD(value) = *(uint16_t *)int_reg | forcepad;
          break;
        case 0x1F801074u:
          LOWORD(value) = int_mask;
          break;
        case 0x1F801100u:
          index = 4 * ((addr >> 4) & 3);
          LOWORD(counter) = rcnt_counter[index];
          flag = rcnt_mode[index] & 0x100;
          freq = 512;
          if ( !flag )
            freq = cpu_speed_scale;
          total = freq + counter;
          if ( flag )
            value = total - (hw_update_counter << 9) / (unsigned int)cpu_speed_scale;
          else
            LOWORD(value) = total - hw_update_counter;
          break;
        case 0x1F801104u:
          goto LABEL_33;
        default:
          goto LABEL_35;
      }
    }
  }
  else
  {
    LOWORD(value) = spu_read_register_cb(addr);
  }
  return value;
}

int hw_reg_read_word(unsigned int addr)
{
  int spu_data;
  int value;
  int channel;
  unsigned int dma_status;
  unsigned int index;
  int counter;
  int flag;
  int freq;
  int total;
  unsigned int freq2;
  unsigned int index2;
  int counter2;
  int flag2;
  unsigned int total2;
  unsigned int elapsed;

  if ( addr < 0x1F801C00 || addr > 0x1F801E2F )
  {
    if ( addr > 0x1F8010E8 )
    {
      if ( addr > 0x1F801124 )
      {
        if ( addr > 0x1F801810 )
        {
          switch ( addr )
          {
            case 0x1F801814u:
              return gpu_readStatus();
            case 0x1F801820u:
              return 0;
            case 0x1F801824u:
              value = mdec_param_count | mdec_status | mdec_timer_count;
              mdec_timer_count = 0;
              break;
            default:
LABEL_44:
              dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", addr, 0, 4);
              return 0;
          }
        }
        else if ( addr == 0x1F801810 )
        {
          return gpu_readData();
        }
        else
        {
          switch ( addr )
          {
            case 0x1F801128u:
            case 0x1F801138u:
LABEL_39:
              value = rcnt_target[4 * ((addr >> 4) & 3)];
              break;
            case 0x1F801130u:
              return 0;
            case 0x1F801134u:
              return rcnt_mode[4 * ((addr >> 4) & 3)];
            default:
              goto LABEL_44;
          }
        }
      }
      else if ( addr == 0x1F801124 )
      {
        return rcnt_mode[4 * ((addr >> 4) & 3)];
      }
      else
      {
        switch ( addr )
        {
          case 0x1F8010F0u:
            value = *(uint32_t *)dma_channel_status;
            break;
          case 0x1F8010F4u:
            value = dma_int_ctrl;
            break;
          case 0x1F801100u:
            index = 4 * ((addr >> 4) & 3);
            counter = rcnt_counter[index];
            flag = rcnt_mode[index] & 0x100;
            freq = 512;
            if ( !flag )
              freq = cpu_speed_scale;
            total = freq + counter;
            if ( flag )
              value = total - (hw_update_counter << 9) / (unsigned int)cpu_speed_scale;
            else
              value = total - hw_update_counter;
            break;
          case 0x1F801104u:
          case 0x1F801114u:
            return rcnt_mode[4 * ((addr >> 4) & 3)];
          case 0x1F801108u:
          case 0x1F801118u:
            goto LABEL_39;
          case 0x1F801110u:
            value = ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                  - ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter)
                  + rcnt_counter[4 * ((addr >> 4) & 3)];
            break;
          case 0x1F801120u:
            freq2 = cpu_speed_scale;
            index2 = 4 * ((addr >> 4) & 3);
            counter2 = rcnt_counter[index2];
            flag2 = rcnt_mode[index2] & 0x200;
            if ( flag2 )
              freq2 = (unsigned int)cpu_speed_scale >> 3;
            total2 = freq2 + counter2;
            elapsed = hw_update_counter;
            if ( flag2 )
              elapsed = (unsigned int)hw_update_counter >> 3;
            value = total2 - elapsed;
            break;
          default:
            goto LABEL_44;
        }
      }
    }
    else if ( addr == 0x1F8010E8 )
    {
LABEL_15:
      channel = (uint8_t)addr >> 4;
      value = mdec_dma_control[3 * channel - 24];
      if ( channel == 10 && gpu_dma2_state <= 0 )
      {
        dma_status = *(uint32_t *)gpu_dma_channel_status & 0xFEFFFFFF;
        *(uint32_t *)gpu_dma_channel_status &= ~0x1000000u;
        if ( gpu_dma2_state <= -2 )
          return dma_status;
      }
    }
    else
    {
      switch ( addr )
      {
        case 0x1F801014u:
        case 0x1F801060u:
          value = *(uint32_t *)&hw_regs[(uint16_t)addr];
          break;
        case 0x1F801040u:
        case 0x1F801044u:
          value = sio_read_register(addr, 4);
          break;
        case 0x1F801070u:
          if ( *(uint32_t *)sio_irq_pending )
          {
            if ( (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
            {
              *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
              *(uint32_t *)sio_irq_pending = 0;
            }
          }
          value = *(uint32_t *)int_reg | forcepad;
          break;
        case 0x1F801074u:
          value = int_mask;
          break;
        case 0x1F801080u:
        case 0x1F801090u:
        case 0x1F8010A0u:
        case 0x1F8010B0u:
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
          value = mdec_dma_src[3 * ((uint8_t)addr >> 4) - 24];
          break;
        case 0x1F801088u:
        case 0x1F801098u:
        case 0x1F8010A8u:
        case 0x1F8010B8u:
        case 0x1F8010C8u:
        case 0x1F8010D8u:
          goto LABEL_15;
        default:
          goto LABEL_44;
      }
    }
  }
  else
  {
    spu_data = (uint16_t)spu_read_register_cb(addr);
    return spu_data | ((uint16_t)spu_read_register_cb(addr + 2) << 16);
  }
  return value;
}

int hw_reg_freeze(const char *name, int gzf)
{
  char Buffer[3];

  sprintf(Buffer, "%s", name);
  gzwrite(gzf, (uint8_t *)Buffer, 7u);
  gzwrite(gzf, (uint8_t *)dma_channel_status, 4u);
  gzwrite(gzf, (uint8_t *)hw_saved_state, 4u);
  gzwrite(gzf, (uint8_t *)mdec_dma_src, 0x60u);
  return gzwrite(gzf, (uint8_t *)hw_regs, 0x10000u);
}

int hw_reg_unfreeze(int unused, uint32_t *gzf)
{
  char tag[16];

  gzread(gzf, tag, 7);
  gzread(gzf, dma_channel_status, 4);
  gzread(gzf, hw_saved_state, 4);
  gzread(gzf, (char *)mdec_dma_src, 96);
  return gzread(gzf, hw_regs, 0x10000);
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char hw_regs[0x10000];
unsigned int sio_irq_pending;
unsigned int dma_int_ctrl;
unsigned int rcnt_counter[1];
unsigned int rcnt_mode[1];
unsigned int dma_channel_status[1];
unsigned int mdec_dma_bcr[1];
unsigned int g_cdr_dma_channel_control;
unsigned int pio_dma_chcr;
unsigned int dma6_madr;
unsigned int dma6_bcr;
unsigned int hw_saved_state;
unsigned int gpu_dma6_status;
unsigned int hw_update_counter;
unsigned int mdec_dma_control[1];
unsigned int mdec_dma_src[1];
unsigned int mdec_dma_status;
unsigned int mdec_param_count;
