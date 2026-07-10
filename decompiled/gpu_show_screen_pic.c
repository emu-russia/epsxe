#include "pch.h"
void __cdecl gpu_show_screen_pic(unsigned __int8 a1)
{
  void *v1; // ebx
  FILE *v2; // eax
  FILE *v3; // edi
  FILE *v4; // eax
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( GPUshowScreenPic )
  {
    v1 = malloc(0x9000u);
    sprintf(Buffer, "%s%s.%03d.pic", "sstates\\", byte_8B3D80, a1);
    v2 = fopen(Buffer, "rb");
    v3 = v2;
    if ( v2 )
    {
      fread(v1, 1u, 0x9000u, v2);
      fclose(v3);
    }
    else
    {
      sprintf(Buffer, "%s%s.%03d", "sstates\\", byte_8B3D80, a1);
      v4 = fopen(Buffer, "rb");
      if ( v4 )
      {
        fclose(v4);
        sub_42EB00((char *)v1, a1);
      }
      else
      {
        sub_42EBF0((char *)v1, a1);
      }
    }
    GPUshowScreenPic(v1);
    free(v1);
  }
}
