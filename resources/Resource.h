//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by ePSXe.rc
//
// Resource identifiers of the ePSXe user interface.
// The numeric values of the macros must match the identifiers
// defined directly in ePSXe.rc so the dialogs keep working.
#ifndef EPSXE_RESOURCE_H
#define EPSXE_RESOURCE_H

// ---------------------------------------------------------------------------
// Menu (EPSXMENU)
// ---------------------------------------------------------------------------
#define IDM_RUN_CDROM              40001
#define IDM_RUN_BIOS               40002
#define IDM_RUN_ISO                40003
#define IDM_RUN_PS_EXE             40004
#define IDM_EXIT                   40005

#define IDM_CONFIG_VIDEO           40006
#define IDM_CONFIG_SOUND           40007
#define IDM_CONFIG_CDROM           40008
#define IDM_CONFIG_BIOS            40009

#define IDM_CHEAT                  40012 // opens the cheat dialog (no menu item)

#define IDM_ABOUT                  40013
#define IDM_VISIT_WEBSITE          40015

#define IDM_CONTINUE               40016
#define IDM_RESET                  40017

#define IDM_PAD1                   40018
#define IDM_PAD2                   40019
#define IDM_PAD3                   40052
#define IDM_PAD4                   40053
#define IDM_MULTITAP               40054

#define IDM_MEMORY_CARD            40022
#define IDM_CHANGE_DISC_CDROM      40024
#define IDM_CHANGE_DISC_ISO        40025

#define IDM_COUNTRY_AUTODETECT     40026
#define IDM_COUNTRY_NTSC           40027
#define IDM_COUNTRY_PAL            40028

#define IDM_SAVE_STATE_1           40030
#define IDM_SAVE_STATE_2           40031
#define IDM_SAVE_STATE_3           40032
#define IDM_SAVE_STATE_4           40033
#define IDM_SAVE_STATE_5           40034
#define IDM_LOAD_STATE_1           40035
#define IDM_LOAD_STATE_2           40036
#define IDM_LOAD_STATE_3           40037
#define IDM_LOAD_STATE_4           40038
#define IDM_LOAD_STATE_5           40039

#define IDM_CONFIG_GUIDE_EN        40041
#define IDM_CONFIG_GUIDE_ES        40042

#define IDM_NETPLAY                40047
#define IDM_WIZARD_GUIDE           40048
#define IDM_PPF_AUTOLOAD           40049
#define IDM_HELP_CONTENTS          40050
#define IDM_ENABLE_LOGS            40051

// ---------------------------------------------------------------------------
// IDD_ABOUT dialog
// ---------------------------------------------------------------------------
#define IDC_ABOUT_OK               1002

// ---------------------------------------------------------------------------
// IDD_BIOS dialog
// ---------------------------------------------------------------------------
#define IDC_BIOS_PATH              1025
#define IDC_BIOS_SELECT            1027
#define IDC_BIOS_OK                1028
#define IDC_BIOS_CANCEL            1029

// ---------------------------------------------------------------------------
// IDD_BURUTTER_INFO dialog
// ---------------------------------------------------------------------------
#define IDC_BURUTTER_BUY_NOW       1098
#define IDC_BURUTTER_BACK          1003

// ---------------------------------------------------------------------------
// IDD_CDROM dialog
// ---------------------------------------------------------------------------
#define IDC_CDROM_PLUGIN_LIST      1000
#define IDC_CDROM_TEST             1001
#define IDC_CDROM_CONFIGURE        1003
#define IDC_CDROM_ABOUT            1004
#define IDC_CDROM_OK               1023
#define IDC_CDROM_CANCEL           1024

// ---------------------------------------------------------------------------
// IDD_CDROMCORE2K dialog (internal CDR W2K core)
// ---------------------------------------------------------------------------
#define IDC_CDROM2K_LETTER         1133
#define IDC_CDROM2K_OK             1134
#define IDC_CDROM2K_CANCEL         1135
#define IDC_CDROM2K_SUBCHANNEL_READ       1139
#define IDC_CDROM2K_SUBCHANNEL_CACHE      1140
#define IDC_CDROM2K_SUBCHANNEL_CACHE_LG   1141

