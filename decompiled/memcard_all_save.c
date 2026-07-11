#include "pch.h"
char memcard_all_save()
{
  int v0; // eax

  v0 = dword_4FC478;
  if ( dword_4FC478 )
    v0 = ++dword_4FC478;
  if ( dword_4FC47C )
    ++dword_4FC47C;
  if ( v0 == 120 )
  {
    dword_4FC478 = 0;
    LOBYTE(v0) = memcard1_save();
  }
  if ( dword_4FC47C == 120 )
  {
    dword_4FC47C = 0;
    LOBYTE(v0) = memcard2_save();
  }
  return v0;
}
