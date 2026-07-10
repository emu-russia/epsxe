#include "pch.h"
int sub_422360()
{
  sprintf((char *const)Memcard1, "memcards\\temp.000");
  Offset = 0;
  byte_4FC460 = 1;
  return save_settings();
}
