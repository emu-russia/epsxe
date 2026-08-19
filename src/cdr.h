#pragma once

/**
 * \file cdr.h
 * \brief Emulation of the PSX CD-ROM drive controller.
 *
 * Implements the CD controller registers (index/status, command,
 * parameter FIFO and request registers), the response FIFO and IRQ
 * handling, DMA transfers of read data, and the per-frame drive tick
 * (seek, motor spinup, CDDA playback and read-ahead sectors).
 */
/* Decompiled globals (previously generated in src/_gen) */

/** \brief Command-line timing-adjustment flag (-adjusttiming / -noadjusttiming); when set, the CD controller forces drive speed and response timing. */
extern int adjust_timing;

/** \brief When non-zero, CD response bytes are replaced with rand() values (set by the -legaia switch to bypass game copy-protection checks). */
extern unsigned char cdr_randomize_response_flag;

/** \brief Number of data bytes already transferred from the CD data buffer during the current DMA transfer. */
extern unsigned int g_cdr_data_bytes_transferred;

/** \brief Pending CD controller IRQ flag; set when a response is queued and asserted via irq_cdrom_assert_int(). */
extern unsigned char g_cdr_irq_pending;

/** \brief Read index into the CD response FIFO. */
extern unsigned char g_cdr_response_index;

/** \brief Number of valid bytes currently in the CD response FIFO. */
extern unsigned char g_cdr_response_size;

/** \brief When non-zero, CD report mode is enabled: the current MSF position is included in the per-sector response (disabled by -disablereportmode). */
extern unsigned char report_mode_enabled;

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Performs the CD-ROM DMA transfer.
 *
 * Computes the transfer size from the DMA block control register,
 * copies the requested bytes from the CD data buffer to the destination
 * memory area (mem_dma_read) and invalidates the corresponding dynarec
 * cache range when the recompiler is active.
 *
 * \return The transferred byte count (or the dynarec invalidation result).
 */
unsigned int cdr_dma();

/**
 * \brief Saves the CD controller state for a save state.
 *
 * Writes the given tag and the whole CD controller state (response FIFO
 * and status registers, 0x112C bytes) to the gzip stream.
 *
 * \param tag     Identifier tag written to the stream.
 * \param gz_file Gzip stream (from the save-state machinery).
 * \return The result of the final gzwrite() call.
 */
int cdr_freeze(const char *tag, int gz_file);

/**
 * \brief Returns the current CD response status byte.
 *
 * \return The value of the response status register, or 0 when the IRQ
 *         mode is 24.
 */
int cdr_get_response_status();

/**
 * \brief Forces the CD response status to the given value.
 *
 * Sets the response status register and prepares a one-byte response in
 * the FIFO.
 *
 * \param status Status value to force (e.g. 2 = "no disc").
 * \return The status value that was set.
 */
int cdr_get_status(int status);

/**
 * \brief Converts an MSF position to an LBA sector number.
 *
 * Applies the standard 2-second (150-sector) offset used by CD-ROMs.
 *
 * \param minute Minutes.
 * \param second Seconds.
 * \param frame  Frames (75 per second).
 * \return The corresponding LBA.
 */
int cdr_msf_to_lba(uint8_t minute, uint8_t second, uint8_t frame);

/**
 * \brief Advances the CD controller by one emulated frame tick.
 *
 * Increments the current MSF position, queues the per-sector responses
 * (including the MSF report when report mode is enabled), drives the
 * read-ahead sector fetches and stops at the seek target when a read
 * completes. Called once per frame from the CPU core.
 */
void cdr_play_tick();

/**
 * \brief Processes the delayed CD response queue.
 *
 * Increments the response delay counter and queues the pending response
 * (raising the CD IRQ) once the delay has elapsed.
 *
 * \return The current response status, or 10 when a response was queued.
 */
char cdr_process_delays();

/**
 * \brief Handles writes to the CD index/status register.
 *
 * Sets the IRQ-pending flag for command 1 and selects the register set
 * for other commands.
 *
 * \param command Value written to the index/status register.
 * \return A status value derived from the current register state.
 */
char cdr_reg0_write(char command);

/**
 * \brief Handles writes to the CD command register.
 *
 * Dispatches the full CD command set (Getstat, GetID, GetTN, Seek,
 * ReadN, Stop, Pause, etc.), updating the status registers and preparing
 * the primary/secondary responses for each command.
 *
 * \param command CD command byte written by the CPU.
 */
void cdr_reg1_write(uint8_t command);

/**
 * \brief Handles writes to the CD parameter FIFO register.
 *
 * Pushes a parameter byte into the parameter FIFO, or sets the IRQ mode
 * when a mode-select write is pending.
 *
 * \param command Parameter byte (or IRQ mode) written by the CPU.
 * \return A status value derived from the current register state.
 */
char cdr_reg2_write(char command);

/**
 * \brief Handles writes to the CD request register.
 *
 * Acknowledges the pending CD IRQ, advances the response FIFO index and
 * triggers delivery of the next queued response.
 *
 * \param command Value written to the request register.
 */
void cdr_reg3_write(char command);

/**
 * \brief Resets the CD controller to its initial state.
 *
 * Clears the response FIFO, status registers, IRQ state and DMA flags.
 *
 * \return The current "no CD" flag.
 */
char cdr_reset_controller();

/**
 * \brief Starts motor spinup.
 *
 * Sets the motor spinup state and queues the spinup response (0x10) with
 * a pending IRQ.
 */
void cdr_spinup_motor();

/**
 * \brief Restores the CD controller state from a save state (old format).
 *
 * Reads the tag and controller state from the gzip stream, restores the
 * timing counters and resumes CDDA playback or stops the drive through
 * the CD-ROM callbacks.
 *
 * \param unused  Unused argument (historically the tag).
 * \param gz_file Gzip stream (from the save-state machinery).
 * \return The result of the CDDA play/stop callback.
 */
int cdr_unfreeze(int unused, uint32_t *gz_file);

/**
 * \brief Restores the CD controller state from a save state (new format).
 *
 * Like cdr_unfreeze() but for the newer state format: reads the tag and
 * controller state, restores only the response delay counter and resumes
 * CDDA playback or stops the drive through the CD-ROM callbacks.
 *
 * \param unused  Unused argument (historically the tag).
 * \param gz_file Gzip stream (from the save-state machinery).
 * \return The result of the CDDA play/stop callback.
 */
int cdr_unfreeze_new(int unused, uint32_t *gz_file);

/**
 * \brief Updates the motor spinup state.
 *
 * Decrements the spinup counter; when spinup completes, sets the motor-on
 * flag and returns 0.
 *
 * \return 0 when spinup finished, otherwise the remaining spinup count.
 */
char cdr_update_motor_status();
