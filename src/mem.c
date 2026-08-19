#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned int console_log_handle;
unsigned char dcache[0x1000];
static unsigned char dummy_page[0x10000];
static unsigned char mem_handlers_inited = 0x1;
unsigned int mem_read_hooks[0x10000];
unsigned int mem_write_hooks[0x10000];
static unsigned char pio_mem[0x20000];
unsigned char ram[0x200000];
unsigned int sio0_control_reg;

int mem_clear_memory()
{
    memset(ram, 0, 0x200000u);
    memset(pio_mem, 0xFFu, 0x20000u);
    memset(dcache, 0, sizeof(dcache));
    return 0;
}

void mem_init_memory_handlers()
{
  int i;
  int *ram_ptr;
  char *pio_ptr;

  for ( i = 0; i < 0x10000; ++i )
  {
    mem_read_hooks[i] = (int)dummy_page;
    mem_write_hooks[i] = (int)dummy_page;
    if ( (unsigned int)i < 0x80
      || i >= 0x8000 && i <= 0x807F
      || i >= 0xA000 && i <= 0xA07F
      || i >= 0x3C00 && i <= 0x3C7F )
    {
      ram_ptr = &ram[0x4000 * (i & 0x1F)];
      mem_read_hooks[i] = (int)ram_ptr;
      mem_write_hooks[i] = (int)ram_ptr;
    }
    if ( i >= 0x1F00 && i <= 0x1F01 )
    {
      pio_ptr = &pio_mem[0x10000 * (uint8_t)i];
      mem_read_hooks[i] = (int)pio_ptr;
      mem_write_hooks[i] = (int)pio_ptr;
    }
    if ( i >= 0x1FC0 && i <= 0x1FC7 || i >= 0x9FC0 && i <= 0x9FC7 || i >= 0xBFC0 && i <= 0xBFC7 )
    {
      mem_read_hooks[i] = (int)&bios_image[0x10000 * (i & 7)];
      mem_write_hooks[i] = (int)dummy_page;
    }
  }
  mem_handlers_inited = 1;
  dbg_print_no_flush(" * Memory handlers init. \n");
}

void mem_hw_reg_read_byte(unsigned int addr)
{
  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) != 0x1F800000 || (uint16_t)addr < 0x1000u )
    return;
  if ( addr >= 0x1F801C00 && addr <= 0x1F801EEF )
  {
    spu_read_register_cb(addr);
    return;
  }
  if ( addr > 0x1F801801 )
  {
    if ( addr == 0x1F801802 )
    {
      ++g_cdr_data_bytes_transferred;
      return;
    }
    if ( addr == 0x1F801803 )
      return;
LABEL_19:
    dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", addr, 0, 1);
    return;
  }
  if ( addr == 0x1F801801 )
  {
    if ( (uint8_t)g_cdr_response_index < (uint8_t)g_cdr_response_size )
    {
      if ( g_cdr_irq_pending )
      {
        if ( (uint8_t)++g_cdr_response_index >= (uint8_t)g_cdr_response_size )
          g_cdr_irq_pending = 0;
      }
    }
    return;
  }
  if ( addr == 528486464 )
  {
    sio_read_data_byte();
    return;
  }
  if ( addr != 528486646 && addr != 528488448 )
    goto LABEL_19;
}

int16_t mem_read_half(unsigned int addr)
{
  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) != 0x1F800000 )
    return *(uint16_t *)((uint16_t)addr + mem_read_hooks[HIWORD(addr)]);
  if ( (uint16_t)addr >= 0x1000u )
    return hw_reg_read_half(addr);
  return *(uint16_t *)&dcache[addr & 0xFFF];
}

int mem_read_word(unsigned int addr)
{
  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) != 0x1F800000 )
    return *(uint32_t *)((uint16_t)addr + mem_read_hooks[HIWORD(addr)]);
  if ( (uint16_t)addr >= 0x1000u )
    return hw_reg_read_word(addr);
  return *(uint32_t *)&dcache[addr & 0xFFF];
}

