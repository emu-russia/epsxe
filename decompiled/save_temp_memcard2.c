#include "pch.h"
int save_temp_memcard2()
{
  sprintf((char *const)Memcard2, "memcards\\temp.001");
  dword_4FC474 = 0;
  byte_4FC460 = 1;
  return save_settings();
}
