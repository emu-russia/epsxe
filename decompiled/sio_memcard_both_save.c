#include "pch.h"
// Microsoft VisualC 2-14/net runtime
char sio_memcard_both_save()
{
  sio_memcard1_save();
  return sio_memcard2_save();
}
