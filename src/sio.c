#include "pch.h"
static char sio_schedule_transfer(char a1, char *a2)
{
  int v2;

  LOBYTE(v2) = a1;
  if ( !a1 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg | 2;
  sio_tx_fifo[(uint8_t)sio_rx_fifo_count + 3] = *a2;
  LOBYTE(sio_rx_fifo_count) = sio_rx_fifo_count + 1;
  if ( a1 )
  {
    LOBYTE(v2) = sio0_control_reg;
    if ( (sio0_control_reg & 0x1000) != 0 )
    {
      irq_sio_update();
      v2 = hw_update_counter;
      if ( hw_update_counter >= 0 )
      {
        if ( (unsigned int)hw_update_counter > 0x1F9 )
        {
          sio_transfer_timeout = hw_update_counter - 505;
          sio_transfer_pending = 128;
          LOBYTE(v2) = hw_update_counter + 7;
          return v2;
        }
      }
      else
      {
        v2 = 0;
        hw_update_counter = 0;
      }
      sio_scheduled_transfer_timeout = cpu_speed_scale + v2 - 505;
      sio_transfer_pending = 0;
    }
  }
  return v2;
}

static int sio_handle_config_command(char a1, int a2, char a3)
{
  int v3;
  int v4;
  int v5;
  int v6;
  char v7;
  int v8;
  int v10;
  uint8_t v11[9];

  v3 = controller_port_modes[(uint8_t)a1];
  if ( !v3 )
    goto LABEL_24;
  v4 = v3 - 1;
  if ( v4 )
  {
    if ( v4 == 3 )
    {
      sio_last_command_slot[(uint8_t)sio_controller_state[0]] = a3;
      if ( a3 == 66 || a3 == 67 )
      {
        if ( pad_analog_mode_flags[(uint8_t)a1] )
        {
          cont_build_controller_response_analog(a1, v11);
        }
        else
        {
          cont_build_controller_response_digital(a1, v11);
          *(uint32_t *)&v11[5] = -2139062144;
        }
      }
      switch ( a3 )
      {
        case 'D':
          v5 = *(uint32_t *)sio_config_data;
          v6 = *(uint32_t *)&sio_config_data[4];
          v7 = sio_config_data[8];
          goto LABEL_17;
        case 'E':
          *(uint32_t *)v11 = *(uint32_t *)&sio_config_data[12];
          *(uint32_t *)&v11[4] = *(uint32_t *)&sio_config_data[16];
          v8 = pad_analog_mode_flags[(uint8_t)a1];
          v11[8] = sio_config_data[20];
          if ( v8 == 1 )
            v11[5] = 1;
          break;
        case 'F':
          v5 = *(uint32_t *)&sio_config_data[24];
          v6 = *(uint32_t *)&sio_config_data[28];
          v7 = sio_config_data[32];
          goto LABEL_17;
        case 'G':
          v5 = *(uint32_t *)&sio_config_data[36];
          v6 = *(uint32_t *)&sio_config_data[40];
          v7 = sio_config_data[44];
          goto LABEL_17;
        case 'L':
          v5 = *(uint32_t *)&sio_config_data[60];
          v6 = *(uint32_t *)&sio_config_data[64];
          v7 = sio_config_data[68];
          goto LABEL_17;
        case 'M':
          v5 = *(uint32_t *)&sio_config_data[48];
          v6 = *(uint32_t *)&sio_config_data[52];
          v7 = sio_config_data[56];
LABEL_17:
          *(uint32_t *)v11 = v5;
          *(uint32_t *)&v11[4] = v6;
          v11[8] = v7;
          break;
        default:
          break;
      }
      v10 = *(uint32_t *)&v11[5];
      *(uint32_t *)a2 = *(uint32_t *)&v11[1];
      *(uint32_t *)(a2 + 4) = v10;
      return a2;
    }
LABEL_24:
    *(uint8_t *)(a2 + 3) = -1;
    *(uint8_t *)(a2 + 2) = -1;
    *(uint8_t *)(a2 + 1) = 90;
    *(uint8_t *)a2 = 65;
    *(uint32_t *)(a2 + 4) = 0x80808080;
    return a2 + 4;
  }
  cont_build_controller_response_digital(a1, v11);
  if ( a3 != 66 )
    v11[1] = a3;
  if ( a3 == 69 )
  {
    *(uint32_t *)v11 = *(uint32_t *)&sio_config_data[72];
    v11[4] = controller_config_response_byte;
  }
  *(uint32_t *)a2 = *(uint32_t *)&v11[1];
  *(uint32_t *)(a2 + 4) = 0x80808080;
  return a2 + 4;
}

static unsigned int sio_build_multitap_response(uint8_t *a1, uint32_t *a2)
{
  int *v2;
  int *v3;
  int v4;
  unsigned int result;

  sio_multitap_state = 0;
  *a2 = 3;
  v2 = &sio_multitap_state;
  v3 = controller_port_modes;
  v4 = 4;
  do
  {
    *(uint8_t *)v2 = *(uint8_t *)a2;
    ++v3;
    v2 = (int *)((char *)v2 + 1);
    --v4;
    *a2 += 8;
  }
  while ( v4 );
  *a1 = 1;
  a1[1] = 0x80;
  result = *a2 - 3;
  a1[2] = 90;
  if ( result < 0x20 )
  {
    result >>= 1;
    LOBYTE(result) = result | 0x80;
    a1[1] = result;
  }
  return result;
}

static void sio_command(char *a1)
{
  char v1;
  int v2;
  int v3;
  uint8_t v4;
  char v6;
  bool v7;
  int v8;
  int v9;
  char v10;
  int v11;
  int v12;
  char v13;
  int v14;
  int v15;
  char v16;
  int v17;
  int v18;
  char v19;
  int v20;
  int v21;
  char v22;
  int v23;
  int v24;
  char v25;
  uint8_t v26;
  int v27;
  unsigned int v28;
  unsigned int v29;
  int v30;
  unsigned int v31;
  unsigned int v32;
  uint8_t *v33;
  bool v34;
  char v35;
  int16_t v36;
  int16_t v37;
  char v38;
  char *v39;
  int v40;
  uint8_t v41;
  uint8_t v42;
  char v43;

  v1 = sio_controller_state[0];
  if ( sio_controller_state[0] >= 0 )
  {
    v2 = (uint8_t)sio_controller_state[0];
    v3 = 65 * (uint8_t)sio_controller_state[0];
    v4 = sio_controller_state[v3 + 2];
    if ( v4 )
    {
      if ( sio_controller_state[1] == 1 )
      {
        if ( v4 == 1 )
        {
          if ( (*a1 & 0x40) != 0x40 )
          {
            sio_schedule_transfer(1, &sio_controller_state[v3 + 3]);
            sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] = 0;
            return;
          }
          v6 = multitap_1;
          v7 = multitap_1 == 0;
          v43 = controller_port_modes[(uint8_t)sio_controller_state[0]];
          sio_last_command_slot[(uint8_t)sio_controller_state[0]] = 0;
          LOWORD(sio_multitap_slot_counter) = -256;
          if ( v7 )
            BYTE1(sio_multitap_slot_counter) = v1;
          if ( v1 )
          {
            if ( v1 == 1 && v6 )
              v43 = 0;
          }
          else if ( v6 )
          {
            v43 = 10;
          }
          switch ( v43 )
          {
            case 0:
              *(uint16_t *)(v3 + 5334371) = -1;
              if ( *a1 != 66 )
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *a1;
              sio_transfer_length = 2;
              break;
            case 1:
              cont_build_controller_response_digital(v2, (uint8_t *)(v3 + 5334371));
              if ( *a1 != 66 )
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *a1;
              sio_transfer_length = 5;
              if ( *a1 == 69 )
              {
                sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 3] = 1;
                sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = -13;
                sio_response_buffer_id[65 * (uint8_t)sio_controller_state[0]] = 90;
                sio_response_buffer_data1[65 * (uint8_t)sio_controller_state[0]] = 0;
                sio_response_buffer_data2[65 * (uint8_t)sio_controller_state[0]] = 0;
              }
              break;
            case 2:
              if ( !pad_analog_mode_flags[v2] )
              {
                cont_build_controller_response_digital(v2, (uint8_t *)(v3 + 5334371));
                if ( *a1 != 66 )
                  sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *a1;
                goto LABEL_30;
              }
              cont_build_mouse_response(v2, (uint8_t *)(v3 + 5334371));
              sio_transfer_length = 7;
              break;
            case 3:
              if ( pad_analog_mode_flags[v2] )
              {
                cont_build_guncon_response(v2, (uint8_t *)(v3 + 5334371));
                sio_transfer_length = 9;
              }
              else
              {
                cont_build_controller_response_digital(v2, (uint8_t *)(v3 + 5334371));
                if ( *a1 == 66 )
                {
LABEL_30:
                  sio_transfer_length = 5;
                }
                else
                {
                  sio_controller_response_buffer[65 * (uint8_t)sio_controller_state[0]] = *a1;
                  sio_transfer_length = 5;
                }
              }
              break;
            case 4:
            case 5:
            case 6:
              sio_last_command_slot[v2] = *a1;
              if ( *a1 == 66 || *a1 == 67 )
              {
                if ( pad_analog_mode_flags[v2] )
                {
                  cont_build_controller_response_analog(v2, (uint8_t *)(v3 + 0x516563));
                }
                else
                {
                  cont_build_controller_response_digital(v2, (uint8_t *)(v3 + 5334371));
                  *(uint32_t *)&sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0]] = -2139062144;
                }
              }
              sio_transfer_length = 9;
              sio_multitap_command_buffer[0] = 1;
              sio_multitap_command_byte[0] = *a1;
              if ( *a1 == 68 )
              {
                v8 = *(uint32_t *)&sio_config_data[4];
                v9 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v9 = *(uint32_t *)sio_config_data;
                v10 = sio_config_data[8];
                *(uint32_t *)(v9 + 4) = v8;
                *(uint8_t *)(v9 + 8) = v10;
              }
              if ( *a1 == 69 )
              {
                v11 = *(uint32_t *)&sio_config_data[16];
                v12 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v12 = *(uint32_t *)&sio_config_data[12];
                v13 = sio_config_data[20];
                *(uint32_t *)(v12 + 4) = v11;
                *(uint8_t *)(v12 + 8) = v13;
                if ( pad_analog_mode_flags[(uint8_t)sio_controller_state[0]] == 1 )
                  sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0]] = 1;
              }
              if ( *a1 == 70 )
              {
                v14 = *(uint32_t *)&sio_config_data[28];
                v15 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v15 = *(uint32_t *)&sio_config_data[24];
                v16 = sio_config_data[32];
                *(uint32_t *)(v15 + 4) = v14;
                *(uint8_t *)(v15 + 8) = v16;
              }
              if ( *a1 == 71 )
              {
                v17 = *(uint32_t *)&sio_config_data[40];
                v18 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v18 = *(uint32_t *)&sio_config_data[36];
                v19 = sio_config_data[44];
                *(uint32_t *)(v18 + 4) = v17;
                *(uint8_t *)(v18 + 8) = v19;
              }
              if ( *a1 == 76 )
              {
                v20 = *(uint32_t *)&sio_config_data[52];
                v21 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v21 = *(uint32_t *)&sio_config_data[48];
                v22 = sio_config_data[56];
                *(uint32_t *)(v21 + 4) = v20;
                *(uint8_t *)(v21 + 8) = v22;
              }
              if ( *a1 == 77 )
              {
                v23 = *(uint32_t *)&sio_config_data[64];
                v24 = 65 * (uint8_t)sio_controller_state[0] + 5334371;
                *(uint32_t *)v24 = *(uint32_t *)&sio_config_data[60];
                v25 = sio_config_data[68];
                *(uint32_t *)(v24 + 4) = v23;
                *(uint8_t *)(v24 + 8) = v25;
              }
              break;
            case 10:
              sio_build_multitap_response((uint8_t *)(v3 + 5334371), &sio_transfer_length);
              break;
            default:
              break;
          }
        }
        else
        {
          sio_multitap_command_buffer[(uint8_t)sio_controller_state[65
                                                                          * (uint8_t)sio_controller_state[0]
                                                                          + 2]] = *a1;
          if ( multitap_1 )
          {
            if ( !v1
              && *((uint8_t *)&sio_multitap_state + (uint8_t)(BYTE1(sio_multitap_slot_counter) + 1)) == sio_controller_state[2] )
            {
              LOBYTE(sio_multitap_slot_counter) = sio_controller_state[2] - 1;
              if ( (*a1 & 0x40) == 0x40 )
              {
                ++BYTE1(sio_multitap_slot_counter);
                sio_last_command_slot[0] = 0;
                sio_handle_config_command(
                  SBYTE1(sio_multitap_slot_counter),
                  (uint8_t)sio_controller_state[2] + 5334371,
                  *a1);
              }
            }
          }
          v26 = sio_multitap_slot_counter;
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 76
            && *a1 == 1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == (uint8_t)sio_multitap_slot_counter + 3 )
          {
            sio_response_buffer_config_byte[65 * (uint8_t)sio_controller_state[0]
                                          + (uint8_t)sio_multitap_slot_counter] = 7;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 70
            && *a1 == 1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == v26 + 3 )
          {
            sio_response_buffer_analog_byte[65 * (uint8_t)sio_controller_state[0] + v26] = 4;
            sio_response_buffer_config_byte[65 * (uint8_t)sio_controller_state[0] + v26] = 3;
            sio_response_buffer_config_byte2[65 * (uint8_t)sio_controller_state[0] + v26] = 1;
            sio_response_buffer_config_byte3[65 * (uint8_t)sio_controller_state[0] + v26] = 30;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 68
            && *a1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == v26 + 3
            && pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] != 1 )
          {
            v41 = BYTE1(sio_multitap_slot_counter);
            pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] = 1;
            cont_update_led_and_mode(v41);
            v26 = sio_multitap_slot_counter;
          }
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 68
            && !*a1
            && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == v26 + 3
            && pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] )
          {
            v42 = BYTE1(sio_multitap_slot_counter);
            pad_analog_mode_flags[BYTE1(sio_multitap_slot_counter)] = 0;
            cont_update_led_and_mode(v42);
            v26 = sio_multitap_slot_counter;
          }
          v27 = (uint8_t)sio_controller_state[0];
          if ( sio_last_command_slot[(uint8_t)sio_controller_state[0]] == 66 )
          {
            if ( (*a1 & 1) != 0
              && (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] == v26 + 3 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)] == 5 )
              {
                joy_issue_small_motor();
                v26 = sio_multitap_slot_counter;
              }
              v28 = g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)];
              if ( v28 && v28 <= 4 )
              {
                diSetEffectMagnitude(0, 1, 2, BYTE1(sio_multitap_slot_counter));
                v26 = sio_multitap_slot_counter;
              }
              v27 = (uint8_t)sio_controller_state[0];
              rumble_small_motor_state[2 * (uint8_t)sio_controller_state[0]] = *a1 & 1;
            }
            if ( sio_last_command_slot[v27] == 66
              && *a1
              && (uint8_t)sio_controller_state[65 * v27 + 2] == v26 + 4 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)] == 5 )
                joy_issue_big_motor();
              v29 = g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)];
              if ( v29 && v29 <= 4 )
                diSetEffectMagnitude(1, (uint8_t)*a1, 2, BYTE1(sio_multitap_slot_counter));
              rumble_big_motor_state[2 * (uint8_t)sio_controller_state[0]] = *a1;
            }
          }
        }
        v30 = 65 * (uint8_t)sio_controller_state[0];
        v31 = (uint8_t)sio_controller_state[v30 + 2];
        if ( v31 >= sio_transfer_length - 1 )
          sio_schedule_transfer(0, (char *)(v31 + v30 + 5334371));
        else
          sio_schedule_transfer(1, (char *)(v31 + v30 + 5334371));
        v32 = sio_transfer_length;
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        v33 = (uint8_t *)(65 * (uint8_t)sio_controller_state[0] + 5334370);
        v34 = (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] < v32;
      }
      else
      {
        if ( sio_controller_state[1] != 2 )
          return;
        if ( v4 == 1 )
        {
          if ( *a1 == 87 )
          {
            v35 = 87;
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
            if ( *a1 != 82 )
            {
              sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] = 0;
              return;
            }
            v1 = sio_controller_state[0];
            v35 = 82;
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
          v35 = memcard2_buffer[129024];
        }
        if ( v35 == 82 )
        {
          if ( v4 == 4 )
          {
            LOBYTE(v37) = 0;
            HIBYTE(v37) = *a1;
            memcard_current_address = v37;
            memcard2_buffer[129033] = *a1;
          }
          if ( v4 == 5 )
          {
            memcard_current_address |= (uint8_t)*a1;
            memcard2_buffer[129034] = *a1;
          }
          if ( v4 == 6 )
          {
            qmemcpy(
              &memcard2_buffer[129035],
              &sio_memcard_data_slot1[128
                                    * ((uint16_t)memcard_current_address
                                     + ((uint8_t)sio_controller_state[0] << 10))],
              0x80u);
            v38 = 0;
            memcard2_buffer[129163] = 0;
            v39 = &memcard2_buffer[129033];
            v40 = 130;
            do
            {
              v38 ^= *v39++;
              --v40;
              memcard2_buffer[129163] = v38;
            }
            while ( v40 );
          }
        }
        else if ( v35 == 87 )
        {
          if ( v1 )
            sio_memcard2_dirty_counter = 1;
          else
            sio_memcard1_dirty_counter = 1;
          if ( v4 > 3u && v4 < 0x86u )
            memcard2_buffer[v4 + 129026] = *a1;
          if ( v4 == 0x89 )
          {
            LOBYTE(v36) = 0;
            HIBYTE(v36) = memcard2_buffer[129030];
            memcard_current_address = (uint8_t)memcard2_buffer[129031] | v36;
            qmemcpy(
              &sio_memcard_data_slot1[128 * ((uint16_t)memcard_current_address + (v2 << 10))],
              &memcard2_buffer[129032],
              0x80u);
          }
        }
        if ( v4 >= (unsigned int)memcard2_buffer[129025] )
          sio_schedule_transfer(0, &memcard2_buffer[v4 + 129025]);
        else
          sio_schedule_transfer(1, &memcard2_buffer[v4 + 129025]);
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
        v33 = (uint8_t *)(65 * (uint8_t)sio_controller_state[0] + 5334370);
        v34 = (uint8_t)sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2] < (unsigned int)memcard2_buffer[129025];
      }
      if ( !v34 )
        *v33 = 0;
    }
    else
    {
      if ( *a1 == 1 )
      {
        sio_controller_state[1] = 1;
        ++sio_controller_state[65 * (uint8_t)sio_controller_state[0] + 2];
LABEL_9:
        sio_schedule_transfer(1, (char *)(65 * (uint8_t)sio_controller_state[0] + 5334371));
        return;
      }
      if ( *a1 == -127 )
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
        goto LABEL_9;
      }
      sio_schedule_transfer(0, (char *)(v3 + 5334371));
    }
  }
}

