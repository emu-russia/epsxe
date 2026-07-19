#include "pch.h"
int cfg_cdrom_iso_set_path()
{
  return cfg_set_value("Software\\epsxe\\config", "IsoDirectory", (BYTE *)IsoDirectory);
}
