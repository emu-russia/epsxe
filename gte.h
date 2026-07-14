#pragma once

#pragma pack(push,1)

typedef union _GTE_REG {

	struct {
		uint16_t hi;
		uint16_t lo;
	} u16;

	struct {
		int16_t hi;
		int16_t lo;
	} s16;

	uint32_t u32;
	int32_t s32;

} GTE_REG;

typedef struct _GTE_REGS {
	GTE_REG data[32];
	GTE_REG ctrl[32];
} GTE_REGS;

#pragma pack(pop)