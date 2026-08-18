#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int dword_4FC45C;

/* Function prototypes (previously generated in src/_gen) */
BOOL __cdecl Big_Motor(unsigned int a1, int a2);
int JOY_Close();
int JOY_init();
BOOL __cdecl Small_Motor(unsigned int a1, int a2);
int joy_init(void);
int joy_issue_big_motor();
int joy_issue_small_motor();
