#include "pch.h"
int W9x_disable_subchannel_mode()
{
  HANDLE EventA; // esi
  _BYTE v2[4]; // [esp+8h] [ebp-5Ch] BYREF
  char v3[8]; // [esp+Ch] [ebp-58h] BYREF
  _DWORD v4[20]; // [esp+14h] [ebp-50h] BYREF

  v2[0] = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 8;
  strcpy(v3, "S");
  v3[2] = 0;
  v3[3] = 0;
  v3[4] = 0;
  v3[5] = 0;
  v3[6] = 8;
  v3[7] = 0;
  byte_4FD9C8 = 0;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v4, 0, sizeof(v4));
  BYTE2(v4[0]) = cdrom_haid;
  LOBYTE(v4[2]) = cdrom_target;
  LOBYTE(v4[0]) = 2;
  BYTE1(v4[2]) = cdrom_lun;
  HIBYTE(v4[0]) = 68;
  v4[3] = 12;
  v4[4] = v2;
  LOWORD(v4[5]) = 1550;
  v4[6] = EventA;
  LOBYTE(v4[12]) = 21;
  LOBYTE(v4[13]) = 12;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(v4) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(v4[0]) != 1 ? 4 : 1;
}
