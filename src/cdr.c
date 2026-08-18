#include "pch.h"
int __cdecl cdr_bcd_to_hex(unsigned __int8 a1)
{
  return a1 % 10 + 16 * (a1 / 10);
}

int __cdecl cdr_hex_to_bcd(unsigned __int8 a1)
{
  return (a1 & 0xF) + 10 * (a1 >> 4);
}

char __cdecl cdr_reg0_write(char a1)
{
  char result; // al

  result = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    result = a1 - 1;
    if ( a1 == 1 )
    {
      g_cdr_irq_pending = 1;
    }
    else
    {
      result = a1 - 2;
      if ( a1 == 2 )
      {
        g_cdr_param_fifo_count = 1;
        g_cdr_status_regs[64] = a1 & 1;
        return result;
      }
    }
    g_cdr_status_regs[64] = a1 & 1;
  }
  return result;
}

void __cdecl cdr_reg1_write(unsigned __int8 a1)
{
  int v1; // esi
  char v2; // al
  char v3; // dl
  unsigned __int8 v4; // al
  unsigned __int8 v5; // al
  unsigned __int8 v6; // al
  unsigned __int8 v7; // al
  int v8; // ecx
  unsigned __int8 v9; // al
  int v10; // [esp-14h] [ebp-24h]
  int v11; // [esp-14h] [ebp-24h]
  int v12; // [esp+8h] [ebp-8h] BYREF
  int v13; // [esp+Ch] [ebp-4h] BYREF

  v1 = loaded_file_type;
  if ( loaded_file_type != 4 && !g_cdr_param_fifo_count )
  {
    BYTE1(g_cdr_registers) = a1;
    g_cdr_status_regs[61] = 0;
    switch ( a1 )
    {
      case 0u:
        goto LABEL_93;
      case 1u:
        v2 = g_cdr_status_regs[68] == 0 ? 0 : 2;
        g_cdr_status_regs[66] = v2;
        if ( g_cdr_status_regs[69] )
        {
          v2 |= 0x10u;
          g_cdr_status_regs[66] = v2;
        }
        if ( g_cdr_status_regs[63] )
        {
          g_cdr_secondary_response_size = 3;
          LOBYTE(g_cdr_secondary_response) = v2 | g_cdr_status_regs[67] | g_cdr_status_regs[70];
          g_cdr_secondary_response_index = 1;
        }
        else
        {
          g_cdr_status_regs[63] = 3;
          LOBYTE(g_cdr_primary_response) = v2 | g_cdr_status_regs[67] | g_cdr_status_regs[70];
LABEL_8:
          g_cdr_status_regs[60] = 1;
        }
        goto LABEL_9;
      case 2u:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[66] = 2;
        LOBYTE(g_cdr_cur_msf_pos) = cdr_hex_to_bcd(g_cdr_param_fifo);
        BYTE1(g_cdr_cur_msf_pos) = cdr_hex_to_bcd(HIBYTE(g_cdr_param_fifo));
        BYTE2(g_cdr_cur_msf_pos) = cdr_hex_to_bcd(g_cdr_param_fifo_byte[0]);
        if ( !(_WORD)g_cdr_cur_msf_pos )
          BYTE1(g_cdr_cur_msf_pos) = v3;
        dword_5053E0 = 0;
        dword_5053E4 = 0;
        dword_5053E8 = 0;
        g_cdr_status_regs[62] = 0;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = v3;
        g_cdr_status_regs[60] = 1;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        dword_5053EC = 0;
        word_455FA6 = 200;
        return;
      case 3u:
        if ( !g_cdr_status_regs[70] )
        {
          v10 = (unsigned __int8)cdr_bcd_to_hex(BYTE1(g_cdr_cur_msf_pos));
          v4 = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
          cdrom_lba_to_msf_cb(v4, v10, 0, &g_cdr_seek_target_msf, (char *)&g_cdr_seek_target_msf + 1, &byte_50BF7C);
          v5 = BYTE1(g_cdr_cur_msf_pos);
          if ( g_cdr_seek_target_msf == (_WORD)g_cdr_cur_msf_pos )
          {
            v6 = BYTE1(g_cdr_cur_msf_pos) + 2;
            BYTE1(g_cdr_cur_msf_pos) = v6;
            if ( v6 >= 0x3Cu )
            {
              v6 -= 60;
              BYTE1(g_cdr_cur_msf_pos) = v6;
              LOBYTE(g_cdr_cur_msf_pos) = g_cdr_cur_msf_pos + 1;
            }
            v11 = (unsigned __int8)cdr_bcd_to_hex(v6);
            v7 = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
            cdrom_lba_to_msf_cb(v7, v11, 0, &g_cdr_seek_target_msf, (char *)&g_cdr_seek_target_msf + 1, &byte_50BF7C);
            v5 = BYTE1(g_cdr_cur_msf_pos);
          }
          cdrom_play_cdda_cb((unsigned __int8)g_cdr_cur_msf_pos, v5, BYTE2(g_cdr_cur_msf_pos));
        }
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0x80;
        g_cdr_status_regs[66] = -126;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = -126;
        g_cdr_status_regs[60] = 1;
        cdr_init_report_mode();
        goto LABEL_9;
      case 4u:
      case 5u:
        g_cdr_status_regs[68] = 1;
        goto LABEL_93;
      case 6u:
        cdrom_stop_cb();
        g_cdr_status_regs[66] = 34;
        LOBYTE(g_cdr_primary_response) = 34;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] |= 0x40u;
        g_cdr_status_regs[67] = 32;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[62] = 0;
        g_cdr_status_regs[63] = 3;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        g_cdr_status_regs[60] = 1;
        g_cdr_retry_count = 0;
        if ( (g_cdr_status_regs[72] & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
        goto LABEL_27;
      case 7u:
        cdrom_stop_cb();
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[62] = 0;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] &= 0x3Fu;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 2;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        return;
      case 8u:
        cdrom_stop_cb();
        g_cdr_status_regs[68] = 0;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[66] = 0;
        g_cdr_status_regs[62] = 2;
        g_cdr_response_fifo[0] = 0;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        goto LABEL_10;
      case 9u:
        cdrom_stop_cb();
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] &= 0x3Fu;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[62] = 0;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        g_cdr_secondary_response_size = 2;
        LOBYTE(g_cdr_secondary_response) = 2;
        g_cdr_secondary_response_index = 1;
        if ( adjust_timing )
          *(_DWORD *)&byte_455945 = 5;
        word_455FA6 = 550;
        return;
      case 0xAu:
        cdrom_stop_cb();
        g_cdr_status_regs[65] &= 0x3Fu;
        g_cdr_status_regs[72] = 0;
        g_cdr_data_bytes_transferred = 0;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        goto LABEL_34;
      case 0xBu:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[67] | 2;
        goto LABEL_8;
      case 0xCu:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        goto LABEL_8;
      case 0xDu:
        g_cdr_status_regs[62] = 0;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        g_cdr_cur_track = g_cdr_param_fifo;
        g_cdr_response_fifo[0] = 2;
        return;
      case 0xEu:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] |= 0x40u;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | 2;
        g_cdr_status_regs[72] = g_cdr_param_fifo;
        g_cdr_status_regs[62] = 3;
        g_cdr_response_fifo[0] = g_cdr_status_regs[67] | 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        goto LABEL_10;
      case 0xFu:
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[62] = 2;
        g_cdr_response_fifo[0] = 2;
        g_cdr_status_regs[68] = 1;
        g_cdr_response_fifo[1] = g_cdr_status_regs[72];
        *(_WORD *)&g_cdr_response_fifo[2] = g_cdr_cur_track;
        LOWORD(g_cdr_response_extra) = 0;
        g_cdr_response_size = 6;
        g_cdr_response_index = 0;
        goto LABEL_10;
      case 0x10u:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | 2;
        if ( g_cdr_read_ahead_sectors != g_cdr_delay_counter && g_cdr_status_regs[67] )
          cdr_read_data_sector();
        if ( g_cdr_status_regs[62] )
        {
          if ( g_cdr_status_regs[63] )
          {
            g_cdr_secondary_response = g_cdr_pending_response;
            dword_50BF70 = *(_DWORD *)g_cdr_xa_buffer;
            g_cdr_secondary_response_size = 3;
            g_cdr_secondary_response_index = 8;
            if ( byte_4FD881 )
              LOBYTE(g_cdr_secondary_response) = rand();
          }
          else
          {
            g_cdr_primary_response = g_cdr_pending_response;
            g_cdr_status_regs[1] = g_cdr_xa_buffer[1];
            g_cdr_status_regs[0] = g_cdr_xa_buffer[0];
            g_cdr_status_regs[63] = 3;
            g_cdr_status_regs[2] = g_cdr_xa_buffer[2];
            g_cdr_status_regs[3] = g_cdr_xa_buffer[3];
            g_cdr_status_regs[60] = 8;
            if ( byte_4FD881 )
              LOBYTE(g_cdr_primary_response) = rand();
          }
        }
        else
        {
          g_cdr_response_extra = *(_DWORD *)g_cdr_xa_buffer;
          *(_DWORD *)g_cdr_response_fifo = g_cdr_pending_response;
          g_cdr_status_regs[62] = 3;
          g_cdr_response_size = 8;
          g_cdr_response_index = 0;
          if ( !byte_4FD881 )
            goto LABEL_10;
          g_cdr_response_fifo[0] = rand();
        }
        goto LABEL_9;
      case 0x11u:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | g_cdr_status_regs[70] | 2;
        if ( g_cdr_read_ahead_sectors != g_cdr_delay_counter && g_cdr_status_regs[67] )
        {
          cdr_read_data_sector();
          v1 = loaded_file_type;
        }
        if ( !g_cdr_status_regs[62] )
        {
          if ( v1 == 3 )
          {
            iso_verify_sub(
              g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              SBYTE2(g_cdr_cur_msf_pos),
              (int)g_cdr_response_fifo);
          }
          else
          {
            cdrom_verify_sub_cb(
              (unsigned __int8)g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              BYTE2(g_cdr_cur_msf_pos),
              g_cdr_response_fifo);
            g_cdr_response_fifo[1] = g_cdr_status_regs[70] != 0;
          }
          g_cdr_response_size = 8;
          g_cdr_response_index = 0;
          g_cdr_status_regs[62] = 3;
          goto LABEL_10;
        }
        v8 = 0;
        if ( g_cdr_status_regs[63] )
        {
          LOBYTE(v8) = BYTE2(g_cdr_cur_msf_pos);
          if ( v1 == 3 )
          {
            iso_verify_sub(
              g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              SBYTE2(g_cdr_cur_msf_pos),
              (int)&g_cdr_secondary_response);
          }
          else
          {
            cdrom_verify_sub_cb(
              (unsigned __int8)g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              v8,
              &g_cdr_secondary_response);
            BYTE1(g_cdr_secondary_response) = g_cdr_status_regs[70] != 0;
          }
          g_cdr_secondary_response_index = 8;
          g_cdr_secondary_response_size = 3;
        }
        else
        {
          LOBYTE(v8) = BYTE1(g_cdr_cur_msf_pos);
          if ( v1 == 3 )
          {
            iso_verify_sub(
              g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              SBYTE2(g_cdr_cur_msf_pos),
              (int)&g_cdr_primary_response);
          }
          else
          {
            cdrom_verify_sub_cb(
              (unsigned __int8)g_cdr_cur_msf_pos,
              v8,
              BYTE2(g_cdr_cur_msf_pos),
              &g_cdr_primary_response);
            BYTE1(g_cdr_primary_response) = g_cdr_status_regs[70] != 0;
          }
          g_cdr_status_regs[60] = 8;
          g_cdr_status_regs[63] = 3;
        }
        goto LABEL_9;
      case 0x13u:
        cdrom_get_first_last_TN_cb(&a1, &v12);
        if ( loaded_file_type == 3 )
        {
          a1 = 1;
          LOBYTE(v12) = 1;
        }
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[67] | 2;
        BYTE1(g_cdr_primary_response) = cdr_bcd_to_hex(a1);
        BYTE2(g_cdr_primary_response) = cdr_bcd_to_hex(v12);
        g_cdr_status_regs[60] = 3;
        goto LABEL_9;
      case 0x14u:
        v9 = cdr_hex_to_bcd(g_cdr_param_fifo);
        cdrom_track_to_msf(v9, &a1, &v12, &v13);
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[67] | 2;
        BYTE1(g_cdr_primary_response) = cdr_bcd_to_hex(a1);
        BYTE2(g_cdr_primary_response) = cdr_bcd_to_hex(v12);
        HIBYTE(g_cdr_primary_response) = cdr_bcd_to_hex(v13);
        g_cdr_status_regs[60] = 4;
        goto LABEL_9;
      case 0x15u:
      case 0x16u:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[62] = 3;
        g_cdr_secondary_response_size = 2;
        g_cdr_response_fifo[0] = 66;
        LOBYTE(g_cdr_secondary_response) = 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        g_cdr_secondary_response_index = 1;
        goto LABEL_10;
      case 0x18u:
        goto LABEL_9;
      case 0x19u:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[66];
        g_cdr_status_regs[60] = 1;
        if ( (unsigned __int8)g_cdr_param_fifo < 4u )
          goto LABEL_78;
        if ( (unsigned __int8)g_cdr_param_fifo <= 5u )
        {
          g_cdr_secondary_response_index = 1;
          LOBYTE(g_cdr_secondary_response) = 0;
        }
        else
        {
          if ( (_BYTE)g_cdr_param_fifo == 32 )
            g_cdr_secondary_response = *(_DWORD *)"for SCEA";
          else
LABEL_78:
            g_cdr_secondary_response = *(_DWORD *)"for SCEA";
          g_cdr_secondary_response_index = 4;
        }
        g_cdr_status_regs[66] = 2;
        g_cdr_secondary_response_size = 2;
        goto LABEL_9;
      case 0x1Au:
        dword_50BF70 = *(_DWORD *)"SCEA";
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        g_cdr_secondary_response_size = 2;
        g_cdr_secondary_response = 0;
        if ( (_BYTE)g_cdr_registers )
        {
          if ( (unsigned __int8)g_cdr_registers == 2 )
          {
            LOWORD(g_cdr_secondary_response) = -4088;
            g_cdr_secondary_response_index = 8;
            goto LABEL_9;
          }
        }
        else
        {
          BYTE1(g_cdr_secondary_response) = 0x80;
        }
        g_cdr_secondary_response_index = 8;
LABEL_9:
        if ( g_cdr_status_regs[62] )
        {
LABEL_10:
          g_cdr_irq_pending = 1;
          if ( g_cdr_irq_mode != 24 )
            irq_cdrom_assert_int();
        }
        break;
      case 0x1Bu:
        g_cdr_status_regs[66] = 34;
        LOBYTE(g_cdr_primary_response) = 34;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] |= 0x40u;
        g_cdr_data_bytes_transferred = 255;
        g_cdr_status_regs[67] = 32;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[62] = 0;
        g_cdr_status_regs[63] = 3;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        g_cdr_status_regs[60] = 1;
        if ( adjust_timing )
          *(_DWORD *)&byte_455945 = 0;
        g_cdr_retry_count = 0;
        if ( (g_cdr_status_regs[72] & 0x40) != 0 )
          spu_set_adpcm_flag_cb();
