#include "pch.h"
int __cdecl sub_430E40(BYTE a1, BYTE a2, BYTE a3)
{
  HANDLE EventA; // esi
  int result; // eax
  char v5; // dl
  int v6; // esi
  char *v7; // ecx
  int v8; // ecx
  SRB_ExecSCSICmd v9; // [esp+Ch] [ebp-B4h] BYREF
  _DWORD v10[25]; // [esp+5Ch] [ebp-64h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&v9, 0, sizeof(v9));
  memset(v10, 0, sizeof(v10));
  v9.SRB_Target = a2;
  v9.SRB_Cmd = 2;
  v9.SRB_HaId = a1;
  v9.SRB_Lun = a3;
  v9.SRB_Flags = 72;
  v9.SRB_BufLen = 100;
  v9.SRB_BufPointer = (BYTE *)v10;
  *(_WORD *)&v9.SRB_SenseLen = 1550;
  v9.SRB_PostProc = EventA;
  v9.CDBByte[0] = 18;
  v9.CDBByte[4] = 100;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&v9) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  result = CloseHandle(EventA);
  if ( v9.SRB_Status == 1 )
  {
    v5 = HIBYTE(dword_4FD9BC);
    v6 = v10[4];
    result = HIBYTE(dword_4FD9BC) << 6;
    *(int *)((char *)&dword_504FE0 + result) = v10[2];
    *(int *)((char *)&dword_504FE4 + result) = v10[3];
    byte_504FE8[result] = 0;
    v7 = &byte_504FE9[result];
    *(_DWORD *)v7 = v6;
    *((_DWORD *)v7 + 1) = v10[5];
    *((_DWORD *)v7 + 2) = v10[6];
    *((_DWORD *)v7 + 3) = v10[7];
    v8 = v10[8];
    byte_504FF9[result] = 0;
    *(int *)((char *)&dword_504FFA + result) = v8;
    byte_504FFE[result] = 0;
    qmemcpy(&byte_504FFF[result], &v10[9], 0x14u);
    byte_505013[result] = 0;
    *(int *)((char *)&dword_505014 + result) = a1;
    *(int *)((char *)&dword_505018 + result) = a2;
    *(int *)((char *)dword_50501C + result) = a3;
    HIBYTE(dword_4FD9BC) = v5 + 1;
  }
  return result;
}
