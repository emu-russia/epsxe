#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
int adjust_timing;
unsigned char cdr_randomize_response_flag;
static unsigned char g_cdr_seek_target_frame;
static unsigned int g_cdr_last_sector_header;
static unsigned int g_cdr_dma_address;
static unsigned int g_cdr_dma_block_control;
static unsigned int g_cdr_cur_msf_pos;
static unsigned short g_cdr_cur_track;
static unsigned char g_cdr_data_buffer[0xc];
unsigned int g_cdr_data_bytes_transferred;
static unsigned short g_cdr_delay_counter;
static unsigned char g_cdr_dma_active;
static unsigned char g_cdr_idle_counter;
static unsigned char g_cdr_irq_enabled;
static unsigned char g_cdr_irq_mode;
unsigned char g_cdr_irq_pending;
static unsigned int g_cdr_last_lba_read;
static unsigned short g_cdr_param_fifo;
static unsigned char g_cdr_param_fifo_byte[0x3e];
static unsigned char g_cdr_param_fifo_count;
static unsigned int g_cdr_pending_response;
static unsigned int g_cdr_primary_response;
static unsigned short g_cdr_read_ahead_sectors;
static unsigned char g_cdr_region_code;
static unsigned int g_cdr_registers;
static unsigned int g_cdr_response_extra;
static unsigned int g_cdr_response_fifo[1];
unsigned char g_cdr_response_index;
unsigned char g_cdr_response_size;
static unsigned char g_cdr_retry_count;
static unsigned int g_cdr_secondary_response;
static unsigned char g_cdr_secondary_response_index;
static unsigned char g_cdr_secondary_response_size;
static unsigned short g_cdr_seek_target_msf;
static unsigned char g_cdr_spindown_counter;
static unsigned char g_cdr_status_regs[0x49];
static unsigned char g_cdr_xa_buffer[0xff2];
unsigned char report_mode_enabled = 0x1;
static unsigned short g_cdr_response_delay = 0xa;
static unsigned short g_cdr_response_delay_counter;
static unsigned short g_cdr_seek_target_sf;
static unsigned short g_cdr_tick_counter;


/* static prototypes for internal functions */
static char cdr_read_data_sector();
static int16_t cdr_init_report_mode();

static int cdr_bcd_to_hex(uint8_t bcd)
{
  return bcd % 10 + 16 * (bcd / 10);
}

static int cdr_hex_to_bcd(uint8_t hex)
{
  return (hex & 0xF) + 10 * (hex >> 4);
}

char cdr_reg0_write(char command)
{
  char status;

  status = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    status = command - 1;
    if ( command == 1 )
    {
      g_cdr_irq_pending = 1;
    }
    else
    {
      status = command - 2;
      if ( command == 2 )
      {
        g_cdr_param_fifo_count = 1;
        g_cdr_status_regs[64] = command & 1;
        return status;
      }
    }
    g_cdr_status_regs[64] = command & 1;
  }
  return status;
}

