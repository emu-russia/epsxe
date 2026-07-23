#include "pch.h"
void dynarec_deinit()
{
  if ( recomp_buffer )
    free(recomp_buffer);
  if ( recomp_code_base )
    free(recomp_code_base);
  if ( recomp_metadata )
    free(recomp_metadata);
}