bool sio_controller_init(int16_t a1)
{
  bool result;

  if ( (a1 & 2) != 0 )
  {
    result = (a1 & 0x2000) != 0;
    sio_controller_state[0] = result;
  }
  else
  {
    sio_controller_slot_index = 0;
    sio_controller_state[2] = 0;
    sio_controller_state[0] = 0x80;
    return 0;
  }
  return result;
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
  FILE *v0;
  unsigned int i;
  unsigned int j;
  unsigned int k;
  FILE *v4;
  FILE *v5;
  FILE *v6;

  LOBYTE(v0) = sio_memcard_loaded;
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
    v4 = fopen((const char *)Memcard1, "rb");
    v5 = v4;
    if ( v4 )
    {
      fseek(v4, 0, 2);
      sio_memcard1_file_offset = ftell(v5) - 0x20000;
      fseek(v5, sio_memcard1_file_offset, 0);
      fread(sio_memcard_data_slot1, 1u, 0x20000u, v5);
      fclose(v5);
    }
    else
    {
      sio_memcard1_file_offset = 0;
    }
    v0 = fopen((const char *)Memcard2, "rb");
    v6 = v0;
    if ( v0 )
    {
      fseek(v0, 0, 2);
      sio_memcard2_file_offset = ftell(v6) - 0x20000;
      fseek(v6, sio_memcard2_file_offset, 0);
      fread(sio_memcard_data_slot2, 1u, 0x20000u, v6);
      LOBYTE(v0) = fclose(v6);
    }
    else
    {
      sio_memcard2_file_offset = 0;
    }
    sio_memcard_loaded = 1;
  }
  return (char)v0;
}

