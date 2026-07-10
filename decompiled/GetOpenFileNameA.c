#include "pch.h"
// attributes: thunk
BOOL __stdcall GetOpenFileNameA(LPOPENFILENAMEA a1)
{
  return __imp_GetOpenFileNameA(a1);
}
