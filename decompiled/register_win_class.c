#include "pch.h"
BOOL register_win_class()
{
  WNDCLASSEXA v1; // [esp+8h] [ebp-30h] BYREF

  v1.cbSize = 48;
  v1.style = 0;
  v1.cbClsExtra = 0;
  v1.cbWndExtra = 0;
  v1.hIcon = LoadIconA(nullptr, (LPCSTR)0x89);
  v1.hIconSm = LoadIconA(g_hInstance, (LPCSTR)0x89);
  v1.hCursor = nullptr;
  v1.hInstance = g_hInstance;
  v1.lpfnWndProc = main_window_callback;
  v1.hbrBackground = (HBRUSH)GetStockObject(0);
  v1.lpszMenuName = aEpsxmenu;
  v1.lpszClassName = ClassName;
  return RegisterClassExA(&v1) != 0;
}
