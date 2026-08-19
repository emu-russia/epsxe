#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char SubchannelW9xCaching;
extern unsigned char cd_device_product[0x10];
extern unsigned int cdrom_haid;
extern unsigned int cdrom_lun;
extern unsigned int cdrom_target;
extern unsigned int w9x_cdrom_info;
extern unsigned int cached_sector_lba;
extern unsigned int cd_device_haid;
extern unsigned int cd_device_target;
extern unsigned int cd_device_lun[0xf1];

/* Function prototypes (previously generated in src/_gen) */
uint32_t * W9x_bcd_to_dword(uint32_t *dest, uint8_t *src);
HMODULE W9x_cdrom_deinit();
char W9x_cdrom_init();
int W9x_cdrom_read_data(uint8_t minute, uint8_t second, uint8_t frame, char *Buffer);
char W9x_cdrom_stop();
char W9x_cdrom_subchannel_read();
HMODULE W9x_free_winaspi_dll();
char W9x_get_first_last_track(uint8_t *first_track, uint8_t *last_track);
uint8_t W9x_get_track_start_lba( uint8_t minute, uint8_t second, uint8_t frame, uint8_t *minute_out, uint8_t *second_out, uint8_t *frame_out);
char W9x_init_aspi();
int W9x_load_win_aspi_silent();
int ( *W9x_load_winaspi_dll())(LPSRB);
char W9x_play_cdda(unsigned int minute, int second, uint8_t track);
void W9x_reset_cdrom_state();
unsigned int W9x_track_to_msf(int16_t track, uint8_t *minute, uint8_t *second, uint8_t *frame);
char W9x_verify_subchannel_data(unsigned int minute, uint8_t second, uint8_t frame, int buffer);
