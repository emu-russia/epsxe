#include "pch.h"
int save_temp_memcard1()
{
  sprintf((char *const)Memcard1, "memcards\\temp.000");
  sio_memcard1_file_offset = 0;
  sio_memcard_loaded = 1;
  return cfg_save_settings();
}
