#include "pch.h"
char gpu_init_performance_counter()
{
  int PerformanceFrequency;
  int64_t v2;

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

static int __stdcall gpu_output_win_callback(HWND hWnd, UINT a2, WPARAM a3, LPARAM a4)
{
  int result;

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

static BOOL gpu_register_output_win_class()
{
  WNDCLASSA WndClass;

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

static void gpu_clear_dynarec_callback()
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
  HMODULE LibraryA;
  FARPROC GPUclearDynarec;
  int v2;
  CHAR LibFileName[1024];

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
  GPUopen = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUopen");
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
  GPUwriteData = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUwriteData");
  if ( !GPUwriteData )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteData");
  GPUwriteStatus = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUwriteStatus");
  if ( !GPUwriteStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUwriteStatus");
  GPUreadData = GetProcAddress(hGpuModule, "GPUreadData");
  if ( !GPUreadData )
    ui_error(" * GetProcAddress error %s\n", "GPUreadData");
  GPUreadStatus = GetProcAddress(hGpuModule, "GPUreadStatus");
  if ( !GPUreadStatus )
    ui_error(" * GetProcAddress error %s\n", "GPUreadStatus");
  GPUdmaChain = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hGpuModule, "GPUdmaChain");
  if ( !GPUdmaChain )
    ui_error(" * GetProcAddress error %s\n", "GPUdmaChain");
  GPUgetMode = (int)GetProcAddress(hGpuModule, "GPUgetMode");
  if ( !GPUgetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUgetMode");
  GPUsetMode = (int)GetProcAddress(hGpuModule, "GPUsetMode");
  if ( !GPUsetMode )
    ui_error(" * GetProcAddress error %s\n", "GPUsetMode");
  GPUupdateLace = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUupdateLace");
  if ( !GPUupdateLace )
    ui_error(" * GetProcAddress error %s\n", "GPUupdateLace");
  GPUmakeSnapshot = (int (__stdcall *)(void))GetProcAddress(hGpuModule, "GPUmakeSnapshot");
  GPUwriteDataMem = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hGpuModule, "GPUwriteDataMem");
  GPUreadDataMem = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hGpuModule, "GPUreadDataMem");
  GPUdisplayFlags = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUdisplayFlags");
  GPUfreeze = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hGpuModule, "GPUfreeze");
  GPUgetScreenPic = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUgetScreenPic");
  GPUshowScreenPic = (int (__stdcall *)(uint32_t))GetProcAddress(hGpuModule, "GPUshowScreenPic");
  GPUcursor = (int (__stdcall *)(uint32_t, uint32_t, uint32_t))GetProcAddress(hGpuModule, "GPUcursor");
  GPUclearDynarec = GetProcAddress(hGpuModule, "GPUclearDynarec");
  gpu_clear_dynarec_ptr = (int)GPUclearDynarec;
  if ( GPUclearDynarec )
    ((void (__stdcall *)(void (*)()))GPUclearDynarec)(gpu_clear_dynarec_callback);
  v2 = GPUinit();
  dbg_print(" * Doing init gpu[%d]... \n", v2);
  net_load_plugin();
  net_open();
  net_netplay_handler();
  return gpu_create_output_window();
}

