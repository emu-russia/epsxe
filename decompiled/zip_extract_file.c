#include "pch.h"
int __cdecl zip_extract_file(char *FileName, char *arg4, LPVOID *arg8, size_t *a4)
{
  FILE *v4; // eax
  FILE *v5; // ebp
  int file_size; // esi
  char *v8; // esi
  char v9; // al
  void *v11; // eax
  int v12; // eax
  int v13; // [esp-8h] [ebp-ACh]
  LPVOID v14; // [esp+Ch] [ebp-98h] BYREF
  LPVOID lpMem; // [esp+10h] [ebp-94h] BYREF
  int v16; // [esp+14h] [ebp-90h] BYREF
  __int16 v17; // [esp+18h] [ebp-8Ch]
  __int16 v18; // [esp+1Ah] [ebp-8Ah]
  __int16 v19; // [esp+1Ch] [ebp-88h]
  __int16 v20; // [esp+1Eh] [ebp-86h]
  ZipLocalFileHeaderInMem a3; // [esp+2Ch] [ebp-78h] BYREF
  char ArgList[32]; // [esp+50h] [ebp-54h] BYREF
  ZipCentralDirectoryEntry a2; // [esp+70h] [ebp-34h] BYREF

  lpMem = nullptr;
  v14 = nullptr;
  *(_DWORD *)zip_filename = zip_get_filename_from_path(FileName);
  v4 = fopen(FileName, "rb");
  v5 = v4;
  if ( v4 )
  {
    file_size = zip_get_file_size(v4, &zip_file_size);
    if ( file_size )
    {
      zip_print("Error in zipfile %s: get_file_length() failed\n", *(const char **)zip_filename);
    }
    else
    {
      file_size = zip_locate_central_dir(v5, &v16);
      if ( file_size )
      {
        zip_print("Error reading 'end of central directory' in zipfile %s\n", *(const char **)zip_filename);
      }
      else
      {
        if ( v17 != v18 || v19 != v20 || !v20 )
        {
          file_size = -1;
          zip_print("Unsupported zipfile %s: zipfile cannot span disks\n", *(const char **)zip_filename);
          goto LABEL_13;
        }
        v8 = ArgList;
        do
        {
          v13 = *arg4++;
          v9 = toupper(v13);
          *v8++ = v9;
        }
        while ( v9 );
        file_size = zip_load_central_directory(v5, ArgList, (int)&v16, &a2);
        if ( file_size )
        {
          zip_print("Could not find %s in zipfile %s\n", ArgList, *(_DWORD *)zip_filename);
        }
        else
        {
          file_size = zip_read_local_file_header(v5, (int)&a2, &a3, (unsigned __int8 *)&zip_central_dir_buffer);
          if ( !file_size )
          {
            if ( a3.compression_method )
            {
              if ( a3.compression_method == 8 )
              {
                file_size = zip_read_compressed_data_to_buffer(v5, (int)&a2, (int)&a3, &lpMem);
                if ( file_size )
                {
                  zip_print("Could not create input buffer for zipfile %s\n", *(const char **)zip_filename);
                  goto LABEL_13;
                }
                zipfile_input_buffer = (int)lpMem;
                v11 = malloc(a3.uncompressed_size);
                v14 = v11;
                if ( !v11 )
                {
                  zip_print(
                    "Couldn't allocate %d bytes for zipfile %s output buffer\n",
                    *(_DWORD *)zip_filename,
                    (const char *)a3.uncompressed_size);
                  file_size = -1;
                  goto LABEL_13;
                }
                zip_inflate_output_ptr = (int)v11;
                zip_sliding_window = malloc(0x8000u);
                if ( !zip_sliding_window )
                {
                  zip_print("Could not create 32K sliding window for zipfile %s\n", *(const char **)zip_filename);
                  file_size = -1;
                  goto LABEL_13;
                }
                v12 = zip_inflate_file();
                file_size = v12;
                if ( v12 )
                {
                  zip_print("Error %d inflating compressed file from zipfile %s\n", v12, *(_DWORD *)zip_filename);
                  goto LABEL_13;
                }
              }
            }
            else
            {
              file_size = zip_read_compressed_data_to_buffer(v5, (int)&a2, (int)&a3, &v14);
              if ( file_size )
              {
                zip_print("Couldn't extract uncompressed file from zipfile %s\n", *(const char **)zip_filename);
                goto LABEL_13;
              }
            }
            *arg8 = v14;
            *a4 = a3.uncompressed_size;
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
  file_size = -1;
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
  return file_size;
}
