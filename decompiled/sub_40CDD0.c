#include "pch.h"
__int16 sub_40CDD0()
{
  __int16 result; // ax

  result = *(_WORD *)((char *)spu_ram + dword_4F7554);
  dword_4F7554 = (dword_4F7554 + 2) & 0x7FFFF;
  return result;
}
