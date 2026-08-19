#pragma once

/**
 * \file net.h
 * \brief Declarations for the netplay subsystem.
 *
 * Wraps the external netplay plugin (plugins\NetPlugin.dll, i.e. the DLL
 * named by the NetPlugin config path): loads it,
 * opens/closes the session, exchanges pad/mouse state and configuration
 * with the peers, and synchronizes memory cards and BIOS images between
 * the connected players.
 */

/* Decompiled globals (previously generated in src/_gen) */
/** \brief Non-zero when the netplay plugin is loaded and netplay is enabled. */
extern unsigned int network_enabled;
/** \brief Timing value exchanged with peers in the netplay configuration (purpose unknown). */
extern unsigned int unknown_timing_value;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Closes and shuts down the netplay plugin.
 *
 * Calls the plugin's NETclose() (once) and NETshutdown() entry points when
 * the module is loaded.
 *
 * \return The plugin module handle (or the network_enabled flag when no
 *         module is loaded).
 */
HMODULE net_close();
/**
 * \brief Sends the local pad/mouse state to the netplay plugin and applies the received state.
 *
 * Packs the current controller, joystick and mouse input, forwards it via
 * NETpadState(), and copies the remote state back into the emulator input
 * globals.
 *
 * \return 1 if a netplay reset was requested by a peer, 0 otherwise.
 */
int net_fill_input();
/**
 * \brief Loads the netplay plugin DLL and resolves its NET* entry points.
 *
 * Fatal error if the plugin cannot be loaded; each unresolved entry point
 * is reported via ui_error().
 *
 * \return The result of the final dbg_print() call.
 */
int net_load_plugin();
/**
 * \brief Netplay handshake/synchronization handler.
 *
 * Compares the game ID, start options, sound settings, SPU plugin and BIOS
 * image with the peers (fatal error on mismatch) and transfers memory card
 * and configuration data between the sites.
 *
 * \return The netplay configuration flag xa_read_enable when netplay is
 *         enabled, otherwise the network_enabled flag.
 */
char net_netplay_handler();
/**
 * \brief Opens the netplay session.
 *
 * Calls the plugin's NETopen() with the emulator output window.
 *
 * \return The result of the final dbg_print() call when netplay is enabled,
 *         otherwise the network_enabled flag.
 */
int net_open();
/**
 * \brief Pauses the netplay session.
 *
 * \return The plugin's NETpause() result when a module is loaded, otherwise
 *         the network_enabled flag.
 */
HMODULE net_pause();
/**
 * \brief Resumes the netplay session.
 *
 * \return The plugin's NETresume() result when a module is loaded, otherwise
 *         the network_enabled flag.
 */
HMODULE net_resume();
