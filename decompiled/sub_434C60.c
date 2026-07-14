#include "pch.h"
int sub_434C60()
{
  HANDLE EventA; // esi
  _BYTE v2[4]; // [esp+8h] [ebp-5Ch] BYREF
  char v3[8]; // [esp+Ch] [ebp-58h] BYREF
  DWORD BytesReturned[20]; // [esp+14h] [ebp-50h] BYREF

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
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  HIBYTE(BytesReturned[0]) = 68;
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
