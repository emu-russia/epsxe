#include "pch.h"
void loader_load_zip()
{
  char *v0; // esi
  void *v1; // esi
  char *v2; // ebx
  char *v3; // eax
  unsigned __int8 v4; // bl
  int v5; // eax
  const char *v6; // esi
  char *Str2; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h] BYREF

  v0 = &FileName[-3];
  if ( !strncmp(&FileName[strlen(FileName) - 3], "zip", 3u) || !strncmp(&v0[strlen(FileName)], "ZIP", 3u) )
  {
    if ( !strncmp(&v0[strlen(FileName)], "zip", 3u) || !strncmp(&v0[strlen(FileName)], "ZIP", 3u) )
    {
      v1 = malloc(0x2000u);
      memset(v1, 0, 0x2000u);
      if ( zip_load_file(FileName) )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      free(v1);
      if ( !zip_num_entries_loaded )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      if ( zip_num_entries_loaded == 1 )
      {
        if ( strncmp(&byte_566980[strlen(byte_566980) - 3], "exe", 3u)
          && strncmp(&byte_566980[strlen(byte_566980) - 3], "EXE", 3u) )
        {
          fatal_error_with_message_box("* EPSX: DEMO not found [%s]. \n", byte_566980);
        }
        Str2 = (char *)malloc(Size[0]);
        if ( zip_extract_file(FileName, byte_566980, (LPVOID *)&Str2, (size_t *)&v8) )
          fatal_error_with_message_box(" * EPSX: error loading .zip file.");
        v2 = Str2;
        if ( strncmp("PS-X EXE", Str2, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", byte_566980);
        v3 = Str2;
        qmemcpy((char *)ram + (*((_DWORD *)v2 + 6) & 0x1FFFFF), Str2 + 2048, *((_DWORD *)v2 + 7));
        cpu_gpr[28] = *((_DWORD *)v2 + 5);
        cpu_gpr[29] = -2145386752;
        cpu_gpr[30] = -2145386752;
        cpu_gpr[31] = 0;
        *(_DWORD *)reg_pc = *((_DWORD *)v2 + 4);
        free(v3);
      }
      else
      {
        v4 = 0;
        LOBYTE(Str2) = -1;
        if ( zip_num_entries_loaded <= 0 )
          goto LABEL_26;
        v5 = 0;
        do
        {
          v6 = &byte_566980[256 * v5];
          if ( !strncmp(&v6[strlen(v6) - 3], "pll", 3u) || !strncmp(&v6[strlen(v6) - 3], "PLL", 3u) )
            LOBYTE(Str2) = v4;
          LOBYTE(v8) = ++v4;
          v5 = v4;
        }
        while ( v4 < zip_num_entries_loaded );
        if ( (_BYTE)Str2 == 0xFF )
LABEL_26:
          fatal_error_with_message_box("* EPSX: DEMO .pll not found. \n");
        loader_load_file(&byte_566980[256 * (unsigned __int8)Str2], Size[(unsigned __int8)Str2]);
      }
    }
  }
  else
  {
    loader_load_demo(FileName);
  }
}
