#include "pch.h"
int (*spu_update())(void)
{
  int (*result)(void); // eax

  result = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return result;
}
