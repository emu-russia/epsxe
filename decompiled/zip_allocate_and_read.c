#include "pch.h"
int __cdecl zip_allocate_and_read(FILE *Stream, int a2, int a3, LPVOID *a4)
{
  size_t v4; // esi
  void *v5; // eax
  int v7; // edi

  v4 = *(_DWORD *)(a3 + 20);
  v5 = malloc(v4);
  *a4 = v5;
  if ( !v5 )
  {
    zip_print("Couldn't allocate %ld bytes for input buffer for zipfile %s\n", v4, *(const char **)zip_filename);
    return -1;
  }
  v7 = fseek(Stream, *(unsigned __int16 *)(a3 + 28) + *(unsigned __int16 *)(a3 + 30) + *(_DWORD *)(a2 + 44) + 30, 0);
  if ( v7 )
  {
    zip_print("Error reading zipfile %s: fseek to compressed data failed\n", *(const char **)zip_filename);
LABEL_7:
    if ( *a4 )
    {
      free(*a4);
      *a4 = nullptr;
    }
    return v7;
  }
  if ( fread(*a4, 1u, v4, Stream) != v4 )
  {
    zip_print("Error in zipfile %s: couldn't read %ld bytes of compressed data\n", *(const char **)zip_filename, v4);
    v7 = -1;
    goto LABEL_7;
  }
  return v7;
}
