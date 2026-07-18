#include "pch.h"
int __cdecl diGetJoystickButtonState3(int a1)
{
  return g_KeyboardState[LOWORD(word_4FD890[2 * a1])];
}
