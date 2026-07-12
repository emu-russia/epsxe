#include "pch.h"
void ppf_free()
{
  if ( auto_ppf_load )
  {
    free(dword_4FFC28);
    free(dword_4FFC24);
  }
}
