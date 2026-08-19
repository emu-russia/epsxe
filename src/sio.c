#include "pch.h"
static char sio_schedule_transfer(char has_more, char *buffer)
{
  int tmp;

  LOBYTE(tmp) = has_more;
  if ( !has_more )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg | 2;
  sio_tx_fifo[(uint8_t)sio_rx_fifo_count + 3] = *buffer;
  LOBYTE(sio_rx_fifo_count) = sio_rx_fifo_count + 1;
  if ( has_more )
  {
    LOBYTE(tmp) = sio0_control_reg;
    if ( (sio0_control_reg & 0x1000) != 0 )
    {
      irq_sio_update();
      tmp = hw_update_counter;
      if ( hw_update_counter >= 0 )
      {
        if ( (unsigned int)hw_update_counter > 0x1F9 )
        {
          sio_transfer_timeout = hw_update_counter - 505;
          sio_transfer_pending = 128;
          LOBYTE(tmp) = hw_update_counter + 7;
          return tmp;
        }
      }
      else
      {
        tmp = 0;
        hw_update_counter = 0;
      }
      sio_scheduled_transfer_timeout = cpu_speed_scale + tmp - 505;
      sio_transfer_pending = 0;
    }
  }
  return tmp;
}

static int sio_handle_config_command(char port, int out_buf, char command)
{
  int mode;
  int mode_idx;
  int word1;
  int word2;
  char byte3;
  int analog_mode;
  int tail_word;
  uint8_t response[9];

  mode = controller_port_modes[(uint8_t)port];
  mode_idx = mode - 1;
  if ( mode_idx )
  {
    if ( mode_idx == 3 )
    {
      sio_last_command_slot[(uint8_t)sio_controller_state[0]] = command;
      if ( command == 66 || command == 67 )
      {
        if ( pad_analog_mode_flags[(uint8_t)port] )
        {
          cont_build_controller_response_analog(port, response);
        }
        else
        {
          cont_build_controller_response_digital(port, response);
          *(uint32_t *)&response[5] = -2139062144;
        }
      }
      switch ( command )
      {
        case 'D':
          word1 = *(uint32_t *)sio_config_data;
          word2 = *(uint32_t *)&sio_config_data[4];
          byte3 = sio_config_data[8];
          goto LABEL_17;
        case 'E':
          *(uint32_t *)response = *(uint32_t *)&sio_config_data[12];
          *(uint32_t *)&response[4] = *(uint32_t *)&sio_config_data[16];
          analog_mode = pad_analog_mode_flags[(uint8_t)port];
          response[8] = sio_config_data[20];
          if ( analog_mode == 1 )
            response[5] = 1;
          break;
        case 'F':
          word1 = *(uint32_t *)&sio_config_data[24];
          word2 = *(uint32_t *)&sio_config_data[28];
          byte3 = sio_config_data[32];
          goto LABEL_17;
        case 'G':
          word1 = *(uint32_t *)&sio_config_data[36];
          word2 = *(uint32_t *)&sio_config_data[40];
          byte3 = sio_config_data[44];
          goto LABEL_17;
        case 'L':
          word1 = *(uint32_t *)&sio_config_data[60];
          word2 = *(uint32_t *)&sio_config_data[64];
          byte3 = sio_config_data[68];
          goto LABEL_17;
        case 'M':
          word1 = *(uint32_t *)&sio_config_data[48];
          word2 = *(uint32_t *)&sio_config_data[52];
          byte3 = sio_config_data[56];
LABEL_17:
          *(uint32_t *)response = word1;
          *(uint32_t *)&response[4] = word2;
          response[8] = byte3;
          break;
        default:
          break;
      }
      tail_word = *(uint32_t *)&response[5];
      *(uint32_t *)out_buf = *(uint32_t *)&response[1];
      *(uint32_t *)(out_buf + 4) = tail_word;
      return out_buf;
    }
    *(uint8_t *)(out_buf + 3) = -1;
    *(uint8_t *)(out_buf + 2) = -1;
    *(uint8_t *)(out_buf + 1) = 90;
    *(uint8_t *)out_buf = 65;
    *(uint32_t *)(out_buf + 4) = 0x80808080;
    return out_buf + 4;
  }
  cont_build_controller_response_digital(port, response);
  if ( command != 66 )
    response[1] = command;
  if ( command == 69 )
  {
    *(uint32_t *)response = *(uint32_t *)&sio_config_data[72];
    response[4] = controller_config_response_byte;
  }
  *(uint32_t *)out_buf = *(uint32_t *)&response[1];
  *(uint32_t *)(out_buf + 4) = 0x80808080;
  return out_buf + 4;
}

