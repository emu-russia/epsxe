#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char byte_44C124;
extern unsigned char byte_8B1960[0x20];
extern unsigned int dword_44C134[4];
extern unsigned int dword_44C144;

/* Function prototypes (previously generated in src/_gen) */
_DWORD *__cdecl xa_clear_adpcm_state(_DWORD *a1);
int *__cdecl xa_decode_adpcm_block(int *a1, unsigned __int8 a2, __int16 *a3, _WORD *a4, unsigned int a5);
int xa_decode_mono_blocks(int a1, int a2, int a3);
int __cdecl xa_decode_stereo_blocks(int a1, int a2);
int __cdecl xa_decode_wrapper(_DWORD *a1, int a2, int a3);
int __cdecl xa_get_audio_mode(int a1);
int __cdecl xa_setup_adpcm_decoder(_DWORD *a1, int a2, int a3, int a4);
