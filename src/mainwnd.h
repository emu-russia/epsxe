#pragma once
/**
 * \file mainwnd.h
 * \brief Main window creation and save/load state handling.
 *
 * Declares the main GUI window creation routine and the save/load
 * state routine, plus the window/instance handles and input-state
 * flags they share with the rest of the emulator.
 */
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Buffer holding the path of the bin/ISO file selected from the Run menu. */
extern unsigned char bin_iso_file[0x100];
/** \brief Whether mouse input is disabled (default 1); cleared when a game is running. */
extern unsigned char g_bDisableMouse;
/** \brief Application instance handle of the emulator process. */
extern unsigned int g_hInstance;
/** \brief Handle of the main emulator window. */
extern unsigned int g_hWnd;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Creates the main emulator window and runs its message loop.
 *
 * Registers the "EPSXGUI" window class, loads the window bitmaps,
 * creates and shows the main window, then pumps messages until the
 * window is closed.
 *
 * \return The result of ShowWindow() when hiding the window.
 */
BOOL create_main_window();
/**
 * \brief Handles save/load state from the main window.
 *
 * Pauses the running game (muting the SPU, saving memcards, closing
 * GPU/SPU output), shows the main window so the user can pick a state
 * slot from the menu, then either saves (slots 10+) or loads (slots
 * 0-9) the chosen state and resumes emulation.
 */
void save_load_state();
