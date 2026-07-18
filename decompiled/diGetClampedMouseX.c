#include "pch.h"
int diGetClampedMouseX()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  diGetMouseState();
  result = g_MouseX;
  if ( g_MouseX < g_MouseMinX )
  {
    result = g_MouseMinX;
    g_MouseX = g_MouseMinX;
  }
  if ( result > g_MouseMaxX )
  {
    g_MouseX = g_MouseMaxX;
    return g_MouseMaxX;
  }
  return result;
}
