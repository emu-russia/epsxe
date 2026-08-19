#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static LARGE_INTEGER Frequency;
static unsigned int GPUabout;
static int (__stdcall *GPUclose)();
static unsigned int GPUconfigure;
static int (__stdcall *GPUcursor)();
static int (__stdcall *GPUdisplayFlags)();
static int (__stdcall *GPUdmaChain)();
static int (__stdcall *GPUfreeze)();
static unsigned int GPUgetMode;
static int (__stdcall *GPUgetScreenPic)();
static int (__stdcall *GPUinit)();
static int (__stdcall *GPUmakeSnapshot)();
static int (__stdcall *GPUopen)();
static int (__stdcall *GPUreadData)();
static int (__stdcall *GPUreadDataMem)();
static int (__stdcall *GPUreadStatus)();
static unsigned int GPUsetMode;
static int (__stdcall *GPUshowScreenPic)();
static int (__stdcall *GPUshutdown)();
static unsigned int GPUtest;
static int (__stdcall *GPUupdateLace)();
static int (__stdcall *GPUwriteData)();
static int (__stdcall *GPUwriteDataMem)();
static int (__stdcall *GPUwriteStatus)();
static LARGE_INTEGER PerformanceCount;
static unsigned int gpu_clear_dynarec_ptr;
static MSG g_msg;
static unsigned char gpu_closed;
unsigned char gpu_dma2_delay_counter;
unsigned char gpu_dma2_state;
unsigned char gpu_dma6_delay_counter;
static unsigned int gpu_dma_address;
unsigned int gpu_dma_channel_status[1];
static unsigned int gpu_dma_control;
static unsigned int gpu_hInstance;
static LARGE_INTEGER gpu_performance_counter;
static uint64_t gpu_performance_threshold;
static unsigned char gpu_save_pic_data[24] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0};
static unsigned int hGpuModule;
unsigned int hInst_For_DInput;
unsigned int hOutputWnd;
unsigned char use_performance_counters;

char gpu_init_performance_counter()
{
  int status;
  int64_t delay_ms;

  LOBYTE(status) = use_performance_counters;
  if ( use_performance_counters )
  {
    gpu_performance_threshold = 0;
    status = QueryPerformanceFrequency(&Frequency);
    if ( status )
    {
      HIDWORD(delay_ms) = 0;
      if ( country_setting )
        LODWORD(delay_ms) = 20;
      else
        LODWORD(delay_ms) = 16;
      gpu_performance_threshold = Frequency.QuadPart * delay_ms / 1000;
      LOBYTE(status) = QueryPerformanceCounter(&PerformanceCount);
    }
  }
  return status;
}

static int __stdcall gpu_output_win_callback(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  int handled;

  if ( msg > 0xF )
  {
    switch ( msg )
    {
      case 0x100u:
        gpu_keyboard_state[wParam] = 1;
        return 0;
      case 0x101u:
        gpu_keyboard_state[wParam] = 0;
        return 0;
      case 0x200u:
        diAcquireMouseDevice();
        return 1;
      default:
        return DefWindowProcA(hWnd, msg, wParam, lParam);
    }
  }
  else if ( msg == 15 )
  {
    ValidateRect(hWnd, nullptr);
    return 1;
  }
  else
  {
    switch ( msg )
    {
      case 1u:
        return 1;
      case 2u:
        sio_memcard_both_save();
        PostQuitMessage(0);
        handled = 1;
        break;
      case 6u:
        diAcquireAllDevices();
        handled = 1;
        break;
      case 7u:
        ShowWindow(hWnd, 1);
        handled = 1;
        break;
      case 8u:
        diUnacquireAllDevices();
        handled = 1;
        break;
      default:
        return DefWindowProcA(hWnd, msg, wParam, lParam);
    }
  }
  return handled;
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
  int status;
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
  status = GPUinit();
  dbg_print(" * Doing init gpu[%d]... \n", status);
  net_load_plugin();
  net_open();
  net_netplay_handler();
  return gpu_create_output_window();
}

