#include "pch.h"
HANDLE W2k_cdrom_deinit()
{
  HANDLE result; // eax

  if ( byte_456D70 >= 0 )
    sub_42FA10();
  if ( dword_50C37C == 3 )
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
