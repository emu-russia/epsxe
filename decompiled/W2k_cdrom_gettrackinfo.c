#include "pch.h"
char W2k_cdrom_gettrackinfo()
{
  HANDLE EventA; // esi
  char result; // al
  unsigned __int8 v2; // bl
  int v3; // esi
  char v4; // [esp+12h] [ebp-5Eh]
  char v5; // [esp+13h] [ebp-5Dh]
  unsigned __int8 v6; // [esp+13h] [ebp-5Dh]
  unsigned int v7; // [esp+14h] [ebp-5Ch] BYREF
  int v8; // [esp+18h] [ebp-58h]
  int v9; // [esp+1Ch] [ebp-54h] BYREF
  DWORD BytesReturned[20]; // [esp+20h] [ebp-50h] BYREF

  v5 = 10;
  v4 = 0;
  do
  {
    if ( v4 )
      break;
    memset(BytesReturned, 0, sizeof(BytesReturned));
    memset(&byte_4FFC40, 0, 0x324u);
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    LOBYTE(BytesReturned[0]) = 2;
    BYTE2(BytesReturned[0]) = byte_457338;
    LOBYTE(BytesReturned[2]) = byte_4FD9D0;
    BYTE1(BytesReturned[2]) = byte_4FD9D4;
    HIBYTE(BytesReturned[0]) = 72;
    BytesReturned[3] = 804;
    BytesReturned[4] = (DWORD)&byte_4FFC40;
    LOWORD(BytesReturned[5]) = 2574;
    BytesReturned[6] = (DWORD)EventA;
    LOWORD(BytesReturned[12]) = 67;
    HIBYTE(BytesReturned[13]) = 3;
    LOBYTE(BytesReturned[14]) = 36;
    ResetEvent(EventA);
    if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    CloseHandle(EventA);
    if ( BYTE1(BytesReturned[0]) == 1 )
      v4 = 1;
    ++v5;
  }
  while ( v5 );
  if ( BYTE1(BytesReturned[0]) != 1 )
    return dbg_print(" * gettrackinfo error[%d]\n", BYTE1(BytesReturned[0]));
  dbg_print(" * First/Last track: %d %d\n", (unsigned __int8)byte_4FFC42, (unsigned __int8)byte_4FFC43);
  result = byte_4FFC43 - byte_4FFC42 + 1;
  v2 = 0;
  v6 = result;
  byte_4FD9E3 = result;
  LOBYTE(v8) = 0;
  if ( byte_4FFC43 - byte_4FFC42 != 0xFF )
  {
    do
    {
      v3 = (unsigned __int8)v8;
      dbg_print(" * Track %d: ", (unsigned __int8)byte_4FFC46[8 * (unsigned __int8)v8]);
      if ( (byte_4FFC45[8 * v3] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !v2 )
          nocd = 2;
      }
      sub_431110(&v7, (unsigned __int8 *)(8 * v3 + 5241928));
      v7 += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", v3, (unsigned __int8)(v7 / 0x4B / 0x3C), v7 / 0x4B % 0x3C, v7 % 0x4B);
      sub_431110(&v7, (unsigned __int8 *)(8 * v3 + 5241928));
      sub_431110(&v9, (unsigned __int8 *)(8 * v3 + 5241936));
      dbg_print(" Length %02d:%02d\n", (v9 - v7) / 0x4B / 0x3C, (v9 - v7) / 0x4B % 0x3C);
      result = v6;
      LOBYTE(v8) = ++v2;
    }
    while ( v2 < v6 );
  }
  return result;
}
