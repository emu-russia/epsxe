#include "pch.h"
unsigned int __cdecl zip_copy_sliding_window_to_output(const void *a1, unsigned int a2)
{
  qmemcpy((void *)zip_inflate_output_ptr, a1, a2);
  zip_inflate_output_ptr += a2;
  return a2;
}
