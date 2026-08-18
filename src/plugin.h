#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int (__cdecl *cdrom_get_first_last_TN_cb)();
extern int (__cdecl *cdrom_init_cb)();
extern int (__cdecl *cdrom_lba_to_msf_cb)();
extern int (__cdecl *cdrom_play_cdda_cb)();
extern int (__cdecl *cdrom_read_data_cb)();
extern int (__cdecl *cdrom_reset_cb)();
extern int (__cdecl *cdrom_stop_cb)();
extern int (__cdecl *cdrom_subchannel_read_cb)();
extern int (__cdecl *cdrom_track_to_msf)();
extern unsigned int cdrom_unused_cb;
extern int (__cdecl *cdrom_verify_sub_cb)();
extern int (__cdecl *spu_async_update_cb)();
extern int (__cdecl *spu_dma_cb)();
extern int (__cdecl *spu_freeze_cb)();
extern int (__cdecl *spu_init_cb)();
extern int (__cdecl *spu_play_adpcm_cb)();
extern int (__cdecl *spu_read_register_cb)();
extern int (__cdecl *spu_set_adpcm_flag_cb)();
extern int (__cdecl *spu_unfreeze_cb)();
extern int (__cdecl *spu_update_cb)();
extern int (__cdecl *spu_write_register_cb)();

/* Function prototypes (previously generated in src/_gen) */
char select_cdrom_core();
int select_plugins_backend();
