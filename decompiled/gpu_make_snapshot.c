#include "pch.h"
int (*gpu_make_snapshot())(void)
{
  int (*result)(void); // eax

  result = (int (*)(void))GPUmakeSnapshot;
  if ( GPUmakeSnapshot )
    return GPUmakeSnapshot();
  return result;
}
