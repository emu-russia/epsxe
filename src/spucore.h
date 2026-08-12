#pragma once

// TODO

#pragma pack(push,1)
typedef struct _VOICE_PARAM {
    // Регистры голоса (1F801C00h + N*10h)
    // ============================================
    
    // Адрес 0x00: Volume Left (1F801C00h + N*10h)
    uint32_t volume_left;          // 0-14: volume, 15: sweep mode flag
    // Адрес 0x02: Volume Right (1F801C02h + N*10h)
    uint32_t volume_right;         // 0-14: volume, 15: sweep mode flag
    
    // Адрес 0x04: Pitch/Sample Rate (1F801C04h + N*10h)
    uint32_t pitch;                // 0-15: sample rate (1000h = 44100Hz)
    
    // Адрес 0x06: Start Address (1F801C06h + N*10h)
    uint32_t start_addr;           // Start address in 8-byte units
    
    // Адрес 0x08: ADSR lower 16-bit (1F801C08h + N*10h)
    // биты: 15=attack mode, 14-10=attack shift, 9-8=attack step,
    //       7-4=decay shift, 3-0=sustain level
    uint32_t adsr_lower;
    
    // Адрес 0x0A: ADSR upper 16-bit (1F801C0Ah + N*10h)
    // биты: 31=sustain mode, 30=sustain direction, 28-24=sustain shift,
    //       23-22=sustain step, 21=release mode, 20-16=release shift
    uint32_t adsr_upper;
    
    // Адрес 0x0C: Current ADSR Volume (1F801C0Ch + N*10h)
    int32_t current_adsr_vol;      // Current ADSR envelope volume (0..+7FFFh)
    
    // Адрес 0x0E: Repeat Address (1F801C0Eh + N*10h)
    uint32_t repeat_addr;          // Loop address in 8-byte units

    // Внутренние параметры (не отображаются на I/O)
    // ============================================
    
    // Состояние ADSR (0=off, 1=attack, 2=decay, 3=sustain, 4=release)
    uint32_t adsr_state;
    
    // Декодированные параметры ADSR
    uint32_t attack_mode;           // 0=linear, 1=exponential
    uint32_t attack_shift;          // 0..31
    uint32_t attack_step;           // 0..3 (+7,+6,+5,+4)
    uint32_t attack_dir;            // always increase
    
    uint32_t decay_mode;            // always exponential
    uint32_t decay_shift;           // 0..15
    uint32_t decay_step;            // always -8
    uint32_t decay_dir;             // always decrease
    
    uint32_t sustain_level;         // 0..15, level = (N+1)*800h
    uint32_t sustain_mode;          // 0=linear, 1=exponential
    uint32_t sustain_shift;         // 0..31
    uint32_t sustain_step;          // 0..3 (+7,+6,+5,+4) or (-8,-7,-6,-5)
    uint32_t sustain_dir;           // 0=increase, 1=decrease
    
    uint32_t release_mode;          // 0=linear, 1=exponential
    uint32_t release_shift;         // 0..31
    uint32_t release_step;          // always -8
    uint32_t release_dir;           // always decrease
    
    // Параметры Pitch
    uint32_t pitch_value;          // Current pitch value (0..3FFFh)
    float pitch_float;             // Pitch as floating point
    
    // Pitch counter (для интерполяции)
    uint32_t pitch_counter;        // Internal pitch counter
    
    // Текущий адрес воспроизведения
    uint32_t current_addr;         // Current sample address in 8-byte units
    uint32_t next_addr;            // Next ADPCM block address
    
    // Состояние декодирования ADPCM
    int32_t sample_prev1;          // Previous sample (s1)
    int32_t sample_prev2;          // Older sample (s2)
    
    // История сэмплов для интерполяции (28 samples)
    int32_t sample_history[28];    // Buffer for interpolation
    
    // Флаг состояния блока
    uint32_t block_state;           // 0=waiting, 1=ok, 2=end
    
} VOICE_PARAM;
#pragma pack(pop)

#if 0

