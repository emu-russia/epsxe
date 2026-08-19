#pragma once

/**
 * \file cfg.h
 * \brief Emulator configuration: settings storage and plugin/misc globals.
 *
 * Declares the configuration globals (plugin DLL paths, key bindings,
 * pad/axis calibration, subchannel options) and the functions that
 * load and save them to the Windows registry, plus the CD-ROM core
 * configuration helpers.
 */

/** \brief Whether the debug console window is allocated (persisted as "Logswindow"). */
extern uint8_t console_allocated;

/* Decompiled globals (previously generated in src/_gen) */
/** \brief Path buffer for the CD-ROM plugin DLL (default "NULL"). */
extern unsigned char CdromPlugin[0x400];
/** \brief Per-pad axis calibration values (low/high word per axis), persisted as "GamepadAxis". */
extern unsigned short GamepadAxis[0x10];
/** \brief Directory used by the ISO file dialog, persisted as "IsoDirectory". */
extern unsigned char IsoDirectory[0x400];
/** \brief Keyboard bindings for pad 1 (head of a 16-word region; defaults set in cfg.c). */
extern unsigned short Keys1[10];
/** \brief Keyboard bindings for pad 4 (16 entries). */
extern unsigned short Keys4[16];
/** \brief Path buffer for the netplay plugin DLL (default "DISABLED"). */
extern unsigned char NetPlugin[0x400];
/** \brief Path buffer for the sound plugin DLL (default "SPUCORE"). */
extern unsigned char SoundPlugin[0x400];
/** \brief Win2000 CD-ROM core: subchannel caching option (LG). */
extern unsigned char SubchannelW2kCachingLG;
/** \brief Win2000 CD-ROM core: subchannel read enabled. */
extern unsigned char SubchannelW2kCdromEnabled;
/** \brief Win9x CD-ROM core: subchannel caching option (LG). */
extern unsigned char SubchannelW9xCachingLG;
/** \brief Win9x CD-ROM core: subchannel read enabled. */
extern unsigned char SubchannelW9xCdromEnabled;
/** \brief Path buffer for the video (GPU) plugin DLL (default "NULL"). */
extern unsigned char VideoPlugin[0x400];
/** \brief Whether the GUI main window is created (default 1). */
extern unsigned char create_window_flag;
/** \brief Big motor (rumble) type for pad 2. */
extern unsigned int pad2_big_motor_type;
/** \brief Analog mode flag for pad 2. */
extern unsigned int pad2_analog_mode_flag;
/** \brief Analog mode flag for pad 3. */
extern unsigned int pad3_analog_mode_flag;
/** \brief Analog mode flag for pad 4. */
extern unsigned int pad4_analog_mode_flag;
/** \brief Force-feedback effect type for the first effect set, used by diSetEffectMagnitude when effectSet is non-zero. */
extern unsigned int g_EffectType1[1];
/** \brief Device map for pad 2: which DirectInput joystick is assigned. */
extern unsigned int g_PlayerDeviceMap2;
/** \brief Device map for pad 3: which DirectInput joystick is assigned. */
extern unsigned int g_PlayerDeviceMap3;
/** \brief Disable MDEC decoding flag (set by -nomdec/-mdec). */
extern unsigned int mdec_disable;
/** \brief Whether the first-run setup wizard is required (set when the stored config version is old). */
extern unsigned char setup_wizard_required;
/** \brief Whether XA sound is used. */
extern unsigned char sound_use_xa;
/** \brief Emulator config version/region setting (0x10600 = 1.6.0); used to detect old configs. */
extern unsigned int version_setting;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Saves the ISO directory to the registry.
 *
 * \return The result of the registry write.
 */
int cfg_cdrom_iso_set_path();
/**
 * \brief Saves the Win9x ASPI CD-ROM device address (HAID/target/LUN) to the registry.
 *
 * \return The result of the last registry write.
 */
int cfg_cdrom_set_hain_target_lun();
/**
 * \brief Saves the Win2000 CD-ROM drive letter to the registry.
 *
 * \return The result of the registry write.
 */
int cfg_cdrom_set_letter();
/**
 * \brief Loads all emulator settings from the Windows registry.
 *
 * Reads the configuration keys from the emulator's registry branch
 * (HKEY_CURRENT_USER, subkey Software, value epsxe; written as
 * "Software\\epsxe" in the code),
 * applying defaults for missing values (plugin paths, BIOS name,
 * memcard files, key bindings, pad/axis settings, subchannel options)
 * and upgrading the stored config version when it is older than 1.6.0.
 *
 * \return The length of the string written to IsoDirectory.
 */
int cfg_load_settings();
/**
 * \brief Saves all emulator settings to the Windows registry.
 *
 * \return The result of the final registry write (Logswindow value).
 */
int cfg_save_settings();