static unsigned int sio_build_multitap_response(uint8_t *buffer, uint32_t *length)
{
  int *state_ptr;
  int i;
  unsigned int length_byte;

  sio_multitap_state = 0;
  *length = 3;
  state_ptr = &sio_multitap_state;
  i = 4;
  do
  {
    *(uint8_t *)state_ptr = *(uint8_t *)length;
    state_ptr = (int *)((char *)state_ptr + 1);
    --i;
    *length += 8;
  }
  while ( i );
  *buffer = 1;
  buffer[1] = 0x80;
  length_byte = *length - 3;
  buffer[2] = 90;
  if ( length_byte < 0x20 )
  {
    length_byte >>= 1;
    LOBYTE(length_byte) = length_byte | 0x80;
    buffer[1] = length_byte;
  }
  return length_byte;
}

static void sio_command(char *cmd)
{
  char port;
  int port_idx;
  int offset;
  uint8_t index;
  char multitap;
  bool no_multitap;
  int d_word2;
  int d_dst;
  char d_byte3;
  int e_word2;
  int e_dst;
  char e_byte3;
  int f_word2;
  int f_dst;
  char f_byte3;
  int g_word2;
  int g_dst;
  char g_byte3;
  int l_word2;
  int l_dst;
  char l_byte3;
  int m_word2;
  int m_dst;
  char m_byte3;
  uint8_t slot;
  int port_cur;
  unsigned int small_device;
  unsigned int big_device;
  int tx_offset;
  unsigned int byte_pos;
  unsigned int transfer_len;
  uint8_t *buf_ptr;
  bool has_more;
  char memcard_cmd;
  int16_t addr_hi;
  int16_t addr_hi2;
  char checksum;
  char *src;
  int count;
  uint8_t slot_hi;
  uint8_t slot_hi2;
  char mode;

  port = sio_controller_state[0];
  if ( sio_controller_state[0] >= 0 )
  {
    port_idx = (uint8_t)sio_controller_state[0];
    offset = 65 * (uint8_t)sio_controller_state[0];
    index = sio_controller_state[offset + 2];
    if ( index )
    {
      if ( sio_controller_state[1] == 1 )
      {
        if ( index == 1 )
        {
          if ( (*cmd & 0x40) != 0x40 )
          {
            sio_schedule_transfer(1, &sio_controller_state[offset + 3]);
            sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] = 0;
            return;
          }
          multitap = multitap_1;
          no_multitap = multitap_1 == 0;
          mode = controller_port_modes[(uint8_t)sio_controller_state[0]];
          sio_last_command_slot[(uint8_t)sio_controller_state[0]] = 0;
          LOWORD(sio_multitap_slot_counter) = -256;
          if ( no_multitap )
            BYTE1(sio_multitap_slot_counter) = port;
          if ( port )
          {
            if ( port == 1 && multitap )
              mode = 0;
          }
          else if ( multitap )
          {
            mode = 10;
          }
          switch ( mode )
          {
            case 0:
              *(uint16_t *)(offset + 5334371) = -1;
              if ( *cmd != 66 )
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *cmd;
              sio_transfer_length = 2;
              break;
            case 1:
              cont_build_controller_response_digital(port_idx, (uint8_t *)(offset + 5334371));
              if ( *cmd != 66 )
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *cmd;
              sio_transfer_length = 5;
              if ( *cmd == 69 )
              {
                sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 3] = 1;
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = -13;
                sio_response_buffer_id[65 * (uint8_t)sio_controller_state[0]] = 90;
                sio_response_buffer_data1[65 * (uint8_t)sio_controller_state[0]] = 0;
                sio_response_buffer_data2[65 * (uint8_t)sio_controller_state[0]] = 0;
              }
              break;
            case 2:
              if ( !pad_analog_mode_flags[port_idx] )
              {
                cont_build_controller_response_digital(port_idx, (uint8_t *)(offset + 5334371));
                if ( *cmd != 66 )
                  sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *cmd;
                goto LABEL_30;
              }
              cont_build_mouse_response(port_idx, (uint8_t *)(offset + 5334371));
              sio_transfer_length = 7;
              break;
            case 3:
              if ( pad_analog_mode_flags[port_idx] )
              {
                cont_build_guncon_response(port_idx, (uint8_t *)(offset + 5334371));
                sio_transfer_length = 9;
              }
              else
              {
                cont_build_controller_response_digital(port_idx, (uint8_t *)(offset + 5334371));
                if ( *cmd == 66 )
                {
LABEL_30:
                  sio_transfer_length = 5;
                }
                else
                {
                  sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *cmd;
                  sio_transfer_length = 5;
                }
              }
              break;
            case 4:
            case 5:
            case 6:
              sio_last_command_slot[port_idx] = *cmd;
              if ( *cmd == 66 || *cmd == 67 )
              {
                if ( pad_analog_mode_flags[port_idx] )
                {
                  cont_build_controller_response_analog(port_idx, (uint8_t *)(offset + 0x516563));
                }
                else
                {
                  cont_build_controller_response_digital(port_idx, (uint8_t *)(offset + 5334371));
                  *(uint32_t *)&sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0]] = -2139062144;
                }
              }
              sio_transfer_length = 9;
              sio_multitap_command_buffer[0] = 1;
              sio_multitap_command_byte[0] = *cmd;
              if ( *cmd == 68 )
              {
                d_word2 = *(uint32_t *)&sio_config_data[4];
                d_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)d_dst = *(uint32_t *)sio_config_data;
                d_byte3 = sio_config_data[8];
                *(uint32_t *)(d_dst + 4) = d_word2;
                *(uint8_t *)(d_dst + 8) = d_byte3;
              }
              if ( *cmd == 69 )
              {
                e_word2 = *(uint32_t *)&sio_config_data[16];
                e_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)e_dst = *(uint32_t *)&sio_config_data[12];
                e_byte3 = sio_config_data[20];
                *(uint32_t *)(e_dst + 4) = e_word2;
                *(uint8_t *)(e_dst + 8) = e_byte3;
                if ( pad_analog_mode_flags[(uint8_t)sio_controller_state[0]] == 1 )
                  sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0]] = 1;
              }
              if ( *cmd == 70 )
              {
                f_word2 = *(uint32_t *)&sio_config_data[28];
                f_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)f_dst = *(uint32_t *)&sio_config_data[24];
                f_byte3 = sio_config_data[32];
                *(uint32_t *)(f_dst + 4) = f_word2;
                *(uint8_t *)(f_dst + 8) = f_byte3;
              }
              if ( *cmd == 71 )
              {
                g_word2 = *(uint32_t *)&sio_config_data[40];
                g_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)g_dst = *(uint32_t *)&sio_config_data[36];
                g_byte3 = sio_config_data[44];
                *(uint32_t *)(g_dst + 4) = g_word2;
                *(uint8_t *)(g_dst + 8) = g_byte3;
              }
              if ( *cmd == 76 )
              {
                l_word2 = *(uint32_t *)&sio_config_data[52];
                l_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)l_dst = *(uint32_t *)&sio_config_data[48];
                l_byte3 = sio_config_data[56];
                *(uint32_t *)(l_dst + 4) = l_word2;
                *(uint8_t *)(l_dst + 8) = l_byte3;
              }
              if ( *cmd == 77 )
              {
                m_word2 = *(uint32_t *)&sio_config_data[64];
                m_dst = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)m_dst = *(uint32_t *)&sio_config_data[60];
                m_byte3 = sio_config_data[68];
                *(uint32_t *)(m_dst + 4) = m_word2;
                *(uint8_t *)(m_dst + 8) = m_byte3;
              }
              break;
            case 10:
              sio_build_multitap_response((uint8_t *)(offset + 5334371), &sio_transfer_length);
              break;
            default:
              break;
          }
        }
        else
        {
          sio_multitap_command_buffer[(uint8_t)sio_controller_state[65
                                                                          * (uint8_t)sio_controller_state[0]
                                                                          + 2]] = *cmd;
          if ( multitap_1 )
          {
            if ( !port
              && *((uint8_t *)&sio_multitap_state + (uint8_t)(BYTE1(sio_multitap_slot_counter) + 1)) == sio_controller_state[2] )
            {
              LOBYTE(sio_multitap_slot_counter) = sio_controller_state[2] - 1;
              if ( (*cmd & 0x40) == 0x40 )
              {
                ++BYTE1(sio_multitap_slot_counter);
                sio_last_command_slot[0] = 0;
                sio_handle_config_command(
                  SBYTE1(sio_multitap_slot_counter),
                  (uint8_t)sio_controller_state[2] + 5334371,
                  *cmd);
              }
            }
          }
          slot = sio_multitap_slot_counter;
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 76
            && *cmd == 1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == (uint8_t)sio_multitap_slot_counter + 3 )
          {
            sio_response_buffer_config_byte[65 * (uint8_t)sio_controller_state[0]
                                          + (uint8_t)sio_multitap_slot_counter] = 7;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 70
            && *cmd == 1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == slot + 3 )
          {
            sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0] + slot] = 4;
            sio_response_buffer_config_byte[65 * (uint8_t)sio_controller_state[0] + slot] = 3;
            sio_response_buffer_config_byte2[65 * (uint8_t)sio_controller_state[0] + slot] = 1;
            sio_response_buffer_config_byte3[65 * (uint8_t)sio_controller_state[0] + slot] = 30;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 68
            && *cmd
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == slot + 3
            && pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] != 1 )
          {
            slot_hi = BYTE1(sio_multitap_slot_counter);
            pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] = 1;
            cont_update_led_and_mode(slot_hi);
            slot = sio_multitap_slot_counter;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 68
            && !*cmd
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == slot + 3
            && pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] )
          {
            slot_hi2 = BYTE1(sio_multitap_slot_counter);
            pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] = 0;
            cont_update_led_and_mode(slot_hi2);
            slot = sio_multitap_slot_counter;
          }
          port_cur = (uint8_t)sio_controller_state[0];
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 66 )
          {
            if ( (*cmd & 1) != 0
              && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == slot + 3 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)] == 5 )
              {
                joy_issue_small_motor();
                slot = sio_multitap_slot_counter;
              }
              small_device = g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)];
              if ( small_device && small_device <= 4 )
              {
                diSetEffectMagnitude(0, 1, 2, BYTE1(sio_multitap_slot_counter));
                slot = sio_multitap_slot_counter;
              }
              port_cur = (uint8_t)sio_controller_state[0];
              rumble_small_motor_state[2 * (uint8_t)sio_controller_state[0]] = *cmd & 1;
            }
            if ( sio_last_command_slot[port_cur] == 66
              && *cmd
              && (uint8_t)sio_controller_state[65 * port_cur + 2] == slot + 4 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)] == 5 )
                joy_issue_big_motor();
              big_device = g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)];
              if ( big_device && big_device <= 4 )
                diSetEffectMagnitude(1, (uint8_t)*cmd, 2, BYTE1(sio_multitap_slot_counter));
              rumble_big_motor_state[2 * (uint8_t)sio_controller_state[0]] = *cmd;
            }
          }
        }
        tx_offset = 65 * (uint8_t)sio_controller_state[0];
        byte_pos = (uint8_t)sio_controller_state[tx_offset + 2];
        if ( byte_pos >= sio_transfer_length - 1 )
          sio_schedule_transfer(0, (char *)(byte_pos + tx_offset + 5334371));
        else
          sio_schedule_transfer(1, (char *)(byte_pos + tx_offset + 5334371));
        transfer_len = sio_transfer_length;
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        buf_ptr = (uint8_t *)(65 * (uint8_t)sio_controller_state[0] + 5334370);
        has_more = (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] < transfer_len;
      }
      else
      {
        if ( sio_controller_state[1] != 2 )
          return;
        if ( index == 1 )
        {
          if ( *cmd == 87 )
          {
            memcard_cmd = 87;
            memcard2_buffer[129024] = 87;
            memcard2_buffer[129025] = -118;
            memcard2_buffer[129026] = 0;
            memcard2_buffer[129027] = 90;
            memcard2_buffer[129028] = 93;
            memcard2_buffer[129029] = 0;
            memcard2_buffer[129160] = 92;
            memcard2_buffer[129161] = 93;
            memcard2_buffer[129162] = 71;
          }
          else
          {
            if ( *cmd != 82 )
            {
              sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] = 0;
              return;
            }
            port = sio_controller_state[0];
            memcard_cmd = 82;
            memcard2_buffer[129024] = 82;
            memcard2_buffer[129025] = -116;
            memcard2_buffer[129026] = 0;
            memcard2_buffer[129027] = 90;
            memcard2_buffer[129028] = 93;
            memcard2_buffer[129029] = 0;
            memcard2_buffer[129030] = 0;
            memcard2_buffer[129031] = 92;
            memcard2_buffer[129032] = 93;
            memcard2_buffer[129164] = 71;
          }
        }
        else
        {
          memcard_cmd = memcard2_buffer[129024];
        }
        if ( memcard_cmd == 82 )
        {
          if ( index == 4 )
          {
            LOBYTE(addr_hi) = 0;
            HIBYTE(addr_hi) = *cmd;
            memcard_current_address = addr_hi;
            memcard2_buffer[129033] = *cmd;
          }
          if ( index == 5 )
          {
            memcard_current_address |= (uint8_t)*cmd;
            memcard2_buffer[129034] = *cmd;
          }
          if ( index == 6 )
          {
            qmemcpy(
              &memcard2_buffer[129035],
              &sio_memcard_data_slot1[128
                                    * ((uint16_t)memcard_current_address
                                     + ((uint8_t)sio_controller_state[0] << 10))],
              0x80u);
            checksum = 0;
            memcard2_buffer[129163] = 0;
            src = &memcard2_buffer[129033];
            count = 130;
            do
            {
              checksum ^= *src++;
              --count;
              memcard2_buffer[129163] = checksum;
            }
            while ( count );
          }
        }
        else if ( memcard_cmd == 87 )
        {
          if ( port )
            sio_memcard2_dirty_counter = 1;
          else
            sio_memcard1_dirty_counter = 1;
          if ( index > 3u && index < 0x86u )
            memcard2_buffer[index + 129026] = *cmd;
          if ( index == 0x89 )
          {
            LOBYTE(addr_hi2) = 0;
            HIBYTE(addr_hi2) = memcard2_buffer[129030];
            memcard_current_address = (uint8_t)memcard2_buffer[129031] | addr_hi2;
            qmemcpy(
              &sio_memcard_data_slot1[128 * ((uint16_t)memcard_current_address + (port_idx << 10))],
              &memcard2_buffer[129032],
              0x80u);
          }
        }
        if ( index >= (unsigned int)memcard2_buffer[129025] )
          sio_schedule_transfer(0, &memcard2_buffer[index + 129025]);
        else
          sio_schedule_transfer(1, &memcard2_buffer[index + 129025]);
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        buf_ptr = (uint8_t *)(65 * (uint8_t)sio_controller_state[0] + 5334370);
        has_more = (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] < (unsigned int)memcard2_buffer[129025];
      }
      if ( !has_more )
        *buf_ptr = 0;
    }
    else
    {
      if ( *cmd == 1 )
      {
        sio_controller_state[1] = 1;
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        sio_schedule_transfer(1, (char *)(65 * (uint8_t)sio_controller_state[0] + 5334371));
        return;
      }
      if ( *cmd == -127 )
      {
        if ( memcard_enabled )
        {
          sio_controller_state[1] = 2;
          ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        }
        else
        {
          sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] = 0;
        }
        sio_schedule_transfer(1, (char *)(65 * (uint8_t)sio_controller_state[0] + 5334371));
        return;
      }
      sio_schedule_transfer(0, (char *)(offset + 5334371));
    }
  }
}

