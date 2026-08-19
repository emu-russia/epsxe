#pragma once

/**
 * \file spucore.h
 * \brief Internal (built-in) SPU core: software sound synthesis, XA/ADPCM playback and SPU DMA.
 *
 * Implements the PlayStation SPU entirely in software (no external plugin):
 * voice mixing, ADSR envelopes, XA decoding, DirectSound output and the SPU
 * DMA channel. Exposes the same interface as the external plugin wrapper
 * (spu_plugin.c) and shares the SPU RAM and DMA state with it.
 */

#pragma pack(push, 1)
// Total size: 74 elements * 4 bytes = 296 bytes
/**
 * \brief Per-voice SPU state: hardware voice registers plus extracted ADSR/ADPCM state.
 *
 * One entry per SPU voice (24 voices); the first eight fields mirror the
 * hardware voice registers (1F801C00h + N*10h), while the remaining fields
 * hold the extracted ADSR parameters, ADPCM decoder state, sample history and
 * pitch-modulation values used by the software mixer.
 */
typedef struct _SPU_VOICE_PARAM {
    // Voice registers (1F801C00h + N*10h) - indices 0x00..0x07
    // [0x00] Volume Left (1F801C00h + N*10h)
    uint32_t volume_left;           // bits 0-14: volume, bit 15: sweep mode

    // [0x01] Volume Right (1F801C02h + N*10h)
    uint32_t volume_right;          // bits 0-14: volume, bit 15: sweep mode

    // [0x02] Pitch/Sample Rate (1F801C04h + N*10h)
    uint32_t pitch;                 // 0-15: sample rate (1000h = 44100Hz)

    // [0x03] Start Address (1F801C06h + N*10h)
    uint32_t start_addr;            // Start address in 8-byte units

    // [0x04] ADSR lower (1F801C08h + N*10h)
    uint32_t adsr_lower;            // 15=attack mode, 14-10=attack shift,
                                    // 9-8=attack step, 7-4=decay shift, 3-0=sustain level

    // [0x05] ADSR upper (1F801C0Ah + N*10h)
    uint32_t adsr_upper;            // 31=sustain mode, 30=sustain direction,
                                    // 28-24=sustain shift, 23-22=sustain step,
                                    // 21=release mode, 20-16=release shift

    // [0x06] Current ADSR Volume (1F801C0Ch + N*10h)
    uint32_t current_adsr_vol;      // Current ADSR envelope volume (0..+7FFFh)

    // [0x07] Repeat Address (1F801C0Eh + N*10h)
    uint32_t repeat_addr;           // Loop address in 8-byte units

    // Extracted ADSR parameters - indices 0x08..0x15
    // [0x08] ADSR Attack mode
    uint32_t adsr_attack_mode;      // 0=linear, 1=exponential

    // [0x09] ADSR Attack shift
    uint32_t adsr_attack_shift;     // 0..31

    // [0x0A] ADSR Attack step
    uint32_t adsr_attack_step;      // 0..3 (+7,+6,+5,+4)

    // [0x0B] ADSR Decay shift
    uint32_t adsr_decay_shift;      // 0..15

    // [0x0C] ADSR Sustain mode
    uint32_t adsr_sustain_mode;     // 0=linear, 1=exponential

    // [0x0D] ADSR Sustain direction
    uint32_t adsr_sustain_dir;      // 0=increase, 1=decrease

    // [0x0E] ADSR Sustain shift
    uint32_t adsr_sustain_shift;    // 0..31

    // [0x0F] ADSR Sustain step
    uint32_t adsr_sustain_step;     // 0..3

    // [0x10] ADSR Sustain level
    uint32_t adsr_sustain_level;    // 0..15, level=(N+1)*800h

    // [0x11] ADSR Release mode
    uint32_t adsr_release_mode;     // 0=linear, 1=exponential

    // [0x12] ADSR Release shift
    uint32_t adsr_release_shift;    // 0..31

    // [0x13] ADSR Envelope counter
    uint32_t adsr_envelope;         // envelope << 9

    // [0x14] Loop Start Address (from ADPCM flags)
    uint32_t loop_start_addr;

    // [0x15] Voice state flags (0=off, 1=key on, 4=key off)
    uint32_t voice_state;

    // Voice state - indices 0x16..0x1F
    // [0x16] Pitch modulation factor
    uint32_t pitch_mod_factor;

    // [0x17] Unknown
    uint32_t unknown17;

    // [0x18] Pitch multiplication factor (fixed point)
    uint32_t pitch_multiplier;      // pitch * 65536

    // [0x19] Current ADPCM block address
    uint32_t current_block_addr;

    // [0x1A] Current ADPCM sample address
    uint32_t current_sample_addr;

    // [0x1B] ADPCM decoder state - s0
    int32_t adpcm_s0;

    // [0x1C] ADPCM decoder state - s1
    int32_t adpcm_s1;

    // Sample history for interpolation - indices 0x1D..0x38 (28 elements)
    // [0x1D..0x38] Sample history buffer (28 samples)
    int32_t sample_history[28];     // 28 * 4 = 112 bytes

    // Additional parameters - indices 0x39..0x49
    // [0x39] ADPCM block decode status (0=idle, 1=decoding, 2=end)
    uint32_t block_status;

    // [0x3A] Unknown
    uint32_t unknown3A;

    // [0x3B] Unknown
    uint32_t unknown3B;

    // [0x3C] Unknown
    uint32_t unknown3C;

    // [0x3D] Unknown
    uint32_t unknown3D;

    // [0x3E] Unknown
    uint32_t unknown3E;

    // [0x3F] Unknown
    uint32_t unknown3F;

    // [0x40] Unknown
    uint32_t unknown40;

    // [0x41] Unknown
    uint32_t unknown41;

    // [0x42] Pitch modulation table value
    uint32_t pitch_mod_table;

    // [0x43] Pitch modulation negative value
    uint32_t pitch_mod_neg;

    // [0x44] Pitch modulation value
    uint32_t pitch_mod_value;

    // [0x45] Noise/pitch modulation parameter
    int32_t pitch_mod_param;

    // [0x46] Noise/pitch modulation parameter 2
    int32_t pitch_mod_param2;

    // [0x47] Unknown
    uint32_t unknown47;

    // [0x48] Unknown
    uint32_t unknown48;

    // [0x49] Unknown (last element, total 74 elements)
    uint32_t unknown49;

} SPU_VOICE_PARAM;
#pragma pack(pop)
/* Decompiled globals (previously generated in src/_gen) */

