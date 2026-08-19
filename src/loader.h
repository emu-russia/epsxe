#pragma once

/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char active_mini_cheat_count;
extern unsigned char bios_image[0x80000];
extern unsigned char bios_name[0x800];
extern unsigned char cd_inc;
extern unsigned int country_setting;
extern unsigned char default_filename[0x400];
extern unsigned int mini_cheat_attr_array[1];
extern unsigned int mini_cheat_id_array[0x1f];
extern unsigned char noauto;
extern unsigned char nocdstatus;
extern unsigned char old_timing;
extern unsigned char parasite_eve_cheat;
extern unsigned char unknown_cd_setting;
extern unsigned int video_scanlines;
extern unsigned char zip_entry_names[0x10000];
extern unsigned int zip_num_entries_loaded;

/* Function prototypes (previously generated in src/_gen) */
int loader_cdrom_detect_region();
int loader_check_bios_file_exists();
void loader_load_bios();
FILE * loader_load_cheat_file(char *FileName);
FILE *loader_load_cheats();
int loader_load_demo(char *FileName);
void loader_load_zip();
int loader_set_bios_name(const char *name);
int loader_set_filename(const char *name);
int loader_touch_demo_file();
