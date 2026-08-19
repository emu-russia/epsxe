#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int ( *cdrom_get_first_last_TN_cb)();
extern int ( *cdrom_init_cb)();
extern int ( *cdrom_lba_to_msf_cb)();
extern int ( *cdrom_play_cdda_cb)();
extern int ( *cdrom_read_data_cb)();
extern int ( *cdrom_reset_cb)();
extern int ( *cdrom_stop_cb)();
extern int ( *cdrom_subchannel_read_cb)();
extern int ( *cdrom_track_to_msf)();
extern unsigned int cdrom_unused_cb;
extern int ( *cdrom_verify_sub_cb)();
extern int ( *spu_async_update_cb)();
extern int ( *spu_dma_cb)();
extern int ( *spu_freeze_cb)();
extern int ( *spu_init_cb)();
extern int ( *spu_play_adpcm_cb)();
extern int ( *spu_read_register_cb)();
extern int ( *spu_set_adpcm_flag_cb)();
extern int ( *spu_unfreeze_cb)();
extern int ( *spu_update_cb)();
extern int ( *spu_write_register_cb)();

/* Function prototypes (previously generated in src/_gen) */
char select_cdrom_core();
int select_plugins_backend();
