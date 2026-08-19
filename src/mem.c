#include "pch.h"
int mem_clear_memory()
{
    memset(ram, 0, 0x200000u);
    memset(pio_mem, 0xFFu, 0x20000u);
    memset(dcache, 0, sizeof(dcache));
    return 0;
}

void mem_init_memory_handlers()
{
  int i; // eax
  int *v1; // ecx
  char *v2; // ecx

  for ( i = 0; i < 0x10000; ++i )
  {
    mem_read_hooks[i] = (int)dummy_page;
    mem_write_hooks[i] = (int)dummy_page;
    if ( (unsigned int)i < 0x80
      || i >= 0x8000 && i <= 0x807F
      || i >= 0xA000 && i <= 0xA07F
      || i >= 0x3C00 && i <= 0x3C7F )
    {
      v1 = &ram[0x4000 * (i & 0x1F)];
      mem_read_hooks[i] = (int)v1;
      mem_write_hooks[i] = (int)v1;
    }
    if ( i >= 0x1F00 && i <= 0x1F01 )
    {
      v2 = &pio_mem[0x10000 * (unsigned __int8)i];
      mem_read_hooks[i] = (int)v2;
      mem_write_hooks[i] = (int)v2;
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

void __cdecl mem_hw_reg_read_byte(unsigned int a1)
{
  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 || (unsigned __int16)a1 < 0x1000u )
    return;
  if ( a1 >= 0x1F801C00 && a1 <= 0x1F801EEF )
  {
    spu_read_register_cb(a1);
    return;
  }
  if ( a1 > 0x1F801801 )
  {
    if ( a1 == 0x1F801802 )
    {
      ++g_cdr_data_bytes_transferred;
      return;
    }
    if ( a1 == 0x1F801803 )
      return;
LABEL_19:
    dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", a1, 0, 1);
    return;
  }
  if ( a1 == 0x1F801801 )
  {
    if ( (unsigned __int8)g_cdr_response_index < (unsigned __int8)g_cdr_response_size )
    {
      if ( g_cdr_irq_pending )
      {
        if ( (unsigned __int8)++g_cdr_response_index >= (unsigned __int8)g_cdr_response_size )
          g_cdr_irq_pending = 0;
      }
    }
    return;
  }
  if ( a1 == 528486464 )
  {
    sio_read_data_byte();
    return;
  }
  if ( a1 != 528486646 && a1 != 528488448 )
    goto LABEL_19;
}

__int16 __cdecl mem_read_half(unsigned int a1)
{
  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 )
    return *(_WORD *)((unsigned __int16)a1 + mem_read_hooks[HIWORD(a1)]);
  if ( (unsigned __int16)a1 >= 0x1000u )
    return hw_reg_read_half(a1);
  return *(_WORD *)&dcache[a1 & 0xFFF];
}

int __cdecl mem_read_word(unsigned int a1)
{
  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 )
    return *(_DWORD *)((unsigned __int16)a1 + mem_read_hooks[HIWORD(a1)]);
  if ( (unsigned __int16)a1 >= 0x1000u )
    return hw_reg_read_word(a1);
  return *(_DWORD *)&dcache[a1 & 0xFFF];
}

void __cdecl mem_hw_reg_write_byte(unsigned int a1, char a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi

  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 < 0x1000u )
    {
      dcache[a1 & 0xFFF] = a2;
      return;
    }
    if ( a1 <= 0x1F801801 )
    {
      switch ( a1 )
      {
        case 0x1F801801u:
          cdr_reg1_write(a2);
          return;
        case 0x1F801040u:
          sio_write_data_byte(0x1F801040, a2);
          return;
        case 0x1F8010F6u:
          dma_int_ctrl = dma_int_ctrl & 0xFF00FFFF | ((unsigned __int8)a2 << 16);
          return;
        case 0x1F801800u:
          cdr_reg0_write(a2);
          return;
      }
      goto LABEL_27;
    }
    switch ( a1 )
    {
      case 0x1F801802u:
        cdr_reg2_write(a2);
        break;
      case 0x1F801803u:
        cdr_reg3_write(a2);
        break;
      case 0x1F802041u:
        hw_regs[8257] = a2;
        break;
      default:
LABEL_27:
        dump_log(
          console_log_handle,
          "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
          "UNK",
          a1,
          (unsigned __int8)a2,
          1,
          *(_DWORD *)reg_pc);
        return;
    }
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(_BYTE *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    if ( recomp_buffer )
    {
      v2 = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + v2) != recomp_buffer )
      {
        v3 = ((_BYTE *)recomp_buffer - (_BYTE *)recomp_metadata) >> 2;
        for ( *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer;
              v3;
              *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer )
        {
          v4 = *(LPVOID *)((char *)recomp_code_base + v2 - 4);
          v2 -= 4;
          if ( v4 == recomp_buffer )
            break;
          --v3;
        }
      }
    }
  }
}

