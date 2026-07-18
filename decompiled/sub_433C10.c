#include "pch.h"
int __cdecl sub_433C10(unsigned __int8 a1, _DWORD *a2, _DWORD *a3, _DWORD *a4)
{
  HANDLE v4; // ebx
  unsigned __int8 v6; // cl
  unsigned __int8 v7; // al
  DWORD BytesReturned; // [esp+8h] [ebp-404h] BYREF
  _DWORD OutBuffer[256]; // [esp+Ch] [ebp-400h] BYREF

  v4 = sub_433B70(a1);
  if ( v4 == (HANDLE)-1 )
  {
    printf(" %c error handle \n", a1);
    return -1;
  }
  else
  {
    memset(OutBuffer, 0, sizeof(OutBuffer));
    OutBuffer[0] = 8;
    if ( DeviceIoControl(v4, IOCTL_SCSI_GET_ADDRESS, nullptr, 0, OutBuffer, 8u, &BytesReturned, nullptr) )
    {
      v6 = BYTE2(OutBuffer[1]);
      *a2 = LOBYTE(OutBuffer[1]);
      v7 = HIBYTE(OutBuffer[1]);
      *a3 = v6;
      *a4 = v7;
      CloseHandle(v4);
      return 0;
    }
    else
    {
      printf(" %c: error \n", a1);
      return -1;
    }
  }
}
