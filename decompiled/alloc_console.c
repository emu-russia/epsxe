#include "pch.h"
char alloc_console()
{
  HANDLE StdHandle; // eax

  LOBYTE(StdHandle) = console_allocated;
  if ( console_allocated )
  {
    AllocConsole();
    SetConsoleTitleA("ePSXe - Enhanced PSX emulator");
    StdHandle = GetStdHandle(0xFFFFFFF5);
    hConsoleOutput = StdHandle;
  }
  return (char)StdHandle;
}
