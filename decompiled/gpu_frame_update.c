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
