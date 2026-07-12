#include "pch.h"
int sub_4315A0()
{
  HANDLE EventA; // esi
  _BYTE v2[10]; // [esp+8h] [ebp-5Ch] BYREF
  _BYTE v3[2]; // [esp+12h] [ebp-52h] BYREF
  _DWORD v4[20]; // [esp+14h] [ebp-50h] BYREF

  v2[0] = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 8;
  v2[4] = 0;
  v2[5] = 0;
  v2[6] = 0;
  v2[7] = 0;
  v2[8] = 0;
  v2[9] = 0;
  qmemcpy(v3, "\t0", sizeof(v3));
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v4, 0, sizeof(v4));
  BYTE2(v4[0]) = cdrom_hain;
  LOBYTE(v4[2]) = cdrom_target;
  LOBYTE(v4[0]) = 2;
  BYTE1(v4[2]) = cdrom_lun;
  HIBYTE(v4[0]) = 64;
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
