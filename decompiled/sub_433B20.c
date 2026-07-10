#include "pch.h"
char sub_433B20()
{
  int v0; // ebx
  CHAR RootPathName[4]; // [esp+8h] [ebp-4h] BYREF

  v0 = 65;
  while ( 1 )
  {
    sprintf(RootPathName, "%c:\\", v0);
    if ( GetDriveTypeA(RootPathName) == 5 )
      break;
    if ( (unsigned int)++v0 > 0x5A )
      return 0;
  }
  return v0;
}
