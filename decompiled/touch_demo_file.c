#include "pch.h"
int touch_demo_file()
{
  FILE *v0; // eax

  if ( !strncmp(aNull_0, "NULL", 4u) )
    return 0;
  v0 = fopen(aNull_0, "rb");
  if ( !v0 )
    fatal_error_with_message_box(" * EPSX: DEMO not found [%s]. \n", aNull_0);
  fclose(v0);
  return 1;
}
