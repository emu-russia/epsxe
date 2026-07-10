#include "pch.h"
int sub_431540()
{
  if ( byte_456D70 >= 0 )
    sub_42FA10();
  if ( dword_50C37C == 3 )
    iso_close();
  if ( dword_504C84 )
    free(dword_504C84);
  if ( byte_4FD9C8 )
    sub_431680();
  if ( Stream )
    fclose(Stream);
  W9x_cdrom_stop();
  return sub_4313E0();
}
