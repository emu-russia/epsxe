#pragma once

/**
 * \file main.h
 * \brief Program entry point and main runtime flags.
 *
 * Declares WinMain (the Windows entry point that parses the command
 * line and runs the emulator loop) and the global runtime flags that
 * control emulator behavior (boot mode, CD/Dynarec/SPU/MDEC options).
 */

/** \brief CD save-fake flag (default 0xFF); selects fake CD save/load handling in the CD-ROM core, set from the command line (-savefake/-loadfake). */
extern uint8_t cd_savefake_flag;
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Whether memory card emulation is enabled (default 1); set by -memcard/-nomemcard. */
extern unsigned char memcard_enabled;
/** \brief Current directory path buffer used in startup banner messages. */
extern unsigned char current_dir_path;
/** \brief CPU overclock setting (default 1); disabled by -nocputrick/-ff9pal or by the cheat database. */
extern unsigned char cpu_overclock_setting;
/** \brief Emulation core selector: 1 = dynamic recompiler, 0 = interpreter. */
extern unsigned int dynarec_enabled;
/** \brief Enable subchannel HLE handling with an external plugin (-extsubchanhle). */
extern unsigned char extsubchanhle;
/** \brief Fast boot flag (default 1): skip the PSX logo when booting a CD image. */
extern unsigned char fastboot;
/** \brief Force the SIO irq always on (bit 0x80); set by -forcepad and toggled at runtime. */
extern unsigned int forcepad;
/** \brief Force the SPU irq always on (non-zero); set by -forcespu and by the cheat database. */
extern unsigned char forcespu;
/** \brief GTE trace flag (-gtrace); when set, traces GTE command codes to the debug log. */
extern unsigned char gtrace;
/** \brief Type of the file loaded (1 = CD image, 2 = CD-ROM, 3 = CD image w/ subchannel, 4 = PS-EXE). */
extern unsigned int loaded_file_type;
/** \brief MDEC accurate-timing flag (default 1); set by -mdectiming/-nomdectiming. */
extern unsigned int mdectiming;
/** \brief Disable CD-ROM emulation (default 1; 0 = CD emulated, 2 = no disc present). */
extern unsigned char nocd;
/** \brief Reset request flag; when set, the main loop reinitializes the emulated console. */
extern unsigned int reset_flag;
/** \brief XA sound read enable (default 1); set by -xaread/-noxaread. */
extern unsigned char xa_read_enable;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Fills a memory region with a repeated 32-bit value.
 *
 * \param dst    Destination buffer.
 * \param value  32-bit value to write.
 * \param count  Number of 32-bit words to write.
 */
void memset32(void* dst, unsigned int value, unsigned int count);
/**
 * \brief Program entry point.
 *
 * Parses the command line into an argument vector, applies the
 * default runtime settings, loads the configuration, selects the
 * CD-ROM core and enters the emulator main loop.
 *
 * \param hInstance     Handle to the current instance of the application.
 * \param hPrevInstance  Always NULL for Win32 applications.
 * \param lpCmdLine     Command line string.
 * \param nShowCmd      How the window is to be shown.
 * \return The process exit code.
 */
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