// ---------------------------------------------------------------------------
// IDD_CDROMCORE9X dialog (internal CDR W9x ASPI core)
// ---------------------------------------------------------------------------
#define IDC_CDROM9X_OK             1079
#define IDC_CDROM9X_CANCEL         1080
#define IDC_CDROM9X_DEVICE_LIST    1081
#define IDC_CDROM9X_SUBCHANNEL_READ       1136
#define IDC_CDROM9X_SUBCHANNEL_CACHE      1137
#define IDC_CDROM9X_SUBCHANNEL_CACHE_LG   1138

// ---------------------------------------------------------------------------
// IDD_CHEAT dialog
// ---------------------------------------------------------------------------
#define IDC_CHEAT_LIST             1142
#define IDC_CHEAT_REMOVE_ALL       1143
#define IDC_CHEAT_REMOVE           1144
#define IDC_CHEAT_ADD              1145
#define IDC_CHEAT_ADDRESS          1146
#define IDC_CHEAT_VALUE            1055
#define IDC_CHEAT_LOAD             1056
#define IDC_CHEAT_SAVE             1057
#define IDC_CHEAT_OK               1058
#define IDC_CHEAT_CANCEL           1059

// ---------------------------------------------------------------------------
// IDD_CONTROLLER / IDD_CONTROLLER_LARGE dialogs
// ---------------------------------------------------------------------------
#define IDC_CONTROLLER_OK          1048
#define IDC_CONTROLLER_CANCEL      1047
#define IDC_CONTROLLER_DEFAULT     1023
#define IDC_CONTROLLER_CLEAR       1055
#define IDC_CONTROLLER_PAD_NUMBER  1049
#define IDC_CONTROLLER_EDIT_BUTTON 1060
#define IDC_CONTROLLER_TYPE        1086
#define IDC_CONTROLLER_DEVICE      1088
#define IDC_CONTROLLER_BIG_MOTOR   1089
#define IDC_CONTROLLER_SMALL_MOTOR 1090

#define IDC_CONTROLLER_UP          1033
#define IDC_CONTROLLER_DOWN        1035
#define IDC_CONTROLLER_LEFT        1034
#define IDC_CONTROLLER_RIGHT       1036
#define IDC_CONTROLLER_TRIANGLE    1042
#define IDC_CONTROLLER_CIRCLE      1043
#define IDC_CONTROLLER_CROSS       1044
#define IDC_CONTROLLER_SQUARE      1045
#define IDC_CONTROLLER_L1          1032
#define IDC_CONTROLLER_L2          1031
#define IDC_CONTROLLER_L3          1046
#define IDC_CONTROLLER_R1          1041
#define IDC_CONTROLLER_R2          1040
#define IDC_CONTROLLER_R3          1050
#define IDC_CONTROLLER_SELECT      1038
#define IDC_CONTROLLER_START       1039
#define IDC_CONTROLLER_AXIS_X1     1052
#define IDC_CONTROLLER_AXIS_X2     1053
#define IDC_CONTROLLER_AXIS_Y1     1051
#define IDC_CONTROLLER_AXIS_Y2     1054

// ---------------------------------------------------------------------------
// Setup wizard dialogs (IDD_INSTALL*)
// ---------------------------------------------------------------------------
#define IDC_INSTALL_SKIP           1109
#define IDC_INSTALL_CONFIG         1110

#define IDC_INSTALL_BIOS_LIST      1106
#define IDC_INSTALL_BIOS_BACK      1107
#define IDC_INSTALL_BIOS_NEXT      1108

#define IDC_INSTALL_GPU_LIST       1124
#define IDC_INSTALL_GPU_CONFIG     1125
#define IDC_INSTALL_GPU_TEST       1126
#define IDC_INSTALL_GPU_BACK       1127
#define IDC_INSTALL_GPU_NEXT       1128
#define IDC_INSTALL_GPU_ABOUT      1129

#define IDC_INSTALL_SPU_LIST       1129
#define IDC_INSTALL_SPU_CONFIG     1111
#define IDC_INSTALL_SPU_TEST       1112
#define IDC_INSTALL_SPU_ABOUT      1113
#define IDC_INSTALL_SPU_BACK       1130
#define IDC_INSTALL_SPU_NEXT       1131

