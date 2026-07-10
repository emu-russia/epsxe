#include "pch.h"
int __cdecl sub_430E40(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3)
{
  HANDLE EventA; // esi
  int result; // eax
  char v5; // dl
  int v6; // esi
  _DWORD *v7; // ecx
  int v8; // ecx
  _DWORD v9[20]; // [esp+Ch] [ebp-B4h] BYREF
  _DWORD v10[25]; // [esp+5Ch] [ebp-64h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v9, 0, sizeof(v9));
  memset(v10, 0, sizeof(v10));
  LOBYTE(v9[2]) = a2;
  LOBYTE(v9[0]) = 2;
  BYTE2(v9[0]) = a1;
  BYTE1(v9[2]) = a3;
  HIBYTE(v9[0]) = 72;
  v9[3] = 100;
  v9[4] = v10;
  LOWORD(v9[5]) = 1550;
  v9[6] = EventA;
  LOBYTE(v9[12]) = 18;
  LOBYTE(v9[13]) = 100;
  ResetEvent(EventA);
  if ( !dword_4FFF68(v9) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  result = CloseHandle(EventA);
  if ( BYTE1(v9[0]) == 1 )
  {
    v5 = HIBYTE(dword_4FD9BC);
    v6 = v10[4];
    result = HIBYTE(dword_4FD9BC) << 6;
    *(int *)((char *)&dword_504FE0 + result) = v10[2];
    *(int *)((char *)&dword_504FE4 + result) = v10[3];
    byte_504FE8[result] = 0;
    v7 = (_DWORD *)((char *)&unk_504FE9 + result);
    *v7 = v6;
    v7[1] = v10[5];
    v7[2] = v10[6];
    v7[3] = v10[7];
    v8 = v10[8];
    byte_504FF9[result] = 0;
    *(int *)((char *)&dword_504FFA + result) = v8;
    byte_504FFE[result] = 0;
    qmemcpy((char *)&unk_504FFF + result, &v10[9], 0x14u);
    byte_505013[result] = 0;
    *(int *)((char *)&dword_505014 + result) = a1;
    *(int *)((char *)&dword_505018 + result) = a2;
    *(int *)((char *)&dword_50501C + result) = a3;
    HIBYTE(dword_4FD9BC) = v5 + 1;
  }
  return result;
}
