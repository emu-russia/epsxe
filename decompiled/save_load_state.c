#include "pch.h"
void sub_40B2B0()
{
  int v0; // esi
  char v1; // [esp+8h] [ebp-4h]
  char v2; // [esp+8h] [ebp-4h]

  *(_DWORD *)dword_44DF24 = 255;
  byte_45B8E8 = 0;
  dword_4F7594 = 1;
  v0 = 20;
  do
  {
    spu_update_cb();
    Sleep(0xAu);
    --v0;
  }
  while ( v0 );
  spu_update_cb();
  memcard2_save();
  spu_close();
  net_pause();
  gpu_close();
  if ( hSaveLoadWnd )
    ShowWindow(hSaveLoadWnd, 0);
  ShowWindow(g_hWnd, 5);
  ShowCursor(1);
  UpdateWindow(g_hWnd);
  while ( GetMessageA(&stru_8A94E0, nullptr, 0, 0) )
  {
    TranslateMessage(&stru_8A94E0);
    DispatchMessageA(&stru_8A94E0);
  }
  ShowCursor(0);
  ShowWindow(g_hWnd, 0);
  close_save_load_window();
  create_save_load_window();
  if ( hSaveLoadWnd )
    ShowWindow(hSaveLoadWnd, 5);
  gpu_open();
  net_resume();
  spu_open();
  dword_4F7594 = 0;
  if ( *(int *)dword_44DF24 >= 10 )
  {
    if ( *(int *)dword_44DF24 < 20 )
    {
      v2 = get_gpu_freeze_counter();
      set_gpu_freeze_counter(dword_44DF24[0] - 10);
      state_save();
      dbg_print(" * SaveState Done! (%d)\n", *(_DWORD *)dword_44DF24 - 10);
      set_gpu_freeze_counter(v2);
      PostQuitMessage(0);
    }
  }
  else
  {
    v1 = get_gpu_freeze_counter();
    set_gpu_freeze_counter(dword_44DF24[0]);
    state_load();
    sub_4291E0();
    dbg_print(" * LoadState Done! (%d)\n", *(_DWORD *)dword_44DF24);
    set_gpu_freeze_counter(v1);
  }
}