int (__stdcall *gpu_open_with_input())(uint32_t, uint32_t)
{
  int status;

  status = GPUopen(hOutputWnd);
  dbg_print(" * Gpu open[%d]... \n", status);
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

int gpu_writeStatus(int data)
{
  return GPUwriteStatus(data);
}

int gpu_writeData(int data)
{
  return GPUwriteData(data);
}

char gpu_dma2_interrupt()
{
  char status;

  if ( gpu_dma2_state > -2 && gpu_dma2_state != 1 )
    --gpu_dma2_state;
  status = gpu_dma2_delay_counter;
  if ( gpu_dma2_delay_counter <= 0 )
  {
    if ( !gpu_dma2_delay_counter )
    {
      *(uint32_t *)gpu_dma_channel_status &= ~0x1000000u;
      gpu_dma2_delay_counter = -1;
      status = irq_dma_assert_int(2u);
      gpu_dma2_state = -2;
    }
  }
  else
  {
    return --gpu_dma2_delay_counter;
  }
  return status;
}

char gpu_dma()
{
  int dma_addr;
  int count;
  int size;
  uint32_t *src;
  char status;
  unsigned int header;
  unsigned int block_total;
  int next_addr;
  int words;
  int total_words;
  int i;
  unsigned int data;
  unsigned int total;

  dma_addr = gpu_dma_address;
  count = HIWORD(gpu_dma_control);
  size = (uint16_t)gpu_dma_control;
  src = (uint32_t *)mem_dma_read(gpu_dma_address);
  total = 0;
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000200 )
  {
    if ( GPUreadDataMem )
    {
      total_words = count * size;
      GPUreadDataMem(src, total_words);
      if ( dynarec_enabled == 1 && total_words )
        dynarec_invalidate_range(dma_addr, total_words);
    }
    else
    {
      if ( dynarec_enabled == 1 && count * size )
        dynarec_invalidate_range(dma_addr, count * size);
      for ( i = count * size; i; --i )
      {
        data = GPUreadData();
        mem_gpu_dma_write(dma_addr, data);
        dma_addr += 4;
      }
    }
    goto LABEL_27;
  }
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000201 )
  {
    words = count * size;
    if ( GPUwriteDataMem )
    {
      GPUwriteDataMem(src, words);
    }
    else
    {
      for ( ; words; --words )
        GPUwriteData(*src++);
    }
LABEL_27:
    status = irq_dma_assert_int(2u);
    gpu_dma2_state = 0;
    return status;
  }
  status = gpu_dma_channel_status[0] - 1;
  if ( *(uint32_t *)gpu_dma_channel_status == 0x1000401 )
  {
    GPUdmaChain(ram, dma_addr & 0x1FFFFF);
    while ( 1 )
    {
      header = mem_gpu_dma_read(dma_addr);
      block_total = HIBYTE(header) + total;
      next_addr = header & 0xFFFFFF;
      total = block_total;
      dma_addr = next_addr;
      if ( !next_addr || next_addr == 0xFFFFFF )
        break;
      if ( block_total >= 0x40 )
        break;
    }
    if ( block_total >= 0x40 )
    {
      gpu_dma2_delay_counter = 1;
      gpu_dma2_state = 1;
      return 1;
    }
    *(uint32_t *)gpu_dma_channel_status &= ~0x1000000u;
    status = irq_dma_assert_int(2u);
    gpu_dma2_state = -2;
  }
  else if ( (*(uint32_t *)gpu_dma_channel_status & 0x1000000) != 0 )
  {
    ui_error(
      "DMA[2] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
      *(uint32_t *)gpu_dma_channel_status,
      dma_addr,
      count,
      size);
  }
  return status;
}

char gpu_dma6_interrupt()
{
  char status;

  status = gpu_dma6_delay_counter;
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
  return status;
}

