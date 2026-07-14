#include "pch.h"
int sub_434B80()
{
  HANDLE EventA; // esi
  _BYTE v2[10]; // [esp+8h] [ebp-5Ch] BYREF
  _BYTE v3[2]; // [esp+12h] [ebp-52h] BYREF
  DWORD BytesReturned[20]; // [esp+14h] [ebp-50h] BYREF

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
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  HIBYTE(BytesReturned[0]) = 64;
  BytesReturned[3] = 12;
  BytesReturned[4] = (DWORD)v2;
  LOWORD(BytesReturned[5]) = 1550;
  BytesReturned[6] = (DWORD)EventA;
  LOBYTE(BytesReturned[12]) = 21;
  LOBYTE(BytesReturned[13]) = 12;
  ResetEvent(EventA);
  if ( !scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(BytesReturned[0]) != 1 ? 4 : 1;
}