bool sio_controller_init(int16_t control)
{
  bool port;

  if ( (control & 2) != 0 )
  {
    port = (control & 0x2000) != 0;
    sio_controller_state[0] = port;
  }
  else
  {
    sio_controller_slot_index = 0;
    sio_controller_state[2] = 0;
    sio_controller_state[0] = 0x80;
    return 0;
  }
  return port;
}

static char sio_reset_controller_state()
{
  unsigned int i;

  sio_controller_state[0] = 0;
  sio_controller_slot_index = 0;
  sio_controller_state[2] = 0;
  sio_controller_state[1] = 0;
  for ( i = 3; i < 6; ++i )
  {
    sio_controller_state[i + 3] = -1;
    sio_controller_response_alt[i] = -1;
  }
  sio_controller_state[3] = 0;
  sio_controller_response_buffer[0] = 65;
  sio_response_buffer_id[0] = 90;
  sio_controller_response_alt[0] = 0;
  controller2_id_byte = 65;
  controller2_response_constant = 90;
  return 90;
}

char sio_memcard_load()
{
  FILE *file2;
  unsigned int i;
  unsigned int j;
  unsigned int k;
  FILE *file1;

  LOBYTE(file2) = sio_memcard_loaded;
  if ( !sio_memcard_loaded )
  {
    if ( !strcmp((const char *)Memcard1, "NULL") )
      sprintf((char *const)Memcard1, "%s", "memcards\\epsxe000.mcr");
    if ( !strcmp((const char *)Memcard2, "NULL") )
      sprintf((char *const)Memcard2, "%s", "memcards\\epsxe001.mcr");
    for ( i = 0; i < 0x20000; ++i )
    {
      sio_memcard_data_slot2[i] = 0;
      sio_memcard_data_slot1[i] = 0;
    }
    sio_memcard_data_slot2[0] = 77;
    sio_memcard_data_slot1[0] = 77;
    memcard2_header[0] = 67;
    memcard2_id_byte = 67;
    memcard2_header_checksum = 14;
    memcard2_checksum = 14;
    for ( j = 0; j < 0x780; j += 128 )
    {
      memcard2_directory_state[j] = -96;
      memcard2_data[j] = -96;
      memcard2_directory_next_block[j] = -1;
      memcard1_directory_next_block[j] = -1;
      memcard2_directory_frame[j] = -1;
      memcard1_directory_frame[j] = -1;
      memcard2_directory_checksum[j] = -96;
      memcard1_directory_checksum[j] = -96;
    }
    for ( k = 0; k < 0xA00; k += 128 )
    {
      memcard2_buffer[k] = -1;
      memcard1_block_state_byte0[k] = -1;
      memcard2_buffer[k + 1] = -1;
      memcard1_block_state_byte1[k] = -1;
      memcard2_buffer[k + 2] = -1;
      memcard1_block_state_byte2[k] = -1;
      memcard2_buffer[k + 3] = -1;
      memcard1_block_state_byte3[k] = -1;
      memcard2_buffer[k + 8] = -1;
      memcard1_block_next_block[k] = -1;
      memcard2_buffer[k + 9] = -1;
      memcard1_save_data[k] = -1;
    }
    file1 = fopen((const char *)Memcard1, "rb");
    if ( file1 )
    {
      fseek(file1, 0, 2);
      sio_memcard1_file_offset = ftell(file1) - 0x20000;
      fseek(file1, sio_memcard1_file_offset, 0);
      fread(sio_memcard_data_slot1, 1u, 0x20000u, file1);
      fclose(file1);
    }
    else
    {
      sio_memcard1_file_offset = 0;
    }
    file2 = fopen((const char *)Memcard2, "rb");
    if ( file2 )
    {
      fseek(file2, 0, 2);
      sio_memcard2_file_offset = ftell(file2) - 0x20000;
      fseek(file2, sio_memcard2_file_offset, 0);
      fread(sio_memcard_data_slot2, 1u, 0x20000u, file2);
      LOBYTE(file2) = fclose(file2);
    }
    else
    {
      sio_memcard2_file_offset = 0;
    }
    sio_memcard_loaded = 1;
  }
  return (char)file2;
}

