#include "pch.h"
char __cdecl sub_430D70(const void *a1, unsigned int a2, int a3, int a4)
{
  HANDLE EventA; // ebx
  _DWORD v6[20]; // [esp+Ch] [ebp-50h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v6, 0, sizeof(v6));
  LOBYTE(v6[2]) = cdrom_target;
  v6[4] = a3;
  BYTE1(v6[5]) = a2;
  BYTE1(v6[2]) = cdrom_lun;
  BYTE2(v6[0]) = cdrom_hain;
  LOBYTE(v6[0]) = 2;
  HIBYTE(v6[0]) = 72;
  v6[3] = a4;
  LOBYTE(v6[5]) = 14;
  v6[6] = EventA;
  qmemcpy(&v6[12], a1, a2);
  ResetEvent(EventA);
  if ( !dword_4FFF68(v6) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(v6[0]) != 1 )
    return 1;
  CloseHandle(EventA);
  return 0;
}
