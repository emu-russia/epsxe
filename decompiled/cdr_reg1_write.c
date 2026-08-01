#include "pch.h"
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
          cdrom_lba_to_msf_cb(v4, v10, 0, &g_cdr_seek_target_msf, (char *)&g_cdr_seek_target_msf + 1, &MEMORY[0x50BF7C]);
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
            cdrom_lba_to_msf_cb(
              v7,
              v11,
              0,
              &g_cdr_seek_target_msf,
              (char *)&g_cdr_seek_target_msf + 1,
              &MEMORY[0x50BF7C]);
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
            sub_42FCB0(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), SBYTE2(g_cdr_cur_msf_pos), (int)g_cdr_response_fifo);
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
            sub_42FCB0(
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
            sub_42FCB0(
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
