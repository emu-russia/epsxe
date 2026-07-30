#include "pch.h"
int __cdecl diGetJoystickButtonState1(int a1)
{
  return g_KeyboardState[LOWORD(GamepadAxis[2 * a1])];
}
