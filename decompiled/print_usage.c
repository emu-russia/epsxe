#include "pch.h"
void print_usage()
{
  printf(" %s v.%1.1f.%d emulator by ePSXe team. Copyright 2000/2002. \n\n", "ePSXe", 1.6, 0);
  printf("      epsxe [options] [PS-EXE] \n");
  printf("      options: \n\n");
  printf("        -pslib                     -   Load libpsx.exe.\n");
  printf("        -nocd                      -   Disable CDR emulation.\n");
  printf("        -sound/-nosound            -   Enable/Disable sound.\n");
  printf("        -xasound/-noxasound        -   Enable/Disable XA sound.\n");
  printf("        -audiocd/noaudiocd         -   Enable/Disable CDDA audio.\n");
  printf("        -forcespu/-noforcespu      -   Enable/Disable SPU irq always ON.\n");
  printf("        -nosubchan/-subchan        -   Enable/Disable subchannel support.\n");
  printf("        -forcepad/-noforcepad      -   Enable/Disable SIO irq always ON.\n");
  printf("        -memcard/-nomemcard        -   Enable/Disable memcard emulation.\n");
  printf("        -mdec/-nomdec              -   Enable/Disable MDEC emulation.\n");
  printf("        -mdectiming/-nomdectiming  -   Enable/Disable MDEC accurate timing.\n");
  printf("        -adjusttiming              -   On the fly re-adjust timing.\n");
  printf("    [Press a key to continue] \n");
  _getch();
  printf("        -oldtiming                 -   Use pre-1.5.1 timing. \n");
  printf("        -fastboot/slowboot         -   Fast/Slow boot cdrom (psx logo).\n");
  printf("        -nogui                     -   Disable internal GUI.\n");
  printf("        -loadiso <file>            -   Load iso file. (Cdrwin/Clonecd)\n");
  printf("        -loadcheat <file>          -   Load internal cheat file.\n");
  printf("        -loadppf <file>            -   Load ppf file.\n");
  printf("        -ppf/-noppf                -   Enable/Disable ppf patches.\n");
  printf("        -loadmemc0 <file>          -   Map file to memcard 0.\n");
  printf("        -loadmemc1 <file>          -   Map file to memcard 1.\n");
  printf("        -ssv0                      -   Save sstate version v.0\n");
  printf("        -gun                       -   Enable namco gun emulation\n");
  printf("        -mouse                     -   Enable mouse emulation.\n");
  printf("        -analogN                   -   Enable dualshock emulation in pad N.\n");
  printf("        -p <num>                   -   Mem access penalty (d.5).\n");
  printf("        -pe2                       -   Parasite eve 2 cheat.\n");
  printf("        -help                      -   Where are you now? ;-)\n");
  exit(0);
}