#define IDC_INSTALL_CDROM_LIST     1119
#define IDC_INSTALL_CDROM_CONFIG   1120
#define IDC_INSTALL_CDROM_TEST     1121
#define IDC_INSTALL_CDROM_BACK     1122
#define IDC_INSTALL_CDROM_NEXT     1123
#define IDC_INSTALL_CDROM_ABOUT    1124
// CD drive letter (in the wizard): the control is missing from ePSXe.rc;
// the code uses both values (decompilation artifact).
#define IDC_INSTALL_CDROM_LETTER     1113
#define IDC_INSTALL_CDROM_LETTER_ALT 1062

#define IDC_INSTALL_PAD_BACK       1115
#define IDC_INSTALL_PAD_NEXT       1116
#define IDC_INSTALL_PAD_1          1117
#define IDC_INSTALL_PAD_2          1118

#define IDC_INSTALL_END_DONE       1114

// ---------------------------------------------------------------------------
// IDD_MDEC dialog
// ---------------------------------------------------------------------------
#define IDC_MDEC_TIMING            1061
#define IDC_MDEC_ENABLE            1064
#define IDC_MDEC_OK                1066
#define IDC_MDEC_CANCEL            1067

// ---------------------------------------------------------------------------
// IDD_MEMCARD dialog
// ---------------------------------------------------------------------------
#define IDC_MEMCARD_FILE1          1082
#define IDC_MEMCARD_FILE2          1026
#define IDC_MEMCARD_SELECT1        1083
#define IDC_MEMCARD_SELECT2        1030
#define IDC_MEMCARD_OK             1084
#define IDC_MEMCARD_CANCEL         1085

// ---------------------------------------------------------------------------
// IDD_NET dialog
// ---------------------------------------------------------------------------
#define IDC_NET_PLUGIN_LIST        1104
#define IDC_NET_TEST               1099
#define IDC_NET_CONFIGURE          1100
#define IDC_NET_ABOUT              1101
#define IDC_NET_OK                 1102
#define IDC_NET_CANCEL             1103

// ---------------------------------------------------------------------------
// IDD_SOUND dialog
// ---------------------------------------------------------------------------
#define IDC_SOUND_PLUGIN_LIST      1010
#define IDC_SOUND_TEST             1011
#define IDC_SOUND_CONFIGURE        1012
#define IDC_SOUND_ABOUT            1013
#define IDC_SOUND_OK               1014
#define IDC_SOUND_CANCEL           1015
#define IDC_SOUND_PLUGIN_GROUP     1016
#define IDC_SOUND_ENABLE           1005
#define IDC_SOUND_XA               1006
#define IDC_SOUND_CDDA             1009
#define IDC_SOUND_SPU_IRQ_HACK     1030

// ---------------------------------------------------------------------------
// IDD_SOUND9X dialog
// ---------------------------------------------------------------------------
#define IDC_SOUND9X_OK             1105

// ---------------------------------------------------------------------------
// IDD_SPUCORE dialog
// ---------------------------------------------------------------------------
#define IDC_SPUCORE_OK             1068
#define IDC_SPUCORE_CANCEL         1069
#define IDC_SPUCORE_STEREO         1070
#define IDC_SPUCORE_QUALITY_0      1072
#define IDC_SPUCORE_QUALITY_1      1073
#define IDC_SPUCORE_QUALITY_2      1074
#define IDC_SPUCORE_QUALITY_3      1078
#define IDC_SPUCORE_QUALITY_4      1075
#define IDC_SPUCORE_QUALITY_5      1076
#define IDC_SPUCORE_QUALITY_6      1077

// ---------------------------------------------------------------------------
// IDD_VIDEO dialog
// ---------------------------------------------------------------------------
#define IDC_VIDEO_PLUGIN_LIST      1017
#define IDC_VIDEO_TEST             1018
#define IDC_VIDEO_CONFIGURE        1019
#define IDC_VIDEO_ABOUT            1020
#define IDC_VIDEO_OK               1021
#define IDC_VIDEO_CANCEL           1022

// ---------------------------------------------------------------------------
// Bitmaps and icons
// ---------------------------------------------------------------------------
#define IDB_MAIN_WINDOW            140
#define IDB_MAIN_WINDOW_BG         142
#define IDB_CONTROLLER             144
#define IDB_BURUTTER               145

#define IDI_APP                    137

#ifndef IDC_STATIC
#define IDC_STATIC                 -1
#endif

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif

#endif /* EPSXE_RESOURCE_H */
