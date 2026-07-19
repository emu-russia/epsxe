#include "pch.h"
int __cdecl epsxe_load_demo(char *FileName)
{
  FILE *v1; // eax
  FILE *v2; // esi
  char Str2[16]; // [esp+8h] [ebp-4Ch] BYREF
  int v5; // [esp+18h] [ebp-3Ch]
  int v6; // [esp+1Ch] [ebp-38h]
  int v7; // [esp+20h] [ebp-34h]
  size_t ElementCount; // [esp+24h] [ebp-30h]

  v1 = fopen(FileName, "rb");
  v2 = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * ePSXe: DEMO not found [%s]. \n", FileName);
  fread(Str2, 1u, 0x4Cu, v1);
  if ( strncmp("PS-X EXE", Str2, 8u) )
    fatal_error_with_message_box(" * ePSXe: [%s] is not a EXE file. \n", FileName);
  check_demo_header(v2, ElementCount);
  fseek(v2, 2048, 0);
  fread((char *)ram + (v7 & 0x1FFFFF), 1u, ElementCount, v2);
  MEMORY[0x50C354] = 0x801FFF00;
  MEMORY[0x50C358] = 0x801FFF00;
  MEMORY[0x50C350] = v6;
  MEMORY[0x50C35C] = 0;
  *(_DWORD *)reg_pc = v5;
  return fclose(v2);
}
