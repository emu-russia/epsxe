#include "pch.h"
int (*gpu_make_snapshot())(void)
{
  int (*result)(void); // eax

  result = GPUmakeSnapshot;
  if ( GPUmakeSnapshot )
    return (int (*)(void))GPUmakeSnapshot();
  return result;
}
