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