LABEL_27:
        cdr_init_report_mode();
        goto LABEL_9;
      case 0x1Cu:
        cdrom_stop_cb();
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[62] = 2;
        g_cdr_response_fifo[0] = 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        goto LABEL_10;
      case 0x1Eu:
LABEL_34:
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        g_cdr_secondary_response_size = 2;
        LOBYTE(g_cdr_secondary_response) = 2;
        g_cdr_secondary_response_index = 1;
        goto LABEL_9;
      default:
        if ( a1 > 0x1Du )
          return;
LABEL_93:
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[62] = 2;
        g_cdr_response_fifo[0] = 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        goto LABEL_10;
    }
  }
}

char __cdecl cdr_reg2_write(char a1)
{
  char result; // al

  result = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    result = g_cdr_status_regs[64];
    if ( g_cdr_status_regs[64] == 2 )
    {
      if ( a1 == 7 && g_cdr_status_regs[61] )
      {
        g_cdr_irq_pending = 1;
        g_cdr_status_regs[61] = 0;
        g_cdr_status_regs[64] = 0;
        return result;
      }
      goto LABEL_7;
    }
    if ( g_cdr_status_regs[64] )
    {
LABEL_7:
      g_cdr_irq_mode = a1;
      g_cdr_status_regs[64] = 0;
      return result;
    }
    result = g_cdr_status_regs[61];
    *((_BYTE *)&g_cdr_param_fifo + (unsigned __int8)g_cdr_status_regs[61]++) = a1;
    g_cdr_status_regs[64] = 0;
  }
  return result;
}