static char sio_memcard1_save()
{
  char loaded;
  FILE *file;

  loaded = sio_memcard_loaded;
  if ( sio_memcard_loaded )
  {
    file = fopen((const char *)Memcard1, "wb");
    if ( file )
    {
      fseek(file, sio_memcard1_file_offset, 0);
      fwrite(sio_memcard_data_slot1, 1u, 0x20000u, file);
      return fclose(file);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard1);
    }
  }
  return loaded;
}

static char sio_memcard2_save()
{
  char loaded;
  FILE *file;

  loaded = sio_memcard_loaded;
  if ( sio_memcard_loaded )
  {
    file = fopen((const char *)Memcard2, "wb");
    if ( file )
    {
      fseek(file, sio_memcard2_file_offset, 0);
      fwrite(sio_memcard_data_slot2, 1u, 0x20000u, file);
      return fclose(file);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard2);
    }
  }
  return loaded;
}

// Microsoft VisualC 2-14/net runtime
char sio_memcard_both_save()
{
  sio_memcard1_save();
  return sio_memcard2_save();
}

char sio_memcard_auto_save()
{
  int dirty1;

  dirty1 = sio_memcard1_dirty_counter;
  if ( sio_memcard1_dirty_counter )
    dirty1 = ++sio_memcard1_dirty_counter;
  if ( sio_memcard2_dirty_counter )
    ++sio_memcard2_dirty_counter;
  if ( dirty1 == 120 )
  {
    sio_memcard1_dirty_counter = 0;
    LOBYTE(dirty1) = sio_memcard1_save();
  }
  if ( sio_memcard2_dirty_counter == 120 )
  {
    sio_memcard2_dirty_counter = 0;
    LOBYTE(dirty1) = sio_memcard2_save();
  }
  return dirty1;
}

