#include "pch.h"
int cfg_cdrom_set_letter()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_letter);
  return cfg_set_value("Software\\epsxe\\config", "CdromLetter", (BYTE *)Buffer);
}
