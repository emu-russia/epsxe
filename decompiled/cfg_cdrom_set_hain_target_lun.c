#include "pch.h"
int cfg_cdrom_set_hain_target_lun()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_haid);
  cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromHain", (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_target);
  cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromTarget", (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_lun);
  return cfg_set_value("Software\\epsxe\\config\\cdrom9x", "CdromLun", (BYTE *)Buffer);
}
