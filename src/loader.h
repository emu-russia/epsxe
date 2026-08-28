#pragma once

/**
 * \file loader.h
 * \brief Declarations for the loader subsystem: BIOS, demos (EXE/PLL) and cheats.
 *
 * Loads the PSX BIOS image, PS-X EXE demos (directly or from ZIP archives),
 * and the cheat databases. Detects the game region from the loaded CD and
 * applies the matching timing/configuration settings.
 */

/* Decompiled globals (previously generated in src/_gen) */
/** \brief Number of mini cheats currently activated for the running game. */
extern unsigned char active_mini_cheat_count;
/** \brief The loaded PSX BIOS image (512 KB). */
extern unsigned char bios_image[0x80000];
/** \brief Path/name of the BIOS file to load. */
extern unsigned char bios_name[0x800];
/** \brief Per-game CD increment flag, set from the cheat database entry. */
extern unsigned char cd_inc;
/** \brief Detected game country/region setting: 1 = PAL, 0 = NTSC. */
extern unsigned int country_setting;
/** \brief Default (detected) game filename used for save states and netplay. */
extern unsigned char default_filename[0x400];
/** \brief Attribute values of the active mini cheats (indexed by 2 * active count). */
extern unsigned int mini_cheat_attr_array[1];
/** \brief Game IDs of the active mini cheats (indexed by 2 * active count). */
extern unsigned int mini_cheat_id_array[0x1f];
/** \brief When non-zero, disables automatic cheat application. */
extern unsigned char noauto;
/** \brief Per-game "no CD status" flag, set from the cheat database entry. */
extern unsigned char nocdstatus;
/** \brief Enables the older (slower) CPU timing model. */
extern unsigned char old_timing;
/** \brief Per-game Parasite Eve cheat flag, set from the cheat database entry. */
extern unsigned char parasite_eve_cheat;
/** \brief Per-game unknown CD setting, set from the cheat database entry. */
extern unsigned char unknown_cd_setting;
/** \brief Video scanlines for the detected region (262 for NTSC, 312 for PAL). */
extern unsigned int video_scanlines;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Detects the region (PAL/NTSC) of the loaded CD-ROM and applies the matching settings.
 *
 * For non-CD file types sets the default filename to "DEMO_999.99" and NTSC
 * timing; for CDs reads the executable name from the CD file system, applies
 * any matching cheat entry, and sets country_setting, video_scanlines and
 * cpu_speed_scale accordingly.
 *
 * \return The result of the final dbg_print() call (or of sprintf() for the
 *         non-CD path).
 */
int loader_cdrom_detect_region();
/**
 * \brief Checks whether the BIOS file exists on disk.
 *
 * \return 0 if the file opens successfully, -1 otherwise.
 */
int loader_check_bios_file_exists();
/**
 * \brief Loads the BIOS image from bios_name into bios_image.
 *
 * Fatal error if the BIOS file cannot be opened.
 */
void loader_load_bios();
/**
 * \brief Loads mini cheat (id/attribute) pairs from a text file.
 *
 * Reads lines of the form "ID ATTR" (ignoring lines starting with '#') into
 * mini_cheat_id_array / mini_cheat_attr_array and updates
 * active_mini_cheat_count.
 *
 * \param FileName Path of the cheat text file.
 * \return The fclose() result cast to FILE * (NULL if the file could not be
 *         opened).
 */
FILE * loader_load_cheat_file(char *FileName);
/**
 * \brief Loads the built-in cheat databases from disk.
 *
 * Reads "cheats\\database.dat" into mini_cheat_db (deduplicating entries)
 * and "cheats\\dataconf.dat" into cheat_db.
 *
 * \return The fclose() result of the second file cast to FILE * (NULL if it
 *         could not be opened).
 */
FILE *loader_load_cheats();
/**
 * \brief Loads a PS-X EXE demo file into RAM and sets up the initial CPU state.
 *
 * Validates the "PS-X EXE" header, reads the executable into RAM at its load
 * address, and sets the initial PC, GP and stack pointer registers.
 *
 * \param FileName Path of the EXE demo file.
 * \return The result of fclose() (fatal error if the file is missing or not
 *         an EXE).
 */
int loader_load_demo(char *FileName);
/**
 * \brief Loads a demo from a .zip archive (EXE or PLL entry) into RAM.
 *
 * If the current file is a .zip, opens it with the ZIP reader, extracts the
 * single EXE entry (or the PLL entry) and loads it like a demo; otherwise
 * falls back to loader_load_demo(). Fatal error if the archive cannot be
 * read or contains no suitable demo.
 */
void loader_load_zip();
/**
 * \brief Sets the BIOS file name.
 *
 * \param name The new BIOS name/path.
 * \return The number of characters written (sprintf() result).
 */
int loader_set_bios_name(const char *name);
/**
 * \brief Sets the current game filename.
 *
 * \param name The new filename.
 * \return The number of characters written (sprintf() result).
 */
int loader_set_filename(const char *name);
/**
 * \brief Checks that the current demo file exists on disk.
 *
 * \return 1 if the file exists, 0 if FileName is "NULL" (fatal error if the
 *         file is missing).
 */
int loader_touch_demo_file();
