#include "pch.h"
char __cdecl set_gpu_freeze_counter(char a1)
{
  LOBYTE(gpu_freeze_counter) = a1;
  return a1;
}
