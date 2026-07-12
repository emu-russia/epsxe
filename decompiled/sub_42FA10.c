#include "pch.h"
FILE *sub_42FA10()
{
  FILE *result; // eax

  if ( cd_savefake_flag == 1 )
  {
    result = FileHandle;
    if ( !FileHandle )
      return result;
    fseek(FileHandle, 0, 0);
    fwrite(&byte_50A090, 1u, 2u, FileHandle);
    fwrite(cdrom_fake_data, 1u, 0x145320u, FileHandle);
  }
  result = FileHandle;
  if ( FileHandle )
    return (FILE *)_close((int)FileHandle);
  return result;
}
