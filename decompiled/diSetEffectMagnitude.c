#include "pch.h"
int __cdecl diSetEffectMagnitude(int a1, int a2, int a3, int a4)
{
  int result; // eax

  if ( a1 )
  {
    result = g_EffectType1[a4];
    if ( result == 1 )
    {
      return diSetConstantForceMagnitude(g_MouseY[g_PlayerDeviceMap1[a4]], a2);
    }
    else if ( result == 2 )
    {
      return diSetPeriodicForceMagnitude((_DWORD *)g_MouseY[g_PlayerDeviceMap1[a4]], a2);
    }
  }
  else
  {
    result = g_EffectType2[a4];
    if ( result == 1 )
    {
      return diSetConstantForceMagnitude(dword_4F8304[g_PlayerDeviceMap1[a4]], a2);
    }
    else if ( result == 2 )
    {
      return diSetPeriodicForceMagnitude((_DWORD *)dword_4F8304[g_PlayerDeviceMap1[a4]], a2);
    }
  }
  return result;
}
