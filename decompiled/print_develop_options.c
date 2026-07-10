#include "pch.h"
void print_develop_options()
{
  printf("      develop options: \n\n");
  printf("        -nocdstatus                -   No return cdstatus.\n");
  printf("        -noauto                    -   Disable autoconf/patch.\n");
  printf("        -noignorecmd               -   No Ignore cdrom commands.\n");
  printf("        -frc1                      -   Faster rootcounter1.\n");
  printf("        -nocputrick                -   Disable a old cpu trick.\n");
  printf("        -extsubchanhle             -   Enable subchannel hle (extplug).\n");
  exit(0);
}
