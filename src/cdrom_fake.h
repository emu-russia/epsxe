#pragma once

/**
 * \file cdrom_fake.h
 * \brief Fake-CD file backend ("save fake" mode).
 *
 * Provides a raw sector dump of the emulated CD: sectors read during a
 * session are appended to a .fake file together with a sector bitmap,
 * and can be reloaded later for fast booting without the original disc.
 */
/* Decompiled globals (previously generated in src/_gen) */

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Creates a new fake-CD file for saving.
 *
 * Allocates the sector bitmap, opens the file for writing and writes the
 * fake-file version header.
 *
 * \param FileName Path of the fake file to create.
 * \return The result of the debug print call.
 */
int cdrom_fake_create_file(char *FileName);

/**
 * \brief Loads an existing fake-CD file.
 *
 * Allocates the sector bitmap, opens the file for reading and loads the
 * version header and sector data.
 *
 * \param FileName Path of the fake file to load.
 * \return The result of the debug print call.
 */
int cdrom_fake_load_file(char *FileName);

/**
 * \brief Reads one 2352-byte sector from the fake file.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param Buffer Destination buffer (2352 bytes).
 * \return The number of bytes read (fread result).
 */
size_t cdrom_fake_read_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);

/**
 * \brief Finalizes and closes the fake-CD file.
 *
 * Writes the version header and the sector bitmap, then closes the file.
 *
 * \return The file handle (or the close result).
 */
FILE *cdrom_fake_write();

/**
 * \brief Appends one sector to the fake-CD file if not yet stored.
 *
 * Records the sector's file offset in the bitmap and returns the new
 * offset, so the same sector is only written once.
 *
 * \param minute BCD minute of the sector.
 * \param second BCD second of the sector.
 * \param frame  BCD frame of the sector.
 * \param Buffer Sector data to append (2352 bytes).
 * \return The new sector offset in the fake file.
 */
void * cdrom_fake_write_portion(uint8_t minute, uint8_t second, uint8_t frame, void *Buffer);
