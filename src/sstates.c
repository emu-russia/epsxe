#include "pch.h"
char gpu_freeze_with_counter()
{
  LOBYTE(gpu_freeze_counter) = ((uint8_t)gpu_freeze_counter + 1) % 5;
  gpu_do_freeze((uint8_t)gpu_freeze_counter);
  return gpu_freeze_counter;
}

char set_gpu_freeze_counter(char value)
{
  LOBYTE(gpu_freeze_counter) = value;
  return value;
}

char get_gpu_freeze_counter()
{
  return gpu_freeze_counter;
}

uint32_t *state_save()
{
  uint32_t *fp;
  uint32_t *fp2;
  char header[64];
  char path[1024];

  sprintf(path, "%s%s.%03d", "sstates\\", default_filename, (uint8_t)gpu_freeze_counter);
  memset(header, 0, sizeof(header));
  fp = gzopen(path, "wb1");
  fp2 = fp;
  if ( fp )
  {
    sprintf(header, "ePSXe");
    if ( save_state_ver == -1 )
      *(uint16_t *)&header[5] = 2;
    else
      *(uint16_t *)&header[5] = save_state_ver;
    *(uint32_t *)&header[7] = *(uint32_t *)default_filename;
    *(uint32_t *)&header[11] = *(uint32_t *)&default_filename[4];
    *(uint32_t *)&header[15] = *(uint32_t *)&default_filename[8];
    gzwrite((int)fp2, (uint8_t *)header, 0x40u);
    sprintf(header, "PSX");
    *(uint32_t *)&header[3] = 364;
    gzwrite((int)fp2, (uint8_t *)header, 7u);
    gzwrite((int)fp2, (uint8_t *)reg_pc, 0x16Cu);
    mem_freeze("MEM", (int)fp2);
    hw_reg_freeze("REG", (int)fp2);
    irq_freeze("IRQ", (int)fp2);
    gte_freeze("GTE", (int)fp2);
    cdr_freeze("CDR", (int)fp2);
    sio_freeze("SIO", (int)fp2);
    if ( save_state_ver == -1 )
      mdec_freeze("MDE", (int)fp2);
    else
      mdec_freeze2("MDE", (int)fp2);
    gpu_freeze("GPU", (int)fp2, path);
    spu_freeze_cb("SPU", fp2);
    return (uint32_t *)gzclose(fp2);
  }
  return fp;
}

uint32_t *state_load()
{
  int dynarec;
  int file_type;
  uint32_t *fp;
  uint32_t *fp2;
  uint16_t version;
  char header[5];
  int tmp;
  char path[1024];

  dynarec = dynarec_enabled;
  file_type = loaded_file_type;
  if ( !strcmp(state_file_from_cmdline, "NULL") )
  {
    sprintf(path, "%s%s.%03d", "sstates\\", default_filename, (uint8_t)gpu_freeze_counter);
  }
  else
  {
    sprintf(path, "%s", state_file_from_cmdline);
    sprintf(state_file_from_cmdline, "NULL");
  }
  fp = gzopen(path, "rb1");
  fp2 = fp;
  if ( fp )
  {
    gzread(fp, header, 64);
    version = tmp;
    gzread(fp2, header, 7);
    gzread(fp2, reg_pc, 364);
    dynarec_enabled = dynarec;
    loaded_file_type = file_type;
    mem_unfreeze((int)"MEM", fp2);
    hw_reg_unfreeze((int)"REG", fp2);
    irq_unfreeze((int)"IRQ", fp2);
    gte_unfreeze((int)"GTE", fp2);
    if ( version >= 2u )
      cdr_unfreeze_new((int)"CDR", fp2);
    else
      cdr_unfreeze((int)"CDR", fp2);
    sio_unfreeze((int)"SIO", fp2);
    if ( version )
      mdec_unfreeze((int)"MDE", fp2);
    else
      mdec_unfreeze2((int)"MDE", fp2);
    gpu_unfreeze((int)"GPU", fp2);
    spu_unfreeze_cb("SPU", fp2);
    return (uint32_t *)gzclose(fp2);
  }
  return fp;
}

char check_state_exists(uint8_t slot)
{
  FILE *fp;
  char path[1024];

  sprintf(path, "%s%s.%03d", "sstates\\", default_filename, slot);
  fp = fopen(path, "rb");
  if ( !fp )
    return -1;
  fclose(fp);
  return 0;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int gpu_freeze_counter = 0x0;
unsigned char save_state_ver = 0xff;
unsigned char state_file_from_cmdline[0x400];
