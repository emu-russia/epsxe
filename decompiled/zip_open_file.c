#include "pch.h"
int __cdecl zip_open_file(char *FileName, char *a2, LPVOID *a3, size_t *a4)
{
  FILE *v4; // eax
  FILE *v5; // ebp
  int file_length; // esi
  char *v8; // esi
  char v9; // al
  void *v11; // eax
  unsigned int v12; // eax
  int v13; // [esp-8h] [ebp-ACh]
  LPVOID v14; // [esp+Ch] [ebp-98h] BYREF
  LPVOID lpMem; // [esp+10h] [ebp-94h] BYREF
  int v16; // [esp+14h] [ebp-90h] BYREF
  __int16 v17; // [esp+18h] [ebp-8Ch]
  __int16 v18; // [esp+1Ah] [ebp-8Ah]
  __int16 v19; // [esp+1Ch] [ebp-88h]
  __int16 v20; // [esp+1Eh] [ebp-86h]
  int v21[2]; // [esp+2Ch] [ebp-78h] BYREF
  __int16 v22; // [esp+34h] [ebp-70h]
  size_t Size; // [esp+44h] [ebp-60h]
  char ArgList[32]; // [esp+50h] [ebp-54h] BYREF
  int v25[13]; // [esp+70h] [ebp-34h] BYREF

  lpMem = nullptr;
  v14 = nullptr;
  *(_DWORD *)zip_filename = zip_get_filename_from_path(FileName);
  v4 = fopen(FileName, "rb");
  v5 = v4;
  if ( v4 )
  {
    file_length = zip_get_file_length(v4, &ElementCount);
    if ( file_length )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(const char **)zip_filename);
    }
    else
    {
      file_length = zip_locate_central_dir(v5, &v16);
      if ( file_length )
      {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", *(const char **)zip_filename);
      }
      else
      {
        if ( v17 != v18 || v19 != v20 || !v20 )
        {
          file_length = -1;
          zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
          goto LABEL_13;
        }
        v8 = ArgList;
        do
        {
          v13 = *a2++;
          v9 = toupper(v13);
          *v8++ = v9;
        }
        while ( v9 );
        file_length = zip_load_central_directory(v5, ArgList, (int)&v16, (int)v25);
        if ( file_length )
        {
          zip_print("Could not find %s in zipfile %s\n", ArgList, *(_DWORD *)zip_filename);
        }
        else
        {
          file_length = zip_read_local_file_header(v5, (int)v25, (int)v21, (unsigned __int8 *)byte_4F8350);
          if ( !file_length )
          {
            if ( v22 )
            {
              if ( v22 == 8 )
              {
                file_length = zip_allocate_and_read(v5, (int)v25, (int)v21, &lpMem);
                if ( file_length )
                {
                  zip_print("Could not create input buffer for zipfile %s\n", *(const char **)zip_filename);
                  goto LABEL_13;
                }
                zipfile_input_buffer = (int)lpMem;
                v11 = malloc(Size);
                v14 = v11;
                if ( !v11 )
                {
                  zip_print(
                    "Couldn't allocate %d bytes for zipfile %s output buffer\n",
                    *(_DWORD *)zip_filename,
                    (const char *)Size);
                  file_length = -1;
                  goto LABEL_13;
                }
                zipfile_output_buffer = (int)v11;
                zip_sliding_window = malloc(0x8000u);
                if ( !zip_sliding_window )
                {
                  zip_print("Could not create 32K sliding window for zipfile %s\n", *(const char **)zip_filename);
                  file_length = -1;
                  goto LABEL_13;
                }
                v12 = zip_inflate_file();
                file_length = v12;
                if ( v12 )
                {
                  zip_print("Error %d inflating compressed file from zipfile %s\n", v12, *(_DWORD *)zip_filename);
                  goto LABEL_13;
                }
              }
            }
            else
            {
              file_length = zip_allocate_and_read(v5, (int)v25, (int)v21, &v14);
              if ( file_length )
              {
                zip_print("Couldn't extract uncompressed file from zipfile %s\n", *(const char **)zip_filename);
                goto LABEL_13;
              }
            }
            *a3 = v14;
            *a4 = Size;
            v14 = nullptr;
            goto LABEL_13;
          }
          zip_print("Error reading 'local file header' in zipfile %s\n", *(const char **)zip_filename);
        }
      }
    }
LABEL_13:
    fclose(v5);
    goto LABEL_14;
  }
  zip_print("Could not open zipfile %s\n", FileName);
  file_length = -1;
LABEL_14:
  if ( lpMem )
    free(lpMem);
  if ( v14 )
    free(v14);
  if ( zip_sliding_window )
  {
    free(zip_sliding_window);
    zip_sliding_window = nullptr;
  }
  return file_length;
}
