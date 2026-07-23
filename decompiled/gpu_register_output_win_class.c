#include "pch.h"
BOOL register_output_win_class()
{
  WNDCLASSA WndClass; // [esp+4h] [ebp-28h] BYREF

  WndClass.style = 35;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hIcon = LoadIconA(nullptr, (LPCSTR)0x7F05);
  memset(&WndClass.hCursor, 0, 12);
  WndClass.hInstance = dword_50AE4C;
  WndClass.lpfnWndProc = gpu_output_win_callback;
  WndClass.lpszClassName = "EPSX";
  return RegisterClassA(&WndClass) != 0;
}
