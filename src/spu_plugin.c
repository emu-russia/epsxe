#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned int SPUabout;
static int (__stdcall *SPUasync)();
static int (__stdcall *SPUclose)();
static unsigned int SPUconfigure;
static int (__stdcall *SPUfreeze)();
static int (__stdcall *SPUgetOne)();
static int (__stdcall *SPUinit)();
static int (__stdcall *SPUopen)();
static int (__stdcall *SPUplayADPCMchannel)();
static unsigned int SPUplaySample;
static int (__stdcall *SPUputOne)();
static int (__stdcall *SPUreadDMA)();
static int (__stdcall *SPUreadDMAMem)();
static int (__stdcall *SPUreadRegister)();
static int (__stdcall *SPUregisterCallback)();
static int (__stdcall *SPUsetAddr)();
static int (__stdcall *SPUsetPitch)();
static int (__stdcall *SPUsetVolumeL)();
static int (__stdcall *SPUsetVolumeR)();
static int (__stdcall *SPUshutdown)();
static int (__stdcall *SPUstartChannels1)();
static int (__stdcall *SPUstartChannels2)();
static int (__stdcall *SPUstopChannels1)();
static int (__stdcall *SPUstopChannels2)();
static unsigned int SPUtest;
static int (__stdcall *SPUupdate)();
static int (__stdcall *SPUwriteDMA)();
static int (__stdcall *SPUwriteDMAMem)();
static int (__stdcall *SPUwriteRegister)();
unsigned int Size[0x100];
static unsigned char spu_plugin_closed_flag = 0x0;
unsigned int spu_dma_chcr_ptr;
static unsigned int spu_transfer_addr;
static unsigned int hSpuModule = 0x0;
unsigned char sound_enabled = 0x1;
unsigned int spu_adpcm_flag = 0x1;
static unsigned char spu_need_to_be_closed;
static unsigned char spu_use_external_plugin = 0x1;
static unsigned short spu_register_cache[0x200];

