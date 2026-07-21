#include "pch.h"
void ppf_free()
{
  if ( ppf_enabled )
  {
    free(ppf_file_data);
    free(ppf_sector_lists);
  }
}
