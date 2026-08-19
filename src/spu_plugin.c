#include "pch.h"
char spu_load_plugin()
{
  char result;
  HMODULE LibraryA;
  CHAR LibFileName[1024];

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)SoundPlugin);
  result = sound_enabled;
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
    result = (char)SPUregisterCallback;
    if ( SPUregisterCallback )
      return SPUregisterCallback(irq_spu_registered_callback);
  }
  else
  {
    spu_use_external_plugin = 0;
  }
  return result;
}

char spu_destroy()
{
  char result;

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      result = (char)hSpuModule;
      if ( hSpuModule )
      {
        dbg_print(" * Closing spu ... \n");
        if ( !spu_plugin_closed_flag )
        {
          SPUclose();
          spu_plugin_closed_flag = 1;
        }
        result = SPUshutdown();
        hSpuModule = nullptr;
      }
    }
  }
  return result;
}

char spu_close()
{
  char result;

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      result = (char)hSpuModule;
      if ( hSpuModule )
      {
        result = SPUclose();
        spu_plugin_closed_flag = 1;
      }
    }
  }
  return result;
}

char spu_open()
{
  char result;

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = spu_need_to_be_closed;
    if ( spu_need_to_be_closed )
    {
      result = (char)hSpuModule;
      if ( hSpuModule )
      {
        result = SPUopen(hOutputWnd);
        spu_plugin_closed_flag = 0;
      }
    }
  }
  return result;
}

void spu_dma()
{
  unsigned int v0;
  int v1;
  int v2;
  int v3;
  int v4;
  uint16_t *j;
  int v6;
  uint16_t *k;
  int v8;
  int v9;
  uint16_t v10;
  int i;
  uint16_t v12;

  v0 = spu_dma_mem_addr;
  v1 = HIWORD(spu_dma_block_size_count);
  v2 = (uint16_t)spu_dma_block_size_count;
  v3 = mem_dma_read(spu_dma_mem_addr);
  if ( sound_enabled )
  {
    if ( *(uint32_t *)spu_dma_chcr_ptr == 0x1000200 )
    {
      v8 = v1 * v2;
      if ( spu_use_external_plugin == 1 )
      {
        if ( SPUreadDMAMem )
        {
          SPUreadDMAMem(v3, 2 * v8);
        }
        else if ( 2 * v8 )
        {
          v9 = 2 * v8;
          do
          {
            v10 = SPUreadDMA();
            mem_hw_reg_write_half(v0, v10);
            v0 += 2;
            --v9;
          }
          while ( v9 );
        }
        if ( dynarec_enabled == 1 && v8 )
          dynarec_invalidate_range(spu_dma_mem_addr, v8);
      }
      else
      {
        for ( i = 2 * v8; i; spu_transfer_addr += 2 )
        {
          v12 = SPUgetOne(spu_transfer_addr);
          mem_hw_reg_write_half(v0, v12);
          v0 += 2;
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
          SPUwriteDMAMem(v3, 2 * v1 * v2);
        }
        else
        {
          v4 = 2 * v1 * v2;
          for ( j = (uint16_t *)mem_dma_read(v0); v4; --v4 )
            SPUwriteDMA(*j++);
        }
      }
      else
      {
        v6 = 2 * v1 * v2;
        for ( k = (uint16_t *)mem_dma_read(v0); v6; spu_transfer_addr += 2 )
        {
          SPUputOne(spu_transfer_addr, *k++);
          --v6;
        }
      }
    }
    else if ( (*(uint32_t *)spu_dma_chcr_ptr & 0x1000000) != 0 )
    {
      ui_error(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(uint32_t *)spu_dma_chcr_ptr,
        v0,
        v1,
        v2);
    }
  }
}

char spu_write_register(unsigned int a1, int16_t a2)
{
  char result;

  if ( spu_use_external_plugin == 1 )
    return SPUwriteRegister(a1, (uint16_t)a2);
  result = a1;
  if ( a1 > 0x1F801CC6 )
  {
    switch ( a1 )
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
          result = SPUsetVolumeL((a1 >> 4) & 0x1F, (uint16_t)a2);
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
          result = SPUsetVolumeR((a1 >> 4) & 0x1F, (uint16_t)a2);
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
          result = SPUsetPitch((a1 >> 4) & 0x1F, (uint16_t)a2);
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
      case 0x1F801D88u:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstartChannels1((uint16_t)a2);
        break;
      case 0x1F801D8Au:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstartChannels2((uint16_t)a2);
        break;
      case 0x1F801D8Cu:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstopChannels1((uint16_t)a2);
        break;
      case 0x1F801D8Eu:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstopChannels2((uint16_t)a2);
        break;
      case 0x1F801DA6u:
        spu_transfer_addr = 8 * (uint16_t)a2;
        break;
      case 0x1F801DA8u:
        result = sound_enabled;
        if ( sound_enabled )
        {
          result = SPUputOne(spu_transfer_addr, (uint16_t)a2);
          spu_transfer_addr += 2;
        }
        break;
      default:
LABEL_26:
        *(int16_t *)((char *)spu_register_cache + (a1 & 0x1FF)) = a2;
        result = a1;
        break;
    }
  }
  else
  {
    if ( a1 != 0x1F801CC6 )
    {
      switch ( a1 )
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
      return SPUsetAddr((a1 >> 4) & 0x1F, (uint16_t)a2);
  }
  return result;
}

