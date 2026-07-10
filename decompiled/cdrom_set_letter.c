#include "pch.h"
int cdrom_set_letter()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_letter);
  return reg_set_value("Software\\epsxe\\config", "CdromLetter", (BYTE *)Buffer);
}
