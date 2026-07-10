#include "pch.h"
int sub_41C940()
{
  FILE *v0; // eax

  if ( !strncmp(aNull_0, aNull, 4u) )
    return 0;
  v0 = fopen(aNull_0, Mode);
  if ( !v0 )
    fatal_error_with_message_box(" * EPSX: DEMO not found [%s]. \n", aNull_0);
  fclose(v0);
  return 1;
}