int (__stdcall *sio_reset_all())(uint32_t)
{
  sio0_mode_reg = 5;
  sio0_control_reg = 0;
  sio_tx_fifo[0] = 0;
  sio_tx_fifo[1] = 0;
  sio_tx_fifo[2] = 1;
  sio_tx_fifo[259] = 0;
  LOBYTE(sio_rx_fifo_count) = 0;
  sio_reset_controller_state();
  sio_memcard_load();
  return cont_update_led_and_mode(0);
}

void sio_write_data_byte(int unused, char data)
{
  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  sio_tx_fifo_data[(uint8_t)--sio_tx_fifo[0]] = data;
  if ( !sio_tx_fifo[0] )
  {
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFE;
    if ( (sio0_control_reg & 1) != 0 )
    {
      sio_command(sio_tx_fifo_data);
      LOBYTE(sio0_mode_reg) = sio0_mode_reg | 5;
      sio_tx_fifo[0] = sio_tx_fifo[2];
      if ( (sio0_control_reg & 0x400) != 0 )
      {
        BYTE1(sio0_mode_reg) |= 2u;
        irq_sio_assert_int();
      }
    }
  }
}

void sio_trigger_rx_ready_irq()
{
  LOWORD(sio0_mode_reg) = sio0_mode_reg | 0x202;
}

