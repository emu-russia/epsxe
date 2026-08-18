#include "pch.h"
void __cdecl hw_reg_write_word(unsigned int a1, unsigned int a2)
{
  int v2; // eax
  unsigned int v3; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // edi
  int v7; // ebx

  if ( a1 <= 0x1F801020 && a1 >= 0x1F801000 )
  {
    *(_DWORD *)&hw_regs[(unsigned __int16)a1] = a2;
    return;
  }
  if ( a1 <= 0x1F801138 && a1 >= 0x1F801100 )
  {
    irq_rcnt_write_reg(a1, a2);
    return;
  }
  if ( a1 <= 0x1F801E0F && a1 >= 0x1F801C00 )
  {
    spu_write_register_cb(a1, (unsigned __int16)a2);
    spu_write_register_cb(a1 + 2, HIWORD(a2));
    return;
  }
  if ( a1 <= 0x1F8010B8 )
  {
    if ( a1 == 0x1F8010B8 )
    {
      g_cdr_dma_channel_control = a2;
      if ( dma_channel_status[1] < 0 )
      {
        cdr_dma();
        g_cdr_dma_channel_control = a2 & 0xFEFFFFFF;
        irq_dma_assert_int(3u);
      }
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F801040u:
          sio_write_data_byte(a1, a2);
          sio_write_data_byte(a1, SBYTE1(a2));
          sio_write_data_byte(a1, SBYTE2(a2));
          sio_write_data_byte(a1, SHIBYTE(a2));
          break;
        case 0x1F801060u:
          *(_DWORD *)&hw_regs[(unsigned __int16)a1] = a2;
          break;
        case 0x1F801070u:
          if ( *(_DWORD *)sio_irq_pending )
          {
            if ( (unsigned int)hw_update_counter < *(_DWORD *)sio_irq_timeout )
            {
              *(_DWORD *)int_reg |= *(_DWORD *)sio_irq_pending;
              *(_DWORD *)sio_irq_pending = 0;
            }
          }
          *(_DWORD *)int_reg &= a2 & int_mask;
          break;
        case 0x1F801074u:
          int_mask = a2;
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
          mdec_dma_control[0] = a2;
          if ( (dma_channel_status[0] & 8) != 0 )
          {
            mdec_dma_in_handler();
            mdec_dma_control[0] = a2 & 0xFEFFFFFF;
            irq_dma_assert_int(0);
          }
          break;
        case 0x1F801098u:
          mdec_dma_status = a2;
          if ( dma_channel_status[0] < 0 )
          {
            mdec_decode();
            if ( !mdectiming )
            {
              mdec_dma_status = a2 & 0xFEFFFFFF;
              irq_dma_assert_int(1u);
            }
          }
          break;
        case 0x1F8010A8u:
          *(_DWORD *)gpu_dma_channel_status = a2;
          if ( (dma_channel_status[1] & 8) != 0 )
            gpu_dma();
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( a1 <= 0x1F8010E4 )
  {
    if ( a1 == 528486628 )
    {
LABEL_37:
      mdec_dma_bcr[3 * ((unsigned __int8)a1 >> 4) - 24] = a2;
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
LABEL_32:
          mdec_dma_src[3 * ((unsigned __int8)a1 >> 4) - 24] = a2;
          break;
        case 0x1F8010C4u:
        case 0x1F8010D4u:
          goto LABEL_37;
        case 0x1F8010C8u:
          *(_DWORD *)spu_dma_chcr_ptr = a2;
          if ( (*(_DWORD *)dma_channel_status & 0x80000) != 0 )
          {
            spu_dma_cb();
            *(_DWORD *)spu_dma_chcr_ptr = a2 & 0xFEFFFFFF;
            irq_dma_assert_int(4u);
          }
          break;
        case 0x1F8010D8u:
          pio_dma_chcr = a2;
          if ( ((unsigned int)&bios_image[37248] & *(_DWORD *)dma_channel_status) != 0 )
          {
            pio_dma_chcr = a2 & 0xFEFFFFFF;
            irq_dma_assert_int(5u);
          }
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( a1 > 0x1F801810 )
  {
    switch ( a1 )
    {
      case 0x1F801814u:
        gpu_writeStatus(a2);
        return;
      case 0x1F801820u:
        mdec_write_command(a2);
        return;
      case 0x1F801824u:
        mdec_handle_special_command(a2);
        return;
    }
LABEL_51:
    dump_log(console_log_handle, "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n", "UNK", a1, a2, 4, *(_DWORD *)reg_pc);
    return;
  }
  if ( a1 == 528488464 )
  {
    gpu_writeData(a2);
    return;
  }
  if ( a1 != 528486632 )
  {
    if ( a1 == 528486640 )
    {
      *(_DWORD *)dma_channel_status = a2;
      return;
    }
    if ( a1 == 528486644 )
    {
      dma_int_ctrl = a2 & 0xFFFFFF | dma_int_ctrl & ~(a2 | 0xFFFFFF);
      return;
    }
    goto LABEL_51;
  }
  *(_DWORD *)gpu_dma6_status = a2;
  if ( (*(_DWORD *)dma_channel_status & 0x8000000) != 0 )
  {
    v2 = dma6_madr;
    v3 = dma6_bcr;
    if ( *(_DWORD *)gpu_dma6_status == 285212674 )
    {
      if ( dma6_bcr )
      {
        v4 = dma6_madr - 4;
        v5 = dma6_bcr;
        do
        {
          v6 = v4 & 0xFFFFFF;
          v7 = v2 & 0x1FFFFF;
          v2 -= 4;
          v4 -= 4;
          --v5;
          *(int *)((char *)ram + v7) = v6;
        }
        while ( v5 );
      }
      *(int *)((char *)&ram[1] + (v2 & 0x1FFFFF)) = 0xFFFFFF;
      if ( v3 <= 0x40 )
      {
        *(_DWORD *)gpu_dma6_status = 268435458;
        irq_dma_assert_int(6u);
      }
      else
      {
        gpu_dma6_delay_counter = 1;
      }
    }
    else if ( (*(_DWORD *)gpu_dma6_status & 0x1000000) != 0 )
    {
      ui_error("DMA[6] mode NOT implemented (%08x)\n", *(_DWORD *)gpu_dma6_status);
    }
  }
}

__int16 __cdecl hw_reg_read_half(unsigned int a1)
{
  int v1; // eax
  int v2; // ecx
  char v3; // al
  __int16 v4; // bx
  unsigned int v5; // esi
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  unsigned int v9; // ecx
  unsigned int v10; // esi
  __int16 v11; // ax
  int v12; // esi
  __int16 v13; // ax

  if ( a1 < 0x1F801C00 || a1 > 0x1F801EEF )
  {
    if ( a1 > 0x1F801108 )
    {
      switch ( a1 )
      {
        case 0x1F801110u:
          LOWORD(v1) = LOWORD(rcnt_counter[4 * ((a1 >> 4) & 3)])
                     + ((rcnt_mode[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                     - ((rcnt_mode[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter);
          return v1;
        case 0x1F801114u:
        case 0x1F801124u:
        case 0x1F801134u:
LABEL_33:
          LOWORD(v1) = rcnt_mode[4 * ((a1 >> 4) & 3)];
          return v1;
        case 0x1F801118u:
        case 0x1F801128u:
        case 0x1F801138u:
          goto LABEL_34;
        case 0x1F801120u:
          LOWORD(v9) = cpu_speed_scale;
          v10 = 4 * ((a1 >> 4) & 3);
          v11 = rcnt_counter[v10];
          v12 = rcnt_mode[v10] & 0x200;
          if ( v12 )
            v9 = (unsigned int)cpu_speed_scale >> 3;
          v13 = v9 + v11;
          LOWORD(v9) = hw_update_counter;
          if ( v12 )
            v9 = (unsigned int)hw_update_counter >> 3;
          LOWORD(v1) = v13 - v9;
          return v1;
        case 0x1F801130u:
          goto LABEL_36;
        default:
LABEL_35:
          dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", a1, 0, 2);
LABEL_36:
          LOWORD(v1) = 0;
          break;
      }
    }
    else if ( a1 == 0x1F801108 )
    {
LABEL_34:
      LOWORD(v1) = rcnt_target[4 * ((a1 >> 4) & 3)];
    }
    else
    {
      HIWORD(v2) = 0;
      switch ( a1 )
      {
        case 0x1F801014u:
          LOWORD(v1) = *(_WORD *)&hw_regs[(unsigned __int16)a1];
          break;
        case 0x1F801040u:
          sio_read_data_byte();
          HIBYTE(v4) = v3;
          sio_read_data_byte();
          LOBYTE(v4) = v1;
          LOWORD(v1) = v4;
          break;
        case 0x1F801044u:
          if ( sio_transfer_pending && hw_update_counter < (unsigned int)sio_transfer_timeout )
          {
            sio_transfer_pending = 0;
            sio_trigger_rx_ready_irq();
          }
          LOWORD(v1) = sio0_mode_reg;
          break;
        case 0x1F801048u:
          LOWORD(v1) = HIWORD(sio0_mode_reg);
          break;
        case 0x1F80104Au:
          LOWORD(v1) = sio0_control_reg;
          break;
        case 0x1F80104Eu:
          LOWORD(v1) = HIWORD(sio0_control_reg);
          break;
        case 0x1F801070u:
          if ( *(_DWORD *)sio_irq_pending && (unsigned int)hw_update_counter < *(_DWORD *)sio_irq_timeout )
          {
            *(_DWORD *)int_reg |= *(_DWORD *)sio_irq_pending;
            *(_DWORD *)sio_irq_pending = 0;
          }
          LOWORD(v1) = *(_WORD *)int_reg | forcepad;
          break;
        case 0x1F801074u:
          LOWORD(v1) = int_mask;
          break;
        case 0x1F801100u:
          v5 = 4 * ((a1 >> 4) & 3);
          LOWORD(v2) = rcnt_counter[v5];
          v6 = rcnt_mode[v5] & 0x100;
          v7 = 512;
          if ( !v6 )
            v7 = cpu_speed_scale;
          v8 = v7 + v2;
          if ( v6 )
            v1 = v8 - (hw_update_counter << 9) / (unsigned int)cpu_speed_scale;
          else
            LOWORD(v1) = v8 - hw_update_counter;
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
    LOWORD(v1) = spu_read_register_cb(a1);
  }
  return v1;
}

int __cdecl hw_reg_read_word(unsigned int a1)
{
  int register_cb; // edi
  int result; // eax
  int v3; // esi
  unsigned int v4; // esi
  unsigned int v5; // esi
  int v6; // ecx
  int v7; // esi
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // esi
  int v12; // eax
  int v13; // esi
  unsigned int v14; // eax
  unsigned int v15; // ecx

  if ( a1 < 0x1F801C00 || a1 > 0x1F801E2F )
  {
    if ( a1 > 0x1F8010E8 )
    {
      if ( a1 > 0x1F801124 )
      {
        if ( a1 > 0x1F801810 )
        {
          switch ( a1 )
          {
            case 0x1F801814u:
              return gpu_readStatus();
            case 0x1F801820u:
              return 0;
            case 0x1F801824u:
              result = mdec_param_count | mdec_status | mdec_timer_count;
              mdec_timer_count = 0;
              break;
            default:
LABEL_44:
              dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", a1, 0, 4);
              return 0;
          }
        }
        else if ( a1 == 0x1F801810 )
        {
          return gpu_readData();
        }
        else
        {
          switch ( a1 )
          {
            case 0x1F801128u:
            case 0x1F801138u:
LABEL_39:
              result = rcnt_target[4 * ((a1 >> 4) & 3)];
              break;
            case 0x1F801130u:
              return 0;
            case 0x1F801134u:
              return rcnt_mode[4 * ((a1 >> 4) & 3)];
            default:
              goto LABEL_44;
          }
        }
      }
      else if ( a1 == 0x1F801124 )
      {
        return rcnt_mode[4 * ((a1 >> 4) & 3)];
      }
      else
      {
        switch ( a1 )
        {
          case 0x1F8010F0u:
            result = *(_DWORD *)dma_channel_status;
            break;
          case 0x1F8010F4u:
            result = dma_int_ctrl;
            break;
          case 0x1F801100u:
            v5 = 4 * ((a1 >> 4) & 3);
            v6 = rcnt_counter[v5];
            v7 = rcnt_mode[v5] & 0x100;
            v8 = 512;
            if ( !v7 )
              v8 = cpu_speed_scale;
            v9 = v8 + v6;
            if ( v7 )
              result = v9 - (hw_update_counter << 9) / (unsigned int)cpu_speed_scale;
            else
              result = v9 - hw_update_counter;
            break;
          case 0x1F801104u:
          case 0x1F801114u:
            return rcnt_mode[4 * ((a1 >> 4) & 3)];
          case 0x1F801108u:
          case 0x1F801118u:
            goto LABEL_39;
          case 0x1F801110u:
            result = ((rcnt_mode[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : cpu_speed_scale)
                   - ((rcnt_mode[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter)
                   + rcnt_counter[4 * ((a1 >> 4) & 3)];
            break;
          case 0x1F801120u:
            v10 = cpu_speed_scale;
            v11 = 4 * ((a1 >> 4) & 3);
            v12 = rcnt_counter[v11];
            v13 = rcnt_mode[v11] & 0x200;
            if ( v13 )
              v10 = (unsigned int)cpu_speed_scale >> 3;
            v14 = v10 + v12;
            v15 = hw_update_counter;
            if ( v13 )
              v15 = (unsigned int)hw_update_counter >> 3;
            result = v14 - v15;
            break;
          default:
            goto LABEL_44;
        }
      }
    }
    else if ( a1 == 0x1F8010E8 )
    {
LABEL_15:
      v3 = (unsigned __int8)a1 >> 4;
      result = mdec_dma_control[3 * v3 - 24];
      if ( v3 == 10 && gpu_dma2_state <= 0 )
      {
        v4 = *(_DWORD *)gpu_dma_channel_status & 0xFEFFFFFF;
        *(_DWORD *)gpu_dma_channel_status &= ~0x1000000u;
        if ( gpu_dma2_state <= -2 )
          return v4;
      }
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F801014u:
        case 0x1F801060u:
          result = *(_DWORD *)&hw_regs[(unsigned __int16)a1];
          break;
        case 0x1F801040u:
        case 0x1F801044u:
          result = sio_read_register(a1, 4);
          break;
        case 0x1F801070u:
          if ( *(_DWORD *)sio_irq_pending )
          {
            if ( (unsigned int)hw_update_counter < *(_DWORD *)sio_irq_timeout )
            {
              *(_DWORD *)int_reg |= *(_DWORD *)sio_irq_pending;
              *(_DWORD *)sio_irq_pending = 0;
            }
          }
          result = *(_DWORD *)int_reg | forcepad;
          break;
        case 0x1F801074u:
          result = int_mask;
          break;
        case 0x1F801080u:
        case 0x1F801090u:
        case 0x1F8010A0u:
        case 0x1F8010B0u:
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
          result = mdec_dma_src[3 * ((unsigned __int8)a1 >> 4) - 24];
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
    register_cb = (unsigned __int16)spu_read_register_cb(a1);
    return register_cb | ((unsigned __int16)spu_read_register_cb(a1 + 2) << 16);
  }
  return result;
}

int __cdecl hw_reg_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 65640;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)dma_channel_status, 4u);
  gzwrite(a2, (unsigned __int8 *)hw_saved_state, 4u);
  gzwrite(a2, (unsigned __int8 *)mdec_dma_src, 0x60u);
  return gzwrite(a2, (unsigned __int8 *)hw_regs, 0x10000u);
}

int __cdecl hw_reg_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, dma_channel_status, 4);
  gzread(a2, hw_saved_state, 4);
  gzread(a2, (char *)mdec_dma_src, 96);
  return gzread(a2, hw_regs, 0x10000);
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
