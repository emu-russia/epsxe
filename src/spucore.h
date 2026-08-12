#pragma once

#pragma pack(push, 1)
// Total size: 74 elements * 4 bytes = 296 bytes
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