void sio_read_data_byte()
{
  if ( sio_transfer_pending && hw_update_counter < (unsigned int)sio_transfer_timeout )
  {
    sio_transfer_pending = 0;
    sio_trigger_rx_ready_irq();
  }
  if ( sio_tx_fifo[259] != (uint8_t)sio_rx_fifo_count && ++sio_tx_fifo[259] == (uint8_t)sio_rx_fifo_count )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFD;
}

static int16_t sio_read_halfword(int address)
{
  char hi_byte;
  int16_t value;
  char lo_byte;
  int16_t reg_value;

  switch ( address )
  {
    case PSX_REG_JOY_DATA:
      sio_read_data_byte();
      HIBYTE(value) = hi_byte;
      sio_read_data_byte();
      LOBYTE(value) = lo_byte;
      reg_value = value;
      break;
    case PSX_REG_JOY_STATUS:
      if ( sio_transfer_pending )
      {
        if ( hw_update_counter < (unsigned int)sio_transfer_timeout )
        {
          sio_transfer_pending = 0;
          sio_trigger_rx_ready_irq();
        }
      }
      reg_value = sio0_mode_reg;
      break;
    case PSX_REG_JOY_MODE:
      reg_value = HIWORD(sio0_mode_reg);
      break;
    case PSX_REG_JOY_CTRL:
      reg_value = sio0_control_reg;
      break;
    case PSX_REG_JOY_BAUD:
      reg_value = HIWORD(sio0_control_reg);
      break;
    default:
      reg_value = 0;
      break;
  }
  return reg_value;
}

