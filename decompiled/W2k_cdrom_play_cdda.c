#include "pch.h"
char __cdecl W2k_cdrom_play_cdda(unsigned int a1, int a2, unsigned __int8 a3)
{
  char result; // al
  unsigned __int8 v4; // bl
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+4h] [ebp-50h] BYREF

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v4 = a2;
    a3 = sub_4342D0(a1, a2);
    BYTE1(dword_457350) = a3;
    HIBYTE(dword_45734C) = a1;
    LOBYTE(dword_457350) = v4;
    sub_431110(&a2, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
    LOBYTE(word_457354) = (a2 + 150) % 0x4Bu;
    BYTE2(dword_457350) = (a2 + 150) / 0x4Bu / 0x3C;
    HIBYTE(dword_457350) = (a2 + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(BytesReturned, 0, sizeof(BytesReturned));
    BYTE2(BytesReturned[0]) = byte_457338;
    LOBYTE(BytesReturned[2]) = byte_4FD9D0;
    BYTE1(BytesReturned[2]) = byte_4FD9D4;
    LOBYTE(BytesReturned[0]) = 2;
    HIBYTE(BytesReturned[0]) = 72;
    LOWORD(BytesReturned[5]) = 2574;
    BytesReturned[3] = 0;
    BytesReturned[4] = 0;
    BytesReturned[6] = (DWORD)EventA;
    BytesReturned[12] = dword_45734C;
    BytesReturned[13] = dword_457350;
    LOWORD(BytesReturned[14]) = word_457354;
    ResetEvent(EventA);
    if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(BytesReturned[0]) == 1 )
      dword_4FD9D8 = 1;
    else
      return printf(" * W2k play cdda error (%d, %d, %d) \n", (unsigned __int8)a1, v4, a3);
  }
  return result;
}
