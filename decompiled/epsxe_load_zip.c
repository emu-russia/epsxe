#include "pch.h"
void epsxe_load_zip()
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

  v0 = &aNull_0[-3];
  if ( !strncmp(&aNull_0[strlen(aNull_0) - 3], off_454EE0, 3u) || !strncmp(&v0[strlen(aNull_0)], off_454EDC, 3u) )
  {
    if ( !strncmp(&v0[strlen(aNull_0)], off_454EE0, 3u) || !strncmp(&v0[strlen(aNull_0)], off_454EDC, 3u) )
    {
      v1 = malloc(0x2000u);
      memset(v1, 0, 0x2000u);
      if ( sub_420240(aNull_0) )
        fatal_error_with_message_box(aEpsxErrorLoadi);
      free(v1);
      if ( !dword_4FC458 )
        fatal_error_with_message_box(aEpsxErrorLoadi);
      if ( dword_4FC458 == 1 )
      {
        if ( strncmp(&byte_566980[strlen(byte_566980) - 3], off_454EB4, 3u)
          && strncmp(&byte_566980[strlen(byte_566980) - 3], off_44ED60, 3u) )
        {
          fatal_error_with_message_box("* EPSX: DEMO not found [%s]. \n", byte_566980);
        }
        Str2 = (char *)malloc(Size[0]);
        if ( sub_41FEB0(aNull_0, byte_566980, (LPVOID *)&Str2, (size_t *)&v8) )
          fatal_error_with_message_box(aEpsxErrorLoadi);
        v2 = Str2;
        if ( strncmp(Str1, Str2, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", byte_566980);
        v3 = Str2;
        qmemcpy((char *)ram_0 + (*((_DWORD *)v2 + 6) & 0x1FFFFF), Str2 + 2048, *((_DWORD *)v2 + 7));
        dword_50C350 = *((_DWORD *)v2 + 5);
        dword_50C354 = -2145386752;
        dword_50C358 = -2145386752;
        dword_50C35C = 0;
        reg_pc = *((_DWORD *)v2 + 4);
        free(v3);
      }
      else
      {
        v4 = 0;
        LOBYTE(Str2) = -1;
        if ( dword_4FC458 <= 0 )
          goto LABEL_26;
        v5 = 0;
        do
        {
          v6 = &byte_566980[256 * v5];
          if ( !strncmp(&v6[strlen(v6) - 3], off_454E90, 3u) || !strncmp(&v6[strlen(v6) - 3], off_454E8C, 3u) )
            LOBYTE(Str2) = v4;
          LOBYTE(v8) = ++v4;
          v5 = v4;
        }
        while ( v4 < dword_4FC458 );
        if ( (_BYTE)Str2 == 0xFF )
LABEL_26:
          fatal_error_with_message_box(aEpsxDemoPllNot);
        epsxe_load(&byte_566980[256 * (unsigned __int8)Str2], Size[(unsigned __int8)Str2]);
      }
    }
  }
  else
  {
    epsxe_load_demo(aNull_0);
  }
}