int gpu_frame_update()
{
  int value;
  DWORD elapsed;

  while ( PeekMessageA(&g_msg, nullptr, 0, 0, 1u) )
  {
    TranslateMessage(&g_msg);
    DispatchMessageA(&g_msg);
  }
  if ( use_performance_counters )
  {
    QueryPerformanceCounter(&gpu_performance_counter);
    for ( elapsed = gpu_performance_counter.LowPart - PerformanceCount.LowPart;
          gpu_performance_counter.QuadPart - PerformanceCount.QuadPart < gpu_performance_threshold;
          elapsed = gpu_performance_counter.LowPart - PerformanceCount.LowPart )
    {
      QueryPerformanceCounter(&gpu_performance_counter);
    }
    GPUupdateLace(elapsed);
    QueryPerformanceCounter(&gpu_performance_counter);
    PerformanceCount = gpu_performance_counter;
  }
  else
  {
    GPUupdateLace(value);
  }
  return cont_process_input();
}

HMODULE gpu_destroy()
{
  HMODULE ret;

  ret = hGpuModule;
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
    ret = (HMODULE)hOutputWnd;
    if ( hOutputWnd )
    {
      ret = (HMODULE)DestroyWindow(hOutputWnd);
      if ( !ret )
      {
        ret = (HMODULE)MessageBoxA(nullptr, "Could NOT release hWnd.", "SHUTDOWN ERROR", 0x40u);
        hOutputWnd = nullptr;
      }
    }
  }
  return ret;
}