void __cdecl mem_write_half(unsigned int a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi
  char v5; // cl

  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
    {
      if ( a1 > 0x1F801138 || a1 < 0x1F801100 )
      {
        if ( a1 > 0x1F801EEF || a1 < 0x1F801C00 )
        {
          switch ( a1 )
          {
            case 0x1F801014u:
              *(_WORD *)&hw_regs[(unsigned __int16)a1] = a2;
              break;
            case 0x1F801040u:
              sio_write_data_byte(a1, a2);
              sio_write_data_byte(a1, SHIBYTE(a2));
              break;
            case 0x1F801048u:
              HIWORD(sio0_mode_reg) = a2;
              break;
            case 0x1F80104Au:
              LOWORD(sio0_control_reg) = a2 & 0xFFEF;
              if ( (a2 & 0x10) != 0 )
                BYTE1(sio0_mode_reg) &= ~2u;
              sio_controller_init(a2);
              if ( (v5 & 1) != 0 )
                LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
              sio_tx_fifo[0] = 1 << (BYTE1(sio0_control_reg) & 3);
              sio_tx_fifo[2] = 1 << (BYTE1(sio0_control_reg) & 3);
              break;
            case 0x1F80104Eu:
              HIWORD(sio0_control_reg) = a2;
              break;
            case 0x1F801070u:
              if ( *(_DWORD *)sio_irq_pending && (unsigned int)hw_update_counter < *(_DWORD *)sio_irq_timeout )
              {
                *(_DWORD *)int_reg |= *(_DWORD *)sio_irq_pending;
                *(_DWORD *)sio_irq_pending = 0;
              }
              *(_DWORD *)int_reg = (unsigned __int16)(int_mask & a2 & *(_WORD *)int_reg);
              break;
            case 0x1F801074u:
              int_mask = a2;
              break;
            default:
              dump_log(
                console_log_handle,
                "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                "UNK",
                a1,
                a2,
                2,
                *(_DWORD *)reg_pc);
              break;
          }
        }
        else
        {
          spu_write_register_cb(a1, a2);
        }
      }
      else
      {
        irq_rcnt_write_reg(a1, a2);
      }
    }
    else
    {
      *(_WORD *)&dcache[a1 & 0xFFF] = a2;
    }
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(_WORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    if ( recomp_buffer )
    {
      v2 = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + v2) != recomp_buffer )
      {
        v3 = ((_BYTE *)recomp_buffer - (_BYTE *)recomp_metadata) >> 2;
        for ( *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer;
              v3;
              *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer )
        {
          v4 = *(LPVOID *)((char *)recomp_code_base + v2 - 4);
          v2 -= 4;
          if ( v4 == recomp_buffer )
            break;
          --v3;
        }
      }
    }
  }
}

void __cdecl mem_write_word(unsigned int a1, unsigned int a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi

  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
      hw_reg_write_word(a1, a2);
    else
      *(_DWORD *)&dcache[a1 & 0xFFF] = a2;
  }
  else if ( (cop0_sr & 0x10000) == 0 )
  {
    *(_DWORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    if ( recomp_buffer )
    {
      v2 = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + v2) != recomp_buffer )
      {
        v3 = ((_BYTE *)recomp_buffer - (_BYTE *)recomp_metadata) >> 2;
        for ( *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer;
              v3;
              *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer )
        {
          v4 = *(LPVOID *)((char *)recomp_code_base + v2 - 4);
          v2 -= 4;
          if ( v4 == recomp_buffer )
            break;
          --v3;
        }
      }
    }
  }
}

int __cdecl mem_dma_read(unsigned int a1)
{
  return mem_read_hooks[HIWORD(a1)] + (unsigned __int16)a1;
}