void mem_hw_reg_write_byte(unsigned int addr, char value)
{
  unsigned int code_off;
  int count;
  LPVOID prev;

  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) == 0x1F800000 )
  {
    if ( (uint16_t)addr < 0x1000u )
    {
      dcache[addr & 0xFFF] = value;
      return;
    }
    if ( addr <= 0x1F801801 )
    {
      switch ( addr )
      {
        case 0x1F801801u:
          cdr_reg1_write(value);
          return;
        case 0x1F801040u:
          sio_write_data_byte(0x1F801040, value);
          return;
        case 0x1F8010F6u:
          dma_int_ctrl = dma_int_ctrl & 0xFF00FFFF | ((uint8_t)value << 16);
          return;
        case 0x1F801800u:
          cdr_reg0_write(value);
          return;
      }
      goto LABEL_27;
    }
    switch ( addr )
    {
      case 0x1F801802u:
        cdr_reg2_write(value);
        break;
      case 0x1F801803u:
        cdr_reg3_write(value);
        break;
      case 0x1F802041u:
        hw_regs[8257] = value;
        break;
      default:
LABEL_27:
        dump_log(
          console_log_handle,
          "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
          "UNK",
          addr,
          (uint8_t)value,
          1,
          *(uint32_t *)reg_pc);
        return;
    }
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(uint8_t *)((uint16_t)addr + mem_write_hooks[HIWORD(addr)]) = value;
    if ( recomp_buffer )
    {
      code_off = (addr & 0xFFF00000) == 0xBFC00000 ? (addr & 0x7FFFC) + 0x200000 : addr & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + code_off) != recomp_buffer )
      {
        count = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
        for ( *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer;
              count;
              *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer )
        {
          prev = *(LPVOID *)((char *)recomp_code_base + code_off - 4);
          code_off -= 4;
          if ( prev == recomp_buffer )
            break;
          --count;
        }
      }
    }
  }
}

void mem_write_half(unsigned int addr, uint16_t value)
{
  unsigned int code_off;
  int count;
  LPVOID prev;
  char sio_status;

  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) == 0x1F800000 )
  {
    if ( (uint16_t)addr >= 0x1000u )
    {
      if ( addr > 0x1F801138 || addr < 0x1F801100 )
      {
        if ( addr > 0x1F801EEF || addr < 0x1F801C00 )
        {
          switch ( addr )
          {
            case 0x1F801014u:
              *(uint16_t *)&hw_regs[(uint16_t)addr] = value;
              break;
            case 0x1F801040u:
              sio_write_data_byte(addr, value);
              sio_write_data_byte(addr, SHIBYTE(value));
              break;
            case 0x1F801048u:
              HIWORD(sio0_mode_reg) = value;
              break;
            case 0x1F80104Au:
              LOWORD(sio0_control_reg) = value & 0xFFEF;
              if ( (value & 0x10) != 0 )
                BYTE1(sio0_mode_reg) &= ~2u;
              sio_controller_init(value);
              if ( (sio_status & 1) != 0 )
                LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
              sio_tx_fifo[0] = 1 << (BYTE1(sio0_control_reg) & 3);
              sio_tx_fifo[2] = 1 << (BYTE1(sio0_control_reg) & 3);
              break;
            case 0x1F80104Eu:
              HIWORD(sio0_control_reg) = value;
              break;
            case 0x1F801070u:
              if ( *(uint32_t *)sio_irq_pending && (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
              {
                *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
                *(uint32_t *)sio_irq_pending = 0;
              }
              *(uint32_t *)int_reg = (uint16_t)(int_mask & value & *(uint16_t *)int_reg);
              break;
            case 0x1F801074u:
              int_mask = value;
              break;
            default:
              dump_log(
                console_log_handle,
                "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                "UNK",
                addr,
                value,
                2,
                *(uint32_t *)reg_pc);
              break;
          }
        }
        else
        {
          spu_write_register_cb(addr, value);
        }
      }
      else
      {
        irq_rcnt_write_reg(addr, value);
      }
    }
    else
    {
      *(uint16_t *)&dcache[addr & 0xFFF] = value;
    }
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(uint16_t *)((uint16_t)addr + mem_write_hooks[HIWORD(addr)]) = value;
    if ( recomp_buffer )
    {
      code_off = (addr & 0xFFF00000) == 0xBFC00000 ? (addr & 0x7FFFC) + 0x200000 : addr & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + code_off) != recomp_buffer )
      {
        count = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
        for ( *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer;
              count;
              *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer )
        {
          prev = *(LPVOID *)((char *)recomp_code_base + code_off - 4);
          code_off -= 4;
          if ( prev == recomp_buffer )
            break;
          --count;
        }
      }
    }
  }
}

void mem_write_word(unsigned int addr, unsigned int value)
{
  unsigned int code_off;
  int count;
  LPVOID prev;

  hw_update_counter -= 4;
  if ( (addr & 0x1FC00000) == 0x1F800000 )
  {
    if ( (uint16_t)addr >= 0x1000u )
      hw_reg_write_word(addr, value);
    else
      *(uint32_t *)&dcache[addr & 0xFFF] = value;
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(uint32_t *)((uint16_t)addr + mem_write_hooks[HIWORD(addr)]) = value;
    if ( recomp_buffer )
    {
      code_off = (addr & 0xFFF00000) == 0xBFC00000 ? (addr & 0x7FFFC) + 0x200000 : addr & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + code_off) != recomp_buffer )
      {
        count = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
        for ( *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer;
              count;
              *(uint32_t *)((char *)recomp_code_base + code_off) = recomp_buffer )
        {
          prev = *(LPVOID *)((char *)recomp_code_base + code_off - 4);
          code_off -= 4;
          if ( prev == recomp_buffer )
            break;
          --count;
        }
      }
    }
  }
}

