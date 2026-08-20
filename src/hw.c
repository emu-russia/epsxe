#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned char hw_regs[0x10000];
unsigned int dma_int_ctrl;
unsigned int rcnt_counter[16];
unsigned int rcnt_mode[16];
unsigned int dma_channel_status[2];
static unsigned int mdec_dma_bcr[1];
unsigned int g_cdr_dma_channel_control;
static unsigned int pio_dma_chcr;
static unsigned int dma6_madr;
static unsigned int dma6_bcr;
/* Backing storage for the hardware-register save-state slot (hw_saved_state
 * is a pointer to it; the decompiler had left it as a raw unsigned int, which
 * made select_plugins_backend() write through a NULL pointer - issue #28). */
static unsigned int hw_saved_state_storage;
unsigned int *hw_saved_state = &hw_saved_state_storage;
/* Backing storage for the GPU DMA channel 6 status slot (same decompile
 * artifact: used as a pointer, was declared as a value). */
static unsigned int gpu_dma6_status_storage;
unsigned int *gpu_dma6_status = &gpu_dma6_status_storage;
unsigned int hw_update_counter;
unsigned int mdec_dma_control[1];
unsigned int mdec_dma_src[0x18];
unsigned int mdec_dma_status;
unsigned int mdec_param_count;