int gpu_close()
{
  int status;

  status = GPUclose();
  gpu_closed = 1;
  return status;
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

static char gpu_pack_pixels(uint8_t *pixel, char color)
{
  char ret;

  ret = color;
  if ( color )
  {
    if ( color == 1 )
    {
      *pixel = -1;
      pixel[1] = -1;
      pixel[2] = -1;
      return (uint8_t)pixel + 1;
    }
    else if ( color == 2 )
    {
      *pixel = 0;
      pixel[1] = 0;
      pixel[2] = -1;
      return (uint8_t)pixel + 1;
    }
  }
  else
  {
    *pixel = 0;
    pixel[1] = 0;
    pixel[2] = 0;
    return (uint8_t)pixel + 1;
  }
  return ret;
}

static BOOL gpu_draw_text_on_screen(LPCSTR lpchText, void *dest)
{
  HDC DC;
  HDC CompatibleDC;
  HBRUSH SolidBrush;
  HPEN Pen;
  HGDIOBJ prev_bitmap;
  void *ppvBits;
  HGDIOBJ old_bitmap;
  HGDIOBJ old_brush;
  HGDIOBJ old_pen;
  HGDIOBJ dib;
  HGDIOBJ brush_obj;
  HGDIOBJ pen_obj;
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
  dib = CreateDIBSection(CompatibleDC, &pbmi, 0, &ppvBits, nullptr, 0);
  old_bitmap = SelectObject(CompatibleDC, dib);
  SolidBrush = CreateSolidBrush(0);
  brush_obj = SolidBrush;
  Pen = CreatePen(0, 0, 0xFF0000u);
  pen_obj = Pen;
  old_brush = SelectObject(CompatibleDC, SolidBrush);
  old_pen = SelectObject(CompatibleDC, Pen);
  SetTextColor(CompatibleDC, 0xFFu);
  SetBkColor(CompatibleDC, 0);
  Rectangle(CompatibleDC, left.left, left.top, left.right, left.bottom);
  InflateRect(&left, -3, -2);
  DrawTextA(CompatibleDC, lpchText, strlen(lpchText), &left, 0x25u);
  prev_bitmap = old_bitmap;
  qmemcpy(dest, ppvBits, 0x9000u);
  SelectObject(CompatibleDC, prev_bitmap);
  SelectObject(CompatibleDC, old_brush);
  SelectObject(CompatibleDC, old_pen);
  DeleteDC(CompatibleDC);
  DeleteObject(dib);
  DeleteObject(brush_obj);
  return DeleteObject(pen_obj);
}

static uint8_t * gpu_draw_no_save_pic(char *buffer, int slot)
{
  char *pixel;
  char *src;
  int row;
  int col;
  uint8_t component;
  uint8_t *cursor;
  uint8_t component2;
  char component3;
  int value;
  char *px;
  int count;
  uint8_t *px2;
  uint8_t *edge;
  int count2;
  uint8_t *edge2;

  pixel = buffer + 309;
  gpu_draw_text_on_screen("NO SAVE PIC", buffer);
  src = &gpu_save_pic_data[120 * slot];
  row = 20;
  do
  {
    col = 6;
    do
    {
      gpu_pack_pixels(pixel, (uint8_t)*src >> 6);
      cursor = pixel + 3;
      gpu_pack_pixels(cursor, (component >> 4) & 3);
      cursor += 3;
      gpu_pack_pixels(cursor, (component2 >> 2) & 3);
      cursor += 3;
      gpu_pack_pixels(cursor, component3 & 3);
      pixel = cursor + 3;
      src = (char *)(value + 1);
      --col;
    }
    while ( col );
    pixel += 312;
    --row;
  }
  while ( row );
  px = buffer;
  count = 128;
  do
  {
    px[36480] = 0;
    *px = 0;
    px2 = px + 1;
    px2[36480] = 0;
    *px2++ = 0;
    px2[36480] = -1;
    *px2 = -1;
    px = px2 + 1;
    --count;
  }
  while ( count );
  edge = buffer;
  count2 = 96;
  do
  {
    edge[381] = 0;
    *edge = 0;
    edge2 = edge + 1;
    edge2[381] = 0;
    *edge2++ = 0;
    edge2[381] = -1;
    *edge2 = -1;
    edge = edge2 + 382;
    --count2;
  }
  while ( count2 );
  return edge;
}

static uint8_t * gpu_draw_free_slot(char *buffer, int slot)
{
  char *pixel;
  char *src;
  int row;
  int col;
  uint8_t component;
  uint8_t *cursor;
  uint8_t component2;
  char component3;
  int value;
  char *px;
  int count;
  uint8_t *px2;
  uint8_t *edge;
  int count2;
  uint8_t *edge2;

  pixel = buffer + 309;
  gpu_draw_text_on_screen("FREE SLOT", buffer);
  src = &gpu_save_pic_data[120 * slot];
  row = 20;
  do
  {
    col = 6;
    do
    {
      gpu_pack_pixels(pixel, (uint8_t)*src >> 6);
      cursor = pixel + 3;
      gpu_pack_pixels(cursor, (component >> 4) & 3);
      cursor += 3;
      gpu_pack_pixels(cursor, (component2 >> 2) & 3);
      cursor += 3;
      gpu_pack_pixels(cursor, component3 & 3);
      pixel = cursor + 3;
      src = (char *)(value + 1);
      --col;
    }
    while ( col );
    pixel += 312;
    --row;
  }
  while ( row );
  px = buffer;
  count = 128;
  do
  {
    px[36480] = 0;
    *px = 0;
    px2 = px + 1;
    px2[36480] = 0;
    *px2++ = 0;
    px2[36480] = -1;
    *px2 = -1;
    px = px2 + 1;
    --count;
  }
  while ( count );
  edge = buffer;
  count2 = 96;
  do
  {
    edge[381] = 0;
    *edge = 0;
    edge2 = edge + 1;
    edge2[381] = 0;
    *edge2++ = 0;
    edge2[381] = -1;
    *edge2 = -1;
    edge = edge2 + 382;
    --count2;
  }
  while ( count2 );
  return edge;
}

int (__stdcall * gpu_display_flags(int flags))(uint32_t)
{
  int (__stdcall *fn)(uint32_t);

  fn = GPUdisplayFlags;
  if ( GPUdisplayFlags )
    return (int (__stdcall *)(uint32_t))GPUdisplayFlags(flags);
  return fn;
}

int (*gpu_make_snapshot())(void)
{
  int (*fn)(void);

  fn = (int (*)(void))GPUmakeSnapshot;
  if ( GPUmakeSnapshot )
    return GPUmakeSnapshot();
  return fn;
}

void gpu_show_screen_pic(uint8_t slot)
{
  void *buf;
  FILE *file;
  FILE *file2;
  FILE *file3;
  char Buffer[1024];

  if ( GPUshowScreenPic )
  {
    buf = malloc(0x9000u);
    sprintf(Buffer, "%s%s.%03d.pic", "sstates\\", default_filename, slot);
    file = fopen(Buffer, "rb");
    file2 = file;
    if ( file )
    {
      fread(buf, 1u, 0x9000u, file);
      fclose(file2);
    }
    else
    {
      sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, slot);
      file3 = fopen(Buffer, "rb");
      if ( file3 )
      {
        fclose(file3);
        gpu_draw_no_save_pic((char *)buf, slot);
      }
      else
      {
        gpu_draw_free_slot((char *)buf, slot);
      }
    }
    GPUshowScreenPic(buf);
    free(buf);
  }
}

