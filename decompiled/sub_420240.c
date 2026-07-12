#include "pch.h"
int __cdecl sub_420240(char *FileName)
{
  FILE *v1; // eax
  FILE *v2; // esi
  int v4; // [esp+4h] [ebp-4Ch] BYREF
  __int16 v5; // [esp+8h] [ebp-48h]
  __int16 v6; // [esp+Ah] [ebp-46h]
  __int16 v7; // [esp+Ch] [ebp-44h]
  __int16 v8; // [esp+Eh] [ebp-42h]
  int v9[13]; // [esp+1Ch] [ebp-34h] BYREF

  *(_DWORD *)ArgList = sub_4201C0(FileName);
  v1 = fopen(FileName, "rb");
  v2 = v1;
  if ( v1 )
  {
    if ( sub_420C70(v1, &ElementCount) )
    {
      sub_420210("Error in zipfile %s: get_file_length() failed\n", *(_DWORD *)ArgList);
    }
    else if ( sub_420AF0(v2, &v4) )
    {
      sub_420210("Error reading 'end of central directory' in zipfile %s\n", *(_DWORD *)ArgList);
    }
    else
    {
      if ( v5 == v6 && v7 == v8 && v8 )
      {
        sub_420730(v2, (int)&v4, (int)v9);
        fclose(v2);
        return 0;
      }
      sub_420210("Unsupported zipfile %s: zipfile cannot span disks\n", *(_DWORD *)ArgList);
    }
    fclose(v2);
  }
  return 0;
}
