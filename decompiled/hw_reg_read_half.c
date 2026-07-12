#include "pch.h"
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
          LOWORD(v1) = LOWORD(dword_50BFD0[4 * ((a1 >> 4) & 3)])
                     + ((dword_50BFD4[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : dword_455940)
                     - ((dword_50BFD4[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : hw_update_counter);
          return v1;
        case 0x1F801114u:
        case 0x1F801124u:
        case 0x1F801134u:
LABEL_33:
          LOWORD(v1) = dword_50BFD4[4 * ((a1 >> 4) & 3)];
          return v1;
        case 0x1F801118u:
        case 0x1F801128u:
        case 0x1F801138u:
          goto LABEL_34;
        case 0x1F801120u:
          LOWORD(v9) = dword_455940;
          v10 = 4 * ((a1 >> 4) & 3);
          v11 = dword_50BFD0[v10];
          v12 = dword_50BFD4[v10] & 0x200;
          if ( v12 )
            v9 = (unsigned int)dword_455940 >> 3;
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
      LOWORD(v1) = dword_50BFD8[4 * ((a1 >> 4) & 3)];
    }
    else
    {
      HIWORD(v2) = 0;
      switch ( a1 )
      {
        case 0x1F801014u:
          LOWORD(v1) = *(_WORD *)&byte_516600[(unsigned __int16)a1];
          break;
        case 0x1F801040u:
          sio_data_read();
          HIBYTE(v4) = v3;
          sio_data_read();
          LOBYTE(v4) = v1;
          LOWORD(v1) = v4;
          break;
        case 0x1F801044u:
          if ( dword_4FD86C && hw_update_counter < (unsigned int)dword_4FD864 )
          {
            dword_4FD86C = 0;
            sub_421FD0();
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
          if ( *(_DWORD *)dword_4FD878 && (unsigned int)hw_update_counter < *(_DWORD *)dword_4FD870 )
          {
            *(_DWORD *)int_reg |= *(_DWORD *)dword_4FD878;
            *(_DWORD *)dword_4FD878 = 0;
          }
          LOWORD(v1) = *(_WORD *)int_reg | forcepad;
          break;
        case 0x1F801074u:
          LOWORD(v1) = int_mask;
          break;
        case 0x1F801100u:
          v5 = 4 * ((a1 >> 4) & 3);
          LOWORD(v2) = dword_50BFD0[v5];
          v6 = dword_50BFD4[v5] & 0x100;
          v7 = 512;
          if ( !v6 )
            v7 = dword_455940;
          v8 = v7 + v2;
          if ( v6 )
            v1 = v8 - (hw_update_counter << 9) / (unsigned int)dword_455940;
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
