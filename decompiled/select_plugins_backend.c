#include "pch.h"
int select_plugins_backend()
{
  if ( !strcmp((const char *)SoundPlugin, "SPUCORE") && sound_enabled )
  {
    spu_dma_cb = (int (*)(void))spucore_dma;
    spu_read_register_cb = (int (__cdecl *)(_DWORD))spucore_read_register;
    spu_write_register_cb = (int (__cdecl *)(_DWORD, _DWORD))spucore_write_register;
    spu_init_cb = spucore_init;
    spu_destroy_cb = (int (__cdecl *)(_DWORD))spucore_destroy;
    spu_play_adpcm_cb = (int (__cdecl *)(_DWORD))spucore_play_adpcm;
    spu_set_adpcm_flag_cb = (int (*)(void))spu_set_adpcm_flag;
    spu_update_cb = spucore_update;
    spu_freeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spucore_freeze;
    spu_unfreeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spucore_unfreeze;
    spu_async_update_cb = (int (__cdecl *)(_DWORD))spucore_update;
  }
  else
  {
    spu_dma_cb = (int (*)(void))spu_dma;
    spu_read_register_cb = (int (__cdecl *)(_DWORD))spu_read_register;
    spu_write_register_cb = (int (__cdecl *)(_DWORD, _DWORD))spu_write_register;
    spu_init_cb = (int (*)(void))spu_load_plugin;
    spu_destroy_cb = (int (__cdecl *)(_DWORD))spu_destroy;
    spu_play_adpcm_cb = (int (__cdecl *)(_DWORD))spu_play_adpcm;
    spu_set_adpcm_flag_cb = (int (*)(void))spu_set_adpcm_flag;
    spu_update_cb = (int (*)(void))spu_update;
    spu_freeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spu_freeze;
    spu_unfreeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spu_unfreeze;
    spu_async_update_cb = (int (__cdecl *)(_DWORD))spu_async_update;
  }
  if ( !strcmp((const char *)CdromPlugin, "W9XCDRCORE") )
  {
    cdrom_init_cb = (int (*)(void))W9x_cdrom_init;
    cdrom_deinit_cb = (int (__fastcall *)(_DWORD))W9x_cdrom_deinit;
    dword_4FC4B8 = (int (__cdecl *)(_DWORD, _DWORD))sub_4314A0;
    dword_4FC4BC = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_4314C0;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W9x_cdrom_read_data;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))W9x_play_cdda;
    cdrom_stop_cb = (int (*)(void))W9x_cdrom_stop;
    dword_4FC4CC = (int (*)(void))sub_433610;
    dword_4FC4D0 = (int)nullsub_1;
    dword_4FC4D4 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))sub_4337F0;
    dword_4FC4D8 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_433930;
    cdrom_subchannel_read_cb = (int (*)(void))W9x_cdrom_subchannel_read;
  }
  else if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
  {
    cdrom_init_cb = (int (*)(void))W2k_cdrom_init;
    cdrom_deinit_cb = (int (__fastcall *)(_DWORD))W2k_cdrom_deinit;
    dword_4FC4B8 = (int (__cdecl *)(_DWORD, _DWORD))sub_4341C0;
    dword_4FC4BC = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_4341E0;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W2k_cdrom_read_data;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))W2k_cdrom_play_cdda;
    cdrom_stop_cb = (int (*)(void))W2k_cdrom_stop;
    dword_4FC4CC = sub_4345E0;
    dword_4FC4D0 = (int)nullsub_1;
    dword_4FC4D4 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))sub_4347A0;
    dword_4FC4D8 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_4348D0;
    cdrom_subchannel_read_cb = (int (*)(void))W2k_cdrom_subchannel_read;
  }
  else
  {
    cdrom_init_cb = (int (*)(void))ext_cdrom_load_plugin;
    cdrom_deinit_cb = (int (__fastcall *)(_DWORD))ext_cdrom_deinit;
    dword_4FC4B8 = (int (__cdecl *)(_DWORD, _DWORD))sub_4304E0;
    dword_4FC4BC = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_430500;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))ext_CDR_read;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))ext_CDRplay;
    cdrom_stop_cb = (int (*)(void))ext_CDRstop;
    dword_4FC4CC = (int (*)(void))sub_430810;
    dword_4FC4D0 = (int)nullsub_1;
    dword_4FC4D4 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))sub_430A00;
    dword_4FC4D8 = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_430B60;
    cdrom_subchannel_read_cb = (int (*)(void))nullsub_1;
  }
  *(_DWORD *)dword_5164D0 = 0;
  *(_DWORD *)dword_566964 = 0;
  memset(dword_5164E0, 0, 0x60u);
  memset(byte_516600, 0, 0x10000u);
  return 0;
}
