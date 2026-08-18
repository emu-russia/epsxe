#include "pch.h"
char __cdecl loader_mini_cheat_find(int a1, int a2)
{
  unsigned __int8 v2; // cl
  int v3; // eax

  v2 = 0;
  if ( mini_cheat_count <= 0 )
    return 0;
  v3 = 0;
  while ( a1 != mini_cheat_id_array[2 * v3] || a2 != *(_DWORD *)((unsigned char *)&mini_cheat_db + 24 * v3 + 20) )
  {
    v3 = ++v2;
    if ( v2 >= mini_cheat_count )
      return 0;
  }
  return 1;
}

FILE *loader_load_cheats()
{
  FILE *v0; // eax
  FILE *v1; // edi
  int v2; // esi
  FILE *result; // eax
  FILE *v4; // esi
  int v5; // eax

  v0 = fopen("cheats\\database.dat", "rb");
  v1 = v0;
  if ( v0 )
  {
    if ( !feof(v0) )
    {
      v2 = mini_cheat_count;
      do
      {
        if ( v2 >= 200 )
          break;
        fread((void *)(24 * v2 + 4520368), 1u, 0x18u, v1);
        v2 = mini_cheat_count;
        if ( !loader_mini_cheat_find(
                *(_DWORD *)((unsigned char *)&mini_cheat_db + 24 * mini_cheat_count + 16),
                *(_DWORD *)((unsigned char *)&mini_cheat_db + 24 * mini_cheat_count + 20)) )
          mini_cheat_count = ++v2;
      }
      while ( !feof(v1) );
    }
    fclose(v1);
  }
  result = fopen("cheats\\dataconf.dat", "rb");
  v4 = result;
  if ( result )
  {
    if ( !feof(result) )
    {
      v5 = cheat_entries_count;
      do
      {
        if ( v5 >= 200 )
          break;
        fread(&cheat_db[v5], 1u, 81u, v4);
        v5 = ++cheat_entries_count;
      }
      while ( !feof(v4) );
    }
    return (FILE *)fclose(v4);
  }
  return result;
}

char __cdecl loader_mini_cheat_find_by_id(int a1, int a2)
{
  unsigned __int8 v2; // cl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v2 = 0;
  v4 = 0;
  if ( !active_mini_cheat_count )
    return 0;
  while ( a1 != mini_cheat_id_array[2 * v4] || a2 != *(_DWORD *)((unsigned char *)&mini_cheat_db + 24 * v4 + 20) )
  {
    v4 = ++v2;
    if ( v2 >= (unsigned __int8)active_mini_cheat_count )
      return 0;
  }
  return 1;
}

char __cdecl loader_apply_mini_cheats(const char *a1)
{
  char result; // al
  int *v2; // ebp
  int v3; // edi
  int v4; // ebp
  int v5; // esi
  char v6; // al
  bool v7; // zf
  const char *v8; // [esp+0h] [ebp-8h]
  int v9; // [esp+4h] [ebp-4h]

  result = noauto;
  if ( !noauto )
  {
    result = mini_cheat_count;
    if ( mini_cheat_count )
    {
      v2 = (int *)((unsigned char *)&mini_cheat_db + 20);
      v8 = (const char *)&mini_cheat_db + 20;
      v9 = mini_cheat_count;
      do
      {
        if ( !strcmp(a1, (const char *)v2 - 20) && (unsigned __int8)active_mini_cheat_count < 0x10u )
        {
          v3 = *v2;
          v4 = *(v2 - 1);
          v5 = 2 * (unsigned __int8)active_mini_cheat_count;
          mini_cheat_attr_array[v5] = v3;
          mini_cheat_id_array[v5] = v4;
          if ( !loader_mini_cheat_find_by_id(v4, v3) )
          {
            v6 = active_mini_cheat_count + 1;
            mini_cheat_attr_array[v5] = v3;
            mini_cheat_id_array[v5] = v4;
            active_mini_cheat_count = v6;
          }
          v2 = (int *)v8;
        }
        v2 += 6;
        result = v9 - 1;
        v7 = v9 == 1;
        v8 = (const char *)v2;
        --v9;
      }
      while ( !v7 );
    }
  }
  return result;
}

