#include "pch.h"
int cdrom_iso_set_path()
{
  return reg_set_value("Software\\epsxe\\config", "IsoDirectory", (BYTE *)IsoDirectory);
}