void __cdecl cdr_reg3_write(char a1)
{
  if ( g_cdr_param_fifo_count )
  {
    if ( a1 == 32 )
      g_cdr_param_fifo_count = 0;
  }
  else
  {
    g_cdr_status_regs[65] |= 0x40u;
    if ( g_cdr_status_regs[64] != 1 || (g_cdr_status_regs[64] = 2, a1 != 7) )
      g_cdr_status_regs[64] = 0;
    if ( g_cdr_irq_pending && a1 == 7 )
    {
      if ( g_cdr_status_regs[62] == 1 && g_cdr_retry_count )
        --g_cdr_retry_count;
      g_cdr_status_regs[62] = 0;
      if ( (unsigned __int8)g_cdr_response_index >= (unsigned __int8)g_cdr_response_size && g_cdr_status_regs[63] )
      {
        if ( g_cdr_status_regs[60] )
        {
          qmemcpy(g_cdr_response_fifo, &g_cdr_primary_response, (unsigned __int8)g_cdr_status_regs[60]);
          g_cdr_response_size = g_cdr_status_regs[60];
          g_cdr_response_index = 0;
          g_cdr_status_regs[60] = 0;
          g_cdr_irq_pending = 1;
        }
        g_cdr_status_regs[62] = g_cdr_status_regs[63];
        g_cdr_status_regs[63] = 0;
        if ( g_cdr_irq_mode != 24 )
          irq_cdrom_assert_int();
        if ( g_cdr_secondary_response_size )
        {
          if ( g_cdr_secondary_response_index )
          {
            qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (unsigned __int8)g_cdr_secondary_response_index);
            g_cdr_status_regs[60] = g_cdr_secondary_response_index;
            g_cdr_irq_pending = 1;
            g_cdr_secondary_response_index = 0;
          }
          g_cdr_status_regs[63] = g_cdr_secondary_response_size;
          g_cdr_secondary_response_size = 0;
        }
      }
    }
  }
}

