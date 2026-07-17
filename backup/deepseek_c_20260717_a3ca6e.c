//=====================================================================
// CD File System (CDFS) routines for PlayStation/ISO9660 boot loader
//=====================================================================

//-------------------------------------------------------------------------
// Global buffers (from .data segment)
//-------------------------------------------------------------------------
unsigned char g_loaded_file_type;          // 1 = CDROM, 3 = ISO (likely)
unsigned char g_sector_buffer[2048];       // byte_4FD9E8 (temp sector read)
unsigned char g_temp_buffer2[4088];        // byte_4FD9F0 (auxiliary)
unsigned char g_root_dir_buffer1[4096];    // byte_4FE9E8 (root directory part)
unsigned char g_root_dir_buffer2[2048];    // byte_4FF1E8 (root directory part)

//-------------------------------------------------------------------------
// Read a 32‑bit little‑endian value from a byte buffer
//-------------------------------------------------------------------------
int cdfs_read_le32(unsigned __int8 *p)
{
    return *p | ((p[1] | ((p[2] | ((char)p[3] << 8)) << 8)) << 8);
}

//-------------------------------------------------------------------------
// Read a sector (or part of it) from CD using LBA address.
// The LBA is converted to MSF (minutes/seconds/frames) with a +150 offset.
//-----------------------------------------------------------------------
unsigned int cdfs_read_sector(int lba, int offset, unsigned int size, void *buffer)
{
    unsigned char minute, second, frame;

    // Convert LBA to MSF (CD sector addressing)
    frame  = (lba + 150) % 0x4B;          // 75 frames per second
    second = (lba + 150) / 0x4B % 0x3C;   // 60 seconds per minute
    minute = (lba + 150) / 0x4B / 0x3C;

    // Read the physical sector depending on loaded media type
    unsigned char temp_buffer[4704];      // v8, large enough for a sector

    if (g_loaded_file_type == 3)
        iso_read_data(minute, second, frame, (int)temp_buffer);
    else if (g_loaded_file_type == 1)
        cdrom_read_data_cb(minute, second, frame, temp_buffer);

    // Copy requested sub‑range from the raw sector data
    memcpy(buffer, &temp_buffer[offset], size);
    return size;
}

//-------------------------------------------------------------------------
// Initialise root directory structures.
// Reads the Primary Volume Descriptor (sector 16) to obtain the
// root directory LBA, then loads the root directory into two buffers.
//-------------------------------------------------------------------------
char *cdfs_init_root_directory(void)
{
    int root_lba;

    // Read the first sector of the Primary Volume Descriptor (PVD)
    cdfs_read_sector(16, 24, 0x800, g_root_dir_buffer1);

    // Offset 158 in PVD holds the LBA of the root directory (little‑endian)
    root_lba = cdfs_read_le32((unsigned __int8 *)&g_root_dir_buffer1[158]);

    // Load the root directory contents (two sectors)
    cdfs_read_sector(root_lba,     24, 0x800, g_root_dir_buffer1);
    cdfs_read_sector(root_lba + 1, 24, 0x800, g_root_dir_buffer2);

    return g_root_dir_buffer1;
}

//-------------------------------------------------------------------------
// Search for a file by name in the root directory.
// The root directory is stored in g_root_dir_buffer1/2 (up to 4096 bytes).
// On success, writes the file's LBA and size into out_lba and out_size.
// Returns out_size (as int*) or NULL if not found.
//-------------------------------------------------------------------------
int *cdfs_find_file(const char *name, int *out_lba, int **out_size)
{
    int pos = 0;

    while (1)
    {
        char *entry = &g_root_dir_buffer1[pos];

        if (!g_root_dir_buffer1[pos])       // end of directory
        {
        not_found:
            *out_lba = 0;
            return out_size;                // (unused return)
        }

        pos += (unsigned char)g_root_dir_buffer1[pos];  // next record

        // Check if this record is a file with a name match
        // entry[33] is the length of the file name (including version)
        if ((unsigned char)entry[33] >= 2)
        {
            // Compare up to 12 chars; if version separator ';' is present,
            // compare only up to 11 chars (skip version)
            if (!strncmp(name, entry + 33, 0xC) ||
                (entry[44] == ';' && !strncmp(name, entry + 33, 0xB)))
            {
                break;
            }
        }

        if (pos >= 4096)
            goto not_found;
    }

    // Extract LBA (offset +2) and size (offset +10) from the directory record
    *out_lba  = cdfs_read_le32((unsigned __int8 *)entry + 2);
    *out_size = (int *)cdfs_read_le32((unsigned __int8 *)entry + 10);
    return *out_size;
}

//-------------------------------------------------------------------------
// Parse the SYSTEM.CNF file to retrieve the executable filename.
// Reads the file contents (given by lba and size), scans for a string
// that looks like an executable name (starting with 'S'/'s' or containing '.'),
// then uses cdfs_find_file to locate that executable and obtain its LBA/size.
//-------------------------------------------------------------------------
unsigned __int8 cdfs_parse_system_cnf(int lba, int size,
                                      char *out_filename,
                                      int *out_lba,
                                      int **out_size)
{
    int i = 0;

    // Read the first sector of the SYSTEM.CNF file
    cdfs_read_sector(lba, 24, 0x800, g_sector_buffer);

    // Scan the sector for potential executable filename (8.3 format)
    if (size > 8)
    {
        do
        {
            unsigned char ch = g_sector_buffer[i];
            // Look for 'S', 's' or a dot (often start of filename)
            if (ch == 'S' || ch == 's' || g_temp_buffer2[i] == '.')
                break;
            ++i;
        }
        while (i + 8 < size);
    }

    if (i + 8 == size)   // no candidate found
    {
        *out_lba = 0;
        return 0;        // (actually returns cdfs_read_data result)
    }
    else
    {
        // Build a 13‑byte filename from the found location (8.3 + version?)
        int name_parts[3];
        name_parts[0] = *(int *)&g_sector_buffer[i];
        name_parts[1] = *(int *)&g_sector_buffer[i + 4];
        name_parts[2] = *(int *)&g_sector_buffer[i + 8];
        unsigned char last_char = g_sector_buffer[i + 12];
        unsigned char term = 0;

        // Format the filename into the output buffer
        sprintf(out_filename, "%s", (const char *)name_parts);

        // Now look up this executable file in the root directory
        // and fill out_lba and out_size with its location
        return (unsigned __int8)cdfs_find_file((const char *)name_parts,
                                               out_lba,
                                               out_size);
    }
}

//-------------------------------------------------------------------------
// Main boot function: locates SYSTEM.CNF, reads it, and extracts the
// name of the actual executable to launch. If SYSTEM.CNF is missing,
// falls back to a default name "SLUS_999.99".
//-------------------------------------------------------------------------
unsigned __int8 cdfs_load_executable(char *out_filename)
{
    int lba, size;
    int *dummy_size_ptr;

    // Initialise root directory structures
    cdfs_init_root_directory();

    // Find SYSTEM.CNF in the root directory
    cdfs_find_file("SYSTEM.CNF;1", &lba, (int **)&size);

    if (lba)
    {
        // Parse SYSTEM.CNF to get the real executable name and its LBA/size
        // (lba = LBA of SYSTEM.CNF, size = its size in bytes)
        return cdfs_parse_system_cnf(lba, size,
                                     out_filename,
                                     &size,                     // re‑use as out_lba
                                     (int **)&out_filename);    // out_size
    }
    else
    {
        // Fallback default executable name
        return sprintf(out_filename, "SLUS_999.99");
    }
}