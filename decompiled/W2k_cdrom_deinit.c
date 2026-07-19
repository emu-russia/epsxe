#include "pch.h"
HANDLE W2k_cdrom_deinit()
{
  HANDLE result; // eax

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  if ( dword_504C84 )
    free(dword_504C84);
  if ( byte_4FD9C8 && hObject )
    sub_434C60();
  if ( Stream )
    fclose(Stream);
  result = hObject;
  if ( hObject )
  {
    W2k_cdrom_stop();
    result = hObject;
    if ( hObject )
      return (HANDLE)CloseHandle(hObject);
  }
  return result;
}
