#pragma once

/**
 * \file mem.h
 * \brief Memory subsystem: main RAM, hook tables and access entry points.
 *
 * Declares the 2 MB main RAM, the 4 KB data cache, the per-64 KB-page
 * read/write hook tables used to route memory accesses, and the
 * byte/halfword/word read-write and save-state entry points.
 */

/* Decompiled globals (previously generated in src/_gen) */

/** \brief Handle of the console log stream (used as a FILE* by the debug logging helpers). */
extern unsigned int console_log_handle;

/** \brief 4 KB data-cache region covering hardware-area addresses below 0x1F801000. */
extern unsigned char dcache[0x1000];

/** \brief Per-64 KB-page table of source pointers used for memory reads. */
extern unsigned int mem_read_hooks[0x10000];

/** \brief Per-64 KB-page table of target pointers used for memory writes. */
extern unsigned int mem_write_hooks[0x10000];

/** \brief 2 MB main RAM. */
extern unsigned char ram[0x200000];

/** \brief SIO0 control register (JOY_CTRL). */
extern unsigned int sio0_control_reg;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Clears the emulated main memory.
 *
 * Zeroes RAM and the data cache, and fills the PIO memory region
 * with 0xFF.
 *
 * \return 0.
 */
int mem_clear_memory();

/**
 * \brief Returns the translated memory pointer used for DMA reads.
 *
 * Resolves the address through the read-hook table, returning the
 * pointer to the backing memory page plus the offset within it.
 *
 * \param addr Address to translate.
 * \return Pointer value (as an int) to the memory backing addr.
 */
int mem_dma_read(unsigned int addr);

/**
 * \brief Saves the memory state to a gzip save-state file.
 *
 * Writes a chunk tag, the whole RAM, the PIO memory region and the
 * data cache to the gzip stream.
 *
 * \param name Chunk tag written to the save-state file.
 * \param gzf  gzip file handle of the save-state file.
 * \return The result of the last gzwrite() call.
 */
int mem_freeze(const char *name, int gzf);

/**
 * \brief Reads a 32-bit value from memory for GPU DMA transfers.
 *
 * Resolves the address through the memory hooks, reading from the
 * hardware registers, the data cache or the hooked memory pages.
 *
 * \param addr Address to read from.
 * \return The 32-bit value read.
 */
unsigned int mem_gpu_dma_read(unsigned int addr);

/**
 * \brief Writes a 32-bit value to memory for GPU DMA transfers.
 *
 * Skips the write when the cache is isolated (cop0_sr bit 16 set)
 * and otherwise resolves the address through the write hooks.
 *
 * \param addr  Address to write to.
 * \param value 32-bit value to write.
 */
void mem_gpu_dma_write(unsigned int addr, unsigned int value);

/**
 * \brief Handles a byte read from the hardware register area.
 *
 * Emulates the side effects of reading CD-ROM, SIO and DMA registers
 * (advancing response indices, consuming SIO bytes, etc.) and logs
 * unknown registers.
 *
 * \param addr Address of the hardware register.
 */
void mem_hw_reg_read_byte(unsigned int addr);

/**
 * \brief Handles a byte write to a hardware register.
 *
 * Dispatches to the CD-ROM command registers, the SIO data register,
 * the DMA interrupt control register or the POST register, and logs
 * unknown registers. Memory writes are skipped while the cache is
 * isolated.
 *
 * \param addr  Address of the hardware register.
 * \param value Byte value to write.
 */
void mem_hw_reg_write_byte(unsigned int addr, char value);

/**
 * \brief Handles a 16-bit write to a hardware register.
 *
 * Dispatches to the root counters, the SPU registers, the SIO/controller
 * registers, the interrupt status/mask registers or the SPU-delay
 * register, and logs unknown registers.
 *
 * \param addr  Address of the hardware register.
 * \param value 16-bit value to write.
 */
void mem_hw_reg_write_half(unsigned int addr, uint16_t value);

/**
 * \brief Initializes the memory handler hook tables.
 *
 * Fills mem_read_hooks/mem_write_hooks for the 64 KB pages: RAM pages
 * for the low and mirrored ranges, the PIO pages, and read-only BIOS
 * pages.
 */
void mem_init_memory_handlers();

/**
 * \brief Reads a 16-bit value from memory.
 *
 * Reads through the memory hooks for normal addresses; addresses in
 * the hardware area are served by hw_reg_read_half() or the data
 * cache.
 *
 * \param addr Address to read from.
 * \return The 16-bit value read.
 */
int16_t mem_read_half(unsigned int addr);

/**
 * \brief Reads a 32-bit value from memory.
 *
 * Reads through the memory hooks for normal addresses; addresses in
 * the hardware area are served by hw_reg_read_word() or the data
 * cache.
 *
 * \param addr Address to read from.
 * \return The 32-bit value read.
 */
int mem_read_word(unsigned int addr);

/**
 * \brief Restores the memory state from a gzip save-state file.
 *
 * Reads back the chunk tag, the whole RAM, the PIO memory region and
 * the data cache written by mem_freeze().
 *
 * \param unused Unused parameter.
 * \param gzf    gzip file handle of the save-state file.
 * \return The result of the last gzread() call.
 */
int mem_unfreeze(int unused, uint32_t *gzf);

/**
 * \brief Writes a 16-bit value to memory.
 *
 * Writes through the memory hooks for normal addresses; addresses in
 * the hardware area are handled by the register writers or the data
 * cache. Recompiled code covering the written address is invalidated.
 *
 * \param addr  Address to write to.
 * \param value 16-bit value to write.
 */
void mem_write_half(unsigned int addr, uint16_t value);

/**
 * \brief Writes a 32-bit value to memory.
 *
 * Writes through the memory hooks for normal addresses; addresses in
 * the hardware area are handled by hw_reg_write_word() or the data
 * cache. Recompiled code covering the written address is invalidated.
 *
 * \param addr  Address to write to.
 * \param value 32-bit value to write.
 */
void mem_write_word(unsigned int addr, unsigned int value);
