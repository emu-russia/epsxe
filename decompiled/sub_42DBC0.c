#include "pch.h"
__int16 __cdecl sub_42DBC0(unsigned __int16 a1, __int16 a2)
{
  __int16 result; // ax

  result = a2;
  if ( a2 )
    *((_WORD *)&word_4FD88C + a1) = a2;
  return result;
}
