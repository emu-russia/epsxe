#include "pch.h"
BOOL __cdecl open_file_dialog(int a1, int a2, int a3, int a4, int a5)
{
  BOOL result; // eax
  int v6; // eax
  CHAR v7; // cl
  _BYTE v8[1100]; // [esp+4h] [ebp-84Ch] BYREF
  _BYTE v9[1024]; // [esp+450h] [ebp-400h] BYREF

  memset(&v8[76], 0, 0x400u);
  memset(v9, 0, sizeof(v9));
  *(_DWORD *)&v8[28] = &v8[76];
  *(_DWORD *)&v8[4] = hWnd;
  *(_DWORD *)&v8[12] = a2;
  *(_DWORD *)&v8[36] = v9;
  *(_DWORD *)&v8[32] = 1024;
  *(_DWORD *)&v8[44] = a4;
  *(_DWORD *)&v8[40] = 1024;
  *(_DWORD *)v8 = 76;
  *(_DWORD *)&v8[16] = 0;
  *(_DWORD *)&v8[20] = 0;
  *(_DWORD *)&v8[24] = 1;
  *(_DWORD *)&v8[48] = a1;
  *(_DWORD *)&v8[60] = a5;
  *(_DWORD *)&v8[52] = 12;
  result = GetOpenFileNameA((LPOPENFILENAMEA)v8);
  if ( result )
  {
    v6 = 0;
    do
    {
      v7 = v8[v6 + 76];
      byte_8B1560[v6++] = v7;
    }
    while ( v7 );
    return 1;
  }
  return result;
}
