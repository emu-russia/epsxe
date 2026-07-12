#include "pch.h"
int (*__cdecl spu_async_update(int a1))(void)
{
  int (*result)(void); // eax

  if ( SPUasync )
    return SPUasync(a1);
  result = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return result;
}
