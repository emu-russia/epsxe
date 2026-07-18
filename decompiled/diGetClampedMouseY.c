#include "pch.h"
int diGetClampedMouseY()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  result = g_MouseY[0];
  if ( g_MouseY[0] < g_MouseMinY )
  {
    result = g_MouseMinY;
    g_MouseY[0] = g_MouseMinY;
  }
  if ( result > g_MouseMaxY )
  {
    g_MouseY[0] = g_MouseMaxY;
    return g_MouseMaxY;
  }
  return result;
}
