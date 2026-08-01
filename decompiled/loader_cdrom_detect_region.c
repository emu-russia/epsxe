#include "pch.h"
int loader_cdrom_detect_region()
{
  int result; // eax
  unsigned int i; // esi
  const char *v2; // [esp-4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( loaded_file_type != 3 && loaded_file_type != 1 )
  {
    sprintf(Buffer, "DEMO_999.99");
    result = sprintf(default_filename, "%s", Buffer);
    dword_45593C = 262;
    cpu_speed_scale = 2154;
    country_setting = 0;
    return result;
  }
  cdfs_load_executable(Buffer);
  if ( Buffer[strlen(Buffer) - 2] == ';' )
    Buffer[strlen(Buffer) - 2] = 0;
  sprintf(default_filename, "%s", Buffer);
  for ( i = 0; i < strlen(default_filename); ++i )
    default_filename[i] = towupper(default_filename[i]);
  loader_parse_cheat_entry(default_filename, Buffer);
  sub_41BDC0(default_filename);
  if ( country_setting == 1 )
  {
    v2 = " * Force PAL cdrom detected. \n";
  }
  else
  {
    if ( !country_setting )
    {
      dword_45593C = 262;
      cpu_speed_scale = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * Force NTSC cdrom detected. \n");
    }
    if ( default_filename[2] != 'E' && default_filename[2] != 'e' )
    {
      country_setting = 0;
      dword_45593C = 262;
      cpu_speed_scale = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * NTSC cdrom detected. \n");
    }
    country_setting = 1;
    v2 = " * PAL cdrom detected. \n";
  }
  dword_45593C = 312;
  cpu_speed_scale = old_timing != 0 ? 1923 : 2171;
  return dbg_print(v2);
}
