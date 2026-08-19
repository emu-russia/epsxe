#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned char active_mini_cheat_count;
unsigned char bios_image[0x80000];
unsigned char bios_name[0x800];
unsigned char cd_inc = 0x1;
static unsigned int cheat_entries_count = 0x27;
unsigned int country_setting;
unsigned char default_filename[0x400];
unsigned int mini_cheat_attr_array[1];
static unsigned int mini_cheat_count = 0x4;
unsigned int mini_cheat_id_array[0x1f];
unsigned char noauto = 0x0;
unsigned char nocdstatus;
unsigned char old_timing = 0x0;
unsigned char parasite_eve_cheat;
unsigned char unknown_cd_setting;
unsigned int video_scanlines = 0x106;
unsigned char zip_entry_names[0x10000];
unsigned int zip_num_entries_loaded;

static char loader_mini_cheat_find(int id, int attr)
{
  uint8_t count;
  int index;

  count = 0;
  if ( mini_cheat_count <= 0 )
    return 0;
  index = 0;
  while ( id != mini_cheat_id_array[2 * index] || attr != *(uint32_t *)((unsigned char *)&mini_cheat_db + 24 * index + 20) )
  {
    index = ++count;
    if ( count >= mini_cheat_count )
      return 0;
  }
  return 1;
}

FILE *loader_load_cheats()
{
  FILE *db_fp;
  int db_index;
  FILE *conf_fp;
  int conf_index;

  db_fp = fopen("cheats\\database.dat", "rb");
  if ( db_fp )
  {
    if ( !feof(db_fp) )
    {
      db_index = mini_cheat_count;
      do
      {
        if ( db_index >= 200 )
          break;
        fread((void *)(24 * db_index + 4520368), 1u, 0x18u, db_fp);
        db_index = mini_cheat_count;
        if ( !loader_mini_cheat_find(
                *(uint32_t *)((unsigned char *)&mini_cheat_db + 24 * mini_cheat_count + 16),
                *(uint32_t *)((unsigned char *)&mini_cheat_db + 24 * mini_cheat_count + 20)) )
          mini_cheat_count = ++db_index;
      }
      while ( !feof(db_fp) );
    }
    fclose(db_fp);
  }
  conf_fp = fopen("cheats\\dataconf.dat", "rb");
  if ( conf_fp )
  {
    if ( !feof(conf_fp) )
    {
      conf_index = cheat_entries_count;
      do
      {
        if ( conf_index >= 200 )
          break;
        fread(&cheat_db[conf_index], 1u, 81u, conf_fp);
        conf_index = ++cheat_entries_count;
      }
      while ( !feof(conf_fp) );
    }
    return (FILE *)fclose(conf_fp);
  }
  return conf_fp;
}

static char loader_mini_cheat_find_by_id(int id, int attr)
{
  uint8_t count;
  uint8_t index;

  count = 0;
  index = 0;
  if ( !active_mini_cheat_count )
    return 0;
  while ( id != mini_cheat_id_array[2 * index] || attr != *(uint32_t *)((unsigned char *)&mini_cheat_db + 24 * index + 20) )
  {
    index = ++count;
    if ( count >= (uint8_t)active_mini_cheat_count )
      return 0;
  }
  return 1;
}

static char loader_apply_mini_cheats(const char *gameid)
{
  char ret;
  int *entry;
  int attr;
  int id;
  int index;
  char new_count;
  bool done;
  const char *entry_ptr;
  int count;

  ret = noauto;
  if ( !noauto )
  {
    ret = mini_cheat_count;
    if ( mini_cheat_count )
    {
      entry = (int *)((unsigned char *)&mini_cheat_db + 20);
      entry_ptr = (const char *)&mini_cheat_db + 20;
      count = mini_cheat_count;
      do
      {
        if ( !strcmp(gameid, (const char *)entry - 20) && (uint8_t)active_mini_cheat_count < 0x10u )
        {
          attr = *entry;
          id = *(entry - 1);
          index = 2 * (uint8_t)active_mini_cheat_count;
          mini_cheat_attr_array[index] = attr;
          mini_cheat_id_array[index] = id;
          if ( !loader_mini_cheat_find_by_id(id, attr) )
          {
            new_count = active_mini_cheat_count + 1;
            mini_cheat_attr_array[index] = attr;
            mini_cheat_id_array[index] = id;
            active_mini_cheat_count = new_count;
          }
          entry = (int *)entry_ptr;
        }
        entry += 6;
        ret = count - 1;
        done = count == 1;
        entry_ptr = (const char *)entry;
        --count;
      }
      while ( !done );
    }
  }
  return ret;
}