int16_t spu_read_register(unsigned int a1)
{
  int v1;

  if ( !unknown_cd_setting || (a1 & 0xF) != 0xC )
  {
    if ( spu_use_external_plugin == 1 )
    {
      LOWORD(v1) = SPUreadRegister(a1);
      return v1;
    }
    if ( a1 > 0x1F801DA8 )
    {
      if ( a1 != 0x1F801DAE )
        goto LABEL_15;
    }
    else
    {
      if ( a1 != 0x1F801DA8 )
      {
        if ( a1 == 0x1F801C0C )
        {
          LOWORD(v1) = hw_update_counter;
          return v1;
        }
        if ( a1 == 0x1F801DA6 )
          return (unsigned int)spu_transfer_addr >> 3;
LABEL_15:
        LOWORD(v1) = *(int16_t *)((char *)spu_register_cache + (a1 & 0x1FF));
        return v1;
      }
      if ( sound_enabled )
      {
        LOWORD(v1) = SPUgetOne(spu_transfer_addr);
        spu_transfer_addr += 2;
        return v1;
      }
    }
    LOWORD(v1) = 0;
    return v1;
  }
  LOWORD(v1) = rand() & 1;
  return v1;
}

char spu_play_adpcm(int a1)
{
  int v1;

  LOBYTE(v1) = sound_enabled;
  if ( sound_enabled )
  {
    LOBYTE(v1) = sound_use_xa;
    if ( sound_use_xa )
    {
      v1 = xa_decode_wrapper(spu_xa_decode_buf_ptr, a1, spu_adpcm_flag);
      if ( !v1 && (spu_xa_samples_left || (LOBYTE(v1) = spu_use_external_plugin) == 0) )
        LOBYTE(v1) = SPUplayADPCMchannel(spu_xa_decode_buf_ptr);
      spu_adpcm_flag = 0;
    }
  }
  return v1;
}

void spu_set_adpcm_flag()
{
  spu_adpcm_flag = 1;
}

int (*spu_update())(void)
{
  int (*result)(void);

  result = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return result;
}

int (* spu_async_update(int a1))(void)
{
  int (*result)(void);

  if ( SPUasync )
    return SPUasync(a1);
  result = (int (*)(void))SPUupdate;
  if ( SPUupdate )
    return SPUupdate();
  return result;
}

void spu_freeze(const char *a1, int a2)
{
  size_t v2;
  uint8_t *v3;
  char Buffer[3];
  int v5;
  size_t Size;

  sprintf(Buffer, "%s", a1);
  v5 = 0;
  gzwrite(a2, (uint8_t *)Buffer, 7u);
  if ( SPUfreeze )
  {
    SPUfreeze(2, Buffer);
    v2 = Size;
    if ( Size )
    {
      v3 = (uint8_t *)malloc(Size);
      SPUfreeze(1, v3);
      gzwrite(a2, v3, v2);
      free(v3);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}

void spu_unfreeze(int a1, uint32_t *a2)
{
  size_t v2;
  void *v3;
  char v4[4];
  int v5;
  int v6;
  size_t Size;

  gzread(a2, v4, 7);
  if ( SPUfreeze )
  {
    gzread(a2, v4, 16);
    v2 = Size;
    if ( Size )
    {
      v3 = malloc(Size);
      *(uint32_t *)v3 = *(uint32_t *)v4;
      *((uint32_t *)v3 + 1) = v5;
      *((uint32_t *)v3 + 2) = v6;
      *((uint32_t *)v3 + 3) = Size;
      gzread(a2, (char *)v3 + 16, v2 - 16);
      SPUfreeze(0, v3);
      free(v3);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}



/* Decompiled globals (previously generated in src/_gen) */
unsigned int SPUabout;
int (__stdcall *SPUasync)();
int (__stdcall *SPUclose)();
unsigned int SPUconfigure;
int (__stdcall *SPUfreeze)();
int (__stdcall *SPUgetOne)();
int (__stdcall *SPUinit)();
int (__stdcall *SPUopen)();
int (__stdcall *SPUplayADPCMchannel)();
unsigned int SPUplaySample;
int (__stdcall *SPUputOne)();
int (__stdcall *SPUreadDMA)();
int (__stdcall *SPUreadDMAMem)();
int (__stdcall *SPUreadRegister)();
int (__stdcall *SPUregisterCallback)();
int (__stdcall *SPUsetAddr)();
int (__stdcall *SPUsetPitch)();
int (__stdcall *SPUsetVolumeL)();
int (__stdcall *SPUsetVolumeR)();
int (__stdcall *SPUshutdown)();
int (__stdcall *SPUstartChannels1)();
int (__stdcall *SPUstartChannels2)();
int (__stdcall *SPUstopChannels1)();
int (__stdcall *SPUstopChannels2)();
unsigned int SPUtest;
int (__stdcall *SPUupdate)();
int (__stdcall *SPUwriteDMA)();
int (__stdcall *SPUwriteDMAMem)();
int (__stdcall *SPUwriteRegister)();
unsigned int Size[0x100];
unsigned char spu_plugin_closed_flag = 0x0;
unsigned int spu_dma_chcr_ptr;
unsigned int spu_transfer_addr;
unsigned int hSpuModule = 0x0;
unsigned char sound_enabled = 0x1;
unsigned int spu_adpcm_flag = 0x1;
unsigned char spu_need_to_be_closed;
unsigned char spu_use_external_plugin = 0x1;
unsigned short spu_register_cache[0x200];
