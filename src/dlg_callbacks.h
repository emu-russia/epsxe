#pragma once
/**
 * \file dlg_callbacks.h
 * \brief Win32 dialog procedures for the emulator configuration dialogs.
 *
 * Declares the dialog procedures for the About, BIOS, cheat, controller
 * setup, memory card, plugin selection and CD-ROM settings dialogs, the
 * shared file-open helper, and the global state they use (plugin entry
 * points, plugin name list, controller configuration).
 */
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Plugin "about" entry point (GPUabout/SPUabout/CDRabout/NETabout), resolved via GetProcAddress. */
extern int (__stdcall *GPUabout_0)();
/** \brief Plugin "init" entry point (GPUinit/SPUinit/CDRinit), resolved via GetProcAddress. */
extern int (__stdcall *GPUinit_0)();
/** \brief Plugin "shutdown" entry point (GPUshutdown/SPUshutdown/CDRshutdown), resolved via GetProcAddress. */
extern int (__stdcall *GPUshutdown_0)();
/** \brief Plugin "test" entry point (GPUtest/SPUtest/CDRtest/NETtest), resolved via GetProcAddress. */
extern int (__stdcall *GPUtest_0)();
/** \brief Plugin configure entry point (GPUconfigure/SPUconfigure/CDRconfigure/NETconfigure), resolved via GetProcAddress. */
extern int ( *PSEconfigure)();
/** \brief PSE plugin API accessor returning the plugin library name. */
extern int ( *PSEgetLibName)();
/** \brief PSE plugin API accessor returning the plugin library type. */
extern int ( *PSEgetLibType)();
/** \brief PSE plugin API accessor returning the plugin library version. */
extern int ( *PSEgetLibVersion)();
/** \brief Head of the plugin name list shift region; used when inserting plugin names into the list. */
extern unsigned char plugin_name_list_shift[0x380];
/** \brief Start of the plugin name list storage; each plugin name occupies a 1024-byte slot. */
extern unsigned char plugin_name_list[0x4];
/** \brief Tail of the plugin name list storage; holds the remainder of names spanning the slot boundary. */
extern unsigned char plugin_name_list_tail[0x7ffc];
/** \brief Controller mode for each pad slot (1 = digital, 4 = analog/joystick, 5 = mouse, 6 = GunCon); sent over netplay. */
extern unsigned int controller_port_modes[8];
/** \brief Number of plugins found during the current plugin search. */
extern unsigned int found_plugin_count;
/** \brief Small motor (rumble) type for pad 2 (0 = constant, 1 = none, 2 = sine). */
extern unsigned int pad2_small_motor_type;
/** \brief Small motor (rumble) type for pad 4 (0 = constant, 1 = none, 2 = sine). */
extern unsigned int pad4_small_motor_type[1];
/** \brief Force-feedback effect type for the second effect set, used by diSetEffectMagnitude when effectSet == 0. */
extern unsigned int g_EffectType2[1];
/** \brief Device map for pad 4: which DirectInput joystick is assigned (0 = none, 1-4 = DX Joy1-4). */
extern unsigned int g_PlayerDeviceMap4[1];
/** \brief Multitap flag: whether the 4-player multitap is enabled. */
extern unsigned char multitap_1;
/** \brief Pad number currently being configured in the controller setup dialog (1-4, default 1). */
extern unsigned char pad_number_menu_selection;
/** \brief Temporary path buffer used by the file open/save dialogs. */
extern unsigned char temp_path[0x400];
/** \brief Head of the per-pad keyboard assignment table (each pad uses a 16-word region). */
extern unsigned short pad_key_assignments[4];

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Dialog procedure for the About dialog (IDD_ABOUT).
 *
 * Initializes the dialog and closes it when the OK button is pressed.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
