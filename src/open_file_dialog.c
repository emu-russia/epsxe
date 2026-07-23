#include "pch.h"
BOOL __cdecl open_file_dialog(const CHAR *a1, const CHAR *a2, CHAR *a3, const CHAR *a4, const CHAR *a5)
{
  BOOL result; // eax
  int v6; // eax
  CHAR v7; // cl
  OPENFILENAMEA v8; // [esp+4h] [ebp-84Ch] BYREF NOPROP
  _BYTE v9[1024]; // [esp+450h] [ebp-400h] BYREF

  memset(&v8.pvReserved, 0, 0x400u);
  memset(v9, 0, sizeof(v9));
  v8.lpstrFile = (LPSTR)&v8.pvReserved;
  v8.hwndOwner = g_hWnd;
  v8.lpstrFilter = a2;
  v8.lpstrFileTitle = v9;
  v8.nMaxFile = 1024;
  v8.lpstrInitialDir = a4;
  v8.nMaxFileTitle = 1024;
  v8.lStructSize = 76;
  v8.lpstrCustomFilter = nullptr;
  v8.nMaxCustFilter = 0;
  v8.nFilterIndex = 1;
  v8.lpstrTitle = a1;
  v8.lpstrDefExt = a5;
  v8.Flags = 12;
  result = GetOpenFileNameA(&v8);
  if ( result )
  {
    v6 = 0;
    do
    {
      v7 = *((_BYTE *)&v8.pvReserved + v6);
      temp_path[v6++] = v7;
    }
    while ( v7 );
    return 1;
  }
  return result;
}

