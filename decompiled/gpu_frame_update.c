#include "pch.h"
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
    QueryPerformanceCounter(&stru_50AA48);
    for ( i = stru_50AA48.LowPart - PerformanceCount.LowPart;
          stru_50AA48.QuadPart - PerformanceCount.QuadPart < qword_50AE58;
          i = stru_50AA48.LowPart - PerformanceCount.LowPart )
    {
      QueryPerformanceCounter(&stru_50AA48);
    }
    GPUupdateLace(i);
    QueryPerformanceCounter(&stru_50AA48);
    PerformanceCount = stru_50AA48;
  }
  else
  {
    GPUupdateLace(v0);
  }
  return cont_process_input();
}
