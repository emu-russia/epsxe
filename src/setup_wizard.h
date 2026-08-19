#pragma once
/**
 * \file setup_wizard.h
 * \brief First-run setup wizard.
 *
 * Declares the setup wizard entry point and its global state: a
 * file-name buffer and the current wizard step counter that drives
 * the sequence of BIOS/plugin configuration dialogs.
 */
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Global 256-byte file-name buffer used by the setup wizard module. */
extern char FileName[256];
/** \brief Current setup wizard step (0-7); starts at 0xFFFFFFFF (uninitialized). */
extern unsigned int setup_wizard_step;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Runs the first-run setup wizard.
 *
 * Moves loose GPU/SPU/CD-ROM plugin DLLs into the plugins directory,
 * then walks the user through the BIOS, video, sound and CD-ROM plugin
 * selection dialogs and the pad configuration; on the final step it
 * saves the selected plugin paths and BIOS name with
 * cfg_save_settings().
 *
 * \param hWndParent  Parent window for the wizard dialogs.
 * \return The final wizard step result (the cfg_save_settings() result on completion).
 */
int setup_wizard_callback(HWND hWndParent);
