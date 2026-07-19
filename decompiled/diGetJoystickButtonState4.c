#include "pch.h"
int __cdecl GetJoystickButtonState4(int a1)
{
  return g_KeyboardState[(unsigned __int16)word_4FD892[4 * a1]];
}
