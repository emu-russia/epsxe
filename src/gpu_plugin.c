#include "pch.h"
char gpu_init_performance_counter()
{
  int PerformanceFrequency; // eax
  __int64 v2; // [esp-8h] [ebp-8h]

  LOBYTE(PerformanceFrequency) = use_performance_counters;
  if ( use_performance_counters )
  {
    gpu_performance_threshold = 0;
    PerformanceFrequency = QueryPerformanceFrequency(&Frequency);
    if ( PerformanceFrequency )
    {
      HIDWORD(v2) = 0;
      if ( country_setting )
        LODWORD(v2) = 20;
      else
        LODWORD(v2) = 16;
      gpu_performance_threshold = Frequency.QuadPart * v2 / 1000;
      LOBYTE(PerformanceFrequency) = QueryPerformanceCounter(&PerformanceCount);
    }
  }
  return PerformanceFrequency;
}

int __stdcall gpu_output_win_callback(HWND hWnd, UINT a2, WPARAM a3, LPARAM a4)
{
  int result; // eax

  if ( a2 > 0xF )
  {
    switch ( a2 )
    {
      case 0x100u:
        gpu_keyboard_state[a3] = 1;
        return 0;
      case 0x101u:
        gpu_keyboard_state[a3] = 0;
        return 0;
      case 0x200u:
        diAcquireMouseDevice();
        return 1;
      default:
        return DefWindowProcA(hWnd, a2, a3, a4);
    }
  }
  else if ( a2 == 15 )
  {
    ValidateRect(hWnd, nullptr);
    return 1;
  }
  else
  {
    switch ( a2 )
    {
      case 1u:
        return 1;
      case 2u:
        sio_memcard_both_save();
        PostQuitMessage(0);
        result = 1;
        break;
      case 6u:
        diAcquireAllDevices();
        result = 1;
        break;
      case 7u:
        ShowWindow(hWnd, 1);
        result = 1;
        break;
      case 8u:
        diUnacquireAllDevices();
        result = 1;
        break;
      default:
        return DefWindowProcA(hWnd, a2, a3, a4);
    }
  }
  return result;
}

BOOL gpu_register_output_win_class()
{
  WNDCLASSA WndClass; // [esp+4h] [ebp-28h] BYREF

  WndClass.style = 35;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hIcon = LoadIconA(nullptr, (LPCSTR)0x7F05);
  memset(&WndClass.hCursor, 0, 12);
  WndClass.hInstance = gpu_hInstance;
  WndClass.lpfnWndProc = gpu_output_win_callback;
  WndClass.lpszClassName = "EPSX";
  return RegisterClassA(&WndClass) != 0;
}

void gpu_clear_dynarec_callback()
{
  dynarec_clear_needed = 1;
}

HWND gpu_create_output_window()
{
  gpu_hInstance = GetModuleHandleA(nullptr);
  if ( !gpu_register_output_win_class() )
    ui_error(" * Error registering window.\n");
  hOutputWnd = CreateWindowExA(
                 0x40100u,
                 "EPSX",
                 "ePSXe - Enhanced PSX emulator",
                 0x60A0000u,
                 0,
                 0,
                 640,
                 480,
                 nullptr,
                 nullptr,
                 gpu_hInstance,
                 nullptr);
  if ( !hOutputWnd )
    ui_error(" * Error creating window.\n");
  ShowCursor(0);
  ShowWindow(hOutputWnd, 5);
  SetForegroundWindow(hOutputWnd);
  return SetFocus(hOutputWnd);
}

BOOL gpu_close_output_window()
{
  ChangeDisplaySettingsA(nullptr, 0);
  ShowCursor(1);
  if ( hOutputWnd && !DestroyWindow(hOutputWnd) )
  {
    MessageBoxA(nullptr, "Could Not Release hWnd.", "SHUTDOWN ERROR", 0x40u);
    hOutputWnd = nullptr;
  }
  return UnregisterClassA("EPSX", gpu_hInstance);
}