int (__stdcall *gpu_hide_screen_pic())(uint32_t)
{
  int (__stdcall *fn)(uint32_t);

  fn = GPUshowScreenPic;
  if ( GPUshowScreenPic )
    return (int (__stdcall *)(uint32_t))GPUshowScreenPic(0);
  return fn;
}

int (__stdcall * gpu_do_freeze(int slot))(uint32_t, uint32_t)
{
  int (__stdcall *fn)(uint32_t, uint32_t);

  fn = GPUfreeze;
  if ( GPUfreeze )
    return (int (__stdcall *)(uint32_t, uint32_t))GPUfreeze(2, &slot);
  return fn;
}

int (__stdcall * gpu_cursor(int x, int y, int flag))(uint32_t, uint32_t, uint32_t)
{
  int (__stdcall *fn)(uint32_t, uint32_t, uint32_t);

  fn = GPUcursor;
  if ( GPUcursor )
    return (int (__stdcall *)(uint32_t, uint32_t, uint32_t))GPUcursor(x, y, flag);
  return fn;
}

void gpu_freeze(const char *id, int ArgList, const char *picname)
{
  uint8_t *buf;
  void *pic;
  FILE *file;
  char Buffer[3];
  char FileName[1024];

  if ( GPUfreeze )
  {
    buf = (uint8_t *)malloc(0x100408u);
    *(uint32_t *)buf = 1;
    sprintf(Buffer, "%s", id);
    GPUfreeze(1, buf);
    gzwrite(ArgList, (uint8_t *)Buffer, 7u);
    gzwrite(ArgList, buf, 0x100408u);
    free(buf);
    if ( GPUgetScreenPic )
    {
      pic = malloc(0x9000u);
      sprintf(FileName, "%s.pic", picname);
      GPUgetScreenPic(pic);
      file = fopen(FileName, "wb");
      fwrite(pic, 1u, 0x9000u, file);
      fclose(file);
      free(pic);
    }
  }
  else
  {
    sprintf(Buffer, "%s", id);
    gzwrite(ArgList, (uint8_t *)Buffer, 7u);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}

void gpu_unfreeze(int unused, uint32_t *ArgList)
{
  char *buf;
  char header[16];

  if ( GPUfreeze )
  {
    buf = (char *)malloc(0x100408u);
    gzread(ArgList, header, 7);
    gzread(ArgList, buf, 1049608);
    GPUfreeze(0, buf);
    free(buf);
  }
  else
  {
    gzread(ArgList, header, 7);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}