void cdr_reg1_write(uint8_t command)
{
  int file_type;
  char status;
  char uninit;
  uint8_t min;
  uint8_t sec_bcd;
  uint8_t sec_adj;
  uint8_t min_hex;
  int frame;
  uint8_t track_bcd;
  int sec;
  int sec_hex;
  int out2;
  int out3;

  file_type = loaded_file_type;
  if ( loaded_file_type != 4 && !g_cdr_param_fifo_count )
  {
    BYTE1(g_cdr_registers) = command;
    g_cdr_status_regs[61] = 0;
    switch ( command )
    {
      case 0u:
        goto LABEL_93;
      case 1u:
        status = g_cdr_status_regs[68] == 0 ? 0 : 2;
        g_cdr_status_regs[66] = status;
        if ( g_cdr_status_regs[69] )
        {
          status |= 0x10u;
          g_cdr_status_regs[66] = status;
        }
        if ( g_cdr_status_regs[63] )
        {
          g_cdr_secondary_response_size = 3;
          LOBYTE(g_cdr_secondary_response) = status | g_cdr_status_regs[67] | g_cdr_status_regs[70];
          g_cdr_secondary_response_index = 1;
        }
        else
        {
          g_cdr_status_regs[63] = 3;
          LOBYTE(g_cdr_primary_response) = status | g_cdr_status_regs[67] | g_cdr_status_regs[70];
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
        if ( !(uint16_t)g_cdr_cur_msf_pos )
          BYTE1(g_cdr_cur_msf_pos) = uninit;
        sub_q_cur0 = 0;
        sub_q_cur1 = 0;
        sub_q_cur2 = 0;
        g_cdr_status_regs[62] = 0;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = uninit;
        g_cdr_status_regs[60] = 1;
        g_cdr_response_size = 0;
        g_cdr_response_index = 0;
        sub_q_cur3 = 0;
        g_cdr_response_delay = 200;
        return;
      case 3u:
        if ( !g_cdr_status_regs[70] )
        {
          sec = (uint8_t)cdr_bcd_to_hex(BYTE1(g_cdr_cur_msf_pos));
          min = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
          cdrom_lba_to_msf_cb(min, sec, 0, &g_cdr_seek_target_msf, (char *)&g_cdr_seek_target_msf + 1, &g_cdr_seek_target_frame);
          sec_bcd = BYTE1(g_cdr_cur_msf_pos);
          if ( g_cdr_seek_target_msf == (uint16_t)g_cdr_cur_msf_pos )
          {
            sec_adj = BYTE1(g_cdr_cur_msf_pos) + 2;
            BYTE1(g_cdr_cur_msf_pos) = sec_adj;
            if ( sec_adj >= 0x3Cu )
            {
              sec_adj -= 60;
              BYTE1(g_cdr_cur_msf_pos) = sec_adj;
              LOBYTE(g_cdr_cur_msf_pos) = g_cdr_cur_msf_pos + 1;
            }
            sec_hex = (uint8_t)cdr_bcd_to_hex(sec_adj);
            min_hex = cdr_bcd_to_hex(g_cdr_cur_msf_pos);
            cdrom_lba_to_msf_cb(min_hex, sec_hex, 0, &g_cdr_seek_target_msf, (char *)&g_cdr_seek_target_msf + 1, &g_cdr_seek_target_frame);
            sec_bcd = BYTE1(g_cdr_cur_msf_pos);
          }
          cdrom_play_cdda_cb((uint8_t)g_cdr_cur_msf_pos, sec_bcd, BYTE2(g_cdr_cur_msf_pos));
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
          *(uint32_t *)&cd_speed = 5;
        g_cdr_response_delay = 550;
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
        *(uint16_t *)&g_cdr_response_fifo[2] = g_cdr_cur_track;
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
            g_cdr_last_sector_header = *(uint32_t *)g_cdr_xa_buffer;
            g_cdr_secondary_response_size = 3;
            g_cdr_secondary_response_index = 8;
            if ( cdr_randomize_response_flag )
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
            if ( cdr_randomize_response_flag )
              LOBYTE(g_cdr_primary_response) = rand();
          }
        }
        else
        {
          g_cdr_response_extra = *(uint32_t *)g_cdr_xa_buffer;
          *(uint32_t *)g_cdr_response_fifo = g_cdr_pending_response;
          g_cdr_status_regs[62] = 3;
          g_cdr_response_size = 8;
          g_cdr_response_index = 0;
          if ( !cdr_randomize_response_flag )
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
          file_type = loaded_file_type;
        }
        if ( !g_cdr_status_regs[62] )
        {
          if ( file_type == 3 )
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
              (uint8_t)g_cdr_cur_msf_pos,
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
        frame = 0;
        if ( g_cdr_status_regs[63] )
        {
          LOBYTE(frame) = BYTE2(g_cdr_cur_msf_pos);
          if ( file_type == 3 )
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
              (uint8_t)g_cdr_cur_msf_pos,
              BYTE1(g_cdr_cur_msf_pos),
              frame,
              &g_cdr_secondary_response);
            BYTE1(g_cdr_secondary_response) = g_cdr_status_regs[70] != 0;
          }
          g_cdr_secondary_response_index = 8;
          g_cdr_secondary_response_size = 3;
        }
        else
        {
          LOBYTE(frame) = BYTE1(g_cdr_cur_msf_pos);
          if ( file_type == 3 )
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
              (uint8_t)g_cdr_cur_msf_pos,
              frame,
              BYTE2(g_cdr_cur_msf_pos),
              &g_cdr_primary_response);
            BYTE1(g_cdr_primary_response) = g_cdr_status_regs[70] != 0;
          }
          g_cdr_status_regs[60] = 8;
          g_cdr_status_regs[63] = 3;
        }
        goto LABEL_9;
      case 0x13u:
        cdrom_get_first_last_TN_cb(&command, &out2);
        if ( loaded_file_type == 3 )
        {
          command = 1;
          LOBYTE(out2) = 1;
        }
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[67] | 2;
        BYTE1(g_cdr_primary_response) = cdr_bcd_to_hex(command);
        BYTE2(g_cdr_primary_response) = cdr_bcd_to_hex(out2);
        g_cdr_status_regs[60] = 3;
        goto LABEL_9;
      case 0x14u:
        track_bcd = cdr_hex_to_bcd(g_cdr_param_fifo);
        cdrom_track_to_msf(track_bcd, &command, &out2, &out3);
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[66] = g_cdr_status_regs[67] | 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = g_cdr_status_regs[67] | 2;
        BYTE1(g_cdr_primary_response) = cdr_bcd_to_hex(command);
        BYTE2(g_cdr_primary_response) = cdr_bcd_to_hex(out2);
        HIBYTE(g_cdr_primary_response) = cdr_bcd_to_hex(out3);
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
        if ( (uint8_t)g_cdr_param_fifo < 4u )
          goto LABEL_78;
        if ( (uint8_t)g_cdr_param_fifo <= 5u )
        {
          g_cdr_secondary_response_index = 1;
          LOBYTE(g_cdr_secondary_response) = 0;
        }
        else
        {
          if ( (uint8_t)g_cdr_param_fifo == 32 )
            g_cdr_secondary_response = *(uint32_t *)"for SCEA";
          else
LABEL_78:
            g_cdr_secondary_response = *(uint32_t *)"for SCEA";
          g_cdr_secondary_response_index = 4;
        }
        g_cdr_status_regs[66] = 2;
        g_cdr_secondary_response_size = 2;
        goto LABEL_9;
      case 0x1Au:
        g_cdr_last_sector_header = *(uint32_t *)"SCEA";
        g_cdr_status_regs[68] = 1;
        g_cdr_status_regs[67] = 0;
        g_cdr_status_regs[70] = 0;
        g_cdr_status_regs[66] = 2;
        g_cdr_status_regs[63] = 3;
        LOBYTE(g_cdr_primary_response) = 2;
        g_cdr_status_regs[60] = 1;
        g_cdr_secondary_response_size = 2;
        g_cdr_secondary_response = 0;
        if ( (uint8_t)g_cdr_registers )
        {
          if ( (uint8_t)g_cdr_registers == 2 )
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
          *(uint32_t *)&cd_speed = 0;
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
        if ( command > 0x1Du )
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

char cdr_reg2_write(char command)
{
  char status;

  status = g_cdr_param_fifo_count;
  if ( !g_cdr_param_fifo_count )
  {
    status = g_cdr_status_regs[64];
    if ( g_cdr_status_regs[64] == 2 )
    {
      if ( command == 7 && g_cdr_status_regs[61] )
      {
        g_cdr_irq_pending = 1;
        g_cdr_status_regs[61] = 0;
        g_cdr_status_regs[64] = 0;
        return status;
      }
      g_cdr_irq_mode = command;
      g_cdr_status_regs[64] = 0;
      return status;
    }
    if ( g_cdr_status_regs[64] )
    {
      g_cdr_irq_mode = command;
      g_cdr_status_regs[64] = 0;
      return status;
    }
    status = g_cdr_status_regs[61];
    *((uint8_t *)&g_cdr_param_fifo + (uint8_t)g_cdr_status_regs[61]++) = command;
    g_cdr_status_regs[64] = 0;
  }
  return status;
}

void cdr_reg3_write(char command)
{
  if ( g_cdr_param_fifo_count )
  {
    if ( command == 32 )
      g_cdr_param_fifo_count = 0;
  }
  else
  {
    g_cdr_status_regs[65] |= 0x40u;
    if ( g_cdr_status_regs[64] != 1 || (g_cdr_status_regs[64] = 2, command != 7) )
      g_cdr_status_regs[64] = 0;
    if ( g_cdr_irq_pending && command == 7 )
    {
      if ( g_cdr_status_regs[62] == 1 && g_cdr_retry_count )
        --g_cdr_retry_count;
      g_cdr_status_regs[62] = 0;
      if ( (uint8_t)g_cdr_response_index >= (uint8_t)g_cdr_response_size && g_cdr_status_regs[63] )
      {
        if ( g_cdr_status_regs[60] )
        {
          qmemcpy(g_cdr_response_fifo, &g_cdr_primary_response, (uint8_t)g_cdr_status_regs[60]);
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
            qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (uint8_t)g_cdr_secondary_response_index);
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

int cdr_msf_to_lba(uint8_t minute, uint8_t second, uint8_t frame)
{
  int seconds;
  int minutes;

  seconds = second - 2;
  minutes = minute;
  if ( seconds < 0 )
  {
    seconds += 60;
    minutes = minute - 1;
  }
  return frame + 75 * (seconds + 60 * minutes);
}

static char cdr_read_data_sector()
{
  int16_t msf;
  int lba;

  msf = g_cdr_cur_msf_pos;
  lba = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  if ( g_cdr_last_lba_read != lba )
  {
    cdrom_read_data_cb((uint8_t)msf, HIBYTE(msf), BYTE2(g_cdr_cur_msf_pos), g_cdr_data_buffer);
    g_cdr_last_lba_read = cdr_msf_to_lba(g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
    LOBYTE(lba) = g_cdr_status_regs[72];
    g_cdr_data_bytes_transferred = (g_cdr_status_regs[72] & 0x20) != 0 ? 12 : 24;
    if ( (g_cdr_xa_buffer[2] & 0xF) == 4 )
    {
      LOBYTE(lba) = g_cdr_status_regs[72] & 0x48;
      if ( (g_cdr_status_regs[72] & 0x48) == 0x40
        || (uint8_t)lba == 72
        && g_cdr_xa_buffer[0] == (uint8_t)g_cdr_cur_track
        && (LOBYTE(lba) = g_cdr_xa_buffer[1], g_cdr_xa_buffer[1] == HIBYTE(g_cdr_cur_track)) )
      {
        LOBYTE(lba) = spu_play_adpcm_cb(g_cdr_xa_buffer);
      }
    }
  }
  return lba;
}

static char cdr_increment_msf()
{
  char value;
  bool carry;

  value = ++BYTE2(g_cdr_cur_msf_pos);
  if ( BYTE2(g_cdr_cur_msf_pos) == 75 )
  {
    value = BYTE1(g_cdr_cur_msf_pos) + 1;
    carry = BYTE1(g_cdr_cur_msf_pos)++ == 59;
    *(uint16_t *)((char *)&g_cdr_cur_msf_pos + 1) = BYTE1(g_cdr_cur_msf_pos);
    if ( carry )
    {
      value = g_cdr_cur_msf_pos + 1;
      LOBYTE(g_cdr_cur_msf_pos) = g_cdr_cur_msf_pos + 1;
      LOWORD(g_cdr_cur_msf_pos) = (uint8_t)g_cdr_cur_msf_pos;
    }
  }
  return value;
}

static char cdr_set_nocd(char flag)
{
  LOBYTE(g_cdr_registers) = flag;
  return flag;
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
    return (uint8_t)g_cdr_status_regs[62];
}

static void cdr_queue_response()
{
  if ( g_cdr_status_regs[63] )
  {
    if ( g_cdr_status_regs[60] )
    {
      qmemcpy(g_cdr_response_fifo, &g_cdr_primary_response, (uint8_t)g_cdr_status_regs[60]);
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
      qmemcpy(&g_cdr_primary_response, &g_cdr_secondary_response, (uint8_t)g_cdr_secondary_response_index);
      g_cdr_status_regs[60] = g_cdr_secondary_response_index;
      g_cdr_secondary_response_index = 0;
    }
    g_cdr_status_regs[63] = g_cdr_secondary_response_size;
    g_cdr_secondary_response_size = 0;
  }
}

char cdr_process_delays()
{
  char status;

  status = g_cdr_status_regs[62];
  if ( !g_cdr_status_regs[62] && (g_cdr_status_regs[63] || (status = g_cdr_secondary_response_size) != 0) )
  {
    status = ++g_cdr_response_delay_counter;
    if ( (uint16_t)g_cdr_response_delay_counter >= (uint16_t)g_cdr_response_delay )
    {
      cdr_queue_response();
      status = 10;
      g_cdr_response_delay_counter = 0;
      if ( (uint16_t)g_cdr_response_delay > 0xAu )
        g_cdr_response_delay = 10;
    }
  }
  return status;
}

static int16_t cdr_init_report_mode()
{
  int16_t region;

  g_cdr_irq_enabled = 1;
  g_cdr_tick_counter = 0;
  g_cdr_spindown_counter = 0;
  g_cdr_dma_active = 0;
  if ( country_setting == 1 )
    LOBYTE(region) = g_cdr_status_regs[72] < 0 ? 104 : -48;
  else
    LOBYTE(region) = g_cdr_status_regs[72] < 0 ? 104 : -47;
  g_cdr_region_code = region;
  region = (uint8_t)region;
  g_cdr_read_ahead_sectors = region;
  g_cdr_delay_counter = (uint8_t)region;
  if ( !g_cdr_status_regs[70] )
  {
    region = 3 * (uint8_t)region;
    g_cdr_delay_counter = region;
  }
  return region;
}

void cdr_play_tick()
{
  char status;

  if ( g_cdr_status_regs[70] )
  {
    if ( (uint16_t)++g_cdr_tick_counter >= (uint16_t)g_cdr_delay_counter )
    {
      status = g_cdr_status_regs[72];
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
          status = g_cdr_status_regs[72];
        }
      }
      if ( (status & 2) == 2
        && g_cdr_seek_target_msf == (uint8_t)g_cdr_cur_msf_pos
        && g_cdr_seek_target_sf == *(uint16_t *)((char *)&g_cdr_cur_msf_pos + 1)
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
      g_cdr_tick_counter = 0;
      cdr_increment_msf();
    }
  }
  else if ( g_cdr_status_regs[67] )
  {
    if ( (uint16_t)++g_cdr_tick_counter >= (uint16_t)g_cdr_delay_counter )
    {
      g_cdr_tick_counter = 0;
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
  int blocks;
  unsigned int block_size;
  unsigned int dma_addr;
  unsigned int byte_count;
  int data_offset;

  blocks = HIWORD(g_cdr_dma_block_control);
  block_size = (uint16_t)g_cdr_dma_block_control;
  dma_addr = g_cdr_dma_address;
  if ( (g_cdr_dma_channel_control & 0x11000000) == 0x11000000 )
  {
    if ( !HIWORD(g_cdr_dma_block_control) )
      blocks = 1;
    if ( !(uint16_t)g_cdr_dma_block_control )
      block_size = 512;
    byte_count = 4 * blocks * block_size;
    data_offset = g_cdr_data_bytes_transferred;
    block_size = byte_count + g_cdr_data_bytes_transferred;
    g_cdr_data_bytes_transferred += byte_count;
    if ( dynarec_enabled == 1 )
      block_size = dynarec_invalidate_range(g_cdr_dma_address, byte_count >> 2);
    if ( byte_count + (dma_addr & 0x1FFFFF) <= 0x200000 )
    {
      block_size = mem_dma_read(dma_addr);
      qmemcpy((void *)block_size, &g_cdr_data_buffer[data_offset], byte_count);
    }
    g_cdr_dma_active = 1;
  }
  return block_size;
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
  char motor_state;

  motor_state = g_cdr_status_regs[69];
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
  return motor_state;
}

int cdr_freeze(const char *tag, int gz_file)
{
  char Buffer[3];

  sprintf(Buffer, "%s", tag);
  g_cdr_idle_counter = g_cdr_response_delay_counter;
  g_cdr_spindown_counter = g_cdr_tick_counter;
  gzwrite(gz_file, (uint8_t *)Buffer, 7u);
  return gzwrite(gz_file, (uint8_t *)g_cdr_response_fifo, 0x112Cu);
}

int cdr_unfreeze_new(int unused, uint32_t *gz_file)
{
  char hdr[16];

  gzread(gz_file, hdr, 7);
  gzread(gz_file, g_cdr_response_fifo, 4396);
  g_cdr_response_delay_counter = (uint8_t)g_cdr_idle_counter;
  if ( g_cdr_status_regs[70] )
    return cdrom_play_cdda_cb((uint8_t)g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  else
    return cdrom_stop_cb();
}

int cdr_unfreeze(int unused, uint32_t *gz_file)
{
  char hdr[16];

  gzread(gz_file, hdr, 7);
  gzread(gz_file, g_cdr_response_fifo, 4396);
  g_cdr_read_ahead_sectors = (uint8_t)g_cdr_region_code;
  g_cdr_delay_counter = (uint8_t)g_cdr_region_code;
  g_cdr_response_delay_counter = (uint8_t)g_cdr_idle_counter;
  g_cdr_tick_counter = (uint8_t)g_cdr_spindown_counter;
  if ( g_cdr_status_regs[70] )
    return cdrom_play_cdda_cb((uint8_t)g_cdr_cur_msf_pos, BYTE1(g_cdr_cur_msf_pos), BYTE2(g_cdr_cur_msf_pos));
  else
    return cdrom_stop_cb();
}

int cdr_get_status(int status)
{
  int value;

  value = status;
  g_cdr_status_regs[62] = status;
  g_cdr_response_index = 0;
  g_cdr_response_size = 1;
  if ( status == 1 )
    g_cdr_response_fifo[0] = 2;
  return value;
}
