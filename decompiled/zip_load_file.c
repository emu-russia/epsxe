#include "pch.h"
int __cdecl zip_load_file(char *FileName)
{
  FILE *v1; // eax
  FILE *v2; // esi
  int v4; // [esp+4h] [ebp-4Ch] BYREF
  __int16 v5; // [esp+8h] [ebp-48h]
  __int16 v6; // [esp+Ah] [ebp-46h]
  __int16 v7; // [esp+Ch] [ebp-44h]
  __int16 v8; // [esp+Eh] [ebp-42h]
  int v9[13]; // [esp+1Ch] [ebp-34h] BYREF

  *(_DWORD *)zip_filename = zip_get_filename_from_path(FileName);
  v1 = fopen(FileName, "rb");
  v2 = v1;
  if ( v1 )
  {
    if ( zip_get_file_length(v1, &ElementCount) )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(_DWORD *)zip_filename);
    }
    else if ( zip_locate_central_dir(v2, &v4) )
    {
      zip_print("Error reading 'end of central directory' in zipfile %s\n", *(_DWORD *)zip_filename);
    }
    else
    {
      if ( v5 == v6 && v7 == v8 && v8 )
      {
        zip_load_local_file_header(v2, (int)&v4, (int)v9);
        fclose(v2);
        return 0;
      }
      zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(_DWORD *)zip_filename);
    }
    fclose(v2);
  }
  return 0;
}