int __cdecl cdr_msf_to_lba(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
  int v3; // ecx
  int v4; // eax

  v3 = a2 - 2;
  v4 = a1;
  if ( v3 < 0 )
  {
    v3 += 60;
    v4 = a1 - 1;
  }
  return a3 + 75 * (v3 + 60 * v4);
}

char cdr_read_data_sector()
{
  __int16 v0; // bx
  int v1; // eax

  v0 = g_cdr_cur_msf_pos;
  v1 = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  if ( g_cdr_last_lba_read != v1 )
  {
    cdrom_read_data_cb((unsigned __int8)v0, HIBYTE(v0), BYTE2(g_cdr_cur_msf_pos), g_cdr_data_buffer);
    g_cdr_last_lba_read = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
    LOBYTE(v1) = g_cdr_status_regs[72];
    g_cdr_data_bytes_transferred = (g_cdr_status_regs[72] & 0x20) != 0 ? 12 : 24;
    if ( (g_cdr_xa_buffer[2] & 0xF) == 4 )
    {
      LOBYTE(v1) = g_cdr_status_regs[72] & 0x48;
      if ( (g_cdr_status_regs[72] & 0x48) == 0x40
        || (_BYTE)v1 == 72
        && g_cdr_xa_buffer[0] == (_BYTE)g_cdr_cur_track
        && (LOBYTE(v1) = g_cdr_xa_buffer[1], g_cdr_xa_buffer[1] == HIBYTE(g_cdr_cur_track)) )
      {
        LOBYTE(v1) = spu_play_adpcm_cb(g_cdr_xa_buffer);
      }
    }
  }
  return v1;
}

