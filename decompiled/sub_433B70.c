#include "pch.h"
HANDLE __cdecl sub_433B70(unsigned __int8 a1)
{
  DWORD v1; // esi
  HANDLE result; // eax
  CHAR FileName[12]; // [esp+8h] [ebp-A0h] BYREF
  struct _OSVERSIONINFOA VersionInformation; // [esp+14h] [ebp-94h] BYREF

  memset(&VersionInformation, 0, sizeof(VersionInformation));
  VersionInformation.dwOSVersionInfoSize = 148;
  GetVersionExA(&VersionInformation);
  v1 = 0x80000000;
  if ( VersionInformation.dwPlatformId == 2 && VersionInformation.dwMajorVersion > 4 )
    v1 = -1073741824;
  wsprintfA(FileName, "\\\\.\\%c:", a1);
  result = CreateFileA(FileName, v1, 1u, nullptr, 3u, 0, nullptr);
  if ( result == (HANDLE)-1 )
    return CreateFileA(FileName, v1 ^ 0x40000000, 1u, nullptr, 3u, 0, nullptr);
  return result;
}
