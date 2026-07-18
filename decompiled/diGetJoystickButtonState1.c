#include "pch.h"
int __cdecl diGetJoystickButtonState1(int a1)
{
  return g_KeyboardState[LOWORD(word_4FD88C[2 * a1])];
}