static char sio_memcard1_save()
{
  char result;
  FILE *v1;

  result = sio_memcard_loaded;
  if ( sio_memcard_loaded )
  {
    v1 = fopen((const char *)Memcard1, "wb");
    if ( v1 )
    {
      fseek(v1, sio_memcard1_file_offset, 0);
      fwrite(sio_memcard_data_slot1, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard1);
    }
  }
  return result;
}

static char sio_memcard2_save()
{
  char result;
  FILE *v1;

  result = sio_memcard_loaded;
  if ( sio_memcard_loaded )
  {
    v1 = fopen((const char *)Memcard2, "wb");
    if ( v1 )
    {
      fseek(v1, sio_memcard2_file_offset, 0);
      fwrite(sio_memcard_data_slot2, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard2);
    }
  }
  return result;
}

// Microsoft VisualC 2-14/net runtime
char sio_memcard_both_save()
{
  sio_memcard1_save();
  return sio_memcard2_save();
}

char sio_memcard_auto_save()
{
  int v0;

  v0 = sio_memcard1_dirty_counter;
  if ( sio_memcard1_dirty_counter )
    v0 = ++sio_memcard1_dirty_counter;
  if ( sio_memcard2_dirty_counter )
    ++sio_memcard2_dirty_counter;
  if ( v0 == 120 )
  {
    sio_memcard1_dirty_counter = 0;
    LOBYTE(v0) = sio_memcard1_save();
  }
  if ( sio_memcard2_dirty_counter == 120 )
  {
    sio_memcard2_dirty_counter = 0;
    LOBYTE(v0) = sio_memcard2_save();
  }
  return v0;
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

void sio_write_data_byte(int a1, char a2)
{
  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  sio_tx_fifo_data[(uint8_t)--sio_tx_fifo[0]] = a2;
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

static int16_t sio_read_halfword(int a1)
{
  char v1;
  int16_t v2;
  char v3;
  int16_t result;

  switch ( a1 )
  {
    case 0x1F801040:
      sio_read_data_byte();
      HIBYTE(v2) = v1;
      sio_read_data_byte();
      LOBYTE(v2) = v3;
      result = v2;
      break;
    case 0x1F801044:
      if ( sio_transfer_pending )
      {
        if ( hw_update_counter < (unsigned int)sio_transfer_timeout )
        {
          sio_transfer_pending = 0;
          sio_trigger_rx_ready_irq();
        }
      }
      result = sio0_mode_reg;
      break;
    case 0x1F801048:
      result = HIWORD(sio0_mode_reg);
      break;
    case 0x1F80104A:
      result = sio0_control_reg;
      break;
    case 0x1F80104E:
      result = HIWORD(sio0_control_reg);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

static int sio_read_word(int a1)
{
  char v2;
  uint16_t v3;
  char v4;
  uint8_t v5;
  int v6;
  uint8_t v7;

  if ( a1 == 0x1F801040 )
  {
    sio_read_data_byte();
    HIBYTE(v3) = v2;
    sio_read_data_byte();
    LOBYTE(v3) = v4;
    sio_read_data_byte();
    v6 = (v5 | (v3 << 8)) << 8;
    sio_read_data_byte();
    return v6 | v7;
  }
  else if ( a1 == 0x1F801044 )
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

int sio_read_register(int a1, char a2)
{
  int result;

  result = 0xFFFF;
  switch ( a2 )
  {
    case 1:
      sio_read_data_byte();
      return (uint8_t)result;
    case 2:
      return (uint16_t)sio_read_halfword(a1);
    case 4:
      return sio_read_word(a1);
  }
  return result;
}

int sio_freeze(const char *a1, int a2)
{
  char Buffer[64];

  sprintf(Buffer, "%s", a1);
  *(uint32_t *)&Buffer[3] = 263532;
  gzwrite(a2, (uint8_t *)Buffer, 7u);
  gzwrite(a2, (uint8_t *)sio_freeze_state, 0x214u);
  gzwrite(a2, (uint8_t *)sio_controller_state, 0x84u);
  gzwrite(a2, (uint8_t *)sio_memcard_data_slot1, 0x40104u);
  memset(Buffer, 0, sizeof(Buffer));
  *(uint32_t *)&Buffer[4] = sio_multitap_state;
  *(uint16_t *)&Buffer[8] = sio_multitap_slot_counter;
  *(uint32_t *)Buffer = sio_transfer_length;
  Buffer[10] = multitap_1 & 1;
  return gzwrite(a2, (uint8_t *)Buffer, 0x40u);
}

void sio_unfreeze(int a1, uint32_t *a2)
{
  char *v2;
  char v3[4];
  int v4;
  int16_t v5;
  char v6;

  v2 = (char *)malloc(0x40104u);
  gzread(a2, v3, 7);
  gzread(a2, sio_freeze_state, 532);
  gzread(a2, sio_controller_state, 132);
  sio_memcard_both_save();
  gzread(a2, v2, 262404);
  gzread(a2, v3, 64);
  sio_multitap_state = v4;
  sio_transfer_length = *(uint32_t *)v3;
  LOWORD(sio_multitap_slot_counter) = v5;
  multitap_1 = v6 & 1;
  free(v2);
}

char * sio_for_netplay(uint8_t a1)
{
  return &netplay_memcard_buffer[0x20000 * a1];
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