int (__stdcall *gpu_open_with_input())(uint32_t, uint32_t)
{
  int v0;

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


int gpu_readStatus()
{
  return GPUreadStatus();
}


int gpu_readData()
{
  return GPUreadData();
}

int gpu_writeStatus(int a1)
{
  return GPUwriteStatus(a1);
}

int gpu_writeData(int a1)
{
  return GPUwriteData(a1);
}

char gpu_dma2_interrupt()
{
  char result;

  if ( gpu_dma2_state > -2 && gpu_dma2_state != 1 )
    --gpu_dma2_state;
  result = gpu_dma2_delay_counter;
  if ( gpu_dma2_delay_counter <= 0 )
  {
    if ( !gpu_dma2_delay_counter )
    {
      *(uint32_t *)gpu_dma_channel_status &= ~0x1000000u;
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
  int v0;
  int v1;
  int v2;
  uint32_t *v3;
  char result;
  unsigned int v5;
  unsigned int v6;
  int v7;
  int v8;
  int v9;
  int i;
  unsigned int v11;
  unsigned int v12;

  v0 = gpu_dma_address;
  v1 = HIWORD(gpu_dma_control);
  v2 = (uint16_t)gpu_dma_control;
  v3 = (uint32_t *)mem_dma_read(gpu_dma_address);
  v12 = 0;
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000200 )
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
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000201 )
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
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000401 )
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
    *(uint32_t *)gpu_dma_channel_status &= ~0x1000000u;
    result = irq_dma_assert_int(2u);
    gpu_dma2_state = -2;
  }
  else if ( (*(uint32_t *)gpu_dma_channel_status & 0x1000000) != 0 )
  {
    ui_error(
      "DMA[2] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
      *(uint32_t *)gpu_dma_channel_status,
      v0,
      v1,
      v2);
  }
  return result;
}