static char loader_parse_cheat_entry(const char *gameid, char *Buffer)
{
  int index;
  CHEAT_DB_ENTRY *i;
  int8_t mdec_timing;
  int8_t timing_value;
  int8_t force_pad;
  char *text;

  if ( noauto )
    return 0;
  index = 0;
  if ( !cheat_entries_count )
    return 0;
  for ( i = cheat_db; strcmp(gameid, i->gameid); ++i )
  {
    if ( ++index >= cheat_entries_count )
      return 0;
  }
  mdec_timing = cheat_db[index].mdectiming;
  if ( mdec_timing != -1 )
    mdectiming = mdec_timing;
  timing_value = cheat_db[index].timing_value;
  if ( timing_value != -1 )
    unknown_timing_value = timing_value;
  if ( cheat_db[index].forcespu != 0xFF )
    forcespu = cheat_db[index].forcespu;
  force_pad = cheat_db[index].forcepad;
  if ( force_pad != -1 )
    forcepad = force_pad;
  if ( cheat_db[index].cpu_overclock != 0xFF )
    cpu_overclock_setting = cheat_db[index].cpu_overclock;
  if ( cheat_db[index].parasite_eve_cheat != 0xFF )
    parasite_eve_cheat = cheat_db[index].parasite_eve_cheat;
  if ( cheat_db[index].cd_increment != 0xFF )
    cd_inc = cheat_db[index].cd_increment;
  if ( cheat_db[index].cd_setting != 0xFF )
    unknown_cd_setting = cheat_db[index].cd_setting;
  if ( cheat_db[index].nocdstatus != 0xFF )
    nocdstatus = cheat_db[index].nocdstatus;
  if ( cheat_db[index].cd_extra != 0xFF )
    cd_extra_setting = cheat_db[index].cd_extra;
  text = cheat_db[index].text;
  if ( !strcmp("NULL", text) )
    return 0;
  sprintf(Buffer, "%s", text);
  return 1;
}

int loader_set_bios_name(const char *name)
{
  return sprintf((char *const)bios_name, "%s", name);
}

int loader_set_filename(const char *name)
{
  return sprintf(FileName, "%s", name);
}

void loader_load_bios()
{
  FILE *fp;
  char Buffer[256];

  sprintf(Buffer, "%s", (const char *)bios_name);
  fp = fopen(Buffer, "rb");
  if ( !fp )
    fatal_error_with_message_box(" * !Error: PSX BIOS not found [%s]. \n", (const char *)bios_name);
  fread(bios_image, 1u, 0x80000u, fp);
  fclose(fp);
  dbg_print_no_flush(" * ePSXe: PSX BIOS loaded [%s]. \n", (const char *)bios_name);
}

int loader_check_bios_file_exists()
{
  FILE *fp;
  char Buffer[256];

  sprintf(Buffer, "%s", (const char *)bios_name);
  fp = fopen(Buffer, "rb");
  if ( !fp )
    return -1;
  fclose(fp);
  return 0;
}

static void loader_check_demo_header(FILE *Stream, int load_size)
{
  int real_size;

  fseek(Stream, 0, 2);
  real_size = ftell(Stream) - 2048;
  if ( load_size != real_size )
    dump_log((FILE *)console_log_handle, " ePSXe: (Demo bugged header) Real: %x Load: %x \n", real_size, load_size);
}

int loader_load_demo(char *FileName)
{
  FILE *fp;
  char exe_header[16];
  int initial_pc;
  int initial_gp;
  int load_addr;
  size_t file_size;

  fp = fopen(FileName, "rb");
  if ( !fp )
    fatal_error_with_message_box(" * ePSXe: DEMO not found [%s]. \n", FileName);
  fread(exe_header, 1u, 0x4Cu, fp);
  if ( strncmp("PS-X EXE", exe_header, 8u) )
    fatal_error_with_message_box(" * ePSXe: [%s] is not a EXE file. \n", FileName);
  loader_check_demo_header(fp, (int)file_size);
  fseek(fp, 2048, 0);
  fread((char *)ram + (load_addr & 0x1FFFFF), 1u, file_size, fp);
  cpu_gpr[29] = 0x801FFF00;
  cpu_gpr[30] = 0x801FFF00;
  cpu_gpr[28] = initial_gp;
  cpu_gpr[31] = 0;
  *(uint32_t *)reg_pc = initial_pc;
  return fclose(fp);
}