HWND gpu_load_plugin()
{
  HMODULE LibraryA; // eax
  FARPROC GPUclearDynarec; // eax
  int v2; // eax
  CHAR LibFileName[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( !strcmp((const char *)VideoPlugin, "NULL") )
    fatal_error_with_message_box(" * !Error video doesn't configurated \n * !Go Config->Video and choose a plugin. \n");
  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)VideoPlugin);
  LibraryA = LoadLibraryA(LibFileName);
  hGpuModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
  gpu_closed = 1;
  GPUinit = GetProcAddress(LibraryA, "GPUinit");
  if ( !GPUinit )
    ui_error(" * GetProcAddress error %s\n", "GPUinit");
  GPUshutdown = GetProcAddress(hGpuModule, "GPUshutdown");
  if ( !GPUshutdown )
    ui_error(" * GetProcAddress error %s\n", "GPUshutdown");
  GPUopen = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUopen");
  if ( !GPUopen )
    ui_error(" * GetProcAddress error %s\n", "GPUopen");
  GPUclose = GetProcAddress(hGpuModule, "GPUclose");
  if ( !GPUclose )
    ui_error(" * GetProcAddress error %s\n", "GPUclose");
  GPUconfigure = (int)GetProcAddress(hGpuModule, "GPUconfigure");
  if ( !GPUconfigure )
    ui_error(" * GetProcAddress error %s\n", "GPUconfigure");
  GPUabout = (int)GetProcAddress(hGpuModule, "GPUabout");
  if ( !GPUabout )
    ui_error(" * GetProcAddress error %s\n", "GPUabout");
  GPUtest = (int)GetProcAddress(hGpuModule, "GPUtest");
  if ( !GPUtest )
    ui_error(" * GetProcAddress error %s\n", "GPUtest");
  GPUwriteData = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUwriteData");
  if ( !GPUwriteData )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteData");
  GPUwriteStatus = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUwriteStatus");
  if ( !GPUwriteStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteStatus");
  GPUreadData = GetProcAddress(hGpuModule, "GPUreadData");
  if ( !GPUreadData )
    ui_error(" * GetProcAddress error %s\n", "GPUreadData");
  GPUreadStatus = GetProcAddress(hGpuModule, "GPUreadStatus");
  if ( !GPUreadStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUreadStatus");
  GPUdmaChain = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUdmaChain");
  if ( !GPUdmaChain )
    ui_error(" * GetProcAddress error %s\n", "GPUdmaChain");
  GPUgetMode = (int)GetProcAddress(hGpuModule, "GPUgetMode");
  if ( !GPUgetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUgetMode");
  GPUsetMode = (int)GetProcAddress(hGpuModule, "GPUsetMode");
  if ( !GPUsetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUsetMode");
  GPUupdateLace = (int (__fastcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUupdateLace");
  if ( !GPUupdateLace )
    ui_error(" * GetProcAddress error %s\n", "GPUupdateLace");
  GPUmakeSnapshot = (int (*(*)(void))(void))GetProcAddress(hGpuModule, "GPUmakeSnapshot");
  GPUwriteDataMem = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUwriteDataMem");
  GPUreadDataMem = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUreadDataMem");
  GPUdisplayFlags = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUdisplayFlags");
  GPUfreeze = (int (__stdcall *)(_DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUfreeze");
  GPUgetScreenPic = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUgetScreenPic");
  GPUshowScreenPic = (int (__stdcall *)(_DWORD))GetProcAddress(hGpuModule, "GPUshowScreenPic");
  GPUcursor = (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GetProcAddress(hGpuModule, "GPUcursor");
  GPUclearDynarec = GetProcAddress(hGpuModule, "GPUclearDynarec");
  dword_50ADD4 = (int)GPUclearDynarec;
  if ( GPUclearDynarec )
    ((void (__stdcall *)(void (*)()))GPUclearDynarec)(gpu_clear_dynarec_callback);
  v2 = GPUinit();
  dbg_print(" * Doing init gpu[%d]... \n", v2);
  net_load_plugin();
  net_open();
  net_netplay_handler();
  return gpu_create_output_window();
}

int (__stdcall *gpu_open_with_input())(_DWORD, _DWORD)
{
  int v0; // eax

  v0 = GPUopen(hOutputWnd);
  dbg_print(" * Gpu open[%d]... \n", v0);
  gpu_closed = 0;
  hDlgInput = (int)hOutputWnd;
  hInst_For_DInput = (int)gpu_hInstance;
  if ( diInitDirectInput() == 1 )
    dbg_print_no_flush(" * Direct input init ok. \n");
  else
    dbg_print_no_flush(" * Direct input init error. \n");
  diUpdateJoystickStates();
  return gpu_do_freeze(0);
}

// attributes: thunk
int gpu_readStatus()
{
  return GPUreadStatus();
}

// attributes: thunk
int gpu_readData()
{
  return GPUreadData();
}

int __cdecl gpu_writeStatus(int a1)
{
  return GPUwriteStatus(a1);
}

int __cdecl gpu_writeData(int a1)
{
  return GPUwriteData(a1);
}

char gpu_dma2_interrupt()
{
  char result; // al

  if ( gpu_dma2_state > -2 && gpu_dma2_state != 1 )
    --gpu_dma2_state;
  result = gpu_dma2_delay_counter;
  if ( gpu_dma2_delay_counter <= 0 )
  {
    if ( !gpu_dma2_delay_counter )
    {
      *(_DWORD *)gpu_dma_channel_status &= ~0x1000000u;
      gpu_dma2_delay_counter = -1;
      result = irq_dma_assert_int(2u);
      gpu_dma2_state = -2;
    }
  }
  else
  {
    return --gpu_dma2_delay_counter;
  }
  return result;
}

char gpu_dma()
{
  int v0; // ebp
  int v1; // edi
  int v2; // esi
  _DWORD *v3; // ebx
  char result; // al
  unsigned int v5; // eax
  unsigned int v6; // ecx
  int v7; // eax
  int v8; // esi
  int v9; // esi
  int i; // esi
  unsigned int v11; // eax
  unsigned int v12; // [esp+10h] [ebp-4h]

  v0 = gpu_dma_address;
  v1 = HIWORD(gpu_dma_control);
  v2 = (unsigned __int16)gpu_dma_control;
  v3 = (_DWORD *)mem_dma_read(gpu_dma_address);
  v12 = 0;
  if ( *(_DWORD *)gpu_dma_channel_status == 0x1000200 )
  {
    if ( GPUreadDataMem )
    {
      v9 = v1 * v2;
      GPUreadDataMem(v3, v9);
      if ( dynarec_enabled == 1 && v9 )
        dynarec_invalidate_range(v0, v9);
    }
    else
    {
      if ( dynarec_enabled == 1 && v1 * v2 )
        dynarec_invalidate_range(v0, v1 * v2);
      for ( i = v1 * v2; i; --i )
      {
        v11 = GPUreadData();
        mem_gpu_dma_write(v0, v11);
        v0 += 4;
      }
    }
    goto LABEL_27;
  }
  if ( *(_DWORD *)gpu_dma_channel_status == 0x1000201 )
  {
    v8 = v1 * v2;
    if ( GPUwriteDataMem )
    {
      GPUwriteDataMem(v3, v8);
    }
    else
    {
      for ( ; v8; --v8 )
        GPUwriteData(*v3++);
    }
LABEL_27:
    result = irq_dma_assert_int(2u);
    gpu_dma2_state = 0;
    return result;
  }
  result = gpu_dma_channel_status[0] - 1;
  if ( *(_DWORD *)gpu_dma_channel_status == 0x1000401 )
  {
    GPUdmaChain(ram, v0 & 0x1FFFFF);
    while ( 1 )
    {
      v5 = mem_gpu_dma_read(v0);
      v6 = HIBYTE(v5) + v12;
      v7 = v5 & 0xFFFFFF;
      v12 = v6;
      v0 = v7;
      if ( !v7 || v7 == 0xFFFFFF )
        break;
      if ( v6 >= 0x40 )
        goto LABEL_10;
    }
    if ( v6 >= 0x40 )
    {
LABEL_10:
      gpu_dma2_delay_counter = 1;
      gpu_dma2_state = 1;
      return 1;
    }
    *(_DWORD *)gpu_dma_channel_status &= ~0x1000000u;
    result = irq_dma_assert_int(2u);
    gpu_dma2_state = -2;
  }
  else if ( (*(_DWORD *)gpu_dma_channel_status & 0x1000000) != 0 )
  {
    ui_error(
      "DMA[2] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
      *(_DWORD *)gpu_dma_channel_status,
      v0,
      v1,
      v2);
  }
  return result;
}

char gpu_dma6_interrupt()
{
  char result; // al

  result = gpu_dma6_delay_counter;
  if ( gpu_dma6_delay_counter <= 0 )
  {
    if ( !gpu_dma6_delay_counter )
    {
      *(_DWORD *)gpu_dma6_status &= ~0x1000000u;
      gpu_dma6_delay_counter = -1;
      return irq_dma_assert_int(6u);
    }
  }
  else
  {
    return --gpu_dma6_delay_counter;
  }
  return result;
}

int gpu_frame_update()
{
  int v0; // ecx
  DWORD i; // ecx

  while ( PeekMessageA(&g_msg, nullptr, 0, 0, 1u) )
  {
    TranslateMessage(&g_msg);
    DispatchMessageA(&g_msg);
  }
  if ( use_performance_counters )
  {
    QueryPerformanceCounter(&gpu_performance_counter);
    for ( i = gpu_performance_counter.LowPart - PerformanceCount.LowPart;
          gpu_performance_counter.QuadPart - PerformanceCount.QuadPart < gpu_performance_threshold;
          i = gpu_performance_counter.LowPart - PerformanceCount.LowPart )
    {
      QueryPerformanceCounter(&gpu_performance_counter);
    }
    GPUupdateLace(i);
    QueryPerformanceCounter(&gpu_performance_counter);
    PerformanceCount = gpu_performance_counter;
  }
  else
  {
    GPUupdateLace(v0);
  }
  return cont_process_input();
}

HMODULE gpu_destroy()
{
  HMODULE result; // eax

  result = hGpuModule;
  if ( hGpuModule )
  {
    if ( !gpu_closed )
    {
      dbg_print(" * Closing gpu ...\n");
      GPUclose();
      gpu_closed = 1;
    }
    dbg_print(" * Shutdown gpu ...\n");
    GPUshutdown();
    ChangeDisplaySettingsA(nullptr, 0);
    ShowCursor(1);
    result = (HMODULE)hOutputWnd;
    if ( hOutputWnd )
    {
      result = (HMODULE)DestroyWindow(hOutputWnd);
      if ( !result )
      {
        result = (HMODULE)MessageBoxA(nullptr, "Could NOT release hWnd.", "SHUTDOWN ERROR", 0x40u);
        hOutputWnd = nullptr;
      }
    }
  }
  return result;
}

int gpu_close()
{
  int result; // eax

  result = GPUclose();
  gpu_closed = 1;
  return result;
}

int gpu_open()
{
  GPUopen(hOutputWnd);
  gpu_closed = 0;
  diShutdownDirectInput();
  hDlgInput = (int)hOutputWnd;
  hInst_For_DInput = (int)gpu_hInstance;
  if ( diInitDirectInput() == 1 )
    dbg_print_no_flush(" * Direct input init ok. \n");
  else
    dbg_print_no_flush(" * Direct input init error. \n");
  return diUpdateJoystickStates();
}

char __cdecl gpu_pack_pixels(_BYTE *a1, char a2)
{
  char result; // al

  result = a2;
  if ( a2 )
  {
    if ( a2 == 1 )
    {
      *a1 = -1;
      a1[1] = -1;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
    else if ( a2 == 2 )
    {
      *a1 = 0;
      a1[1] = 0;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
  }
  else
  {
    *a1 = 0;
    a1[1] = 0;
    a1[2] = 0;
    return (_BYTE)a1 + 1;
  }
  return result;
}

BOOL __cdecl gpu_draw_text_on_screen(LPCSTR lpchText, void *a2)
{
  HDC DC; // edi
  HDC CompatibleDC; // ebx
  HBRUSH SolidBrush; // edi
  HPEN Pen; // esi
  HGDIOBJ v7; // [esp-4h] [ebp-6Ch]
  void *ppvBits; // [esp+10h] [ebp-58h] BYREF
  HGDIOBJ h; // [esp+14h] [ebp-54h]
  HGDIOBJ v10; // [esp+18h] [ebp-50h]
  HGDIOBJ v11; // [esp+1Ch] [ebp-4Ch]
  HGDIOBJ ho; // [esp+20h] [ebp-48h]
  HGDIOBJ v13; // [esp+24h] [ebp-44h]
  HGDIOBJ v14; // [esp+28h] [ebp-40h]
  struct tagRECT left; // [esp+2Ch] [ebp-3Ch] BYREF
  BITMAPINFO pbmi; // [esp+3Ch] [ebp-2Ch] BYREF

  left.left = 0;
  left.top = 0;
  left.right = 128;
  left.bottom = 96;
  DC = GetDC(nullptr);
  CompatibleDC = CreateCompatibleDC(DC);
  ReleaseDC(nullptr, DC);
  memset(&pbmi, 0, sizeof(pbmi));
  pbmi.bmiHeader.biSize = 40;
  pbmi.bmiHeader.biWidth = 128;
  pbmi.bmiHeader.biHeight = -96;
  pbmi.bmiHeader.biPlanes = 1;
  pbmi.bmiHeader.biBitCount = 24;
  pbmi.bmiHeader.biCompression = 0;
  ho = CreateDIBSection(CompatibleDC, &pbmi, 0, &ppvBits, nullptr, 0);
  h = SelectObject(CompatibleDC, ho);
  SolidBrush = CreateSolidBrush(0);
  v13 = SolidBrush;
  Pen = CreatePen(0, 0, 0xFF0000u);
  v14 = Pen;
  v10 = SelectObject(CompatibleDC, SolidBrush);
  v11 = SelectObject(CompatibleDC, Pen);
  SetTextColor(CompatibleDC, 0xFFu);
  SetBkColor(CompatibleDC, 0);
  Rectangle(CompatibleDC, left.left, left.top, left.right, left.bottom);
  InflateRect(&left, -3, -2);
  DrawTextA(CompatibleDC, lpchText, strlen(lpchText), &left, 0x25u);
  v7 = h;
  qmemcpy(a2, ppvBits, 0x9000u);
  SelectObject(CompatibleDC, v7);
  SelectObject(CompatibleDC, v10);
  SelectObject(CompatibleDC, v11);
  DeleteDC(CompatibleDC);
  DeleteObject(ho);
  DeleteObject(v13);
  return DeleteObject(v14);
}

_BYTE *__cdecl gpu_draw_no_save_pic(char *a1, int a2)
{
  char *v2; // esi
  char *v3; // edx
  int v4; // ebp
  int v5; // edi
  unsigned __int8 v6; // cl
  _BYTE *v7; // esi
  unsigned __int8 v8; // cl
  char v9; // cl
  int v10; // edx
  char *v11; // eax
  int v12; // edx
  _BYTE *v13; // eax
  _BYTE *result; // eax
  int v15; // edx
  _BYTE *v16; // eax

  v2 = a1 + 309;
  gpu_draw_text_on_screen("NO SAVE PIC", a1);
  v3 = &gpu_save_pic_data[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_pack_pixels(v2, (unsigned __int8)*v3 >> 6);
      v7 = v2 + 3;
      gpu_pack_pixels(v7, (v6 >> 4) & 3);
      v7 += 3;
      gpu_pack_pixels(v7, (v8 >> 2) & 3);
      v7 += 3;
      gpu_pack_pixels(v7, v9 & 3);
      v2 = v7 + 3;
      v3 = (char *)(v10 + 1);
      --v5;
    }
    while ( v5 );
    v2 += 312;
    --v4;
  }
  while ( v4 );
  v11 = a1;
  v12 = 128;
  do
  {
    v11[36480] = 0;
    *v11 = 0;
    v13 = v11 + 1;
    v13[36480] = 0;
    *v13++ = 0;
    v13[36480] = -1;
    *v13 = -1;
    v11 = v13 + 1;
    --v12;
  }
  while ( v12 );
  result = a1;
  v15 = 96;
  do
  {
    result[381] = 0;
    *result = 0;
    v16 = result + 1;
    v16[381] = 0;
    *v16++ = 0;
    v16[381] = -1;
    *v16 = -1;
    result = v16 + 382;
    --v15;
  }
  while ( v15 );
  return result;
}

_BYTE *__cdecl gpu_draw_free_slot(char *a1, int a2)
{
  char *v2; // esi
  char *v3; // edx
  int v4; // ebp
  int v5; // edi
  unsigned __int8 v6; // cl
  _BYTE *v7; // esi
  unsigned __int8 v8; // cl
  char v9; // cl
  int v10; // edx
  char *v11; // eax
  int v12; // edx
  _BYTE *v13; // eax
  _BYTE *result; // eax
  int v15; // edx
  _BYTE *v16; // eax

  v2 = a1 + 309;
  gpu_draw_text_on_screen("FREE SLOT", a1);
  v3 = &gpu_save_pic_data[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_pack_pixels(v2, (unsigned __int8)*v3 >> 6);
      v7 = v2 + 3;
      gpu_pack_pixels(v7, (v6 >> 4) & 3);
      v7 += 3;
      gpu_pack_pixels(v7, (v8 >> 2) & 3);
      v7 += 3;
      gpu_pack_pixels(v7, v9 & 3);
      v2 = v7 + 3;
      v3 = (char *)(v10 + 1);
      --v5;
    }
    while ( v5 );
    v2 += 312;
    --v4;
  }
  while ( v4 );
  v11 = a1;
  v12 = 128;
  do
  {
    v11[36480] = 0;
    *v11 = 0;
    v13 = v11 + 1;
    v13[36480] = 0;
    *v13++ = 0;
    v13[36480] = -1;
    *v13 = -1;
    v11 = v13 + 1;
    --v12;
  }
  while ( v12 );
  result = a1;
  v15 = 96;
  do
  {
    result[381] = 0;
    *result = 0;
    v16 = result + 1;
    v16[381] = 0;
    *v16++ = 0;
    v16[381] = -1;
    *v16 = -1;
    result = v16 + 382;
    --v15;
  }
  while ( v15 );
  return result;
}

int (__stdcall *__cdecl gpu_display_flags(int a1))(_DWORD)
{
  int (__stdcall *result)(_DWORD); // eax

  result = GPUdisplayFlags;
  if ( GPUdisplayFlags )
    return (int (__stdcall *)(_DWORD))GPUdisplayFlags(a1);
  return result;
}

int (*gpu_make_snapshot())(void)
{
  int (*result)(void); // eax

  result = (int (*)(void))GPUmakeSnapshot;
  if ( GPUmakeSnapshot )
    return GPUmakeSnapshot();
  return result;
}

void __cdecl gpu_show_screen_pic(unsigned __int8 a1)
{
  void *v1; // ebx
  FILE *v2; // eax
  FILE *v3; // edi
  FILE *v4; // eax
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( GPUshowScreenPic )
  {
    v1 = malloc(0x9000u);
    sprintf(Buffer, "%s%s.%03d.pic", "sstates\\", default_filename, a1);
    v2 = fopen(Buffer, "rb");
    v3 = v2;
    if ( v2 )
    {
      fread(v1, 1u, 0x9000u, v2);
      fclose(v3);
    }
    else
    {
      sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, a1);
      v4 = fopen(Buffer, "rb");
      if ( v4 )
      {
        fclose(v4);
        gpu_draw_no_save_pic((char *)v1, a1);
      }
      else
      {
        gpu_draw_free_slot((char *)v1, a1);
      }
    }
    GPUshowScreenPic(v1);
    free(v1);
  }
}

int (__stdcall *gpu_hide_screen_pic())(_DWORD)
{
  int (__stdcall *result)(_DWORD); // eax

  result = GPUshowScreenPic;
  if ( GPUshowScreenPic )
    return (int (__stdcall *)(_DWORD))GPUshowScreenPic(0);
  return result;
}

int (__stdcall *__cdecl gpu_do_freeze(int a1))(_DWORD, _DWORD)
{
  int (__stdcall *result)(_DWORD, _DWORD); // eax

  result = GPUfreeze;
  if ( GPUfreeze )
    return (int (__stdcall *)(_DWORD, _DWORD))GPUfreeze(2, &a1);
  return result;
}

int (__stdcall *__cdecl gpu_cursor(int a1, int a2, int a3))(_DWORD, _DWORD, _DWORD)
{
  int (__stdcall *result)(_DWORD, _DWORD, _DWORD); // eax

  result = GPUcursor;
  if ( GPUcursor )
    return (int (__stdcall *)(_DWORD, _DWORD, _DWORD))GPUcursor(a1, a2, a3);
  return result;
}

void __cdecl gpu_freeze(const char *a1, int ArgList, const char *a3)
{
  unsigned __int8 *v3; // esi
  void *v4; // esi
  FILE *v5; // edi
  char Buffer[3]; // [esp+8h] [ebp-410h] BYREF
  int v7; // [esp+Bh] [ebp-40Dh]
  char FileName[1024]; // [esp+18h] [ebp-400h] BYREF

  if ( GPUfreeze )
  {
    v3 = (unsigned __int8 *)malloc(0x100408u);
    *(_DWORD *)v3 = 1;
    sprintf(Buffer, "%s", a1);
    v7 = 1049608;
    GPUfreeze(1, v3);
    gzwrite(ArgList, (unsigned __int8 *)Buffer, 7u);
    gzwrite(ArgList, v3, 0x100408u);
    free(v3);
    if ( GPUgetScreenPic )
    {
      v4 = malloc(0x9000u);
      sprintf(FileName, "%s.pic", a3);
      GPUgetScreenPic(v4);
      v5 = fopen(FileName, "wb");
      fwrite(v4, 1u, 0x9000u, v5);
      fclose(v5);
      free(v4);
    }
  }
  else
  {
    sprintf(Buffer, "%s", a1);
    v7 = 0;
    gzwrite(ArgList, (unsigned __int8 *)Buffer, 7u);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}

void __cdecl gpu_unfreeze(int a1, _DWORD *ArgList)
{
  char *v2; // esi
  char v3[16]; // [esp+0h] [ebp-10h] BYREF

  if ( GPUfreeze )
  {
    v2 = (char *)malloc(0x100408u);
    gzread(ArgList, v3, 7);
    gzread(ArgList, v2, 1049608);
    GPUfreeze(0, v2);
    free(v2);
  }
  else
  {
    gzread(ArgList, v3, 7);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}

