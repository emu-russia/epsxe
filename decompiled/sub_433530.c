#include "pch.h"
BOOL sub_433530()
{
  HANDLE EventA; // esi
  _DWORD v2[20]; // [esp+8h] [ebp-50h] BYREF

  BYTE1(dword_456FCC) = (32 * cdrom_lun) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v2, 0, sizeof(v2));
  BYTE2(v2[0]) = cdrom_hain;
  LOBYTE(v2[2]) = cdrom_target;
  BYTE1(v2[2]) = cdrom_lun;
  LOBYTE(v2[0]) = 2;
  HIBYTE(v2[0]) = 80;
  LOWORD(v2[5]) = 2574;
  v2[3] = 0;
  v2[4] = 0;
  v2[6] = EventA;
  v2[12] = dword_456FCC;
  v2[13] = dword_456FD0;
  LOWORD(v2[14]) = word_456FD4;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(v2) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(v2[0]) != 1 )
    printf(" * Resume cdrom error. \n");
  return CloseHandle(EventA);
}
