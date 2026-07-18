#include "pch.h"
BOOL sub_434000()
{
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+8h] [ebp-50h] BYREF

  BYTE1(dword_45733C) = (32 * byte_4FD9D4) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 80;
  LOWORD(BytesReturned[5]) = 2574;
  BytesReturned[3] = 0;
  BytesReturned[4] = 0;
  BytesReturned[6] = (DWORD)EventA;
  BytesReturned[12] = dword_45733C;
  BytesReturned[13] = dword_457340;
  LOWORD(BytesReturned[14]) = word_457344;
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(BytesReturned[0]) != 1 )
    printf(" * Resume cdrom error. \n");
  return CloseHandle(EventA);
}
