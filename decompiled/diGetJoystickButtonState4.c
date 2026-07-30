#include "pch.h"
int __cdecl diGetJoystickButtonState4(int a1)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * a1 + 1])];
}