char cdr_increment_msf()
{
  char result; // al
  bool v1; // zf

  result = ++BYTE2(g_cdr_cur_msf_pos);
  if ( BYTE2(g_cdr_cur_msf_pos) == 75 )
  {
    result = BYTE1(g_cdr_cur_msf_pos) + 1;
    v1 = BYTE1(g_cdr_cur_msf_pos)++ == 59;
    *(_WORD *)((char *)&g_cdr_cur_msf_pos + 1) = BYTE1(g_cdr_cur_msf_pos);
    if ( v1 )
    {
      result = g_cdr_cur_msf_pos + 1;
      LOBYTE(g_cdr_cur_msf_pos) = g_cdr_cur_msf_pos + 1;
      LOWORD(g_cdr_cur_msf_pos) = (unsigned __int8)g_cdr_cur_msf_pos;
    }
  }
  return result;
}

char __cdecl cdr_set_nocd(char a1)
{
  LOBYTE(g_cdr_registers) = a1;
  return a1;
}

char cdr_reset_controller()
{
  g_cdr_response_size = 0;
  g_cdr_status_regs[60] = 0;
  g_cdr_response_index = 0;
  g_cdr_irq_pending = 0;
  g_cdr_status_regs[61] = 0;
  g_cdr_status_regs[62] = 0;
  g_cdr_status_regs[64] = 0;
  g_cdr_status_regs[72] = 0;
  g_cdr_last_lba_read = 0;
  g_cdr_data_bytes_transferred = 0;
  HIBYTE(g_cdr_registers) = 0;
  g_cdr_status_regs[70] = 0;
  g_cdr_dma_active = 0;
  g_cdr_status_regs[68] = 0;
  g_cdr_status_regs[69] = 0;
  g_cdr_param_fifo_count = 0;
  g_cdr_retry_count = 0;
  g_cdr_status_regs[65] = 17;
  g_cdr_status_regs[66] = 2;
  HIBYTE(g_cdr_cur_msf_pos) = 1;
  return cdr_set_nocd(nocd);
}