/** Shared buffer for decoded XA/ADPCM data, filled by xa_decode_wrapper() and consumed by the SPU playback path. */
extern unsigned int spu_xa_decode_buf_ptr[1];

/** Number of decoded XA samples still queued for playback. */
extern unsigned int spu_xa_samples_left;

/** Mute flag (1 = mute); zeroes the mixed output in the DirectSound update loop. */
extern unsigned int spu_mute_flag;

/** SPU DMA memory address: base PSX memory address of the current channel-4 DMA transfer. */
extern unsigned int spu_dma_mem_addr;

/** SPU DMA block size/count for channel 4: low word = block size, high word = block count (BCR register). */
extern unsigned int spu_dma_block_size_count;

/** The 512 KB SPU sample RAM used by the internal SPU core. */
extern unsigned char spu_ram[0x80000];

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Shuts down the internal SPU core.
 *
 * Stops and releases the DirectSound buffer and DirectSound object when the
 * core was previously initialized.
 *
 * \return The dbg_print() result, or 0 if the core was never initialized.
 */
int spucore_destroy();

/**
 * \brief Performs an SPU (DMA channel 4) transfer for the internal core.
 *
 * Reads the DMA address, block count and size from the shared SPU DMA state
 * and copies the data between PSX memory and SPU RAM (FIFO reads for DMA
 * reads, direct word copies for DMA writes). Invalidates the affected dynarec
 * range when the dynarec is enabled.
 */
void spucore_dma();

/**
 * \brief Saves the full internal SPU state into a gzip savestate.
 *
 * Serializes the control registers, SPU RAM, XA decode buffer and all 24
 * voice parameter blocks, and writes them to the gzip file.
 *
 * \param filename Savestate identifier string written to the file.
 * \param file     File descriptor of the open gzip savestate.
 * \return The result of the final gzwrite() call.
 */
int spucore_freeze(const char *filename, int file);

/**
 * \brief Initializes the internal SPU core.
 *
 * Sets up the SPU RAM pointer and gauss interpolation table, initializes
 * DirectSound output, resets the XA sample counter and sets the init flag.
 * Fails fatally (with a message box) when the sound handler cannot be opened.
 *
 * \return The result of the final dbg_print() call.
 */
int spucore_init();

/**
 * \brief Decodes and queues an XA/ADPCM block for playback.
 *
 * When sound and XA playback are enabled, decodes the ADPCM block at pcm_addr
 * via xa_decode_wrapper() into the shared XA buffer, updates the playback
 * position/rate and clears the pending ADPCM flag.
 *
 * \param pcm_addr Memory address of the XA/ADPCM data to play.
 * \return Status of the operation (0 = success, non-zero = failure).
 */
char spucore_play_adpcm(int pcm_addr);

/**
 * \brief Reads an SPU register (voice or global) of the internal core.
 *
 * Dispatches voice-register reads to spucore_read_voice_reg() and serves the
 * global registers (main/reverb volume, pitch mod, noise, DMA, counters, etc.)
 * from the internal state.
 *
 * \param address SPU register address to read.
 * \return The 16-bit register value.
 */
int16_t spucore_read_register(int16_t address);

/**
 * \brief Restores the internal SPU state from a gzip savestate.
 *
 * Reads the saved registers, SPU RAM, XA decode buffer and voice parameter
 * blocks back and re-derives the ADSR/rate tables for all 24 voices.
 *
 * \param unused Unused parameter kept for prototype compatibility.
 * \param file   File descriptor of the open gzip savestate.
 * \return 0 when the "ISPU" magic matches, non-zero otherwise.
 */
int spucore_unfreeze(int unused, uint32_t *file);

/**
 * \brief Produces the next block of internal SPU sound output.
 *
 * Thunk that forwards to spucore_update_dsound(), which mixes the active
 * voices into the DirectSound buffer (respecting the mute flag).
 *
 * \return The result of spucore_update_dsound().
 */
int spucore_update_thunk();

/**
 * \brief Writes an SPU register (voice or global) of the internal core.
 *
 * Dispatches voice-register writes to spucore_write_voice_reg() and handles
 * the global registers (main/reverb volume, key on/off, pitch mod, noise,
 * DMA control, CD/ext volumes, etc.).
 *
 * \param address SPU register address to write.
 * \param value   16-bit value to write.
 * \return The result of the write operation.
 */
int16_t spucore_write_register(int16_t address, int16_t value);
