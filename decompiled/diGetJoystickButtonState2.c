#include "pch.h"
int __cdecl diGetJoystickButtonState2(int a1)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * a1])];
}
