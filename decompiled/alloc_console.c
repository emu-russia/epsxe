#include "pch.h"
char alloc_console()
{
  HANDLE StdHandle; // eax

  LOBYTE(StdHandle) = console_allocated;
  if ( console_allocated )
  {
    AllocConsole();
    SetConsoleTitleA("ePSXe - Enhanced PSX emulator");
    StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    hConsoleOutput = StdHandle;
  }
  return (char)StdHandle;
}
