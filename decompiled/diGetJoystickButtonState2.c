#include "pch.h"
int __cdecl diGetJoystickButtonState2(int a1)
{
  return g_KeyboardState[(unsigned __int16)word_4FD88E[4 * a1]];
}