static int sio_read_word(int address)
{
  char byte1;
  uint16_t word;
  char byte2;
  uint8_t byte3;
  int value;
  uint8_t byte4;

  if ( address == PSX_REG_JOY_DATA )
  {
    sio_read_data_byte();
    HIBYTE(word) = byte1;
    sio_read_data_byte();
    LOBYTE(word) = byte2;
    sio_read_data_byte();
    value = (byte3 | (word << 8)) << 8;
    sio_read_data_byte();
    return value | byte4;
  }
  else if ( address == PSX_REG_JOY_STATUS )
  {
    if ( sio_transfer_pending )
    {
      if ( hw_update_counter < (unsigned int)sio_transfer_timeout )
      {
        sio_transfer_pending = 0;
        sio_trigger_rx_ready_irq();
      }
    }
    return (uint16_t)sio0_mode_reg;
  }
  else
  {
    return 0;
  }
}

int sio_read_register(int address, char size)
{
  int value;

  value = 0xFFFF;
  switch ( size )
  {
    case 1:
      sio_read_data_byte();
      return (uint8_t)value;
    case 2:
      return (uint16_t)sio_read_halfword(address);
    case 4:
      return sio_read_word(address);
  }
  return value;
}

int sio_freeze(const char *tag, int gz_file)
{
  char Buffer[64];

  sprintf(Buffer, "%s", tag);
  *(uint32_t *)&Buffer[3] = 263532;
  gzwrite(gz_file, (uint8_t *)Buffer, 7u);
  gzwrite(gz_file, (uint8_t *)sio_freeze_state, 0x214u);
  gzwrite(gz_file, (uint8_t *)sio_controller_state, 0x84u);
  gzwrite(gz_file, (uint8_t *)sio_memcard_data_slot1, 0x40104u);
  memset(Buffer, 0, sizeof(Buffer));
  *(uint32_t *)&Buffer[4] = sio_multitap_state;
  *(uint16_t *)&Buffer[8] = sio_multitap_slot_counter;
  *(uint32_t *)Buffer = sio_transfer_length;
  Buffer[10] = multitap_1 & 1;
  return gzwrite(gz_file, (uint8_t *)Buffer, 0x40u);
}

