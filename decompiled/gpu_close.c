#include "pch.h"
int gpu_close()
{
  int result; // eax

  result = GPUclose();
  gpu_closed = 1;
  return result;
}
