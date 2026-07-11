#include "pch.h"
int touch_demo_file()
{
  FILE *v0; // eax

  if ( !strncmp(FileName, "NULL", 4u) )
    return 0;
  v0 = fopen(FileName, "rb");
  if ( !v0 )
    fatal_error_with_message_box(" * EPSX: DEMO not found [%s]. \n", FileName);
  fclose(v0);
  return 1;
}