int mem_dma_read(unsigned int addr)
{
  return mem_read_hooks[HIWORD(addr)] + (uint16_t)addr;
}

unsigned int mem_gpu_dma_read(unsigned int addr)
{
  if ( (addr & 0xFF800000) != 0x1F800000 )
    return *(uint32_t *)((uint16_t)addr + mem_read_hooks[HIWORD(addr)]);
  if ( addr >= 0x1F801000 )
    return hw_reg_read_word(addr);
  return *(uint32_t *)&dcache[addr & 0xFFF];
}

void mem_hw_reg_write_half(unsigned int addr, uint16_t value)
{
  char sio_status;

  if ( (cop0_sr & 0x10000) == 0 )
  {
    if ( (addr & 0xFF800000) == 0x1F800000 )
    {
      if ( addr >= 0x1F801000 )
      {
        if ( addr > 0x1F801138 || addr < 0x1F801100 )
        {
          if ( addr > 0x1F801EEF || addr < 0x1F801C00 )
          {
            switch ( addr )
            {
              case 0x1F801014u:
                *(uint16_t *)&hw_regs[(uint16_t)addr] = value;
                break;
              case 0x1F801040u:
                sio_write_data_byte(addr, value);
                sio_write_data_byte(addr, SHIBYTE(value));
                break;
              case 0x1F801048u:
                HIWORD(sio0_mode_reg) = value;
                break;
              case 0x1F80104Au:
                LOWORD(sio0_control_reg) = value & 0xFFEF;
                if ( (value & 0x10) != 0 )
                  BYTE1(sio0_mode_reg) &= ~2u;
                sio_controller_init(value);
                if ( (sio_status & 1) != 0 )
                  LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
                sio_tx_fifo[0] = 1 << (BYTE1(sio0_control_reg) & 3);
                sio_tx_fifo[2] = 1 << (BYTE1(sio0_control_reg) & 3);
                break;
              case 0x1F80104Eu:
                HIWORD(sio0_control_reg) = value;
                break;
              case 0x1F801070u:
                if ( *(uint32_t *)sio_irq_pending && (unsigned int)hw_update_counter < *(uint32_t *)sio_irq_timeout )
                {
                  *(uint32_t *)int_reg |= *(uint32_t *)sio_irq_pending;
                  *(uint32_t *)sio_irq_pending = 0;
                }
                *(uint32_t *)int_reg = (uint16_t)(int_mask & value & *(uint16_t *)int_reg);
                break;
              case 0x1F801074u:
                int_mask = value;
                break;
              default:
                dump_log(
                  console_log_handle,
                  "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                  "UNK",
                  addr,
                  value,
                  2,
                  *(uint32_t *)reg_pc);
                break;
            }
          }
          else
          {
            spu_write_register_cb(addr, value);
          }
        }
        else
        {
          irq_rcnt_write_reg(addr, value);
        }
      }
      else
      {
        *(uint16_t *)&dcache[addr & 0xFFF] = value;
      }
    }
    else
    {
      *(uint16_t *)((uint16_t)addr + mem_write_hooks[HIWORD(addr)]) = value;
    }
  }
}

void mem_gpu_dma_write(unsigned int addr, unsigned int value)
{
  if ( (cop0_sr & 0x10000) == 0 )
  {
    if ( (addr & 0xFF800000) == 0x1F800000 )
    {
      if ( addr >= 0x1F801000 )
        hw_reg_write_word(addr, value);
      else
        *(uint32_t *)&dcache[addr & 0xFFF] = value;
    }
    else
    {
      *(uint32_t *)((uint16_t)addr + mem_write_hooks[HIWORD(addr)]) = value;
    }
  }
}

int mem_freeze(const char *name, int gzf)
{
  char Buffer[3];

  sprintf(Buffer, "%s", name);
  gzwrite(gzf, (uint8_t *)Buffer, 7u);
  gzwrite(gzf, (uint8_t *)ram, 0x200000u);
  gzwrite(gzf, (uint8_t *)pio_mem, 0x20000u);
  return gzwrite(gzf, (uint8_t *)dcache, 0x1000u);
}

int mem_unfreeze(int unused, uint32_t *gzf)
{
  char tag[16];

  gzread(gzf, tag, 7);
  gzread(gzf, (char *)ram, 0x200000);
  gzread(gzf, pio_mem, 0x20000);
  return gzread(gzf, dcache, 4096);
}
