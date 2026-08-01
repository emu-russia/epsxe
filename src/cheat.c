#include "pch.h"

// Mini cheat database - built-in cheats for specific games
int mini_cheat_count = 4;

MINI_CHEAT_ENTRY mini_cheat_db[200] = {
    {"SLUS_008.45", 0x10023458, 0},
    {"SLES_006.27", 0x0005DC98, 0},
    {"SLES_033.42", 0x10036298, 0},
    {"SLES_033.44", 0x100369F0, 0},
};

// Cheat database entries count
int cheat_entries_count = 39;

// Internal cheat database for ePSXe
CHEAT_DB_ENTRY cheat_db[200] = {
    // {gameid, text, mdectiming, dword_50C374, forcespu, forcepad, byte_455946, parasite_eve_cheat, byte_455FA4, byte_4F75AA, nocdstatus, unk, byte_4FC4E6}
    {"SCES_021.05", "NULL", 1, 0xFF, 2, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0},
    {"SLES_025.58", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_125.58", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_025.59", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_125.59", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_025.60", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_125.60", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_025.61", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_125.61", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLUS_010.42", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLUS_010.55", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLPS_024.80", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLPS_024.81", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 0xFF, 0, 0, 0, 0},
    {"SLES_029.69", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_129.69", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_229.69", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_329.69", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_029.65", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_129.65", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_229.65", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_329.65", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_029.66", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_129.66", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_229.66", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_329.66", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_029.67", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_129.67", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_229.67", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_329.67", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_029.68", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_129.68", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_229.68", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLES_329.68", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
    {"SLPS_023.64", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 1},
    {"SLPS_123.64", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 1},
    {"SLUS_010.41", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 1},
    {"SLUS_110.41", "NULL", 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 1},
    {"SLES_021.12", "NULL", 1, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0},
};