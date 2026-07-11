**English Translation of the Analysis**  

This code is a fragment of the **ePSXe** emulator that implements **XA‑ADPCM audio decoding** (CD‑ROM XA – an extension for compressed audio storage). In the PlayStation, this format is used for background music and sound effects. The decompiled source performs low‑level ADPCM stream processing with prediction, sample packing, and playback parameter control.

---

### Overall Structure
The code consists of three logical parts:
1. **ADPCM decoding core** – `sub_403910`.
2. **Initialisation and parameter control** – `sub_403C60`, `sub_403BF0`, `sub_403C30`.
3. **Block processing (byte reordering and core invocation)** – `sub_403DF0` and `sub_403F60`.

---

### 1. Decoding Core – `sub_403910`
**Prototype:**  
```c
int *sub_403910(int *state, unsigned __int8 ctrl, __int16 *src, _WORD *dst, unsigned int stride);
```

**Purpose:**  
Decodes one ADPCM block containing **28 samples** (7 nibbles × 4) and writes them into the destination buffer with a given stride (for channel interleaving).

**Parameters:**  
- `state` – two 32‑bit values holding previous decoded samples (filter state); updated after processing.  
- `ctrl` – control byte:  
  - upper 4 bits – prediction mode (0…4);  
  - lower 4 bits – shift/alignment parameter used for nibble extraction.  
- `src` – pointer to 7 16‑bit words, each packing 4 nibbles.  
- `dst` – output buffer of 16‑bit samples.  
- `stride` – write step (1 for mono, 2 for stereo).

**Algorithm:**  
- Extract `filter_mode = ctrl >> 4` and `shift = ctrl & 0xF`.  
- For each of the 7 input words, extract 4 nibbles (`v8, v9, v10, v11`) using the shift.  
- Apply a prediction filter based on `filter_mode` (fixed coefficients in Q10 format, divided by 1024):  
  - Mode 0 – direct copy.  
  - Mode 1 – first‑order filter (coefficient 960/1024 ≈ 0.9375).  
  - Mode 2 – second‑order with coefficients 832/1024 and 1840/1024 (signs adjusted).  
  - Mode 3 – coefficients 880/1024 and 1568/1024.  
  - Mode 4 – coefficients 960/1024 and 1952/1024.  
- Clamp results to `[-524288, 524272]`, then divide by 16 (right shift 4) and store as 16‑bit values.  
- Update `state[0]` and `state[1]` with the last two samples for the next block.

**Output:**  
Filled `dst` with 28 samples, spaced by `stride`.

---

### 2. Initialisation and Control – `sub_403C60`, `sub_403BF0`, `sub_403C30`

**`sub_403C30` – mode check:**  
Analyses the byte at offset +2 and returns:  
- `2` if bits `0x24` are set;  
- otherwise returns the result of checking bit `0x02`.

**`sub_403C60` – decoder setup:**  
Receives a state structure (`a1`), header address (`a2`), data address (`a3`), and a flag (`a4`).  
From header bytes it extracts:  
- **Sample rate** (global `byte_8B1960`) – encoded in two bits:  
  - 0 → 37800 Hz, 1 → 18900 Hz, 2 → 0 Hz (disabled).  
- **Stereo/mono mode** – stored in `a1[1]`.  
- **Stereo flag** – `a1[2]` (1 = stereo, 0 = mono).  
- **Number of samples per block** – `a1[3]` (4032 for mono, 2016 for stereo).  
Depending on the stereo flag, calls `sub_403DF0` (stereo) or `sub_403F60` (mono).  
Also updates the global rate flag and invokes `spu_set_adpcm_flag_cb` when the rate changes.

**`sub_403BF0` – wrapper:**  
Checks that the audio type (from `sub_403C30`) equals 2, then calls `sub_403C60`. Returns `-1` on error.

---

### 3. Block Processing – `sub_403DF0` and `sub_403F60`

These functions reorder bytes from the input stream into the format expected by the core and invoke `sub_403910` per channel.

**`sub_403DF0` – stereo mode:**  
- Outer loop runs **18 times** (processes 18 blocks of 128 bytes each).  
- Inner loop iterates over an offset table (`byte_44C124`).  
- For each offset:  
  - Reads 16 bytes from the input buffer and packs them into `v22` (7 words, each with 4 nibbles).  
  - Calls `sub_403910` for the **left channel** with state `(a1+16)`, control byte from the offset, and output at `a1+32` (stride 2).  
  - Then calls for the **right channel** with state `(a1+24)`, control byte+1, and output at `a1+33` (stride 2).  
  - Advances the output pointer by 56 (28 samples × 2 bytes).  
- After each outer block, the input pointer moves by 128 bytes.

**`sub_403F60` – mono mode:**  
Similar, but:  
- Uses a different offset table `dword_44C134`.  
- Calls `sub_403910` once per channel (or only one channel) with stride 1.  
- Output buffers are `a1+32` and `a1+60` (two blocks?).

---

### Key Implementation Details
- **Fixed‑point arithmetic:** all filter computations use a 10‑bit shift (division by 1024) for speed.  
- **Dynamic range:** internal values are 19‑bit to prevent overflow.  
- **Nibble packing:** 4 samples per 16‑bit word – efficient storage.  
- **Stereo/mono support:** stride and channel count adapt accordingly.  
- **Global state:** `byte_8B1960` holds the current sample rate for SPU synchronisation.

---

### Role in ePSXe
This module decodes XA audio from CD images. During gameplay, the emulator reads CD sectors, extracts compressed ADPCM data, and feeds it to this decoder. The resulting PCM stream is sent to the SPU emulator for audio output. The code is optimised for real‑time performance and uses permutation tables matching the XA sector structure (2352 bytes, part of which is used for subchannels and headers).

---

### Possible Adaptations
The decompiled code is untidy, but the logic is standard for PlayStation ADPCM. It can be adapted to other platforms by replacing the offset tables and ensuring proper buffering.

---

## Proposed Function Names

| Original Name | Proposed Name | Rationale |
|---------------|---------------|-----------|
| `sub_4038F0` | `xa_clear_adpcm_state` | Sets two 32‑bit values to zero – initialises the filter state. |
| `sub_403910` | `xa_decode_adpcm_block` | Core decoder: unpacks nibbles, applies prediction, and writes samples. |
| `sub_403BF0` | `xa_decode_wrapper` | Checks audio type and calls the setup function. |
| `sub_403C30` | `xa_get_audio_mode` | Extracts mode bits from the header byte. |
| `sub_403C60` | `xa_setup_adpcm_decoder` | Configures sample rate, stereo/mono, block size, and dispatches to stereo/mono handlers. |
| `sub_403DF0` | `xa_decode_stereo_blocks` | Processes stereo data with interleaved channels. |
| `sub_403F60` | `xa_decode_mono_blocks` | Processes mono data (single channel). |

These names reflect the actual behaviour and improve readability for anyone maintaining or porting this code.