char __cdecl loader_parse_cheat_entry(const char *a1, char *Buffer)
{
  int v2; // edi
  CHEAT_DB_ENTRY *i; // ebp
  signed __int8 mdec_timing; // cl
  signed __int8 dword_50C374; // cl
  signed __int8 force_pad; // cl
  char *text; // eax

  if ( noauto )
    return 0;
  v2 = 0;
  if ( !cheat_entries_count )
    return 0;
  for ( i = cheat_db; strcmp(a1, i->gameid); ++i )
  {
    if ( ++v2 >= cheat_entries_count )
      return 0;
  }
  mdec_timing = cheat_db[v2].mdectiming;
  if ( mdec_timing != -1 )
    mdectiming = mdec_timing;
  dword_50C374 = cheat_db[v2].dword_50C374;
  if ( dword_50C374 != -1 )
    unknown_timing_value = dword_50C374;
  if ( cheat_db[v2].forcespu != 0xFF )
    forcespu = cheat_db[v2].forcespu;
  force_pad = cheat_db[v2].forcepad;
  if ( force_pad != -1 )
    forcepad = force_pad;
  if ( cheat_db[v2].byte_455946 != 0xFF )
    cpu_overclock_setting = cheat_db[v2].byte_455946;
  if ( cheat_db[v2].parasite_eve_cheat != 0xFF )
    parasite_eve_cheat = cheat_db[v2].parasite_eve_cheat;
  if ( cheat_db[v2].byte_455FA4 != 0xFF )
    cd_inc = cheat_db[v2].byte_455FA4;
  if ( cheat_db[v2].byte_4F75AA != 0xFF )
    unknown_cd_setting = cheat_db[v2].byte_4F75AA;
  if ( cheat_db[v2].nocdstatus != 0xFF )
    nocdstatus = cheat_db[v2].nocdstatus;
  if ( cheat_db[v2].byte_4FC4E6 != 0xFF )
    cd_extra_setting = cheat_db[v2].byte_4FC4E6;
  text = cheat_db[v2].text;
  if ( !strcmp("NULL", text) )
    return 0;
  sprintf(Buffer, "%s", text);
  return 1;
}

int __cdecl loader_set_bios_name(const char *a1)
{
  return sprintf((char *const)bios_name, "%s", a1);
}

int __cdecl loader_set_filename(const char *a1)
{
  return sprintf(FileName, "%s", a1);
}

void loader_load_bios()
{
  FILE *v0; // eax
  FILE *v1; // esi
  char Buffer[256]; // [esp+4h] [ebp-100h] BYREF

  sprintf(Buffer, "%s", (const char *)bios_name);
  v0 = fopen(Buffer, "rb");
  v1 = v0;
  if ( !v0 )
    fatal_error_with_message_box(" * !Error: PSX BIOS not found [%s]. \n", (const char *)bios_name);
  fread(bios_image, 1u, 0x80000u, v0);
  fclose(v1);
  dbg_print_no_flush(" * ePSXe: PSX BIOS loaded [%s]. \n", (const char *)bios_name);
}

int loader_check_bios_file_exists()
{
  FILE *v0; // eax
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  sprintf(Buffer, "%s", (const char *)bios_name);
  v0 = fopen(Buffer, "rb");
  if ( !v0 )
    return -1;
  fclose(v0);
  return 0;
}

void __cdecl loader_check_demo_header(FILE *Stream, int a2)
{
  int v2; // eax

  fseek(Stream, 0, 2);
  v2 = ftell(Stream) - 2048;
  if ( a2 != v2 )
    dump_log((FILE *)console_log_handle, " ePSXe: (Demo bugged header) Real: %x Load: %x \n", v2, a2);
}

int __cdecl loader_load_demo(char *FileName)
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
  loader_check_demo_header(v2, (int)ElementCount);
  fseek(v2, 2048, 0);
  fread((char *)ram + (v7 & 0x1FFFFF), 1u, ElementCount, v2);
  cpu_gpr[29] = 0x801FFF00;
  cpu_gpr[30] = 0x801FFF00;
  cpu_gpr[28] = v6;
  cpu_gpr[31] = 0;
  *(_DWORD *)reg_pc = v5;
  return fclose(v2);
}

