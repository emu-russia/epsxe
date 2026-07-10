#include "pch.h"
int __cdecl sub_401090(LPCSTR lpSubKey, LPCSTR lpValueName, BYTE *lpData)
{
  int result; // eax
  HKEY hKey; // [esp+0h] [ebp-8h] BYREF
  HKEY phkResult; // [esp+4h] [ebp-4h] BYREF

  result = RegConnectRegistryA(nullptr, HKEY_CURRENT_USER, &phkResult);
  if ( !result )
  {
    if ( !RegOpenKeyA(phkResult, lpSubKey, &hKey) || !RegCreateKeyA(phkResult, lpSubKey, &hKey) )
    {
      RegSetValueExA(hKey, lpValueName, 0, 1u, lpData, strlen((const char *)lpData) + 1);
      RegCloseKey(hKey);
    }
    return RegCloseKey(phkResult);
  }
  return result;
}
