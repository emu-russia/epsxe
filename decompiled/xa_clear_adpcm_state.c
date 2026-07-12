#include "pch.h"
_DWORD *__cdecl xa_clear_adpcm_state(_DWORD *a1)
{
  *a1 = 0;
  a1[1] = 0;
  return a1;
}
