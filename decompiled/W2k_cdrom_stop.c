#include "pch.h"
char W2k_cdrom_stop()
{
  char result; // al
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+0h] [ebp-50h] BYREF

  BYTE1(dword_457358) = (32 * byte_4FD9D4) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = dword_4FD9D8;
    if ( dword_4FD9D8 )
    {
      dword_4FD9D8 = 0;
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
      BytesReturned[12] = dword_457358;
      BytesReturned[13] = dword_45735C;
      LOWORD(BytesReturned[14]) = word_457360;
      ResetEvent(EventA);
      if ( !sub_433CF0((DWORD)BytesReturned) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(BytesReturned[0]) != 1 )
        printf(" * W2k stop cdrom error. \n");
      result = CloseHandle(EventA);
      dword_4FD9DC = 1;
    }
  }
  return result;
}
