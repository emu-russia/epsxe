#include "pch.h"
HMODULE W9x_cdrom_deinit()
{
  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  if ( dword_504C84 )
    free(dword_504C84);
  if ( byte_4FD9C8 )
    W9x_disable_subchannel_mode();
  if ( Stream )
    fclose(Stream);
  W9x_cdrom_stop();
  return W9x_free_winaspi_dll();
}
