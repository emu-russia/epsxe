#include "pch.h"
char gpu_freeze_with_counter()
{
  LOBYTE(gpu_freeze_counter) = ((unsigned __int8)gpu_freeze_counter + 1) % 5;
  do_GPUfreeze((unsigned __int8)gpu_freeze_counter);
  return gpu_freeze_counter;
}
