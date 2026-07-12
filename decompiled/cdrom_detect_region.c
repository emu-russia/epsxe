#include "pch.h"
int cdrom_detect_region()
{
  int result; // eax
  unsigned int i; // esi
  const char *v2; // [esp-4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( loaded_file_type != 3 && loaded_file_type != 1 )
  {
    sprintf(Buffer, "DEMO_999.99");
    result = sprintf(byte_8B3D80, "%s", Buffer);
    dword_45593C = 262;
    dword_455940 = 2154;
    country_setting = 0;
    return result;
  }
  sub_436AF0(Buffer);
  if ( Buffer[strlen(Buffer) - 2] == 59 )
    Buffer[strlen(Buffer) - 2] = 0;
  sprintf(byte_8B3D80, "%s", Buffer);
  for ( i = 0; i < strlen(byte_8B3D80); ++i )
    byte_8B3D80[i] = towupper(byte_8B3D80[i]);
  sub_41BEA0(byte_8B3D80, Buffer);
  sub_41BDC0(byte_8B3D80);
  if ( country_setting == 1 )
  {
    v2 = " * Force PAL cdrom detected. \n";
  }
  else
  {
    if ( !country_setting )
    {
      dword_45593C = 262;
      dword_455940 = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * Force NTSC cdrom detected. \n");
    }
    if ( byte_8B3D82 != 'E' && byte_8B3D82 != 'e' )
    {
      country_setting = 0;
      dword_45593C = 262;
      dword_455940 = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * NTSC cdrom detected. \n");
    }
    country_setting = 1;
    v2 = " * PAL cdrom detected. \n";
  }
  dword_45593C = 312;
  dword_455940 = old_timing != 0 ? 1923 : 2171;
  return dbg_print(v2);
}
