#include "pch.h"
void __cdecl sio_command(char *a1)
{
  char v1; // bl
  int v2; // esi
  int v3; // eax
  unsigned __int8 v4; // dl
  char v6; // cl
  bool v7; // zf
  int v8; // edx
  int v9; // eax
  char v10; // cl
  int v11; // ecx
  int v12; // edx
  char v13; // al
  int v14; // eax
  int v15; // ecx
  char v16; // dl
  int v17; // edx
  int v18; // eax
  char v19; // cl
  int v20; // ecx
  int v21; // edx
  char v22; // al
  int v23; // eax
  int v24; // ecx
  char v25; // dl
  unsigned __int8 v26; // si
  int v27; // eax
  unsigned int v28; // ecx
  unsigned int v29; // ecx
  int v30; // eax
  unsigned int v31; // ecx
  unsigned int v32; // edx
  _BYTE *v33; // eax
  bool v34; // cf
  char v35; // al
  __int16 v36; // ax
  __int16 v37; // ax
  char v38; // al
  char *v39; // ecx
  int v40; // esi
  unsigned __int8 v41; // [esp-4h] [ebp-14h]
  unsigned __int8 v42; // [esp-4h] [ebp-14h]
  char v43; // [esp+14h] [ebp+4h]

  v1 = sio_controller_state[0];
  if ( sio_controller_state[0] >= 0 )
  {
    v2 = (unsigned __int8)sio_controller_state[0];
    v3 = 65 * (unsigned __int8)sio_controller_state[0];
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
            sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] = 0;
            return;
          }
          v6 = multitap_1;
          v7 = multitap_1 == 0;
          v43 = dword_456048[(unsigned __int8)sio_controller_state[0]];
          sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] = 0;
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
              *(_WORD *)(v3 + 5334371) = -1;
              if ( *a1 != 66 )
                sio_controller_response_buffer[65 * (unsigned __int8)sio_controller_state[0]] = *a1;
              sio_transfer_length = 2;
              break;
            case 1:
              sub_42D010(v2, (_BYTE *)(v3 + 5334371));
              if ( *a1 != 66 )
                sio_controller_response_buffer[65 * (unsigned __int8)sio_controller_state[0]] = *a1;
              sio_transfer_length = 5;
              if ( *a1 == 69 )
              {
                sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 3] = 1;
                sio_controller_response_buffer[65 * (unsigned __int8)sio_controller_state[0]] = -13;
                byte_516565[65 * (unsigned __int8)sio_controller_state[0]] = 90;
                byte_516566[65 * (unsigned __int8)sio_controller_state[0]] = 0;
                byte_516567[65 * (unsigned __int8)sio_controller_state[0]] = 0;
              }
              break;
            case 2:
              if ( !dword_4FD8E0[v2] )
              {
                sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                if ( *a1 != 66 )
                  sio_controller_response_buffer[65 * (unsigned __int8)sio_controller_state[0]] = *a1;
                goto LABEL_30;
              }
              sub_42D3C0(v2, (_BYTE *)(v3 + 5334371));
              sio_transfer_length = 7;
              break;
            case 3:
              if ( dword_4FD8E0[v2] )
              {
                sub_42D440(v2, (_BYTE *)(v3 + 5334371));
                sio_transfer_length = 9;
              }
              else
              {
                sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                if ( *a1 == 66 )
                {
LABEL_30:
                  sio_transfer_length = 5;
                }
                else
                {
                  sio_controller_response_buffer[65 * (unsigned __int8)sio_controller_state[0]] = *a1;
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
                if ( dword_4FD8E0[v2] )
                {
                  sub_42D0E0(v2, (_BYTE *)(v3 + 0x516563));
                }
                else
                {
                  sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                  *(_DWORD *)&byte_516568[65 * (unsigned __int8)sio_controller_state[0]] = -2139062144;
                }
              }
              sio_transfer_length = 9;
              byte_526820[0] = 1;
              byte_526821[0] = *a1;
              if ( *a1 == 68 )
              {
                v8 = *(_DWORD *)&sio_config_data[4];
                v9 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v9 = *(_DWORD *)sio_config_data;
                v10 = sio_config_data[8];
                *(_DWORD *)(v9 + 4) = v8;
                *(_BYTE *)(v9 + 8) = v10;
              }
              if ( *a1 == 69 )
              {
                v11 = *(_DWORD *)&sio_config_data[16];
                v12 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v12 = *(_DWORD *)&sio_config_data[12];
                v13 = sio_config_data[20];
                *(_DWORD *)(v12 + 4) = v11;
                *(_BYTE *)(v12 + 8) = v13;
                if ( dword_4FD8E0[(unsigned __int8)sio_controller_state[0]] == 1 )
                  byte_516568[65 * (unsigned __int8)sio_controller_state[0]] = 1;
              }
              if ( *a1 == 70 )
              {
                v14 = *(_DWORD *)&sio_config_data[28];
                v15 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v15 = *(_DWORD *)&sio_config_data[24];
                v16 = sio_config_data[32];
                *(_DWORD *)(v15 + 4) = v14;
                *(_BYTE *)(v15 + 8) = v16;
              }
              if ( *a1 == 71 )
              {
                v17 = *(_DWORD *)&sio_config_data[40];
                v18 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v18 = *(_DWORD *)&sio_config_data[36];
                v19 = sio_config_data[44];
                *(_DWORD *)(v18 + 4) = v17;
                *(_BYTE *)(v18 + 8) = v19;
              }
              if ( *a1 == 76 )
              {
                v20 = *(_DWORD *)&sio_config_data[52];
                v21 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v21 = *(_DWORD *)&sio_config_data[48];
                v22 = sio_config_data[56];
                *(_DWORD *)(v21 + 4) = v20;
                *(_BYTE *)(v21 + 8) = v22;
              }
              if ( *a1 == 77 )
              {
                v23 = *(_DWORD *)&sio_config_data[64];
                v24 = 65 * (unsigned __int8)sio_controller_state[0] + 5334371;
                *(_DWORD *)v24 = *(_DWORD *)&sio_config_data[60];
                v25 = sio_config_data[68];
                *(_DWORD *)(v24 + 4) = v23;
                *(_BYTE *)(v24 + 8) = v25;
              }
              break;
            case 10:
              sio_build_multitap_response((_BYTE *)(v3 + 5334371), &sio_transfer_length);
              break;
            default:
              break;
          }
        }
        else
        {
          byte_526820[(unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2]] = *a1;
          if ( multitap_1 )
          {
            if ( !v1
              && *((_BYTE *)&sio_multitap_state + (unsigned __int8)(BYTE1(sio_multitap_slot_counter) + 1)) == sio_controller_state[2] )
            {
              LOBYTE(sio_multitap_slot_counter) = sio_controller_state[2] - 1;
              if ( (*a1 & 0x40) == 0x40 )
              {
                ++BYTE1(sio_multitap_slot_counter);
                sio_last_command_slot[0] = 0;
                sio_handle_config_command(
                  SBYTE1(sio_multitap_slot_counter),
                  (unsigned __int8)sio_controller_state[2] + 5334371,
                  *a1);
              }
            }
          }
          v26 = sio_multitap_slot_counter;
          if ( sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] == 76
            && *a1 == 1
            && (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] == (unsigned __int8)sio_multitap_slot_counter + 3 )
          {
            byte_516569[65 * (unsigned __int8)sio_controller_state[0] + (unsigned __int8)sio_multitap_slot_counter] = 7;
          }
          if ( sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] == 70
            && *a1 == 1
            && (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] == v26 + 3 )
          {
            byte_516568[65 * (unsigned __int8)sio_controller_state[0] + v26] = 4;
            byte_516569[65 * (unsigned __int8)sio_controller_state[0] + v26] = 3;
            byte_51656A[65 * (unsigned __int8)sio_controller_state[0] + v26] = 1;
            byte_51656B[65 * (unsigned __int8)sio_controller_state[0] + v26] = 30;
          }
          if ( sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] == 68
            && *a1
            && (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] == v26 + 3
            && dword_4FD8E0[BYTE1(sio_multitap_slot_counter)] != 1 )
          {
            v41 = BYTE1(sio_multitap_slot_counter);
            dword_4FD8E0[BYTE1(sio_multitap_slot_counter)] = 1;
            sub_42D620(v41);
            v26 = sio_multitap_slot_counter;
          }
          if ( sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] == 68
            && !*a1
            && (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] == v26 + 3
            && dword_4FD8E0[BYTE1(sio_multitap_slot_counter)] )
          {
            v42 = BYTE1(sio_multitap_slot_counter);
            dword_4FD8E0[BYTE1(sio_multitap_slot_counter)] = 0;
            sub_42D620(v42);
            v26 = sio_multitap_slot_counter;
          }
          v27 = (unsigned __int8)sio_controller_state[0];
          if ( sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] == 66 )
          {
            if ( (*a1 & 1) != 0
              && (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] == v26 + 3 )
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
              v27 = (unsigned __int8)sio_controller_state[0];
              byte_4FC468[2 * (unsigned __int8)sio_controller_state[0]] = *a1 & 1;
            }
            if ( sio_last_command_slot[v27] == 66
              && *a1
              && (unsigned __int8)sio_controller_state[65 * v27 + 2] == v26 + 4 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)] == 5 )
                joy_issue_big_motor();
              v29 = g_PlayerDeviceMap1[BYTE1(sio_multitap_slot_counter)];
              if ( v29 && v29 <= 4 )
                diSetEffectMagnitude(1, (unsigned __int8)*a1, 2, BYTE1(sio_multitap_slot_counter));
              byte_4FC469[2 * (unsigned __int8)sio_controller_state[0]] = *a1;
            }
          }
        }
        v30 = 65 * (unsigned __int8)sio_controller_state[0];
        v31 = (unsigned __int8)sio_controller_state[v30 + 2];
        if ( v31 >= sio_transfer_length - 1 )
          sio_schedule_transfer(0, (char *)(v31 + v30 + 5334371));
        else
          sio_schedule_transfer(1, (char *)(v31 + v30 + 5334371));
        v32 = sio_transfer_length;
        ++sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2];
        v33 = (_BYTE *)(65 * (unsigned __int8)sio_controller_state[0] + 5334370);
        v34 = (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] < v32;
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
            byte_547060[129024] = 87;
            byte_547060[129025] = -118;
            byte_547060[129026] = 0;
            byte_547060[129027] = 90;
            byte_547060[129028] = 93;
            byte_547060[129029] = 0;
            byte_547060[129160] = 92;
            byte_547060[129161] = 93;
            byte_547060[129162] = 71;
          }
          else
          {
            if ( *a1 != 82 )
            {
              sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] = 0;
              return;
            }
            v1 = sio_controller_state[0];
            v35 = 82;
            byte_547060[129024] = 82;
            byte_547060[129025] = -116;
            byte_547060[129026] = 0;
            byte_547060[129027] = 90;
            byte_547060[129028] = 93;
            byte_547060[129029] = 0;
            byte_547060[129030] = 0;
            byte_547060[129031] = 92;
            byte_547060[129032] = 93;
            byte_547060[129164] = 71;
          }
        }
        else
        {
          v35 = byte_547060[129024];
        }
        if ( v35 == 82 )
        {
          if ( v4 == 4 )
          {
            LOBYTE(v37) = 0;
            HIBYTE(v37) = *a1;
            word_566962 = v37;
            byte_547060[129033] = *a1;
          }
          if ( v4 == 5 )
          {
            word_566962 |= (unsigned __int8)*a1;
            byte_547060[129034] = *a1;
          }
          if ( v4 == 6 )
          {
            qmemcpy(
              &byte_547060[129035],
              &sio_memcard_data_slot1[128
                                    * ((unsigned __int16)word_566962 + ((unsigned __int8)sio_controller_state[0] << 10))],
              0x80u);
            v38 = 0;
            byte_547060[129163] = 0;
            v39 = &byte_547060[129033];
            v40 = 130;
            do
            {
              v38 ^= *v39++;
              --v40;
              byte_547060[129163] = v38;
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
            byte_547060[v4 + 129026] = *a1;
          if ( v4 == 0x89 )
          {
            LOBYTE(v36) = 0;
            HIBYTE(v36) = byte_547060[129030];
            word_566962 = (unsigned __int8)byte_547060[129031] | v36;
            qmemcpy(
              &sio_memcard_data_slot1[128 * ((unsigned __int16)word_566962 + (v2 << 10))],
              &byte_547060[129032],
              0x80u);
          }
        }
        if ( v4 >= (unsigned int)byte_547060[129025] )
          sio_schedule_transfer(0, &byte_547060[v4 + 129025]);
        else
          sio_schedule_transfer(1, &byte_547060[v4 + 129025]);
        ++sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2];
        v33 = (_BYTE *)(65 * (unsigned __int8)sio_controller_state[0] + 5334370);
        v34 = (unsigned __int8)sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] < (unsigned int)byte_547060[129025];
      }
      if ( !v34 )
        *v33 = 0;
    }
    else
    {
      if ( *a1 == 1 )
      {
        sio_controller_state[1] = 1;
        ++sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2];
LABEL_9:
        sio_schedule_transfer(1, (char *)(65 * (unsigned __int8)sio_controller_state[0] + 5334371));
        return;
      }
      if ( *a1 == -127 )
      {
        if ( byte_4557A8 )
        {
          sio_controller_state[1] = 2;
          ++sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2];
        }
        else
        {
          sio_controller_state[65 * (unsigned __int8)sio_controller_state[0] + 2] = 0;
        }
        goto LABEL_9;
      }
      sio_schedule_transfer(0, (char *)(v3 + 5334371));
    }
  }
}
