#include "pch.h"
char sio_memcard_load()
{
  FILE *v0; // eax
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax
  FILE *v4; // eax
  FILE *v5; // esi
  FILE *v6; // esi

  LOBYTE(v0) = sio_memcard_loaded;
  if ( !sio_memcard_loaded )
  {
    if ( !strcmp((const char *)Memcard1, "NULL") )
      sprintf((char *const)Memcard1, "%s", "memcards\\epsxe000.mcr");
    if ( !strcmp((const char *)Memcard2, "NULL") )
      sprintf((char *const)Memcard2, "%s", "memcards\\epsxe001.mcr");
    for ( i = 0; i < 0x20000; ++i )
    {
      sio_memcard_data_slot2[i] = 0;
      sio_memcard_data_slot1[i] = 0;
    }
    sio_memcard_data_slot2[0] = 77;
    sio_memcard_data_slot1[0] = 77;
    byte_546861[0] = 67;
    memcard2_id_byte = 67;
    byte_5468DF = 14;
    memcard2_checksum = 14;
    for ( j = 0; j < 0x780; j += 128 )
    {
      byte_5468E0[j] = -96;
      memcard2_data[j] = -96;
      byte_5468E8[j] = -1;
      byte_5268E8[j] = -1;
      byte_5468E9[j] = -1;
      byte_5268E9[j] = -1;
      byte_54695F[j] = -96;
      byte_52695F[j] = -96;
    }
    for ( k = 0; k < 0xA00; k += 128 )
    {
      byte_547060[k] = -1;
      byte_527060[k] = -1;
      byte_547060[k + 1] = -1;
      byte_527061[k] = -1;
      byte_547060[k + 2] = -1;
      byte_527062[k] = -1;
      byte_547060[k + 3] = -1;
      byte_527063[k] = -1;
      byte_547060[k + 8] = -1;
      byte_527068[k] = -1;
      byte_547060[k + 9] = -1;
      byte_527069[k] = -1;
    }
    v4 = fopen((const char *)Memcard1, "rb");
    v5 = v4;
    if ( v4 )
    {
      fseek(v4, 0, 2);
      sio_memcard1_file_offset = ftell(v5) - 0x20000;
      fseek(v5, sio_memcard1_file_offset, 0);
      fread(sio_memcard_data_slot1, 1u, 0x20000u, v5);
      fclose(v5);
    }
    else
    {
      sio_memcard1_file_offset = 0;
    }
    v0 = fopen((const char *)Memcard2, "rb");
    v6 = v0;
    if ( v0 )
    {
      fseek(v0, 0, 2);
      sio_memcard2_file_offset = ftell(v6) - 0x20000;
      fseek(v6, sio_memcard2_file_offset, 0);
      fread(sio_memcard_data_slot2, 1u, 0x20000u, v6);
      LOBYTE(v0) = fclose(v6);
    }
    else
    {
      sio_memcard2_file_offset = 0;
    }
    sio_memcard_loaded = 1;
  }
  return (char)v0;
}
