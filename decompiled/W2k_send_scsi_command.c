#include "pch.h"
bool __cdecl W2k_send_scsi_command(const void *a1, unsigned int a2, DWORD a3, DWORD a4)
{
  HANDLE EventA; // ebx
  DWORD BytesReturned[20]; // [esp+Ch] [ebp-50h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  BytesReturned[4] = a3;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  BYTE2(BytesReturned[0]) = byte_457338;
  BytesReturned[3] = a4;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 72;
  LOWORD(BytesReturned[5]) = 3086;
  BytesReturned[6] = (DWORD)EventA;
  qmemcpy(&BytesReturned[12], a1, a2);
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  CloseHandle(EventA);
  return BYTE1(BytesReturned[0]) != 1;
}
