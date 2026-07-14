#include "pch.h"
char W9x_cdrom_stop()
{
  char result; // al
  HANDLE EventA; // esi
  _DWORD v2[20]; // [esp+0h] [ebp-50h] BYREF

  BYTE1(dword_456FC0) = (32 * cdrom_lun) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = dword_4FD9C0;
    if ( dword_4FD9C0 )
    {
      dword_4FD9C0 = 0;
      EventA = CreateEventA(nullptr, 1, 0, nullptr);
      memset(v2, 0, sizeof(v2));
      BYTE2(v2[0]) = cdrom_haid;
      LOBYTE(v2[2]) = cdrom_target;
      BYTE1(v2[2]) = cdrom_lun;
      LOBYTE(v2[0]) = 2;
      HIBYTE(v2[0]) = 80;
      LOWORD(v2[5]) = 2574;
      v2[3] = 0;
      v2[4] = 0;
      v2[6] = EventA;
      v2[12] = dword_456FC0;
      v2[13] = dword_456FC4;
      LOWORD(v2[14]) = word_456FC8;
      ResetEvent(EventA);
      if ( !SendASPI32Command_cb(v2) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(v2[0]) != 1 )
        printf(" * Stop cdrom error. \n");
      result = CloseHandle(EventA);
      dword_4FD9C4 = 1;
    }
  }
  return result;
}
