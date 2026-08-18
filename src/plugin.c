#include "pch.h"
char select_cdrom_core()
{
  int win_aspi_silent; // eax
  struct _OSVERSIONINFOA VersionInformation; // [esp+8h] [ebp-94h] BYREF

  LOBYTE(win_aspi_silent) = 0;
  if ( !strcmp((const char *)CdromPlugin, "NULL") )
  {
    memset(&VersionInformation, 0, sizeof(VersionInformation));
    VersionInformation.dwOSVersionInfoSize = 148;
    GetVersionExA(&VersionInformation);
    if ( VersionInformation.dwPlatformId == 2 )
    {
      LOBYTE(win_aspi_silent) = sprintf((char *const)CdromPlugin, "W2KCDRCORE");
    }
    else
    {
      win_aspi_silent = W9x_load_win_aspi_silent();
      if ( !win_aspi_silent )
      {
        W9x_init_aspi();
        W9x_free_winaspi_dll();
        LOBYTE(win_aspi_silent) = HIBYTE(w9x_cdrom_info);
        if ( HIBYTE(w9x_cdrom_info) )
        {
          cdrom_haid = cd_device_haid;
          cdrom_target = cd_device_target;
          cdrom_lun = cd_device_lun[0];
          LOBYTE(win_aspi_silent) = sprintf((char *const)CdromPlugin, "W9XCDRCORE");
        }
      }
    }
  }
  return win_aspi_silent;
}

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
    spu_update_cb = spucore_update_thunk;
    spu_freeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spucore_freeze;
    spu_unfreeze_cb = (int (__cdecl *)(_DWORD, _DWORD))spucore_unfreeze;
    spu_async_update_cb = (int (__cdecl *)(_DWORD))spucore_update_thunk;
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
    cdrom_deinit_cb = (int (__cdecl *)(_DWORD))W9x_cdrom_deinit;
    cdrom_get_first_last_TN_cb = (int (__cdecl *)(_DWORD, _DWORD))W9x_get_first_last_track;
    cdrom_track_to_msf = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W9x_track_to_msf;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W9x_cdrom_read_data;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))W9x_play_cdda;
    cdrom_stop_cb = (int (*)(void))W9x_cdrom_stop;
    cdrom_reset_cb = (int (*)(void))W9x_reset_cdrom_state;
    cdrom_unused_cb = (int)nullsub_1;
    cdrom_lba_to_msf_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))W9x_get_track_start_lba;
    cdrom_verify_sub_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W9x_verify_subchannel_data;
    cdrom_subchannel_read_cb = (int (*)(void))W9x_cdrom_subchannel_read;
  }
  else if ( !strcmp((const char *)CdromPlugin, "W2KCDRCORE") )
  {
    cdrom_init_cb = (int (*)(void))W2k_cdrom_init;
    cdrom_deinit_cb = (int (__cdecl *)(_DWORD))W2k_cdrom_deinit;
    cdrom_get_first_last_TN_cb = (int (__cdecl *)(_DWORD, _DWORD))W2k_get_first_last_track;
    cdrom_track_to_msf = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W2k_track_to_msf;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W2k_cdrom_read_data;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))W2k_cdrom_play_cdda;
    cdrom_stop_cb = (int (*)(void))W2k_cdrom_stop;
    cdrom_reset_cb = (int (*)(void))W2k_reset_cdda_state;
    cdrom_unused_cb = (int)nullsub_1;
    cdrom_lba_to_msf_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))W2k_lba_to_msf;
    cdrom_verify_sub_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))W2k_check_subchannel_data;
    cdrom_subchannel_read_cb = (int (*)(void))W2k_cdrom_subchannel_read;
  }
  else
  {
    cdrom_init_cb = (int (*)(void))ext_cdrom_load_plugin;
    cdrom_deinit_cb = (int (__cdecl *)(_DWORD))ext_cdrom_deinit;
    cdrom_get_first_last_TN_cb = (int (__cdecl *)(_DWORD, _DWORD))ext_CDR_get_first_last_track;
    cdrom_track_to_msf = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))ext_CDR_track_to_msf;
    cdrom_read_data_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))ext_CDR_read;
    cdrom_play_cdda_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD))ext_CDRplay;
    cdrom_stop_cb = (int (*)(void))ext_CDRstop;
    cdrom_reset_cb = (int (*)(void))ext_CDR_reset_state;
    cdrom_unused_cb = (int)nullsub_1;
    cdrom_lba_to_msf_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))ext_CDR_lba_to_msf;
    cdrom_verify_sub_cb = (int (__cdecl *)(_DWORD, _DWORD, _DWORD, _DWORD))ext_CDR_verify_subchannel_data;
    cdrom_subchannel_read_cb = (int (*)(void))nullsub_1;
  }
  *(_DWORD *)dma_channel_status = 0;
  *(_DWORD *)hw_saved_state = 0;
  memset(mdec_dma_src, 0, 0x60u);
  memset(hw_regs, 0, 0x10000u);
  return 0;
}




/* Decompiled globals (previously generated in src/_gen) */
int (__cdecl *cdrom_get_first_last_TN_cb)();
int (__cdecl *cdrom_init_cb)();
int (__cdecl *cdrom_lba_to_msf_cb)();
int (__cdecl *cdrom_play_cdda_cb)();
int (__cdecl *cdrom_read_data_cb)();
int (__cdecl *cdrom_reset_cb)();
int (__cdecl *cdrom_stop_cb)();
int (__cdecl *cdrom_subchannel_read_cb)();
int (__cdecl *cdrom_track_to_msf)();
unsigned int cdrom_unused_cb;
int (__cdecl *cdrom_verify_sub_cb)();
int (__cdecl *spu_async_update_cb)();
int (__cdecl *spu_dma_cb)();
int (__cdecl *spu_freeze_cb)();
int (__cdecl *spu_init_cb)();
int (__cdecl *spu_play_adpcm_cb)();
int (__cdecl *spu_read_register_cb)();
int (__cdecl *spu_set_adpcm_flag_cb)();
int (__cdecl *spu_unfreeze_cb)();
int (__cdecl *spu_update_cb)();
int (__cdecl *spu_write_register_cb)();