unsigned int __cdecl mem_gpu_dma_read(unsigned int a1)
{
  if ( (a1 & 0xFF800000) != 0x1F800000 )
    return *(_DWORD *)((unsigned __int16)a1 + mem_read_hooks[HIWORD(a1)]);
  if ( a1 >= 0x1F801000 )
    return hw_reg_read_word(a1);
  return *(_DWORD *)&dcache[a1 & 0xFFF];
}

void __cdecl mem_hw_reg_write_half(unsigned int a1, unsigned __int16 a2)
{
  char v2; // cl

  if ( (cop0_sr & 0x10000) == 0 )
  {
    if ( (a1 & 0xFF800000) == 0x1F800000 )
    {
      if ( a1 >= 0x1F801000 )
      {
        if ( a1 > 0x1F801138 || a1 < 0x1F801100 )
        {
          if ( a1 > 0x1F801EEF || a1 < 0x1F801C00 )
          {
            switch ( a1 )
            {
              case 0x1F801014u:
                *(_WORD *)&hw_regs[(unsigned __int16)a1] = a2;
                break;
              case 0x1F801040u:
                sio_write_data_byte(a1, a2);
                sio_write_data_byte(a1, SHIBYTE(a2));
                break;
              case 0x1F801048u:
                HIWORD(sio0_mode_reg) = a2;
                break;
              case 0x1F80104Au:
                LOWORD(sio0_control_reg) = a2 & 0xFFEF;
                if ( (a2 & 0x10) != 0 )
                  BYTE1(sio0_mode_reg) &= ~2u;
                sio_controller_init(a2);
                if ( (v2 & 1) != 0 )
                  LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
                sio_tx_fifo[0] = 1 << (BYTE1(sio0_control_reg) & 3);
                sio_tx_fifo[2] = 1 << (BYTE1(sio0_control_reg) & 3);
                break;
              case 0x1F80104Eu:
                HIWORD(sio0_control_reg) = a2;
                break;
              case 0x1F801070u:
                if ( *(_DWORD *)sio_irq_pending && (unsigned int)hw_update_counter < *(_DWORD *)sio_irq_timeout )
                {
                  *(_DWORD *)int_reg |= *(_DWORD *)sio_irq_pending;
                  *(_DWORD *)sio_irq_pending = 0;
                }
                *(_DWORD *)int_reg = (unsigned __int16)(int_mask & a2 & *(_WORD *)int_reg);
                break;
              case 0x1F801074u:
                int_mask = a2;
                break;
              default:
                dump_log(
                  console_log_handle,
                  "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                  "UNK",
                  a1,
                  a2,
                  2,
                  *(_DWORD *)reg_pc);
                break;
            }
          }
          else
          {
            spu_write_register_cb(a1, a2);
          }
        }
        else
        {
          irq_rcnt_write_reg(a1, a2);
        }
      }
      else
      {
        *(_WORD *)&dcache[a1 & 0xFFF] = a2;
      }
    }
    else
    {
      *(_WORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    }
  }
}

void __cdecl mem_gpu_dma_write(unsigned int a1, unsigned int a2)
{
  if ( (cop0_sr & 0x10000) == 0 )
  {
    if ( (a1 & 0xFF800000) == 0x1F800000 )
    {
      if ( a1 >= 0x1F801000 )
        hw_reg_write_word(a1, a2);
      else
        *(_DWORD *)&dcache[a1 & 0xFFF] = a2;
    }
    else
    {
      *(_DWORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    }
  }
}

int __cdecl mem_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 2232320;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)ram, 0x200000u);
  gzwrite(a2, (unsigned __int8 *)pio_mem, 0x20000u);
  return gzwrite(a2, (unsigned __int8 *)dcache, 0x1000u);
}

int __cdecl mem_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, (char *)ram, 0x200000);
  gzread(a2, pio_mem, 0x20000);
  return gzread(a2, dcache, 4096);
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int console_log_handle;
unsigned char dcache[0x1000];
unsigned char dummy_page[0x10000];
unsigned char mem_handlers_inited = 0x1;
unsigned int mem_read_hooks[0x10000];
unsigned int mem_write_hooks[0x10000];
unsigned char pio_mem[0x20000];
unsigned char ram[0x200000];
unsigned int sio0_control_reg;
