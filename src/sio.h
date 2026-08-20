#pragma once

/**
 * \file sio.h
 * \brief Declarations for the SIO (serial I/O) subsystem: memory cards and controllers.
 *
 * Emulates the PlayStation SIO0 port, which connects the two memory card
 * slots and the controller pads. Exposes the memory card path buffers and
 * per-frame transfer state, plus the entry points used by the emulation
 * core, the save-state (freeze) code and netplay.
 */

/* Decompiled globals (previously generated in src/_gen) */
/** \brief Path of the memory card file for slot 1 (default "memcards\\epsxe000.mcr"). */
extern unsigned char Memcard1[0x400];
/** \brief Path of the memory card file for slot 2 (default "memcards\\epsxe001.mcr"). */
extern unsigned char Memcard2[0x400];
/** \brief Memory card 2 data buffer (filled with the erased-block pattern 0xA0 when the memcards are loaded). */
extern unsigned char memcard2_data[0x2000];
/** \brief Per-port analog mode flags for the controller pads (indexed by port number). */
extern unsigned char pad_analog_mode_flags[8];
/** \brief SIO0 mode/status register (PSX_REG_JOY_STATUS). */
extern unsigned int sio0_mode_reg;
/** \brief Non-zero once the memory card data has been loaded from disk. */
extern unsigned char sio_memcard_loaded;
/** \brief Non-zero while an SIO transfer response is pending; cleared when the data is read. */
extern unsigned int sio_transfer_pending;
/** \brief hw_update_counter deadline used to expire pending SIO transfers. */
extern unsigned int sio_transfer_timeout;
/** \brief SIO0 transmit FIFO: byte [0] is the pending-byte counter, byte [2] the expected command length and byte [259] a received-byte counter. */
extern unsigned char sio_tx_fifo[0x104];

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Points memory card slot 1 at the temporary file "memcards\\temp.000" and marks the memcard as loaded.
 *
 * Resets the slot-1 file offset so the card is written from the start of the
 * file, then saves the emulator settings.
 *
 * \return The result of cfg_save_settings().
 */
int save_temp_memcard1();
/**
 * \brief Points memory card slot 2 at the temporary file "memcards\\temp.001" and marks the memcard as loaded.
 *
 * Resets the slot-2 file offset so the card is written from the start of the
 * file, then saves the emulator settings.
 *
 * \return The result of cfg_save_settings().
 */
int save_temp_memcard2();
/**
 * \brief Initializes the controller port state.
 *
 * If bit 1 of \p control is set, stores the port selected by bit 0x2000 in
 * sio_controller_state[0] and returns it; otherwise resets the controller
 * slot state and returns 0.
 *
 * \param control Controller configuration word.
 * \return The selected port when bit 1 of \p control is set, 0 otherwise.
 */
bool sio_controller_init(int16_t control);
/**
 * \brief Returns the netplay memory card buffer for a memory card slot.
 *
 * Used by the netplay handler to compare and transfer memory card data
 * between peers.
 *
 * \param slot Memory card slot number (1 or 2).
 * \return Pointer to the 0x20000-byte netplay buffer for that slot.
 */
char * sio_for_netplay(uint8_t slot);
/**
 * \brief Writes the SIO (memcard/controller) state into a save state file.
 *
 * Serializes the freeze state, controller state, slot-1 memcard data and
 * multitap state into the gzip stream, prefixed with the \p tag.
 *
 * \param tag    Save state section tag.
 * \param gz_file gzip file handle opened by the save state code.
 * \return The result of the final gzwrite() call.
 */
int sio_freeze(const char *tag, int gz_file);
/**
 * \brief Auto-saves dirty memory cards.
 *
 * Increments the per-slot dirty counters on every call; when a counter
 * reaches 120 the corresponding card is written to disk and the counter is
 * reset.
 *
 * \return The slot-1 dirty counter value (or the result of the slot-1 save
 *         when the counter reached 120).
 */
char sio_memcard_auto_save();
/**
 * \brief Saves both memory cards to their files (slot 1, then slot 2).
 *
 * \return The result of the slot-2 memory card save.
 */
char sio_memcard_both_save();
/**
 * \brief Loads both memory card files into memory.
 *
 * On first call, resets the card data to the erased state and reads the
 * contents of the Memcard1/Memcard2 files (if they exist) into the slot
 * buffers. Subsequent calls do nothing.
 *
 * \return The fclose() result of the slot-2 file when the cards were loaded
 *         now, otherwise the sio_memcard_loaded flag.
 */
char sio_memcard_load();
/**
 * \brief Reads the next received SIO byte and advances the receive state.
 *
 * Clears sio_transfer_pending and asserts the RX-ready IRQ if a transfer is
 * pending and has not expired, then updates the received-byte counter and
 * clears the RX-full bit when the buffer has been fully read.
 *
 * \return The next received byte from the SIO RX buffer.
 */
char sio_read_data_byte();
/**
 * \brief Reads an SIO0 (JOY) register.
 *
 * \param address Register address (PSX_REG_JOY_*).
 * \param size    Access size in bytes (1, 2 or 4).
 * \return The register value read, or 0xFFFF for unsupported sizes.
 */
int sio_read_register(int address, char size);
/**
 * \brief Resets the SIO0 subsystem: registers, TX FIFO, controller state and memory cards.
 *
 * Called on emulator reset; reloads the memory cards from disk.
 *
 * \return The result of cont_update_led_and_mode(0) — the controller port 0
 *         mode callback (a function pointer).
 */
int (__stdcall *sio_reset_all())(uint32_t);
/**
 * \brief Sets the RX-ready IRQ bits in the SIO0 mode register.
 *
 * Sets bits 0x200 and 0x2 of sio0_mode_reg to signal that received data is
 * ready to be read.
 */
void sio_trigger_rx_ready_irq();
/**
 * \brief Restores the SIO (memcard/controller) state from a save state file.
 *
 * Saves the current memory cards before reading back the frozen state,
 * controller state, memcard data and multitap state from the gzip stream.
 *
 * \param unused  Unused parameter.
 * \param gz_file gzip file handle opened by the save state code.
 */
void sio_unfreeze(int unused, uint32_t *gz_file);
/**
 * \brief Writes a byte to the SIO0 transmit FIFO and executes the queued command when complete.
 *
 * Stores the byte in the TX FIFO data, decrementing the pending-byte
 * counter. When the counter reaches zero the command is dispatched via
 * sio_command() and the SIO IRQ is asserted if enabled in the control
 * register.
 *
 * \param unused Unused parameter.
 * \param data   The byte to transmit.
 */
void sio_write_data_byte(int unused, char data);