char gpu_dma6_interrupt()
{
  char result;

  result = gpu_dma6_delay_counter;
  if ( gpu_dma6_delay_counter <= 0 )
  {
    if ( !gpu_dma6_delay_counter )
    {
      *(uint32_t *)gpu_dma6_status &= ~0x1000000u;
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
  int v0;
  DWORD i;

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
  HMODULE result;

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
  int result;

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

static char gpu_pack_pixels(uint8_t *a1, char a2)
{
  char result;

  result = a2;
  if ( a2 )
  {
    if ( a2 == 1 )
    {
      *a1 = -1;
      a1[1] = -1;
      a1[2] = -1;
      return (uint8_t)a1 + 1;
    }
    else if ( a2 == 2 )
    {
      *a1 = 0;
      a1[1] = 0;
      a1[2] = -1;
      return (uint8_t)a1 + 1;
    }
  }
  else
  {
    *a1 = 0;
    a1[1] = 0;
    a1[2] = 0;
    return (uint8_t)a1 + 1;
  }
  return result;
}

static BOOL gpu_draw_text_on_screen(LPCSTR lpchText, void *a2)
{
  HDC DC;
  HDC CompatibleDC;
  HBRUSH SolidBrush;
  HPEN Pen;
  HGDIOBJ v7;
  void *ppvBits;
  HGDIOBJ h;
  HGDIOBJ v10;
  HGDIOBJ v11;
  HGDIOBJ ho;
  HGDIOBJ v13;
  HGDIOBJ v14;
  struct tagRECT left;
  BITMAPINFO pbmi;

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

static uint8_t * gpu_draw_no_save_pic(char *a1, int a2)
{
  char *v2;
  char *v3;
  int v4;
  int v5;
  uint8_t v6;
  uint8_t *v7;
  uint8_t v8;
  char v9;
  int v10;
  char *v11;
  int v12;
  uint8_t *v13;
  uint8_t *result;
  int v15;
  uint8_t *v16;

  v2 = a1 + 309;
  gpu_draw_text_on_screen("NO SAVE PIC", a1);
  v3 = &gpu_save_pic_data[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_pack_pixels(v2, (uint8_t)*v3 >> 6);
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

static uint8_t * gpu_draw_free_slot(char *a1, int a2)
{
  char *v2;
  char *v3;
  int v4;
  int v5;
  uint8_t v6;
  uint8_t *v7;
  uint8_t v8;
  char v9;
  int v10;
  char *v11;
  int v12;
  uint8_t *v13;
  uint8_t *result;
  int v15;
  uint8_t *v16;

  v2 = a1 + 309;
  gpu_draw_text_on_screen("FREE SLOT", a1);
  v3 = &gpu_save_pic_data[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_pack_pixels(v2, (uint8_t)*v3 >> 6);
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

int (__stdcall * gpu_display_flags(int a1))(uint32_t)
{
  int (__stdcall *result)(uint32_t);

  result = GPUdisplayFlags;
  if ( GPUdisplayFlags )
    return (int (__stdcall *)(uint32_t))GPUdisplayFlags(a1);
  return result;
}

int (*gpu_make_snapshot())(void)
{
  int (*result)(void);

  result = (int (*)(void))GPUmakeSnapshot;
  if ( GPUmakeSnapshot )
    return GPUmakeSnapshot();
  return result;
}

void gpu_show_screen_pic(uint8_t a1)
{
  void *v1;
  FILE *v2;
  FILE *v3;
  FILE *v4;
  char Buffer[1024];

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

int (__stdcall *gpu_hide_screen_pic())(uint32_t)
{
  int (__stdcall *result)(uint32_t);

  result = GPUshowScreenPic;
  if ( GPUshowScreenPic )
    return (int (__stdcall *)(uint32_t))GPUshowScreenPic(0);
  return result;
}

int (__stdcall * gpu_do_freeze(int a1))(uint32_t, uint32_t)
{
  int (__stdcall *result)(uint32_t, uint32_t);

  result = GPUfreeze;
  if ( GPUfreeze )
    return (int (__stdcall *)(uint32_t, uint32_t))GPUfreeze(2, &a1);
  return result;
}

int (__stdcall * gpu_cursor(int a1, int a2, int a3))(uint32_t, uint32_t, uint32_t)
{
  int (__stdcall *result)(uint32_t, uint32_t, uint32_t);

  result = GPUcursor;
  if ( GPUcursor )
    return (int (__stdcall *)(uint32_t, uint32_t, uint32_t))GPUcursor(a1, a2, a3);
  return result;
}

void gpu_freeze(const char *a1, int ArgList, const char *a3)
{
  uint8_t *v3;
  void *v4;
  FILE *v5;
  char Buffer[3];
  int v7;
  char FileName[1024];

  if ( GPUfreeze )
  {
    v3 = (uint8_t *)malloc(0x100408u);
    *(uint32_t *)v3 = 1;
    sprintf(Buffer, "%s", a1);
    v7 = 1049608;
    GPUfreeze(1, v3);
    gzwrite(ArgList, (uint8_t *)Buffer, 7u);
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
    gzwrite(ArgList, (uint8_t *)Buffer, 7u);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}

void gpu_unfreeze(int a1, uint32_t *ArgList)
{
  char *v2;
  char v3[16];

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



/* Decompiled globals (previously generated in src/_gen) */
LARGE_INTEGER Frequency;
unsigned int GPUabout;
int (__stdcall *GPUclose)();
unsigned int GPUconfigure;
int (__stdcall *GPUcursor)();
int (__stdcall *GPUdisplayFlags)();
int (__stdcall *GPUdmaChain)();
int (__stdcall *GPUfreeze)();
unsigned int GPUgetMode;
int (__stdcall *GPUgetScreenPic)();
int (__stdcall *GPUinit)();
int (__stdcall *GPUmakeSnapshot)();
int (__stdcall *GPUopen)();
int (__stdcall *GPUreadData)();
int (__stdcall *GPUreadDataMem)();
int (__stdcall *GPUreadStatus)();
unsigned int GPUsetMode;
int (__stdcall *GPUshowScreenPic)();
int (__stdcall *GPUshutdown)();
unsigned int GPUtest;
int (__stdcall *GPUupdateLace)();
int (__stdcall *GPUwriteData)();
int (__stdcall *GPUwriteDataMem)();
int (__stdcall *GPUwriteStatus)();
LARGE_INTEGER PerformanceCount;
unsigned int gpu_clear_dynarec_ptr;
MSG g_msg;
unsigned char gpu_closed;
unsigned char gpu_dma2_delay_counter;
unsigned char gpu_dma2_state;
unsigned char gpu_dma6_delay_counter;
unsigned int gpu_dma_address;
unsigned int gpu_dma_channel_status[1];
unsigned int gpu_dma_control;
unsigned int gpu_hInstance;
LARGE_INTEGER gpu_performance_counter;
uint64_t gpu_performance_threshold;
unsigned char gpu_save_pic_data[24] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0};
unsigned int hGpuModule;
unsigned int hInst_For_DInput;
unsigned int hOutputWnd;
unsigned char use_performance_counters;