int cdr_get_response_status()
{
  if ( g_cdr_irq_mode == 24 )
    return 0;
  else
    return (unsigned __int8)g_cdr_status_regs[62];
}

void cdr_queue_response()
{
  if ( g_cdr_status_regs[63] )
  {
    if ( g_cdr_status_regs[60] )
    {
      qmemcpy(g_cdr_response_fifo, &g_cdr_primary_response, (unsigned __int8)g_cdr_status_regs[60]);
      g_cdr_response_size = g_cdr_status_regs[60];
      g_cdr_response_index = 0;
      g_cdr_status_regs[60] = 0;
      g_cdr_irq_pending = 1;
    }
    g_cdr_status_regs[62] = g_cdr_status_regs[63];
    g_cdr_status_regs[63] = 0;
    if ( g_cdr_irq_mode != 24 )
      irq_cdrom_assert_int();
  }
  if ( g_cdr_secondary_response_size )
  {
    if ( g_cdr_secondary_response_index )
    {
      qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (unsigned __int8)g_cdr_secondary_response_index);
      g_cdr_status_regs[60] = g_cdr_secondary_response_index;
      g_cdr_secondary_response_index = 0;
    }
    g_cdr_status_regs[63] = g_cdr_secondary_response_size;
    g_cdr_secondary_response_size = 0;
  }
}

char cdr_process_delays()
{
  char result; // al

  result = g_cdr_status_regs[62];
  if ( !g_cdr_status_regs[62] && (g_cdr_status_regs[63] || (result = g_cdr_secondary_response_size) != 0) )
  {
    result = ++word_4FD87C;
    if ( (unsigned __int16)word_4FD87C >= (unsigned __int16)word_455FA6 )
    {
      cdr_queue_response();
      result = 10;
      word_4FD87C = 0;
      if ( (unsigned __int16)word_455FA6 > 0xAu )
        word_455FA6 = 10;
    }
  }
  return result;
}

__int16 cdr_init_report_mode()
{
  __int16 result; // ax

  g_cdr_irq_enabled = 1;
  word_50BF82 = 0;
  g_cdr_spindown_counter = 0;
  g_cdr_dma_active = 0;
  if ( country_setting == 1 )
    LOBYTE(result) = g_cdr_status_regs[72] < 0 ? 104 : -48;
  else
    LOBYTE(result) = g_cdr_status_regs[72] < 0 ? 104 : -47;
  g_cdr_region_code = result;
  result = (unsigned __int8)result;
  g_cdr_read_ahead_sectors = result;
  g_cdr_delay_counter = (unsigned __int8)result;
  if ( !g_cdr_status_regs[70] )
  {
    result = 3 * (unsigned __int8)result;
    g_cdr_delay_counter = result;
  }
  return result;
}

