#include "pch.h"
int cdrom_set_hain_target_lun()
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%d", cdrom_hain);
  reg_set_value(aSoftwareEpsxeC_0, aCdromhain, (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_target);
  reg_set_value(aSoftwareEpsxeC_0, aCdromtarget, (BYTE *)Buffer);
  sprintf(Buffer, "%d", cdrom_lun);
  return reg_set_value(aSoftwareEpsxeC_0, aCdromlun, (BYTE *)Buffer);
}