.data:00465540 dword_465540    dd ?                    ; DATA XREF: spucore_write_voice_reg+3B↑w
.data:00465540                                         ; spucore_freeze+2BB↑o ...
.data:00465544 ; int dword_465544[]
.data:00465544 dword_465544    dd ?                    ; DATA XREF: spucore_write_voice_reg+97↑w
.data:00465548 ; int dword_465548[]
.data:00465548 dword_465548    dd ?                    ; DATA XREF: spucore_write_voice_reg+71↑w
.data:0046554C ; int dword_46554C[]
.data:0046554C dword_46554C    dd ?                    ; DATA XREF: spucore_write_voice_reg+CD↑w
.data:00465550 ; int dword_465550[]
.data:00465550 dword_465550    dd ?                    ; DATA XREF: spucore_write_voice_reg+49↑w
.data:00465550                                         ; spucore_freeze+7D↑o ...
.data:00465554 ; int dword_465554[]
.data:00465554 dword_465554    dd ?                    ; DATA XREF: spucore_write_voice_reg+A5↑w
.data:00465558 ; int dword_465558[]
.data:00465558 dword_465558    dd ?                    ; DATA XREF: spucore_write_voice_reg+4F↑w
.data:0046555C ; int dword_46555C[]
.data:0046555C dword_46555C    dd ?                    ; DATA XREF: spucore_write_voice_reg+AB↑w
.data:00465560 ; int dword_465560[]
.data:00465560 dword_465560    dd ?                    ; DATA XREF: spucore_write_voice_reg+5D↑w
.data:00465564 ; int dword_465564[]
.data:00465564 dword_465564    dd ?                    ; DATA XREF: spucore_write_voice_reg+B9↑w
.data:00465568 ; int dword_465568[]
.data:00465568 dword_465568    dd ?                    ; DATA XREF: spucore_write_voice_reg+6B↑w
.data:0046556C ; int dword_46556C[]
.data:0046556C dword_46556C    dd ?                    ; DATA XREF: spucore_write_voice_reg+C7↑w
.data:00465570 ; int dword_465570[]
.data:00465570 dword_465570    dd ?                    ; DATA XREF: spucore_write_voice_reg+F7↑w
.data:00465574 ; int dword_465574[]
.data:00465574 dword_465574    dd ?                    ; DATA XREF: spucore_voice_key_on+A↑r
.data:00465574                                         ; spucore_write_voice_reg+136↑w ...
.data:00465578 dword_465578    dd ?                    ; DATA XREF: spucore_write_voice_reg+15A↑w
.data:0046557C dword_46557C    dd ?                    ; DATA XREF: spucore_write_voice_reg+16A↑w
.data:00465580 dword_465580    dd ?                    ; DATA XREF: spucore_write_voice_reg+19C↑w
.data:00465584 dword_465584    dd ?                    ; DATA XREF: spucore_write_voice_reg+18D↑w
.data:00465588 dword_465588    dd ?                    ; DATA XREF: spucore_write_voice_reg+1CD↑w
.data:0046558C dword_46558C    dd ?                    ; DATA XREF: spucore_write_voice_reg+1EE↑w
.data:00465590 dword_465590    dd ?                    ; DATA XREF: spucore_write_voice_reg+203↑w
.data:00465594 dword_465594    dd ?                    ; DATA XREF: spucore_write_voice_reg+1F4↑w
.data:00465598 dword_465598    dd ?                    ; DATA XREF: spucore_write_voice_reg+209↑w
.data:0046559C ; int dword_46559C[]
.data:0046559C dword_46559C    dd ?                    ; DATA XREF: spucore_voice_key_off:loc_40C611↑w
.data:0046559C                                         ; spucore_write_voice_reg+245↑w ...
.data:004655A0 ; int dword_4655A0[]
.data:004655A0 dword_4655A0    dd ?                    ; DATA XREF: spucore_decode_adpcm_block+B9↑r
.data:004655A0                                         ; spucore_decode_adpcm_block:loc_40C757↑r ...
.data:004655A4 ; int dword_4655A4[]
.data:004655A4 dword_4655A4    dd ?                    ; DATA XREF: spucore_voice_key_on+12↑w
.data:004655A4                                         ; spucore_voice_key_off+A↑r ...
.data:004655A8                 db    ? ;
.data:004655A9                 db    ? ;
.data:004655AA                 db    ? ;
.data:004655AB                 db    ? ;
.data:004655AC ; int dword_4655AC[]
.data:004655AC dword_4655AC    dd ?                    ; DATA XREF: spucore_voice_key_on+28↑w
.data:004655B0 ; int dword_4655B0[]
.data:004655B0 dword_4655B0    dd ?
.data:004655B4 ; int dword_4655B4[]
.data:004655B4 dword_4655B4    dd ?                    ; DATA XREF: spucore_write_voice_reg+118↑w
.data:004655B8 ; int dword_4655B8[]
.data:004655B8 dword_4655B8    dd ?                    ; DATA XREF: spucore_voice_key_on+1C↑w
.data:004655B8                                         ; spucore_voice_key_off+27↑w
.data:004655BC ; int dword_4655BC[]
.data:004655BC dword_4655BC    dd ?                    ; DATA XREF: spucore_voice_key_on+22↑w
.data:004655BC                                         ; spucore_decode_adpcm_block+17↑r ...
.data:004655C0 ; int dword_4655C0[]
.data:004655C0 dword_4655C0    dd ?                    ; DATA XREF: spucore_decode_adpcm_block:loc_40C781↑r
.data:004655C0                                         ; spucore_decode_adpcm_block+1CC↑w ...
.data:004655C4 ; int dword_4655C4[]
.data:004655C4 dword_4655C4    dd ?                    ; DATA XREF: spucore_decode_adpcm_block+167↑r
.data:004655C4                                         ; spucore_decode_adpcm_block+1BF↑w ...
.data:004655C8 ; int dword_4655C8[]
.data:004655C8 dword_4655C8    dd ?                    ; DATA XREF: spucore_decode_adpcm_block+1D7↑w
.data:004655C8                                         ; spucore_decode_adpcm_block:loc_40C874↑o ...
.data:004655CC ; int dword_4655CC[]
.data:004655CC dword_4655CC    dd 1Bh dup(?)           ; DATA XREF: spucore_decode_adpcm_block+22B↑w
.data:00465638 ; int dword_465638[]
.data:00465638 dword_465638    dd 7 dup(?)             ; DATA XREF: spucore_voice_key_on+2E↑w
.data:00465638                                         ; spucore_decode_adpcm_block+AD↑w ...
.data:00465654 dword_465654    dd ?                    ; DATA XREF: spucore_write_voice_reg+180↑w
.data:00465658 dword_465658    dd ?                    ; DATA XREF: spucore_write_voice_reg+1A2↑w
.data:0046565C dword_46565C    dd ?                    ; DATA XREF: spucore_write_voice_reg+1A8↑w
.data:00465660 ; int dword_465660[]
.data:00465660 dword_465660    dd ?                    ; DATA XREF: spucore_write_voice_reg+21D↑w
.data:00465664 ; int dword_465664[1703]
.data:00465664 dword_465664    dd 6A7h dup(?)          ; DATA XREF: spucore_write_voice_reg+223↑w

#endif