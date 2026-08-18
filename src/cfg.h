#pragma once

extern uint8_t console_allocated;

/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char CdromPlugin[0x400];
extern unsigned short GamepadAxis[0x10];
extern unsigned char IsoDirectory[0x400];
extern unsigned short Keys1[10];
extern unsigned short Keys2[16];
extern unsigned short Keys3[16];
extern unsigned short Keys4[16];
extern unsigned char NetPlugin[0x400];
extern unsigned char SoundPlugin[0x400];
extern unsigned char SubchannelW2kCachingLG;
extern unsigned char SubchannelW2kCdromEnabled;
extern unsigned char SubchannelW9xCachingLG;
extern unsigned char SubchannelW9xCdromEnabled;
extern unsigned char VideoPlugin[0x400];
extern unsigned char create_window_flag;
extern unsigned int pad3_small_motor_type;
extern unsigned int pad2_big_motor_type;
extern unsigned int pad3_big_motor_type;
extern unsigned int pad4_big_motor_type;
extern unsigned int pad2_analog_mode_flag;
extern unsigned int pad3_analog_mode_flag;
extern unsigned int pad4_analog_mode_flag;
extern unsigned int g_EffectType1[1];
extern unsigned int g_PlayerDeviceMap2;
extern unsigned int g_PlayerDeviceMap3;
extern unsigned int mdec_disable;
extern unsigned char setup_wizard_required;
extern unsigned char sound_use_xa;
extern unsigned int version_setting;

/* Function prototypes (previously generated in src/_gen) */
int cfg_cdrom_iso_set_path();
int cfg_cdrom_set_hain_target_lun();
int cfg_cdrom_set_letter();
char __cdecl cfg_get_value(LPCSTR lpSubKey, LPCSTR lpValueName, LPBYTE lpData);
int cfg_load_settings();
int cfg_save_settings();
int __cdecl cfg_set_value(LPCSTR lpSubKey, LPCSTR lpValueName, BYTE *lpData);
