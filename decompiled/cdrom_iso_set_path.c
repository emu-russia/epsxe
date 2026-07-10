#include "pch.h"
int cdrom_iso_set_path()
{
  return reg_set_value(SubKey, aIsodirectory, &byte_8B3980);
}
