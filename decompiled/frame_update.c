#include "pch.h"
int frame_update()
{
  DWORD i; // ecx

  while ( PeekMessageA(&stru_50AB80, nullptr, 0, 0, 1u) )
  {
    TranslateMessage(&stru_50AB80);
    DispatchMessageA(&stru_50AB80);
  }
  if ( byte_4FD995 )
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
    return process_input();
  }
  else
  {
    ((void (*)(void))GPUupdateLace)();
    return process_input();
  }
}
