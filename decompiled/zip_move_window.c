#include "pch.h"
unsigned int __cdecl zip_move_window(const void *a1, unsigned int a2)
{
  qmemcpy((void *)zipfile_output_buffer, a1, a2);
  zipfile_output_buffer += a2;
  return a2;
}
