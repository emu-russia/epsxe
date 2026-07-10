#include "pch.h"
int __cdecl sub_433CF0(DWORD BytesReturned)
{
  DWORD v1; // ebp
  int v2; // edx
  int v3; // eax
  _DWORD InBuffer[20]; // [esp+Ch] [ebp-50h] BYREF

  v1 = BytesReturned;
  v2 = *(_DWORD *)(BytesReturned + 16);
  memset(InBuffer, 0, sizeof(InBuffer));
  v3 = *(_DWORD *)(BytesReturned + 12);
  BYTE2(InBuffer[1]) = *(_BYTE *)(BytesReturned + 21);
  InBuffer[3] = v3;
  InBuffer[5] = v2;
  LOWORD(InBuffer[0]) = 44;
  LOBYTE(InBuffer[2]) = 1;
  InBuffer[4] = 5;
  InBuffer[6] = 48;
  qmemcpy(&InBuffer[7], (const void *)(BytesReturned + 48), BYTE2(InBuffer[1]));
  if ( DeviceIoControl(hObject, 0x4D014u, InBuffer, 0x50u, InBuffer, 0x50u, &BytesReturned, nullptr) )
  {
    *(_BYTE *)(v1 + 1) = 1;
  }
  else
  {
    *(_BYTE *)(v1 + 1) = 4;
    *(_BYTE *)(v1 + 23) = 4;
    GetLastError();
  }
  return *(unsigned __int8 *)(v1 + 1);
}