void hw_reg_write_word(unsigned int addr, unsigned int value)
{
  int madr;
  unsigned int bcr;
  int data;
  int count;
  int data24;
  int addr24;

  if ( addr <= PSX_REG_COM_DELAY && addr >= PSX_REG_EXP1_BASE )
  {
    *(uint32_t *)&hw_regs[(uint16_t)addr] = value;
    return;
  }
  /* Root counters 0..2 (1F801100h..1F801128h), plus ePSXe's legacy "timer 3"
     (1F801130h..1F801138h) - not a real PSX register, but emulated here */
  if ( addr <= 0x1F801138 && addr >= PSX_REG_T0_COUNT )
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
  if ( addr <= PSX_REG_CD_DMA_CHCR )
  {
    if ( addr == PSX_REG_CD_DMA_CHCR )
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
        case PSX_REG_JOY_DATA:
          sio_write_data_byte(addr, value);
          sio_write_data_byte(addr, SBYTE1(value));
          sio_write_data_byte(addr, SBYTE2(value));
          sio_write_data_byte(addr, SHIBYTE(value));
          break;
        case PSX_REG_RAM_SIZE:
          *(uint32_t *)&hw_regs[(uint16_t)addr] = value;
          break;
        case PSX_REG_I_STAT:
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
        case PSX_REG_I_MASK:
          int_mask = value;
          break;
        case PSX_REG_MDEC_IN_MADR:
        case PSX_REG_MDEC_OUT_MADR:
        case PSX_REG_GPU_DMA_MADR:
        case PSX_REG_CD_DMA_MADR:
          goto LABEL_32;
        case PSX_REG_MDEC_IN_BCR:
        case PSX_REG_MDEC_OUT_BCR:
        case PSX_REG_GPU_DMA_BCR:
        case PSX_REG_CD_DMA_BCR:
          goto LABEL_37;
        case PSX_REG_MDEC_IN_CHCR:
          mdec_dma_control[0] = value;
          if ( (dma_channel_status[0] & 8) != 0 )
          {
            mdec_dma_in_handler();
            mdec_dma_control[0] = value & 0xFEFFFFFF;
            irq_dma_assert_int(0);
          }
          break;
        case PSX_REG_MDEC_OUT_CHCR:
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
        case PSX_REG_GPU_DMA_CHCR:
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
  if ( addr <= PSX_REG_OTC_DMA_BCR )
  {
    if ( addr == PSX_REG_OTC_DMA_BCR )
    {
LABEL_37:
      mdec_dma_bcr[3 * ((uint8_t)addr >> 4) - 24] = value;
    }
    else
    {
      switch ( addr )
      {
        case PSX_REG_SPU_DMA_MADR:
        case PSX_REG_PIO_DMA_MADR:
        case PSX_REG_OTC_DMA_MADR:
LABEL_32:
          mdec_dma_src[3 * ((uint8_t)addr >> 4) - 24] = value;
          break;
        case PSX_REG_SPU_DMA_BCR:
        case PSX_REG_PIO_DMA_BCR:
          goto LABEL_37;
        case PSX_REG_SPU_DMA_CHCR:
          *(uint32_t *)spu_dma_chcr_ptr = value;
          if ( (*(uint32_t *)dma_channel_status & 0x80000) != 0 )
          {
            spu_dma_cb();
            *(uint32_t *)spu_dma_chcr_ptr = value & 0xFEFFFFFF;
            irq_dma_assert_int(4u);
          }
          break;
        case PSX_REG_PIO_DMA_CHCR:
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
  if ( addr > PSX_REG_GPU_GP0 )
  {
    switch ( addr )
    {
      case PSX_REG_GPU_GP1:
        gpu_writeStatus(value);
        return;
      case PSX_REG_MDEC_CMD:
        mdec_write_command(value);
        return;
      case PSX_REG_MDEC_STATUS:
        mdec_handle_special_command(value);
        return;
    }
LABEL_51:
    dump_log(console_log_handle, "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n", "UNK", addr, value, 4, *(uint32_t *)reg_pc);
    return;
  }
  if ( addr == PSX_REG_GPU_GP0 )
  {
    gpu_writeData(value);
    return;
  }
  if ( addr != PSX_REG_OTC_DMA_CHCR )
  {
    if ( addr == PSX_REG_DMA_PCR )
    {
      *(uint32_t *)dma_channel_status = value;
      return;
    }
    if ( addr == PSX_REG_DMA_ICR )
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
    if ( addr > PSX_REG_T0_TARGET )
    {
      switch ( addr )
      {
        case PSX_REG_T1_COUNT:
          LOWORD(value) = LOWORD(rcnt_counter[4 * ((addr >> 4) & 3)])
                         + ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                         - ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter);
          return value;
        case PSX_REG_T1_MODE:
        case PSX_REG_T2_MODE:
        case 0x1F801134u:        /* legacy timer 3 mode */
LABEL_33:
          LOWORD(value) = rcnt_mode[4 * ((addr >> 4) & 3)];
          return value;
        case PSX_REG_T1_TARGET:
        case PSX_REG_T2_TARGET:
        case 0x1F801138u:        /* legacy timer 3 target */
          goto LABEL_34;
        case PSX_REG_T2_COUNT:
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
        case 0x1F801130u:        /* legacy timer 3 count */
          goto LABEL_36;
        default:
LABEL_35:
          dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", addr, 0, 2);
LABEL_36:
          LOWORD(value) = 0;
          break;
      }
    }
    else if ( addr == PSX_REG_T0_TARGET )
    {
LABEL_34:
      LOWORD(value) = rcnt_target[4 * ((addr >> 4) & 3)];
    }
    else
    {
      HIWORD(counter) = 0;
      switch ( addr )
      {
        case PSX_REG_SPU_DELAY:
          LOWORD(value) = *(uint16_t *)&hw_regs[(uint16_t)addr];
          break;
        case PSX_REG_JOY_DATA:
          HIBYTE(sio_val) = sio_read_data_byte();
          LOBYTE(sio_val) = sio_read_data_byte();
          LOWORD(value) = sio_val;
          break;
        case PSX_REG_JOY_STATUS:
          if ( sio_transfer_pending && hw_update_counter < (unsigned int)sio_transfer_timeout )
          {
            sio_transfer_pending = 0;
            sio_trigger_rx_ready_irq();
          }
          LOWORD(value) = sio0_mode_reg;
          break;
        case PSX_REG_JOY_MODE:
          LOWORD(value) = HIWORD(sio0_mode_reg);
          break;
        case PSX_REG_JOY_CTRL:
          LOWORD(value) = sio0_control_reg;
          break;
        case PSX_REG_JOY_BAUD:
          LOWORD(value) = HIWORD(sio0_control_reg);
          break;
        case PSX_REG_I_STAT:
          if ( *(uint32_t *)sio_irq_pending && (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
          {
            *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
            *(uint32_t *)sio_irq_pending = 0;
          }
          LOWORD(value) = *(uint16_t *)int_reg | forcepad;
          break;
        case PSX_REG_I_MASK:
          LOWORD(value) = int_mask;
          break;
        case PSX_REG_T0_COUNT:
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
        case PSX_REG_T0_MODE:
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
    if ( addr > PSX_REG_OTC_DMA_CHCR )
    {
      if ( addr > PSX_REG_T2_MODE )
      {
        if ( addr > PSX_REG_GPU_GP0 )
        {
          switch ( addr )
          {
            case PSX_REG_GPU_GP1:
              return gpu_readStatus();
            case PSX_REG_MDEC_CMD:
              return 0;
            case PSX_REG_MDEC_STATUS:
              value = mdec_param_count | mdec_status | mdec_timer_count;
              mdec_timer_count = 0;
              break;
            default:
LABEL_44:
              dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", addr, 0, 4);
              return 0;
          }
        }
        else if ( addr == PSX_REG_GPU_GP0 )
        {
          return gpu_readData();
        }
        else
        {
          switch ( addr )
          {
            case PSX_REG_T2_TARGET:
            case 0x1F801138u:    /* legacy timer 3 target */
LABEL_39:
              value = rcnt_target[4 * ((addr >> 4) & 3)];
              break;
            case 0x1F801130u:    /* legacy timer 3 count */
              return 0;
            case 0x1F801134u:    /* legacy timer 3 mode */
              return rcnt_mode[4 * ((addr >> 4) & 3)];
            default:
              goto LABEL_44;
          }
        }
      }
      else if ( addr == PSX_REG_T2_MODE )
      {
        return rcnt_mode[4 * ((addr >> 4) & 3)];
      }
      else
      {
        switch ( addr )
        {
          case PSX_REG_DMA_PCR:
            value = *(uint32_t *)dma_channel_status;
            break;
          case PSX_REG_DMA_ICR:
            value = dma_int_ctrl;
            break;
          case PSX_REG_T0_COUNT:
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
          case PSX_REG_T0_MODE:
          case PSX_REG_T1_MODE:
            return rcnt_mode[4 * ((addr >> 4) & 3)];
          case PSX_REG_T0_TARGET:
          case PSX_REG_T1_TARGET:
            goto LABEL_39;
          case PSX_REG_T1_COUNT:
            value = ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                  - ((rcnt_mode[4 * ((addr >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter)
                  + rcnt_counter[4 * ((addr >> 4) & 3)];
            break;
          case PSX_REG_T2_COUNT:
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
    else if ( addr == PSX_REG_OTC_DMA_CHCR )
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
        case PSX_REG_SPU_DELAY:
        case PSX_REG_RAM_SIZE:
          value = *(uint32_t *)&hw_regs[(uint16_t)addr];
          break;
        case PSX_REG_JOY_DATA:
        case PSX_REG_JOY_STATUS:
          value = sio_read_register(addr, 4);
          break;
        case PSX_REG_I_STAT:
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
        case PSX_REG_I_MASK:
          value = int_mask;
          break;
        case PSX_REG_MDEC_IN_MADR:
        case PSX_REG_MDEC_OUT_MADR:
        case PSX_REG_GPU_DMA_MADR:
        case PSX_REG_CD_DMA_MADR:
        case PSX_REG_SPU_DMA_MADR:
        case PSX_REG_PIO_DMA_MADR:
        case PSX_REG_OTC_DMA_MADR:
          value = mdec_dma_src[3 * ((uint8_t)addr >> 4) - 24];
          break;
        case PSX_REG_MDEC_IN_CHCR:
        case PSX_REG_MDEC_OUT_CHCR:
        case PSX_REG_GPU_DMA_CHCR:
        case PSX_REG_CD_DMA_CHCR:
        case PSX_REG_SPU_DMA_CHCR:
        case PSX_REG_PIO_DMA_CHCR:
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