int __stdcall about_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam);
/**
 * \brief Dialog procedure for the BIOS selection dialog (IDD_BIOS).
 *
 * Shows the current BIOS path, lets the user pick a BIOS .BIN file
 * with the file dialog, and on OK stores the path in bios_name and
 * saves the settings.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall bios_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Computes a checksum over a BIOS image.
 *
 * Sums and XORs the 16-bit words of the buffer and combines the
 * results (checksum ^ (sum << 16)) to identify the BIOS.
 *
 * \param ptr   Pointer to the BIOS data.
 * \param size  Size of the BIOS data in bytes.
 * \return The computed BIOS checksum.
 */
int calc_bios_checksum(uint8_t *ptr, int size);
/**
 * \brief Dialog procedure for the cheat management dialog (IDD_CHEAT).
 *
 * Maintains the list of cheat entries (address/value pairs), supports
 * adding and removing entries, and loading/saving .CHT cheat files;
 * on OK the current list is copied into the active mini-cheat tables.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
LRESULT __stdcall cheat_dialog_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam);
/**
 * \brief Dialog procedure for the controller setup dialog (IDD_CONTROLLER / IDD_CONTROLLER_LARGE).
 *
 * Configures the selected pad: controller type, joystick device,
 * motor types, keyboard bindings and axis calibration, storing the
 * results into Keys1/Keys4, GamepadAxis, controller_port_modes and
 * the pad key assignments.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall controller_setup_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the memory card settings dialog (IDD_MEMCARD).
 *
 * Shows the two memory card file paths, lets the user select new
 * .MCR/.MEM/.MCD/.GME files, and on OK updates Memcard1/Memcard2,
 * reloads the memcards and saves the settings.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall memcard_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Opens a standard Win32 file-open dialog.
 *
 * \param title       Dialog title.
 * \param filter      File type filter string.
 * \param file_path   Unused output parameter (the chosen path is copied into temp_path).
 * \param initial_dir Initial directory.
 * \param def_ext     Default file extension.
 * \return 1 if a file was selected, 0 if the dialog was cancelled.
 */
BOOL open_file_dialog(const CHAR *title, const CHAR *filter, CHAR *file_path, const CHAR *initial_dir, const CHAR *def_ext);
/**
 * \brief Dialog procedure for the CD-ROM plugin selection dialog (IDD_CDROM).
 *
 * Lists the internal ASPI (W9X) and WNT/W2K CD-ROM cores plus external
 * CD-ROM plugins (PSE lib type 1), and lets the user select, test,
 * configure or view info on the chosen plugin.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the netplay plugin selection dialog (IDD_NET).
 *
 * Lists a "Disabled Netplay" entry plus external netplay plugins
 * (PSE lib type 16), and lets the user select, test, configure or
 * view info on the chosen plugin.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the sound plugin selection dialog (IDD_SOUND).
 *
 * Lists the internal ePSXe SPU core plus external SPU plugins (PSE
 * lib type 4), and lets the user select, test, configure or view
 * info on the chosen plugin.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall search_spu_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the video plugin selection dialog (IDD_VIDEO).
 *
 * Lists the external GPU plugins found in the plugins directory
 * (PSE lib type 2), and lets the user select, test, configure or
 * view info on the chosen plugin.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall search_video_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the internal SPU core configuration dialog.
 *
 * Minimal placeholder procedure for the internal SPU core: closes the
 * dialog when the OK button is pressed.
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall spucore_configure_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
/**
 * \brief Dialog procedure for the Windows 9x CD-ROM settings dialog (IDD_CDROM9X).
 *
 * Enumerates the ASPI CD-ROM devices, lets the user pick the device
 * (HAID/target/LUN) and set the subchannel read/cache options, and
 * on OK stores the selection via cfg_cdrom_set_hain_target_lun().
 *
 * \param hDlg   Dialog window handle.
 * \param uMsg   Dialog message.
 * \param wParam Message-specific value.
 * \param lParam Message-specific value.
 * \return 1 when the message is handled, 0 otherwise.
 */
INT_PTR __stdcall w9x_cdrom_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
