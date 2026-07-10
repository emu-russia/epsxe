#include "pch.h"
BOOL create_main_window()
{
  HWND Window; // eax

  byte_45B8E8 = 0;
  g_hInstance = GetModuleHandleA(nullptr);
  if ( !register_win_class() )
    ui_error(aErrorRegisteri);
  dword_45B8D8 = LoadBitmapA(g_hInstance, (LPCSTR)0x8C);
  h = LoadBitmapA(g_hInstance, (LPCSTR)0x8E);
  Window = CreateWindowExA(0, ClassName, WindowName, 0xA0000u, 0, 0, 400, 300, nullptr, nullptr, g_hInstance, nullptr);
  g_hWnd = Window;
  if ( !Window )
    ui_error(aErrorCreatingW);
  ShowWindow(Window, 5);
  UpdateWindow(g_hWnd);
  while ( GetMessageA(&stru_8A94E0, nullptr, 0, 0) )
  {
    TranslateMessage(&stru_8A94E0);
    DispatchMessageA(&stru_8A94E0);
  }
  return ShowWindow(g_hWnd, 0);
}