int __cdecl loader_pll_parse_section(int a1, unsigned int *a2, unsigned int a3, const char *a4, int a5)
{
  unsigned int v5; // eax
  int v6; // eax
  int v7; // edx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // edx
  unsigned int v12; // edx
  unsigned int v13; // edx

  if ( strncmp((const char *)(a1 + *a2), "DATA", 4u) )
  {
    do
    {
      if ( !strncmp((const char *)(a1 + *a2), "LOAD", 4u) )
        break;
      if ( *a2 >= a3 )
        return 0;
      v5 = *a2 + 1;
      *a2 = v5;
    }
    while ( strncmp((const char *)(a1 + v5), "DATA", 4u) );
  }
  if ( *a2 >= a3 )
    return 0;
  v6 = strncmp((const char *)(a1 + *a2), "DATA", 4u);
  v7 = *a2;
  if ( !v6 )
  {
    *a2 = v7 + 5;
    if ( *(_BYTE *)(v7 + 5 + a1) == 32 )
    {
      do
      {
        v8 = *a2 + 1;
        *a2 = v8;
      }
      while ( *(_BYTE *)(v8 + a1) == 32 );
    }
    sscanf((const char *const)(a1 + *a2), "%s ", (char *)a4);
    v9 = (unsigned int)strlen(a4) + *a2;
    *a2 = v9;
    if ( *(_BYTE *)(v9 + a1) == 32 )
    {
      do
      {
        v10 = *a2 + 1;
        *a2 = v10;
      }
      while ( *(_BYTE *)(v10 + a1) == 32 );
    }
    sscanf((const char *const)(a1 + *a2), "%x", (unsigned int *)a5);
    return 1;
  }
  if ( strncmp((const char *)(a1 + v7), "LOAD", 4u) )
    return 0;
  v12 = *a2 + 5;
  *a2 = v12;
  if ( *(_BYTE *)(v12 + a1) == 32 )
  {
    do
    {
      v13 = *a2 + 1;
      *a2 = v13;
    }
    while ( *(_BYTE *)(v13 + a1) == 32 );
  }
  sscanf((const char *const)(a1 + *a2), "%s\n", (char *)a4);
  *a2 += (unsigned int)strlen(a4);
  return 2;
}

size_t __cdecl loader_pll_get_file_size(const char *a1)
{
  size_t result; // eax
  unsigned int v2; // edi
  const char *v3; // ebp
  size_t v4; // [esp+8h] [ebp-4h]

  result = 0x100000;
  v2 = 0;
  v4 = 0x100000;
  if ( zip_num_entries_loaded )
  {
    v3 = zip_entry_names;
    do
    {
      if ( !strcmp(v3, a1) )
        v4 = Size[v2];
      ++v2;
      v3 += 256;
    }
    while ( v2 < zip_num_entries_loaded );
    return v4;
  }
  return result;
}