void sio_unfreeze(int unused, uint32_t *gz_file)
{
  char *buf;
  char block[4];
  int mt_state;
  int16_t slot_counter;
  char multitap_flag;

  buf = (char *)malloc(0x40104u);
  gzread(gz_file, block, 7);
  gzread(gz_file, sio_freeze_state, 532);
  gzread(gz_file, sio_controller_state, 132);
  sio_memcard_both_save();
  gzread(gz_file, buf, 262404);
  gzread(gz_file, block, 64);
  sio_multitap_state = mt_state;
  sio_transfer_length = *(uint32_t *)block;
  LOWORD(sio_multitap_slot_counter) = slot_counter;
  multitap_1 = multitap_flag & 1;
  free(buf);
}

char * sio_for_netplay(uint8_t slot)
{
  return &netplay_memcard_buffer[0x20000 * slot];
}

int save_temp_memcard1()
{
  sprintf((char *const)Memcard1, "memcards\\temp.000");
  sio_memcard1_file_offset = 0;
  sio_memcard_loaded = 1;
  return cfg_save_settings();
}

int save_temp_memcard2()
{
  sprintf((char *const)Memcard2, "memcards\\temp.001");
  sio_memcard2_file_offset = 0;
  sio_memcard_loaded = 1;
  return cfg_save_settings();
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char Memcard1[0x400];
unsigned char Memcard2[0x400];
unsigned char controller_config_response_byte = 0x0;
unsigned char netplay_memcard_buffer[0x3820];
unsigned char controller2_id_byte;
unsigned char controller2_response_constant;
unsigned char sio_freeze_state[0x4];
unsigned char memcard1_directory_next_block[1];
unsigned char memcard1_directory_frame[0x76];
unsigned char memcard1_directory_checksum[0x701];
unsigned char memcard1_block_state_byte0[1];
unsigned char memcard1_block_state_byte1[1];
unsigned char memcard1_block_state_byte2[1];
unsigned char memcard1_block_state_byte3[1];
unsigned char memcard1_block_next_block[1];
unsigned char memcard1_save_data[0x1f7f7];
unsigned char memcard2_header[0x7e];
unsigned char memcard2_header_checksum;
unsigned char memcard2_directory_state[1];
unsigned char memcard2_directory_next_block[1];
unsigned char memcard2_directory_frame[0x76];
unsigned char memcard2_directory_checksum[0x701];
unsigned char memcard2_buffer[0x1f902];
unsigned int memcard2_checksum;
unsigned char memcard2_data[0x2000];
unsigned char memcard2_id_byte;
unsigned int memcard_current_address;
unsigned char pad_analog_mode_flags[8];
unsigned char rumble_big_motor_state[8];
unsigned char rumble_small_motor_state[8];
unsigned int sio0_mode_reg;
unsigned char sio_config_data[19] = {0x1, 0xf3, 0x5a, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xf3, 0x5a, 0x1, 0x2, 0x0, 0x2};
unsigned char sio_controller_response_alt[1];
unsigned char sio_controller_response_buffer[1];
unsigned char sio_controller_slot_index;
unsigned char sio_controller_state[0x4];
unsigned char sio_last_command_slot[1];
unsigned int sio_memcard1_dirty_counter;
unsigned int sio_memcard1_file_offset;
unsigned int sio_memcard2_dirty_counter;
unsigned int sio_memcard2_file_offset;
unsigned char sio_memcard_data_slot1[1];
unsigned char sio_memcard_data_slot2[1];
unsigned char sio_memcard_loaded;
unsigned char sio_multitap_command_buffer[0x40];
unsigned char sio_multitap_command_byte[0x40];
unsigned int sio_multitap_slot_counter;
unsigned int sio_multitap_state;
unsigned char sio_response_buffer_analog_byte[8];
unsigned char sio_response_buffer_config_byte[8];
unsigned char sio_response_buffer_config_byte2[8];
unsigned char sio_response_buffer_config_byte3[8];
unsigned char sio_response_buffer_data1[0x100];
unsigned char sio_response_buffer_data2[0x100];
unsigned char sio_response_buffer_id[8];
unsigned int sio_rx_fifo_count;
unsigned int sio_transfer_length = 0x5;
unsigned int sio_transfer_pending;
unsigned int sio_transfer_timeout;
unsigned char sio_tx_fifo[0x104];
unsigned char sio_tx_fifo_data[0x100];
