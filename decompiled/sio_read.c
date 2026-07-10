#include "pch.h"
int __cdecl sub_422180(int a1, char a2)
{
  int result; // eax

  result = 0xFFFF;
  switch ( a2 )
  {
    case 1:
      return (unsigned __int8)sio_data_read(a1);
    case 2:
      return (unsigned __int16)sio_read_half(a1);
    case 4:
      return sio_read_word(a1);
  }
  return result;
}