void __cdecl loader_load_file(char *a1, size_t Size)
{
  char v2; // al
  int v3; // eax
  size_t file_size; // eax
  char *v5; // ebp
  char *v6; // eax
  size_t v7; // eax
  char *Str2; // [esp+0h] [ebp-118h] BYREF
  LPVOID lpMem; // [esp+4h] [ebp-114h] BYREF
  int v10; // [esp+8h] [ebp-110h] BYREF
  int v11; // [esp+Ch] [ebp-10Ch] BYREF
  unsigned int v12; // [esp+10h] [ebp-108h] BYREF
  int v13; // [esp+14h] [ebp-104h] BYREF
  char ArgList[256]; // [esp+18h] [ebp-100h] BYREF

  lpMem = malloc(Size);
  v12 = 0;
  if ( zip_extract_file(FileName, a1, &lpMem, (size_t *)&v11) )
    fatal_error_with_message_box(" * EPSX: error loading .pll file.");
  v2 = loader_pll_parse_section((int)lpMem, &v12, v11, ArgList, (int)&v10);
  if ( v2 )
  {
    while ( 1 )
    {
      v3 = v2 - 1;
      if ( !v3 )
        break;
      if ( v3 == 1 )
      {
        file_size = loader_pll_get_file_size(ArgList);
        Str2 = (char *)malloc(file_size);
        if ( zip_extract_file(FileName, ArgList, (LPVOID *)&Str2, (size_t *)&v13) )
          fatal_error_with_message_box(" * EPSX: error loading .exe file in pll/zip.");
        v5 = Str2;
        if ( strncmp("PS-X EXE", Str2, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", ArgList);
        v6 = Str2;
        qmemcpy((char *)ram + (*((_DWORD *)v5 + 6) & 0x1FFFFF), Str2 + 2048, *((_DWORD *)v5 + 7));
        cpu_gpr[28] = *((_DWORD *)v5 + 5);
        cpu_gpr[29] = 0x801FFF00;
        cpu_gpr[30] = 0x801FFF00;
        cpu_gpr[31] = 0;
        *(_DWORD *)reg_pc = *((_DWORD *)v5 + 4);
LABEL_14:
        free(v6);
      }
      v2 = loader_pll_parse_section((int)lpMem, &v12, v11, ArgList, (int)&v10);
      if ( !v2 )
        goto LABEL_16;
    }
    v7 = loader_pll_get_file_size(ArgList);
    Str2 = (char *)malloc(v7);
    if ( zip_extract_file(FileName, ArgList, (LPVOID *)&Str2, (size_t *)&v13) )
      fatal_error_with_message_box(" * EPSX: error loading %s.", ArgList);
    v6 = Str2;
    qmemcpy((char *)ram + (v10 & 0x1FFFFF), Str2, v13);
    goto LABEL_14;
  }
LABEL_16:
  free(lpMem);
}

void loader_load_zip()
{
  char *v0; // esi
  void *v1; // esi
  char *v2; // ebx
  char *v3; // eax
  unsigned __int8 v4; // bl
  int v5; // eax
  const char *v6; // esi
  char *Str2; // [esp+Ch] [ebp-8h] BYREF
  int v8; // [esp+10h] [ebp-4h] BYREF

  v0 = &FileName[-3];
  if ( !strncmp(&FileName[strlen(FileName) - 3], "zip", 3u) || !strncmp(&v0[strlen(FileName)], "ZIP", 3u) )
  {
    if ( !strncmp(&v0[strlen(FileName)], "zip", 3u) || !strncmp(&v0[strlen(FileName)], "ZIP", 3u) )
    {
      v1 = malloc(0x2000u);
      memset(v1, 0, 0x2000u);
      if ( zip_load_file(FileName) )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      free(v1);
      if ( !zip_num_entries_loaded )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      if ( zip_num_entries_loaded == 1 )
      {
        if ( strncmp(&zip_entry_names[strlen(zip_entry_names) - 3], "exe", 3u)
          && strncmp(&zip_entry_names[strlen(zip_entry_names) - 3], "EXE", 3u) )
        {
          fatal_error_with_message_box("* EPSX: DEMO not found [%s]. \n", zip_entry_names);
        }
        Str2 = (char *)malloc(Size[0]);
        if ( zip_extract_file(FileName, zip_entry_names, (LPVOID *)&Str2, (size_t *)&v8) )
          fatal_error_with_message_box(" * EPSX: error loading .zip file.");
        v2 = Str2;
        if ( strncmp("PS-X EXE", Str2, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", zip_entry_names);
        v3 = Str2;
        qmemcpy((char *)ram + (*((_DWORD *)v2 + 6) & 0x1FFFFF), Str2 + 2048, *((_DWORD *)v2 + 7));
        cpu_gpr[28] = *((_DWORD *)v2 + 5);
        cpu_gpr[29] = 0x801FFF00;
        cpu_gpr[30] = 0x801FFF00;
        cpu_gpr[31] = 0;
        *(_DWORD *)reg_pc = *((_DWORD *)v2 + 4);
        free(v3);
      }
      else
      {
        v4 = 0;
        LOBYTE(Str2) = -1;
        if ( zip_num_entries_loaded <= 0 )
          goto LABEL_26;
        v5 = 0;
        do
        {
          v6 = &zip_entry_names[256 * v5];
          if ( !strncmp(&v6[strlen(v6) - 3], "pll", 3u) || !strncmp(&v6[strlen(v6) - 3], "PLL", 3u) )
            LOBYTE(Str2) = v4;
          LOBYTE(v8) = ++v4;
          v5 = v4;
        }
        while ( v4 < zip_num_entries_loaded );
        if ( (_BYTE)Str2 == 0xFF )
LABEL_26:
          fatal_error_with_message_box("* EPSX: DEMO .pll not found. \n");
        loader_load_file(&zip_entry_names[256 * (unsigned __int8)Str2], Size[(unsigned __int8)Str2]);
      }
    }
  }
  else
  {
    loader_load_demo(FileName);
  }
}

int loader_touch_demo_file()
{
  FILE *v0; // eax

  if ( !strncmp(FileName, "NULL", 4u) )
    return 0;
  v0 = fopen(FileName, "rb");
  if ( !v0 )
    fatal_error_with_message_box(" * EPSX: DEMO not found [%s]. \n", FileName);
  fclose(v0);
  return 1;
}

int loader_cdrom_detect_region()
{
  int result; // eax
  unsigned int i; // esi
  const char *v2; // [esp-4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( loaded_file_type != 3 && loaded_file_type != 1 )
  {
    sprintf(Buffer, "DEMO_999.99");
    result = sprintf(default_filename, "%s", Buffer);
    video_scanlines = 262;
    cpu_speed_scale = 2154;
    country_setting = 0;
    return result;
  }
  cdfs_load_executable(Buffer);
  if ( Buffer[strlen(Buffer) - 2] == ';' )
    Buffer[strlen(Buffer) - 2] = 0;
  sprintf(default_filename, "%s", Buffer);
  for ( i = 0; i < strlen(default_filename); ++i )
    default_filename[i] = towupper(default_filename[i]);
  loader_parse_cheat_entry(default_filename, Buffer);
  loader_apply_mini_cheats(default_filename);
  if ( country_setting == 1 )
  {
    v2 = " * Force PAL cdrom detected. \n";
  }
  else
  {
    if ( !country_setting )
    {
      video_scanlines = 262;
      cpu_speed_scale = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * Force NTSC cdrom detected. \n");
    }
    if ( default_filename[2] != 'E' && default_filename[2] != 'e' )
    {
      country_setting = 0;
      video_scanlines = 262;
      cpu_speed_scale = old_timing != 0 ? 1916 : 2154;
      return dbg_print(" * NTSC cdrom detected. \n");
    }
    country_setting = 1;
    v2 = " * PAL cdrom detected. \n";
  }
  video_scanlines = 312;
  cpu_speed_scale = old_timing != 0 ? 1923 : 2171;
  return dbg_print(v2);
}

FILE *__cdecl loader_load_cheat_file(char *FileName)
{
  FILE *result; // eax
  FILE *v2; // esi
  int v3; // edx
  int v4; // eax
  int v5; // [esp+4h] [ebp-408h] BYREF
  int v6; // [esp+8h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+Ch] [ebp-400h] BYREF

  active_mini_cheat_count = 0;
  result = fopen(FileName, "r");
  v2 = result;
  if ( result )
  {
    if ( !feof(result) )
    {
      do
      {
        sprintf(Buffer, " ");
        fgets(Buffer, 1024, v2);
        if ( Buffer[0] != '#' && sscanf(Buffer, "%x %x", &v6, &v5) == 2 )
        {
          v3 = v5;
          v4 = 2 * (unsigned __int8)active_mini_cheat_count;
          mini_cheat_id_array[v4] = v6;
          mini_cheat_attr_array[v4] = v3;
          ++active_mini_cheat_count;
        }
      }
      while ( !feof(v2) );
    }
    return (FILE *)fclose(v2);
  }
  return result;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned char active_mini_cheat_count;
unsigned char bios_image[0x80000];
unsigned char bios_name[0x800];
unsigned char cd_inc = 0x1;
unsigned int cheat_entries_count = 0x27;
unsigned int country_setting;
unsigned char default_filename[0x400];
unsigned int mini_cheat_attr_array[1];
unsigned int mini_cheat_count = 0x4;
unsigned int mini_cheat_id_array[0x1f];
unsigned char noauto = 0x0;
unsigned char nocdstatus;
unsigned char old_timing = 0x0;
unsigned char parasite_eve_cheat;
unsigned char unknown_cd_setting;
unsigned int video_scanlines = 0x106;
unsigned char zip_entry_names[0x10000];
unsigned int zip_num_entries_loaded;
