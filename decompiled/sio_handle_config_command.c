#include "pch.h"
int __cdecl sio_handle_config_command(char a1, int a2, char a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  char v7; // dl
  int v8; // ecx
  int v10; // edx
  _BYTE v11[9]; // [esp+4h] [ebp-10h] BYREF

  v3 = dword_456048[(unsigned __int8)a1];
  if ( !v3 )
    goto LABEL_24;
  v4 = v3 - 1;
  if ( v4 )
  {
    if ( v4 == 3 )
    {
      sio_last_command_slot[(unsigned __int8)sio_controller_state[0]] = a3;
      if ( a3 == 66 || a3 == 67 )
      {
        if ( dword_4FD8E0[(unsigned __int8)a1] )
        {
          sub_42D0E0(a1, v11);
        }
        else
        {
          sub_42D010(a1, v11);
          *(_DWORD *)&v11[5] = -2139062144;
        }
      }
      switch ( a3 )
      {
        case 'D':
          v5 = *(_DWORD *)sio_config_data;
          v6 = *(_DWORD *)&sio_config_data[4];
          v7 = sio_config_data[8];
          goto LABEL_17;
        case 'E':
          *(_DWORD *)v11 = *(_DWORD *)&sio_config_data[12];
          *(_DWORD *)&v11[4] = *(_DWORD *)&sio_config_data[16];
          v8 = dword_4FD8E0[(unsigned __int8)a1];
          v11[8] = sio_config_data[20];
          if ( v8 == 1 )
            v11[5] = 1;
          break;
        case 'F':
          v5 = *(_DWORD *)&sio_config_data[24];
          v6 = *(_DWORD *)&sio_config_data[28];
          v7 = sio_config_data[32];
          goto LABEL_17;
        case 'G':
          v5 = *(_DWORD *)&sio_config_data[36];
          v6 = *(_DWORD *)&sio_config_data[40];
          v7 = sio_config_data[44];
          goto LABEL_17;
        case 'L':
          v5 = *(_DWORD *)&sio_config_data[60];
          v6 = *(_DWORD *)&sio_config_data[64];
          v7 = sio_config_data[68];
          goto LABEL_17;
        case 'M':
          v5 = *(_DWORD *)&sio_config_data[48];
          v6 = *(_DWORD *)&sio_config_data[52];
          v7 = sio_config_data[56];
LABEL_17:
          *(_DWORD *)v11 = v5;
          *(_DWORD *)&v11[4] = v6;
          v11[8] = v7;
          break;
        default:
          break;
      }
      v10 = *(_DWORD *)&v11[5];
      *(_DWORD *)a2 = *(_DWORD *)&v11[1];
      *(_DWORD *)(a2 + 4) = v10;
      return a2;
    }
LABEL_24:
    *(_BYTE *)(a2 + 3) = -1;
    *(_BYTE *)(a2 + 2) = -1;
    *(_BYTE *)(a2 + 1) = 90;
    *(_BYTE *)a2 = 65;
    *(_DWORD *)(a2 + 4) = 0x80808080;
    return a2 + 4;
  }
  sub_42D010(a1, v11);
  if ( a3 != 66 )
    v11[1] = a3;
  if ( a3 == 69 )
  {
    *(_DWORD *)v11 = *(_DWORD *)&sio_config_data[72];
    v11[4] = byte_4557FC;
  }
  *(_DWORD *)a2 = *(_DWORD *)&v11[1];
  *(_DWORD *)(a2 + 4) = 0x80808080;
  return a2 + 4;
}
