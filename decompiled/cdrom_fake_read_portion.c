#include "pch.h"
size_t __cdecl cdrom_fake_read_portion(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer)
{
  int v4; // eax

  v4 = *((_DWORD *)cdrom_fake_data + sub_42C6D0(a1, a2, a3));
  if ( v4 == -1 )
  {
    _close((int)FileHandle);
    fatal_error_with_message_box(" * fake sector doesn't found \n");
  }
  fseek(FileHandle, v4 + 1332002, 0);
  return fread(Buffer, 1u, 0x930u, FileHandle);
}
