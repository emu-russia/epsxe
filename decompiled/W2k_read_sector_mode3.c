#include "pch.h"
bool __cdecl W2k_read_sector_mode3(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5)
{
  char v6; // [esp+0h] [ebp-Ch] BYREF
  __int16 v7; // [esp+1h] [ebp-Bh]
  char v8; // [esp+3h] [ebp-9h]
  char v9; // [esp+4h] [ebp-8h]
  __int16 v10; // [esp+5h] [ebp-7h]
  char v11; // [esp+7h] [ebp-5h]
  __int16 v12; // [esp+8h] [ebp-4h]
  __int16 v13; // [esp+Ah] [ebp-2h]

  v11 = 0;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v7 = 4;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = 2;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 16 * a4);
}