char spu_load_plugin()
{
  char status;
  HMODULE LibraryA;
  CHAR LibFileName[1024];

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)SoundPlugin);
  status = sound_enabled;
  spu_need_to_be_closed = 0;
  if ( sound_enabled )
  {
    spu_need_to_be_closed = 1;
    LibraryA = LoadLibraryA(LibFileName);
    hSpuModule = LibraryA;
    if ( !LibraryA )
      fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
    SPUinit = GetProcAddress(LibraryA, "SPUinit");
    if ( !SPUinit )
      ui_error(" * GetProcAddress error %s\n", "SPUinit");
    SPUshutdown = GetProcAddress(hSpuModule, "SPUshutdown");
    if ( !SPUshutdown )
      ui_error(" * GetProcAddress error %s\n", "SPUshutdown");
    SPUopen = (int (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUopen");
    if ( !SPUopen )
      ui_error(" * GetProcAddress error %s\n", "SPUopen");
    SPUclose = GetProcAddress(hSpuModule, "SPUclose");
    if ( !SPUclose )
      ui_error(" * GetProcAddress error %s\n", "SPUclose");
    SPUconfigure = (int)GetProcAddress(hSpuModule, "SPUconfigure");
    if ( !SPUconfigure )
      ui_error(" * GetProcAddress error %s\n", "SPUconfigure");
    SPUabout = (int)GetProcAddress(hSpuModule, "SPUabout");
    if ( !SPUabout )
      ui_error(" * GetProcAddress error %s\n", "SPUabout");
    SPUtest = (int)GetProcAddress(hSpuModule, "SPUtest");
    if ( !SPUtest )
      ui_error(" * GetProcAddress error %s\n", "SPUtest");
    SPUplaySample = (int)GetProcAddress(hSpuModule, "SPUplaySample");
    if ( !SPUplaySample )
      ui_error(" * GetProcAddress error %s\n", "SPUplaySample");
    SPUstartChannels1 = (char (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUstartChannels1");
    if ( !SPUstartChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels1");
    SPUstartChannels2 = (char (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUstartChannels2");
    if ( !SPUstartChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstartChannels2");
    SPUstopChannels1 = (char (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUstopChannels1");
    if ( !SPUstopChannels1 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels1");
    SPUstopChannels2 = (char (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUstopChannels2");
    if ( !SPUstopChannels2 )
      ui_error(" * GetProcAddress error %s\n", "SPUstopChannels2");
    SPUputOne = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUputOne");
    if ( !SPUputOne )
      ui_error(" * GetProcAddress error %s\n", "SPUputOne");
    SPUgetOne = (int (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUgetOne");
    if ( !SPUgetOne )
      ui_error(" * GetProcAddress error %s\n", "SPUgetOne");
    SPUsetAddr = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUsetAddr");
    if ( !SPUsetAddr )
      ui_error(" * GetProcAddress error %s\n", "SPUsetAddr");
    SPUsetPitch = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUsetPitch");
    if ( !SPUsetPitch )
      ui_error(" * GetProcAddress error %s\n", "SPUsetPitch");
    SPUsetVolumeL = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUsetVolumeL");
    if ( !SPUsetVolumeL )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeL");
    SPUsetVolumeR = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUsetVolumeR");
    if ( !SPUsetVolumeR )
      ui_error(" * GetProcAddress error %s\n", "SPUsetVolumeR");
    SPUplayADPCMchannel = (int (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUplayADPCMchannel");
    if ( !SPUplayADPCMchannel )
      ui_error(" * GetProcAddress error %s\n", "SPUplayADPCMchannel");
    SPUwriteRegister = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUwriteRegister");
    if ( !SPUwriteRegister )
      spu_use_external_plugin = 0;
    SPUreadRegister = (int16_t (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUreadRegister");
    if ( !SPUreadRegister )
      spu_use_external_plugin = 0;
    SPUwriteDMA = (int (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUwriteDMA");
    if ( !SPUwriteDMA )
      spu_use_external_plugin = 0;
    SPUreadDMA = GetProcAddress(hSpuModule, "SPUreadDMA");
    if ( !SPUreadDMA )
      spu_use_external_plugin = 0;
    SPUregisterCallback = (char (__stdcall *)(uint32_t))GetProcAddress(hSpuModule, "SPUregisterCallback");
    SPUfreeze = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUfreeze");
    SPUupdate = (int (__stdcall *)(void))GetProcAddress(hSpuModule, "SPUupdate");
    SPUasync = (int (*(__stdcall *)(uint32_t))(void))GetProcAddress(hSpuModule, "SPUasync");
    SPUreadDMAMem = (int (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUreadDMAMem");
    SPUwriteDMAMem = (char (__stdcall *)(uint32_t, uint32_t))GetProcAddress(hSpuModule, "SPUwriteDMAMem");
    dbg_print(" * Doing spu init... \n");
    SPUinit();
    dbg_print(" * Spu open... \n");
    SPUopen(hOutputWnd);
    status = (char)SPUregisterCallback;
    if ( SPUregisterCallback )
      return SPUregisterCallback(irq_spu_registered_callback);
  }
  else
  {
    spu_use_external_plugin = 0;
  }
  return status;
}

char spu_destroy()
{
  char status;

  status = sound_enabled;
  if ( sound_enabled )
  {
    status = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      status = (char)hSpuModule;
      if ( hSpuModule )
      {
        dbg_print(" * Closing spu ... \n");
        if ( !spu_plugin_closed_flag )
        {
          SPUclose();
          spu_plugin_closed_flag = 1;
        }
        status = SPUshutdown();
        hSpuModule = nullptr;
      }
    }
  }
  return status;
}

char spu_close()
{
  char status;

  status = sound_enabled;
  if ( sound_enabled )
  {
    status = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      status = (char)hSpuModule;
      if ( hSpuModule )
      {
        status = SPUclose();
        spu_plugin_closed_flag = 1;
      }
    }
  }
  return status;
}

char spu_open()
{
  char status;

  status = sound_enabled;
  if ( sound_enabled )
  {
    status = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      status = (char)hSpuModule;
      if ( hSpuModule )
      {
        status = SPUopen(hOutputWnd);
        spu_plugin_closed_flag = 0;
      }
    }
  }
  return status;
}

void spu_dma()
{
  unsigned int dma_addr;
  int count;
  int size;
  int src;
  int write_halfwords;
  uint16_t *src16;
  int put_halfwords;
  uint16_t *mem16;
  int word_count;
  int read_halfwords;
  uint16_t data;
  int i;
  uint16_t sample;

  dma_addr = spu_dma_mem_addr;
  count = HIWORD(spu_dma_block_size_count);
  size = (uint16_t)spu_dma_block_size_count;
  src = mem_dma_read(spu_dma_mem_addr);
  if ( sound_enabled )
  {
    if ( *(uint32_t *)spu_dma_chcr_ptr == 0x1000200 )
    {
      word_count = count * size;
      if ( spu_use_external_plugin == 1 )
      {
        if ( SPUreadDMAMem )
        {
          SPUreadDMAMem(src, 2 * word_count);
        }
        else if ( 2 * word_count )
        {
          read_halfwords = 2 * word_count;
          do
          {
            data = SPUreadDMA();
            mem_hw_reg_write_half(dma_addr, data);
            dma_addr += 2;
            --read_halfwords;
          }
          while ( read_halfwords );
        }
        if ( dynarec_enabled == 1 && word_count )
          dynarec_invalidate_range(spu_dma_mem_addr, word_count);
      }
      else
      {
        for ( i = 2 * word_count; i; spu_transfer_addr += 2 )
        {
          sample = SPUgetOne(spu_transfer_addr);
          mem_hw_reg_write_half(dma_addr, sample);
          dma_addr += 2;
          --i;
        }
      }
    }
    else if ( *(uint32_t *)spu_dma_chcr_ptr == 0x1000201 )
    {
      if ( spu_use_external_plugin == 1 )
      {
        if ( SPUwriteDMAMem )
        {
          SPUwriteDMAMem(src, 2 * count * size);
        }
        else
        {
          write_halfwords = 2 * count * size;
          for ( src16 = (uint16_t *)mem_dma_read(dma_addr); write_halfwords; --write_halfwords )
            SPUwriteDMA(*src16++);
        }
      }
      else
      {
        put_halfwords = 2 * count * size;
        for ( mem16 = (uint16_t *)mem_dma_read(dma_addr); put_halfwords; spu_transfer_addr += 2 )
        {
          SPUputOne(spu_transfer_addr, *mem16++);
          --put_halfwords;
        }
      }
    }
    else if ( (*(uint32_t *)spu_dma_chcr_ptr & 0x1000000) != 0 )
    {
      ui_error(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(uint32_t *)spu_dma_chcr_ptr,
        dma_addr,
        count,
        size);
    }
  }
}

char spu_write_register(unsigned int reg, int16_t value)
{
  char status;

  if ( spu_use_external_plugin == 1 )
    return SPUwriteRegister(reg, (uint16_t)value);
  status = reg;
  if ( reg > 0x1F801CC6 )
  {
    switch ( reg )
    {
      case 0x1F801CD0u:
      case 0x1F801CE0u:
      case 0x1F801CF0u:
      case 0x1F801D00u:
      case 0x1F801D10u:
      case 0x1F801D20u:
      case 0x1F801D30u:
      case 0x1F801D40u:
      case 0x1F801D50u:
      case 0x1F801D60u:
      case 0x1F801D70u:
LABEL_7:
        if ( sound_enabled )
          status = SPUsetVolumeL((reg >> 4) & 0x1F, (uint16_t)value);
        break;
      case 0x1F801CD2u:
      case 0x1F801CE2u:
      case 0x1F801CF2u:
      case 0x1F801D02u:
      case 0x1F801D12u:
      case 0x1F801D22u:
      case 0x1F801D32u:
      case 0x1F801D42u:
      case 0x1F801D52u:
      case 0x1F801D62u:
      case 0x1F801D72u:
LABEL_9:
        if ( sound_enabled )
          status = SPUsetVolumeR((reg >> 4) & 0x1F, (uint16_t)value);
        break;
      case 0x1F801CD4u:
      case 0x1F801CE4u:
      case 0x1F801CF4u:
      case 0x1F801D04u:
      case 0x1F801D14u:
      case 0x1F801D24u:
      case 0x1F801D34u:
      case 0x1F801D44u:
      case 0x1F801D54u:
      case 0x1F801D64u:
      case 0x1F801D74u:
LABEL_11:
        if ( sound_enabled )
          status = SPUsetPitch((reg >> 4) & 0x1F, (uint16_t)value);
        break;
      case 0x1F801CD6u:
      case 0x1F801CE6u:
      case 0x1F801CF6u:
      case 0x1F801D06u:
      case 0x1F801D16u:
      case 0x1F801D26u:
      case 0x1F801D36u:
      case 0x1F801D46u:
      case 0x1F801D56u:
      case 0x1F801D66u:
      case 0x1F801D76u:
        goto LABEL_13;
      case PSX_REG_SPU_KON_L:
        status = sound_enabled;
        if ( sound_enabled )
          status = SPUstartChannels1((uint16_t)value);
        break;
      case PSX_REG_SPU_KON_R:
        status = sound_enabled;
        if ( sound_enabled )
          status = SPUstartChannels2((uint16_t)value);
        break;
      case PSX_REG_SPU_KOFF_L:
        status = sound_enabled;
        if ( sound_enabled )
          status = SPUstopChannels1((uint16_t)value);
        break;
      case PSX_REG_SPU_KOFF_R:
        status = sound_enabled;
        if ( sound_enabled )
          status = SPUstopChannels2((uint16_t)value);
        break;
      case PSX_REG_SPU_TRANS_ADDR:
        spu_transfer_addr = 8 * (uint16_t)value;
        break;
      case PSX_REG_SPU_TRANS_FIFO:
        status = sound_enabled;
        if ( sound_enabled )
        {
          status = SPUputOne(spu_transfer_addr, (uint16_t)value);
          spu_transfer_addr += 2;
        }
        break;
      default:
LABEL_26:
        *(int16_t *)((char *)spu_register_cache + (reg & 0x1FF)) = value;
        status = reg;
        break;
    }
  }
  else
  {
    if ( reg != 0x1F801CC6 )
    {
      switch ( reg )
      {
        case 0x1F801C00u:
        case 0x1F801C10u:
        case 0x1F801C20u:
        case 0x1F801C30u:
        case 0x1F801C40u:
        case 0x1F801C50u:
        case 0x1F801C60u:
        case 0x1F801C70u:
        case 0x1F801C80u:
        case 0x1F801C90u:
        case 0x1F801CA0u:
        case 0x1F801CB0u:
        case 0x1F801CC0u:
          goto LABEL_7;
        case 0x1F801C02u:
        case 0x1F801C12u:
        case 0x1F801C22u:
        case 0x1F801C32u:
        case 0x1F801C42u:
        case 0x1F801C52u:
        case 0x1F801C62u:
        case 0x1F801C72u:
        case 0x1F801C82u:
        case 0x1F801C92u:
        case 0x1F801CA2u:
        case 0x1F801CB2u:
        case 0x1F801CC2u:
          goto LABEL_9;
        case 0x1F801C04u:
        case 0x1F801C14u:
        case 0x1F801C24u:
        case 0x1F801C34u:
        case 0x1F801C44u:
        case 0x1F801C54u:
        case 0x1F801C64u:
        case 0x1F801C74u:
        case 0x1F801C84u:
        case 0x1F801C94u:
        case 0x1F801CA4u:
        case 0x1F801CB4u:
        case 0x1F801CC4u:
          goto LABEL_11;
        case 0x1F801C06u:
        case 0x1F801C16u:
        case 0x1F801C26u:
        case 0x1F801C36u:
        case 0x1F801C46u:
        case 0x1F801C56u:
        case 0x1F801C66u:
        case 0x1F801C76u:
        case 0x1F801C86u:
        case 0x1F801C96u:
        case 0x1F801CA6u:
        case 0x1F801CB6u:
          break;
        default:
          goto LABEL_26;
      }
    }
LABEL_13:
    if ( sound_enabled )
      return SPUsetAddr((reg >> 4) & 0x1F, (uint16_t)value);
  }
  return status;
}

int16_t spu_read_register(unsigned int reg)
{
  int value;

  if ( !unknown_cd_setting || (reg & 0xF) != 0xC )
  {
    if ( spu_use_external_plugin == 1 )
    {
      LOWORD(value) = SPUreadRegister(reg);
      return value;
    }
    if ( reg > PSX_REG_SPU_TRANS_FIFO )
    {
      if ( reg != PSX_REG_SPU_STAT )
        goto LABEL_15;
    }
    else
    {
      if ( reg != PSX_REG_SPU_TRANS_FIFO )
      {
        if ( reg == 0x1F801C0C )
        {
          LOWORD(value) = hw_update_counter;
          return value;
        }
        if ( reg == PSX_REG_SPU_TRANS_ADDR )
          return (unsigned int)spu_transfer_addr >> 3;
LABEL_15:
        LOWORD(value) = *(int16_t *)((char *)spu_register_cache + (reg & 0x1FF));
        return value;
      }
      if ( sound_enabled )
      {
        LOWORD(value) = SPUgetOne(spu_transfer_addr);
        spu_transfer_addr += 2;
        return value;
      }
    }
    LOWORD(value) = 0;
    return value;
  }
  LOWORD(value) = rand() & 1;
  return value;
}

char spu_play_adpcm(int hdr)
{
  int status;

  LOBYTE(status) = sound_enabled;
  if ( sound_enabled )
  {
    LOBYTE(status) = sound_use_xa;
    if ( sound_use_xa )
    {
      status = xa_decode_wrapper(spu_xa_decode_buf_ptr, hdr, spu_adpcm_flag);
      if ( !status && (spu_xa_samples_left || (LOBYTE(status) = spu_use_external_plugin) == 0) )
        LOBYTE(status) = SPUplayADPCMchannel(spu_xa_decode_buf_ptr);
      spu_adpcm_flag = 0;
    }
  }
  return status;
}

void spu_set_adpcm_flag()
{
  spu_adpcm_flag = 1;
}

int (*spu_update())(void)
{
  int (*fn)(void);

  fn = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return fn;
}

int (* spu_async_update(int cycles))(void)
{
  int (*fn)(void);

  if ( SPUasync )
    return SPUasync(cycles);
  fn = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return fn;
}

void spu_freeze(const char *id, int gzfile)
{
  size_t write_size;
  uint8_t *buf;
  char Buffer[3];
  size_t Size;

  sprintf(Buffer, "%s", id);
  gzwrite(gzfile, (uint8_t *)Buffer, 7u);
  if ( SPUfreeze )
  {
    SPUfreeze(2, Buffer);
    write_size = Size;
    if ( Size )
    {
      buf = (uint8_t *)malloc(Size);
      SPUfreeze(1, buf);
      gzwrite(gzfile, buf, write_size);
      free(buf);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}

void spu_unfreeze(int unused, uint32_t *gzfile)
{
  size_t size;
  void *buf;
  char header[4];
  int field1;
  int field2;
  size_t Size;

  gzread(gzfile, header, 7);
  if ( SPUfreeze )
  {
    gzread(gzfile, header, 16);
    size = Size;
    if ( Size )
    {
      buf = malloc(Size);
      *(uint32_t *)buf = *(uint32_t *)header;
      *((uint32_t *)buf + 1) = field1;
      *((uint32_t *)buf + 2) = field2;
      *((uint32_t *)buf + 3) = Size;
      gzread(gzfile, (char *)buf + 16, size - 16);
      SPUfreeze(0, buf);
      free(buf);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}
