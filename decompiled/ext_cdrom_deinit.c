#include "pch.h"
int (*ext_cdrom_deinit())(void)
{
  int (*result)(void); // eax

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  ext_CDRstop();
  if ( CDRclose )
    CDRclose();
  result = (int (*)(void))CDRshutdown;
  if ( CDRshutdown )
    return CDRshutdown();
  return result;
}
