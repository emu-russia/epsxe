#include "pch.h"
char __cdecl W9x_play_cdda(unsigned int a1, int a2, unsigned __int8 track_by_msf)
{
  char result; // al
  unsigned __int8 v4; // bl
  HANDLE EventA; // esi
  _DWORD v6[20]; // [esp+4h] [ebp-50h] BYREF

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v4 = a2;
    track_by_msf = W9x_find_track_by_msf(a1, a2);
    BYTE1(dword_456FB8) = track_by_msf;
    HIBYTE(dword_456FB4) = a1;
    LOBYTE(dword_456FB8) = v4;
    W9x_bcd_to_dword(&a2, (unsigned __int8 *)(8 * (unsigned __int8)dword_4FD9BC + 5262504));
    LOBYTE(word_456FBC) = (a2 + 150) % 0x4Bu;
    BYTE2(dword_456FB8) = (a2 + 150) / 0x4Bu / 0x3C;
    HIBYTE(dword_456FB8) = (a2 + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(v6, 0, sizeof(v6));
    BYTE2(v6[0]) = cdrom_haid;
    LOBYTE(v6[2]) = cdrom_target;
    BYTE1(v6[2]) = cdrom_lun;
    LOBYTE(v6[0]) = 2;
    HIBYTE(v6[0]) = 72;
    LOWORD(v6[5]) = 2574;
    v6[3] = 0;
    v6[4] = 0;
    v6[6] = EventA;
    v6[12] = dword_456FB4;
    v6[13] = dword_456FB8;
    LOWORD(v6[14]) = word_456FBC;
    ResetEvent(EventA);
    if ( !SendASPI32Command_cb(v6) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(v6[0]) == 1 )
      dword_4FD9C0 = 1;
    else
      return printf(" * Play cdda error (%d, %d, %d) \n", (unsigned __int8)a1, v4, track_by_msf);
  }
  return result;
}
