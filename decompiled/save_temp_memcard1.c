#include "pch.h"
int save_temp_memcard1()
{
  sprintf((char *const)Memcard1, "memcards\\temp.000");
  Offset = 0;
  byte_4FC460 = 1;
  return save_settings();
}