static int loader_pll_parse_section(int base, unsigned int *offset, unsigned int size, const char *out_name, int out_addr)
{
  unsigned int scan_off;
  int data_cmp;
  int section_off;
  unsigned int skip_off;
  unsigned int name_end;
  unsigned int skip_off2;
  unsigned int skip_off3;
  unsigned int skip_off4;

  if ( strncmp((const char *)(base + *offset), "DATA", 4u) )
  {
    do
    {
      if ( !strncmp((const char *)(base + *offset), "LOAD", 4u) )
        break;
      if ( *offset >= size )
        return 0;
      scan_off = *offset + 1;
      *offset = scan_off;
    }
    while ( strncmp((const char *)(base + scan_off), "DATA", 4u) );
  }
  if ( *offset >= size )
    return 0;
  data_cmp = strncmp((const char *)(base + *offset), "DATA", 4u);
  section_off = *offset;
  if ( !data_cmp )
  {
    *offset = section_off + 5;
    if ( *(uint8_t *)(section_off + 5 + base) == 32 )
    {
      do
      {
        skip_off = *offset + 1;
        *offset = skip_off;
      }
      while ( *(uint8_t *)(skip_off + base) == 32 );
    }
    sscanf((const char *const)(base + *offset), "%s ", (char *)out_name);
    name_end = (unsigned int)strlen(out_name) + *offset;
    *offset = name_end;
    if ( *(uint8_t *)(name_end + base) == 32 )
    {
      do
      {
        skip_off2 = *offset + 1;
        *offset = skip_off2;
      }
      while ( *(uint8_t *)(skip_off2 + base) == 32 );
    }
    sscanf((const char *const)(base + *offset), "%x", (unsigned int *)out_addr);
    return 1;
  }
  if ( strncmp((const char *)(base + section_off), "LOAD", 4u) )
    return 0;
  skip_off3 = *offset + 5;
  *offset = skip_off3;
  if ( *(uint8_t *)(skip_off3 + base) == 32 )
  {
    do
    {
      skip_off4 = *offset + 1;
      *offset = skip_off4;
    }
    while ( *(uint8_t *)(skip_off4 + base) == 32 );
  }
  sscanf((const char *const)(base + *offset), "%s\n", (char *)out_name);
  *offset += (unsigned int)strlen(out_name);
  return 2;
}

static size_t loader_pll_get_file_size(const char *name)
{
  size_t default_size;
  unsigned int index;
  const char *entry_name;
  size_t size;

  default_size = 0x100000;
  index = 0;
  size = 0x100000;
  if ( zip_num_entries_loaded )
  {
    entry_name = zip_entry_names;
    do
    {
      if ( !strcmp(entry_name, name) )
        size = Size[index];
      ++index;
      entry_name += 256;
    }
    while ( index < zip_num_entries_loaded );
    return size;
  }
  return default_size;
}

