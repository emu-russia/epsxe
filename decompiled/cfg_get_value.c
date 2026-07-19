#include "pch.h"
char __cdecl cfg_get_value(LPCSTR lpSubKey, LPCSTR lpValueName, LPBYTE lpData)
{
  char v3; // bl
  HKEY hKey; // [esp+4h] [ebp-10h] BYREF
  HKEY phkResult; // [esp+8h] [ebp-Ch] BYREF
  DWORD cbData; // [esp+Ch] [ebp-8h] BYREF
  DWORD Type; // [esp+10h] [ebp-4h] BYREF

  v3 = -1;
  if ( !RegConnectRegistryA(nullptr, HKEY_CURRENT_USER, &phkResult) )
  {
    if ( !RegOpenKeyA(phkResult, lpSubKey, &hKey) )
    {
      cbData = 1024;
      if ( !RegQueryValueExA(hKey, lpValueName, nullptr, &Type, lpData, &cbData) )
        v3 = 0;
      RegCloseKey(hKey);
    }
    RegCloseKey(phkResult);
  }
  return v3;
}