void cdr_play_tick()
{
  char v0; // cl

  if ( g_cdr_status_regs[70] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)g_cdr_delay_counter )
    {
      v0 = g_cdr_status_regs[72];
      if ( (g_cdr_status_regs[72] & 4) == 4 )
      {
        if ( g_cdr_status_regs[62] )
        {
          if ( g_cdr_status_regs[62] != 1 )
          {
            if ( (g_cdr_status_regs[72] & 2) != 0 )
              g_cdr_status_regs[63] = 1;
            LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[70] | 0x22;
            g_cdr_status_regs[60] = 1;
          }
        }
        else
        {
          g_cdr_status_regs[62] = 1;
          g_cdr_response_fifo[0] = g_cdr_status_regs[70] | 0x22;
          if ( (g_cdr_status_regs[72] & 2) != 0 )
          {
            g_cdr_response_size = 1;
          }
          else
          {
            g_cdr_response_fifo[1] = 1;
            g_cdr_response_fifo[2] = 0x80;
            if ( report_mode_enabled )
              g_cdr_response_fifo[3] = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
            else
              g_cdr_response_fifo[3] = 0;
            LOBYTE(g_cdr_response_extra) = cdr_bcd_to_hex(BYTE1(g_cdr_cur_msf_pos));
            BYTE1(g_cdr_response_extra) = cdr_bcd_to_hex(BYTE2(g_cdr_cur_msf_pos));
            g_cdr_response_size = 6;
          }
          g_cdr_response_index = 0;
          g_cdr_irq_pending = 1;
          irq_cdrom_assert_int();
          v0 = g_cdr_status_regs[72];
        }
      }
      if ( (v0 & 2) == 2
        && g_cdr_seek_target_msf == (_BYTE)g_cdr_cur_msf_pos
        && word_50BF7B == *(_WORD *)((char *)&g_cdr_cur_msf_pos + 1)
        && loaded_file_type != 3 )
      {
        g_cdr_status_regs[62] = 4;
        g_cdr_response_fifo[0] = 2;
        g_cdr_response_size = 1;
        g_cdr_response_index = 0;
        g_cdr_irq_pending = 1;
        cdrom_stop_cb();
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[65] &= 0x3Fu;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
      }
      word_50BF82 = 0;
      cdr_increment_msf();
    }
  }
  else if ( g_cdr_status_regs[67] )
  {
    if ( (unsigned __int16)++word_50BF82 >= (unsigned __int16)g_cdr_delay_counter )
    {
      word_50BF82 = 0;
      if ( !g_cdr_retry_count )
      {
        cdr_read_data_sector();
        g_cdr_data_bytes_transferred = (g_cdr_status_regs[72] & 0x20) != 0 ? 12 : 24;
        cdr_increment_msf();
        g_cdr_delay_counter = g_cdr_read_ahead_sectors;
        if ( (g_cdr_xa_buffer[2] & 0xF) != 4 || (g_cdr_status_regs[72] & 0x40) != 0x40 )
        {
          if ( g_cdr_status_regs[62] )
          {
            if ( g_cdr_status_regs[62] == 1 )
              return;
            if ( !g_cdr_status_regs[63] )
            {
              g_cdr_status_regs[63] = 1;
              LOBYTE(g_cdr_primary_response) = 34;
              g_cdr_status_regs[60] = 1;
              ++g_cdr_retry_count;
              return;
            }
          }
          else if ( !g_cdr_status_regs[63] )
          {
            g_cdr_status_regs[62] = 1;
            g_cdr_response_fifo[0] = 34;
            g_cdr_response_size = 1;
            g_cdr_response_index = 0;
            g_cdr_irq_pending = 1;
            irq_cdrom_assert_int();
            ++g_cdr_retry_count;
            return;
          }
          g_cdr_secondary_response_size = 1;
          g_cdr_secondary_response_index = 1;
          LOBYTE(g_cdr_secondary_response) = 34;
          ++g_cdr_retry_count;
        }
      }
    }
  }
}

unsigned int cdr_dma()
{
  int v0; // ecx
  unsigned int result; // eax
  unsigned int v2; // edi
  unsigned int v3; // ebp
  int v4; // esi

  v0 = HIWORD(dword_516508);
  result = (unsigned __int16)dword_516508;
  v2 = dword_516504;
  if ( (dword_51650C & 0x11000000) == 0x11000000 )
  {
    if ( !HIWORD(dword_516508) )
      v0 = 1;
    if ( !(_WORD)dword_516508 )
      result = 512;
    v3 = 4 * v0 * result;
    v4 = g_cdr_data_bytes_transferred;
    result = v3 + g_cdr_data_bytes_transferred;
    g_cdr_data_bytes_transferred += v3;
    if ( dynarec_enabled == 1 )
      result = dynarec_invalidate_range(dword_516504, v3 >> 2);
    if ( v3 + (v2 & 0x1FFFFF) <= 0x200000 )
    {
      result = mem_dma_read(v2);
      qmemcpy((void *)result, &g_cdr_data_buffer[v4], v3);
    }
    g_cdr_dma_active = 1;
  }
  return result;
}

