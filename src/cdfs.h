#pragma once

/**
 * \file cdfs.h
 * \brief Direct CD filesystem executable loading.
 *
 * Parses the ISO9660 root directory of the CD to find SYSTEM.CNF and
 * the BOOT= executable name, allowing an executable to be loaded
 * directly from the filesystem instead of from a fixed filename.
 */
/* Decompiled globals (previously generated in src/_gen) */

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Loads the executable name directly from the CD filesystem.
 *
 * Reads the root directory, locates SYSTEM.CNF, parses it for the BOOT=
 * entry and writes the executable filename into Buffer.
 *
 * \param Buffer Receives the executable filename (e.g. "SLUS_999.99").
 * \return The found filename length (sprintf result).
 */
uint8_t cdfs_load_executable(char *Buffer);
