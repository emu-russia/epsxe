#include "pch.h"
int (*sub_40C050())(void)
{
  int (*result)(void); // eax

  result = SPUupdate;
  if ( SPUupdate )
    return (int (*)(void))SPUupdate();
  return result;
}
