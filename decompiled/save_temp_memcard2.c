#include "pch.h"
int save_temp_memcard2()
{
  sprintf((char *const)Memcard2, "memcards\\temp.001");
  sio_memcard2_file_offset = 0;
  sio_memcard_loaded = 1;
  return cfg_save_settings();
}