static void loader_load_file(char *name, size_t Size)
{
  char section;
  int section_idx;
  size_t file_size;
  size_t load_size;
  char *exe_data;
  LPVOID pll_data;
  int load_addr;
  int pll_size;
  unsigned int offset;
  int extracted_size;
  char ArgList[256];

  pll_data = malloc(Size);
  offset = 0;
  if ( zip_extract_file(FileName, name, &pll_data, (size_t *)&pll_size) )
    fatal_error_with_message_box(" * EPSX: error loading .pll file.");
  section = loader_pll_parse_section((int)pll_data, &offset, pll_size, ArgList, (int)&load_addr);
  if ( section )
  {
    while ( 1 )
    {
      section_idx = section - 1;
      if ( !section_idx )
        break;
      if ( section_idx == 1 )
      {
        file_size = loader_pll_get_file_size(ArgList);
        exe_data = (char *)malloc(file_size);
        if ( zip_extract_file(FileName, ArgList, (LPVOID *)&exe_data, (size_t *)&extracted_size) )
          fatal_error_with_message_box(" * EPSX: error loading .exe file in pll/zip.");
        if ( strncmp("PS-X EXE", exe_data, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", ArgList);
        qmemcpy((char *)ram + (*((uint32_t *)exe_data + 6) & 0x1FFFFF), exe_data + 2048, *((uint32_t *)exe_data + 7));
        cpu_gpr[28] = *((uint32_t *)exe_data + 5);
        cpu_gpr[29] = 0x801FFF00;
        cpu_gpr[30] = 0x801FFF00;
        cpu_gpr[31] = 0;
        *(uint32_t *)reg_pc = *((uint32_t *)exe_data + 4);
LABEL_14:
        free(exe_data);
      }
      section = loader_pll_parse_section((int)pll_data, &offset, pll_size, ArgList, (int)&load_addr);
      if ( !section )
        goto LABEL_16;
    }
    load_size = loader_pll_get_file_size(ArgList);
    exe_data = (char *)malloc(load_size);
    if ( zip_extract_file(FileName, ArgList, (LPVOID *)&exe_data, (size_t *)&extracted_size) )
      fatal_error_with_message_box(" * EPSX: error loading %s.", ArgList);
    qmemcpy((char *)ram + (load_addr & 0x1FFFFF), exe_data, extracted_size);
    goto LABEL_14;
  }
LABEL_16:
  free(pll_data);
}

void loader_load_zip()
{
  char *ext;
  void *scratch;
  uint8_t count;
  int index;
  const char *entry_name;
  char *exe_data;
  int tmp;

  ext = &FileName[-3];
  if ( !strncmp(&FileName[strlen(FileName) - 3], "zip", 3u) || !strncmp(&ext[strlen(FileName)], "ZIP", 3u) )
  {
    if ( !strncmp(&ext[strlen(FileName)], "zip", 3u) || !strncmp(&ext[strlen(FileName)], "ZIP", 3u) )
    {
      scratch = malloc(0x2000u);
      memset(scratch, 0, 0x2000u);
      if ( zip_load_file(FileName) )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      free(scratch);
      if ( !zip_num_entries_loaded )
        fatal_error_with_message_box(" * EPSX: error loading .zip file.");
      if ( zip_num_entries_loaded == 1 )
      {
        if ( strncmp(&zip_entry_names[strlen(zip_entry_names) - 3], "exe", 3u)
          && strncmp(&zip_entry_names[strlen(zip_entry_names) - 3], "EXE", 3u) )
        {
          fatal_error_with_message_box("* EPSX: DEMO not found [%s]. \n", zip_entry_names);
        }
        exe_data = (char *)malloc(Size[0]);
        if ( zip_extract_file(FileName, zip_entry_names, (LPVOID *)&exe_data, (size_t *)&tmp) )
          fatal_error_with_message_box(" * EPSX: error loading .zip file.");
        if ( strncmp("PS-X EXE", exe_data, 8u) )
          fatal_error_with_message_box(" * EPSX: [%s] is not a EXE file. \n", zip_entry_names);
        qmemcpy((char *)ram + (*((uint32_t *)exe_data + 6) & 0x1FFFFF), exe_data + 2048, *((uint32_t *)exe_data + 7));
        cpu_gpr[28] = *((uint32_t *)exe_data + 5);
        cpu_gpr[29] = 0x801FFF00;
        cpu_gpr[30] = 0x801FFF00;
        cpu_gpr[31] = 0;
        *(uint32_t *)reg_pc = *((uint32_t *)exe_data + 4);
        free(exe_data);
      }
      else
      {
        count = 0;
        LOBYTE(exe_data) = -1;
        if ( zip_num_entries_loaded <= 0 )
          goto LABEL_26;
        index = 0;
        do
        {
          entry_name = &zip_entry_names[256 * index];
          if ( !strncmp(&entry_name[strlen(entry_name) - 3], "pll", 3u) || !strncmp(&entry_name[strlen(entry_name) - 3], "PLL", 3u) )
            LOBYTE(exe_data) = count;
          LOBYTE(tmp) = ++count;
          index = count;
        }
        while ( count < zip_num_entries_loaded );
        if ( (uint8_t)exe_data == 0xFF )
LABEL_26:
          fatal_error_with_message_box("* EPSX: DEMO .pll not found. \n");
        loader_load_file(&zip_entry_names[256 * (uint8_t)exe_data], Size[(uint8_t)exe_data]);
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
  FILE *fp;

  if ( !strncmp(FileName, "NULL", 4u) )
    return 0;
  fp = fopen(FileName, "rb");
  if ( !fp )
    fatal_error_with_message_box(" * EPSX: DEMO not found [%s]. \n", FileName);
  fclose(fp);
  return 1;
}

int loader_cdrom_detect_region()
{
  int ret;
  unsigned int i;
  const char *msg;
  char Buffer[1024];

  if ( loaded_file_type != 3 && loaded_file_type != 1 )
  {
    sprintf(Buffer, "DEMO_999.99");
    ret = sprintf(default_filename, "%s", Buffer);
    video_scanlines = 262;
    cpu_speed_scale = 2154;
    country_setting = 0;
    return ret;
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
    msg = " * Force PAL cdrom detected. \n";
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
    msg = " * PAL cdrom detected. \n";
  }
  video_scanlines = 312;
  cpu_speed_scale = old_timing != 0 ? 1923 : 2171;
  return dbg_print(msg);
}

FILE * loader_load_cheat_file(char *FileName)
{
  FILE *fp;
  int id;
  int attr;
  int index;
  char Buffer[1024];

  active_mini_cheat_count = 0;
  fp = fopen(FileName, "r");
  if ( fp )
  {
    if ( !feof(fp) )
    {
      do
      {
        sprintf(Buffer, " ");
        fgets(Buffer, 1024, fp);
        if ( Buffer[0] != '#' && sscanf(Buffer, "%x %x", &id, &attr) == 2 )
        {
          index = 2 * (uint8_t)active_mini_cheat_count;
          mini_cheat_id_array[index] = id;
          mini_cheat_attr_array[index] = attr;
          ++active_mini_cheat_count;
        }
      }
      while ( !feof(fp) );
    }
    return (FILE *)fclose(fp);
  }
  return fp;
}
