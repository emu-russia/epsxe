#include "pch.h"
char sio_memcard2_save()
{
  char result; // al
  FILE *v1; // esi

  result = sio_memcard_loaded;
  if ( sio_memcard_loaded )
  {
    v1 = fopen((const char *)Memcard2, "wb");
    if ( v1 )
    {
      fseek(v1, sio_memcard2_file_offset, 0);
      fwrite(sio_memcard_data_slot2, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard2);
    }
  }
  return result;
}
