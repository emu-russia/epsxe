#include "pch.h"
int (*__cdecl spu_async_update(int a1))(void)
{
  int (*result)(void); // eax

  if ( SPUasync )
    return (int (*)(void))SPUasync(a1);
  result = SPUupdate;
  if ( SPUupdate )
    return (int (*)(void))SPUupdate();
  return result;
}