void cdr_spinup_motor()
{
  g_cdr_status_regs[68] = 0;
  g_cdr_status_regs[69] = 2;
  g_cdr_last_lba_read = 0;
  if ( g_cdr_status_regs[62] )
  {
    g_cdr_status_regs[63] = 2;
    LOBYTE(g_cdr_primary_response) = 16;
    g_cdr_status_regs[60] = 1;
  }
  else
  {
    g_cdr_status_regs[62] = 2;
    g_cdr_response_fifo[0] = 16;
    g_cdr_response_size = 1;
    g_cdr_response_index = 0;
    g_cdr_irq_pending = 1;
    irq_cdrom_assert_int();
  }
}

char cdr_update_motor_status()
{
  char result; // al

  result = g_cdr_status_regs[69];
  if ( g_cdr_status_regs[69] == 1 )
  {
    g_cdr_status_regs[68] = 1;
    g_cdr_status_regs[69] = 0;
    return 0;
  }
  else if ( g_cdr_status_regs[69] )
  {
    return --g_cdr_status_regs[69];
  }
  return result;
}

int __cdecl cdr_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 4396;
  g_cdr_idle_counter = word_4FD87C;
  g_cdr_spindown_counter = word_50BF82;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)g_cdr_response_fifo, 0x112Cu);
}

int __cdecl cdr_unfreeze_new(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, g_cdr_response_fifo, 4396);
  word_4FD87C = (unsigned __int8)g_cdr_idle_counter;
  if ( g_cdr_status_regs[70] )
    return cdrom_play_cdda_cb((unsigned __int8)g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  else
    return cdrom_stop_cb();
}

int __cdecl cdr_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  gzread(a2, g_cdr_response_fifo, 4396);
  g_cdr_read_ahead_sectors = (unsigned __int8)g_cdr_region_code;
  g_cdr_delay_counter = (unsigned __int8)g_cdr_region_code;
  word_4FD87C = (unsigned __int8)g_cdr_idle_counter;
  word_50BF82 = (unsigned __int8)g_cdr_spindown_counter;
  if ( g_cdr_status_regs[70] )
    return cdrom_play_cdda_cb((unsigned __int8)g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  else
    return cdrom_stop_cb();
}

int __cdecl cdr_get_status(int a1)
{
  int result; // eax

  result = a1;
  g_cdr_status_regs[62] = a1;
  g_cdr_response_index = 0;
  g_cdr_response_size = 1;
  if ( a1 == 1 )
    g_cdr_response_fifo[0] = 2;
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
int adjust_timing;
unsigned char byte_4FD881;
unsigned char byte_50BF7C;
unsigned int dword_50BF70;
unsigned int dword_516504;
unsigned int dword_516508;
unsigned int g_cdr_cur_msf_pos;
unsigned short g_cdr_cur_track;
unsigned char g_cdr_data_buffer[0xc];
unsigned int g_cdr_data_bytes_transferred;
unsigned short g_cdr_delay_counter;
unsigned char g_cdr_dma_active;
unsigned char g_cdr_idle_counter;
unsigned char g_cdr_irq_enabled;
unsigned char g_cdr_irq_mode;
unsigned char g_cdr_irq_pending;
unsigned int g_cdr_last_lba_read;
unsigned short g_cdr_param_fifo;
unsigned char g_cdr_param_fifo_byte[0x3e];
unsigned char g_cdr_param_fifo_count;
unsigned int g_cdr_pending_response;
unsigned int g_cdr_primary_response;
unsigned short g_cdr_read_ahead_sectors;
unsigned char g_cdr_region_code;
unsigned int g_cdr_registers;
unsigned int g_cdr_response_extra;
unsigned int g_cdr_response_fifo[1];
unsigned char g_cdr_response_index;
unsigned char g_cdr_response_size;
unsigned char g_cdr_retry_count;
unsigned int g_cdr_secondary_response;
unsigned char g_cdr_secondary_response_index;
unsigned char g_cdr_secondary_response_size;
unsigned short g_cdr_seek_target_msf;
unsigned char g_cdr_spindown_counter;
unsigned char g_cdr_status_regs[0x49];
unsigned char g_cdr_xa_buffer[0xff2];
unsigned char report_mode_enabled = 0x1;
unsigned short word_455FA6 = 0xa;
unsigned short word_4FD87C;
unsigned short word_50BF7B;
unsigned short word_50BF82;
