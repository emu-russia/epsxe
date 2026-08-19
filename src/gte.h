/*
 * gte.h - Geometry Transformation Engine (GTE) definitions for PSX emulator
 *
 * Based on the GTE documentation from docs/gte.txt, verified against
 * PSXSPX (https://psx-spx.consoledev.net/) geometrytransformationenginegte.md
 * and gtepipelinetimings.md (issue #24).
 *
 */

#pragma once

/* --------------------------------------------------------------------------
 * Core GTE state structure
 * -------------------------------------------------------------------------- */

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
    GTE_REG data[32];   /* data registers 0..31 */
    GTE_REG ctrl[32];   /* control registers 0..31 (mapped 1:1 from hardware) */
} GTE_REGS;

#pragma pack(pop)

/* --------------------------------------------------------------------------
 * Data Register Index Enum (0..31)
 * -------------------------------------------------------------------------- */

typedef enum _GTEDataReg {
    GTE_DATA_VXY0   = 0,   /* V0 X (lo), Y (hi) */
    GTE_DATA_VZ0    = 1,   /* V0 Z */
    GTE_DATA_VXY1   = 2,   /* V1 X (lo), Y (hi) */
    GTE_DATA_VZ1    = 3,   /* V1 Z */
    GTE_DATA_VXY2   = 4,   /* V2 X (lo), Y (hi) */
    GTE_DATA_VZ2    = 5,   /* V2 Z */
    GTE_DATA_RGBC   = 6,   /* Color/code (R,G,B,CODE as bytes) */
    GTE_DATA_OTZ    = 7,   /* Average Z (unsigned 16-bit) */
    GTE_DATA_IR0    = 8,   /* Interpolation factor (signed 16-bit) */
    GTE_DATA_IR1    = 9,   /* Interpolation register 1 (signed 16-bit) */
    GTE_DATA_IR2    = 10,  /* Interpolation register 2 (signed 16-bit) */
    GTE_DATA_IR3    = 11,  /* Interpolation register 3 (signed 16-bit) */
    GTE_DATA_SXY0   = 12,  /* Screen XY FIFO 0 (oldest) – SX0 lo, SY0 hi */
    GTE_DATA_SXY1   = 13,  /* Screen XY FIFO 1 – SX1 lo, SY1 hi */
    GTE_DATA_SXY2   = 14,  /* Screen XY FIFO 2 (newest) – SX2 lo, SY2 hi */
    GTE_DATA_SXYP   = 15,  /* Mirror of SXY2 with move-on-write – SXP lo, SYP hi */
    GTE_DATA_SZ0    = 16,  /* Screen Z FIFO 0 (oldest) – unsigned 16-bit */
    GTE_DATA_SZ1    = 17,  /* Screen Z FIFO 1 */
    GTE_DATA_SZ2    = 18,  /* Screen Z FIFO 2 */
    GTE_DATA_SZ3    = 19,  /* Screen Z FIFO 3 (newest) */
    GTE_DATA_RGB0   = 20,  /* Color FIFO 0 – R,G,B,CODE as bytes */
    GTE_DATA_RGB1   = 21,  /* Color FIFO 1 */
    GTE_DATA_RGB2   = 22,  /* Color FIFO 2 */
    GTE_DATA_RES1   = 23,  /* Reserved / unused FIFO stage */
    GTE_DATA_MAC0   = 24,  /* Accumulator 0 (signed 32-bit) */
    GTE_DATA_MAC1   = 25,  /* Accumulator 1 (signed 32-bit) */
    GTE_DATA_MAC2   = 26,  /* Accumulator 2 (signed 32-bit) */
    GTE_DATA_MAC3   = 27,  /* Accumulator 3 (signed 32-bit) */
    GTE_DATA_IRGB   = 28,  /* Color conversion input (15-bit RGB) */
    GTE_DATA_ORGB   = 29,  /* Color conversion output (15-bit RGB) */
    GTE_DATA_LZCS   = 30,  /* Leading Zero Count Source */
    GTE_DATA_LZCR   = 31   /* Leading Zero Count Result */
} GTEDataReg;

/* --------------------------------------------------------------------------
 * Control Register Index Enum (0..31) – these map directly to the ctrl[] array
 * -------------------------------------------------------------------------- */

typedef enum _GTECtrlReg {
    GTE_CTRL_RT11_RT12 = 0,   /* RT11 (lo), RT12 (hi) */
    GTE_CTRL_RT13_RT21 = 1,   /* RT13 (lo), RT21 (hi) */
    GTE_CTRL_RT22_RT23 = 2,   /* RT22 (lo), RT23 (hi) */
    GTE_CTRL_RT31_RT32 = 3,   /* RT31 (lo), RT32 (hi) */
    GTE_CTRL_RT33      = 4,   /* RT33 (full 16-bit, sign-extended on read) */
    GTE_CTRL_TRX       = 5,   /* Translation X (signed 32-bit) */
    GTE_CTRL_TRY       = 6,   /* Translation Y */
    GTE_CTRL_TRZ       = 7,   /* Translation Z */
    GTE_CTRL_L11_L12   = 8,   /* L11 (lo), L12 (hi) */
    GTE_CTRL_L13_L21   = 9,   /* L13 (lo), L21 (hi) */
    GTE_CTRL_L22_L23   = 10,  /* L22 (lo), L23 (hi) */
    GTE_CTRL_L31_L32   = 11,  /* L31 (lo), L32 (hi) */
    GTE_CTRL_L33       = 12,  /* L33 (full 16-bit, sign-extended) */
    GTE_CTRL_RBK       = 13,  /* Background red (signed 32-bit) */
    GTE_CTRL_GBK       = 14,  /* Background green */
    GTE_CTRL_BBK       = 15,  /* Background blue */
    GTE_CTRL_LR1_LR2   = 16,  /* LR1 (lo), LR2 (hi) */
    GTE_CTRL_LR3_LG1   = 17,  /* LR3 (lo), LG1 (hi) */
    GTE_CTRL_LG2_LG3   = 18,  /* LG2 (lo), LG3 (hi) */
    GTE_CTRL_LB1_LB2   = 19,  /* LB1 (lo), LB2 (hi) */
    GTE_CTRL_LB3       = 20,  /* LB3 (full 16-bit, sign-extended) */
    GTE_CTRL_RFC       = 21,  /* Far red (signed 32-bit) */
    GTE_CTRL_GFC       = 22,  /* Far green */
    GTE_CTRL_BFC       = 23,  /* Far blue */
    GTE_CTRL_OFX       = 24,  /* Screen offset X (signed 32-bit) */
    GTE_CTRL_OFY       = 25,  /* Screen offset Y */
    GTE_CTRL_H         = 26,  /* Projection plane distance (unsigned 16-bit) – read bug */
    GTE_CTRL_DQA       = 27,  /* Depth queuing A (signed 16-bit) */
    GTE_CTRL_DQB       = 28,  /* Depth queuing B (signed 32-bit) */
    GTE_CTRL_ZSF3      = 29,  /* Z scale factor 3 (signed 16-bit) */
    GTE_CTRL_ZSF4      = 30,  /* Z scale factor 4 (signed 16-bit) */
    GTE_CTRL_FLAG      = 31   /* FLAG register (32-bit) */
} GTECtrlReg;

/* --------------------------------------------------------------------------
 * Fake Command Enum (bits 20-24) – ignored by hardware, used for SDK ordering
 * -------------------------------------------------------------------------- */

typedef enum _GTEFakeCommand {
    GTE_FAKE_UNUSED_00   = 0x00,   /* Reserved */
    GTE_FAKE_RTPS        = 0x01,   /* RTPS */
    GTE_FAKE_RTPT        = 0x02,   /* RTPT */
    GTE_FAKE_UNUSED_03   = 0x03,
    GTE_FAKE_MVMVA       = 0x04,   /* MVMVA */
    GTE_FAKE_UNUSED_05   = 0x05,
    GTE_FAKE_DCPL        = 0x06,   /* DCPL */
    GTE_FAKE_DPCS        = 0x07,   /* DPCS */
    GTE_FAKE_DPCT        = 0x08,   /* DPCT (SDK accidentally uses 0Fh here, same as NCDT) */
    GTE_FAKE_INTPL       = 0x09,   /* INTPL */
    GTE_FAKE_SQR         = 0x0A,   /* SQR */
    GTE_FAKE_UNUSED_0B   = 0x0B,
    GTE_FAKE_NCS         = 0x0C,   /* NCS */
    GTE_FAKE_NCT         = 0x0D,   /* NCT */
    GTE_FAKE_NCDS        = 0x0E,   /* NCDS */
    GTE_FAKE_NCDT        = 0x0F,   /* NCDT */
    GTE_FAKE_NCCS        = 0x10,   /* NCCS */
    GTE_FAKE_NCCT        = 0x11,   /* NCCT */
    GTE_FAKE_CDP         = 0x12,   /* CDP */
    GTE_FAKE_CC          = 0x13,   /* CC */
    GTE_FAKE_NCLIP       = 0x14,   /* NCLIP */
    GTE_FAKE_AVSZ3       = 0x15,   /* AVSZ3 */
    GTE_FAKE_AVSZ4       = 0x16,   /* AVSZ4 */
    GTE_FAKE_OP          = 0x17,   /* OP */
    GTE_FAKE_UNUSED_18   = 0x18,
    GTE_FAKE_GPF         = 0x19,   /* GPF */
    GTE_FAKE_GPL         = 0x1A,   /* GPL */
    GTE_FAKE_UNUSED_1B   = 0x1B,
    GTE_FAKE_UNUSED_1C   = 0x1C,
    GTE_FAKE_UNUSED_1D   = 0x1D,
    GTE_FAKE_UNUSED_1E   = 0x1E,
    GTE_FAKE_UNUSED_1F   = 0x1F
} GTEFakeCommand;

/* --------------------------------------------------------------------------
 * COP2 Instruction Encoding (25-bit immediate field)
 * -------------------------------------------------------------------------- */

#define GTE_COP2_OPCODE       0x4A000000U   /* bits 31-25: 0100101, rest zero */
#define GTE_CMD_FAKE_MASK     0x1F000000U   /* bits 20-24: fake command (ignored) */
#define GTE_CMD_FAKE_SHIFT    24
#define GTE_CMD_SF_MASK       0x00080000U   /* bit 19: shift fraction (0/1 for 12-bit) */
#define GTE_CMD_SF_SHIFT      19
#define GTE_CMD_MVMVA_MX_MASK 0x00060000U   /* bits 17-18: matrix select */
#define GTE_CMD_MVMVA_MX_SHIFT 17
#define GTE_CMD_MVMVA_V_MASK  0x00018000U   /* bits 15-16: vector select */
#define GTE_CMD_MVMVA_V_SHIFT 15
#define GTE_CMD_MVMVA_CV_MASK 0x00006000U   /* bits 13-14: translation select */
#define GTE_CMD_MVMVA_CV_SHIFT 13
#define GTE_CMD_LM_MASK       0x00000400U   /* bit 10: saturation mode (0=±7FFF, 1=0..7FFF) */
#define GTE_CMD_LM_SHIFT      10
#define GTE_CMD_REAL_MASK     0x0000003FU   /* bits 0-5: real GTE command */
#define GTE_CMD_REAL_SHIFT    0

/* MVMVA matrix selection values */
#define GTE_MVMVA_MX_ROTATION 0   /* Rotation matrix (RT) */
#define GTE_MVMVA_MX_LIGHT    1   /* Light matrix (LLM) */
#define GTE_MVMVA_MX_COLOR    2   /* Color matrix (LCM) */
#define GTE_MVMVA_MX_RESERVED 3   /* Garbage matrix (buggy) */

/* MVMVA vector selection values */
#define GTE_MVMVA_V_V0        0   /* V0 */
#define GTE_MVMVA_V_V1        1   /* V1 */
#define GTE_MVMVA_V_V2        2   /* V2 */
#define GTE_MVMVA_V_IR        3   /* IR1,IR2,IR3 */

/* MVMVA translation selection values */
#define GTE_MVMVA_CV_TR       0   /* Translation vector (TR) */
#define GTE_MVMVA_CV_BK       1   /* Background color (BK) */
#define GTE_MVMVA_CV_FC       2   /* Far color (FC) - buggy */
#define GTE_MVMVA_CV_NONE     3   /* No translation */

/* --------------------------------------------------------------------------
 * GTE Real Commands (bits 0-5 of instruction)
 * -------------------------------------------------------------------------- */

typedef enum _GTERealCommand {
    GTE_CMD_RTPS   = 0x01,   /* 15 cycles */
    GTE_CMD_NCLIP  = 0x06,   /* 8 cycles */
    GTE_CMD_OP     = 0x0C,   /* 6 cycles */
    GTE_CMD_DPCS   = 0x10,   /* 8 cycles */
    GTE_CMD_INTPL  = 0x11,   /* 8 cycles */
    GTE_CMD_MVMVA  = 0x12,   /* 8 cycles */
    GTE_CMD_NCDS   = 0x13,   /* 19 cycles */
    GTE_CMD_CDP    = 0x14,   /* 13 cycles */
    GTE_CMD_NCDT   = 0x16,   /* 44 cycles */
    GTE_CMD_NCCS   = 0x1B,   /* 17 cycles */
    GTE_CMD_CC     = 0x1C,   /* 11 cycles */
    GTE_CMD_NCS    = 0x1E,   /* 14 cycles */
    GTE_CMD_NCT    = 0x20,   /* 30 cycles */
    GTE_CMD_SQR    = 0x28,   /* 5 cycles */
    GTE_CMD_DCPL   = 0x29,   /* 8 cycles */
    GTE_CMD_DPCT   = 0x2A,   /* 17 cycles */
    GTE_CMD_AVSZ3  = 0x2D,   /* 5 cycles */
    GTE_CMD_AVSZ4  = 0x2E,   /* 6 cycles */
    GTE_CMD_RTPT   = 0x30,   /* 23 cycles */
    GTE_CMD_GPF    = 0x3D,   /* 5 cycles */
    GTE_CMD_GPL    = 0x3E,   /* 5 cycles */
    GTE_CMD_NCCT   = 0x3F    /* 39 cycles */
} GTERealCommand;

/* --------------------------------------------------------------------------
 * FLAG Register (control index 31) Bit Definitions
 * -------------------------------------------------------------------------- */

#define GTE_FLAG_ERROR          (1U << 31)  /* OR of bits 30-23 and 18-13 */
#define GTE_FLAG_MAC1_POS_OVF   (1U << 30)  /* positive 44-bit overflow */
#define GTE_FLAG_MAC2_POS_OVF   (1U << 29)
#define GTE_FLAG_MAC3_POS_OVF   (1U << 28)
#define GTE_FLAG_MAC1_NEG_OVF   (1U << 27)  /* negative 44-bit overflow */
#define GTE_FLAG_MAC2_NEG_OVF   (1U << 26)
#define GTE_FLAG_MAC3_NEG_OVF   (1U << 25)
#define GTE_FLAG_IR1_SAT        (1U << 24)  /* IR1 saturated */
#define GTE_FLAG_IR2_SAT        (1U << 23)  /* IR2 saturated */
#define GTE_FLAG_IR3_SAT        (1U << 22)  /* IR3 saturated */
#define GTE_FLAG_RGB_R_SAT      (1U << 21)  /* Color FIFO red saturated */
#define GTE_FLAG_RGB_G_SAT      (1U << 20)  /* Color FIFO green saturated */
#define GTE_FLAG_RGB_B_SAT      (1U << 19)  /* Color FIFO blue saturated */
#define GTE_FLAG_SZ3_OTZ_SAT    (1U << 18)  /* SZ3 or OTZ saturated to 0..FFFF */
#define GTE_FLAG_DIV_OVF        (1U << 17)  /* divide overflow */
#define GTE_FLAG_MAC0_POS_OVF   (1U << 16)  /* MAC0 positive 32-bit overflow */
#define GTE_FLAG_MAC0_NEG_OVF   (1U << 15)  /* MAC0 negative 32-bit overflow */
#define GTE_FLAG_SX2_SAT        (1U << 14)  /* SX2 saturated to -400..+3FF */
#define GTE_FLAG_SY2_SAT        (1U << 13)  /* SY2 saturated */
#define GTE_FLAG_IR0_SAT        (1U << 12)  /* IR0 saturated to 0..1000 */

/* --------------------------------------------------------------------------
 * Convenience macros for reading/writing individual GTE registers
 * All access is direct to data[] or ctrl[] arrays using the enums above.
 * -------------------------------------------------------------------------- */

/* ---- Helper to extract signed/unsigned 16-bit halves from a 32-bit value ---- */
#define GTE_LO16(val)   ((int16_t)((val) & 0xFFFF))
#define GTE_LO16U(val)  ((uint16_t)((val) & 0xFFFF))
#define GTE_HI16(val)   ((int16_t)((val) >> 16))
#define GTE_HI16U(val)  ((uint16_t)((val) >> 16))
#define GTE_MAKE32(lo, hi) (((uint32_t)(hi) << 16) | ((uint32_t)(lo) & 0xFFFF))

/* ---- Data registers (0..31) ---- */

/* V0 */
#define GTE_VX0(gte)   ((gte)->data[GTE_DATA_VXY0].s16.lo)
#define GTE_VY0(gte)   ((gte)->data[GTE_DATA_VXY0].s16.hi)
#define GTE_VZ0(gte)   ((gte)->data[GTE_DATA_VZ0].s16.lo)

/* V1 */
#define GTE_VX1(gte)   ((gte)->data[GTE_DATA_VXY1].s16.lo)
#define GTE_VY1(gte)   ((gte)->data[GTE_DATA_VXY1].s16.hi)
#define GTE_VZ1(gte)   ((gte)->data[GTE_DATA_VZ1].s16.lo)

/* V2 */
#define GTE_VX2(gte)   ((gte)->data[GTE_DATA_VXY2].s16.lo)
#define GTE_VY2(gte)   ((gte)->data[GTE_DATA_VXY2].s16.hi)
#define GTE_VZ2(gte)   ((gte)->data[GTE_DATA_VZ2].s16.lo)

/* IR0..IR3 (signed 16-bit) – stored in lo, hi may be ignored */
#define GTE_IR0(gte)   ((gte)->data[GTE_DATA_IR0].s16.lo)
#define GTE_IR1(gte)   ((gte)->data[GTE_DATA_IR1].s16.lo)
#define GTE_IR2(gte)   ((gte)->data[GTE_DATA_IR2].s16.lo)
#define GTE_IR3(gte)   ((gte)->data[GTE_DATA_IR3].s16.lo)

/* Screen XY FIFO */
#define GTE_SX0(gte)   ((gte)->data[GTE_DATA_SXY0].s16.lo)
#define GTE_SY0(gte)   ((gte)->data[GTE_DATA_SXY0].s16.hi)
#define GTE_SX1(gte)   ((gte)->data[GTE_DATA_SXY1].s16.lo)
#define GTE_SY1(gte)   ((gte)->data[GTE_DATA_SXY1].s16.hi)
#define GTE_SX2(gte)   ((gte)->data[GTE_DATA_SXY2].s16.lo)
#define GTE_SY2(gte)   ((gte)->data[GTE_DATA_SXY2].s16.hi)
#define GTE_SXP(gte)   ((gte)->data[GTE_DATA_SXYP].s16.lo)
#define GTE_SYP(gte)   ((gte)->data[GTE_DATA_SXYP].s16.hi)

/* Screen Z FIFO (unsigned 16-bit) */
#define GTE_SZ0(gte)   ((gte)->data[GTE_DATA_SZ0].u16.lo)
#define GTE_SZ1(gte)   ((gte)->data[GTE_DATA_SZ1].u16.lo)
#define GTE_SZ2(gte)   ((gte)->data[GTE_DATA_SZ2].u16.lo)
#define GTE_SZ3(gte)   ((gte)->data[GTE_DATA_SZ3].u16.lo)

/* MAC0..MAC3 (signed 32-bit) */
#define GTE_MAC0(gte)  ((gte)->data[GTE_DATA_MAC0].s32)
#define GTE_MAC1(gte)  ((gte)->data[GTE_DATA_MAC1].s32)
#define GTE_MAC2(gte)  ((gte)->data[GTE_DATA_MAC2].s32)
#define GTE_MAC3(gte)  ((gte)->data[GTE_DATA_MAC3].s32)

/* OTZ (unsigned 16-bit) */
#define GTE_OTZ(gte)   ((gte)->data[GTE_DATA_OTZ].u16.lo)

/* Color FIFO (RGB0, RGB1, RGB2) – each byte is 8-bit */
#define GTE_RGB0_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_RGB0].u32 & 0xFF))
#define GTE_RGB0_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB0].u32 >> 8) & 0xFF))
#define GTE_RGB0_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB0].u32 >> 16) & 0xFF))
#define GTE_RGB0_C(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB0].u32 >> 24) & 0xFF))

#define GTE_RGB1_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_RGB1].u32 & 0xFF))
#define GTE_RGB1_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB1].u32 >> 8) & 0xFF))
#define GTE_RGB1_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB1].u32 >> 16) & 0xFF))
#define GTE_RGB1_C(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB1].u32 >> 24) & 0xFF))

#define GTE_RGB2_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_RGB2].u32 & 0xFF))
#define GTE_RGB2_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB2].u32 >> 8) & 0xFF))
#define GTE_RGB2_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB2].u32 >> 16) & 0xFF))
#define GTE_RGB2_C(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGB2].u32 >> 24) & 0xFF))

/* IRGB – 15-bit RGB packed in bits 0-14 */
#define GTE_IRGB_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_IRGB].u32 & 0x1F))
#define GTE_IRGB_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_IRGB].u32 >> 5) & 0x1F))
#define GTE_IRGB_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_IRGB].u32 >> 10) & 0x1F))

/* ORGB – read-only mirror of IRGB (but we treat it as separate) */
#define GTE_ORGB_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_ORGB].u32 & 0x1F))
#define GTE_ORGB_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_ORGB].u32 >> 5) & 0x1F))
#define GTE_ORGB_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_ORGB].u32 >> 10) & 0x1F))

/* LZCS/LZCR (signed 32-bit) */
#define GTE_LZCS(gte)   ((gte)->data[GTE_DATA_LZCS].s32)
#define GTE_LZCR(gte)   ((gte)->data[GTE_DATA_LZCR].s32)

/* RGBC – color/code as 4 bytes */
#define GTE_RGBC_R(gte)  ((uint8_t)((gte)->data[GTE_DATA_RGBC].u32 & 0xFF))
#define GTE_RGBC_G(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGBC].u32 >> 8) & 0xFF))
#define GTE_RGBC_B(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGBC].u32 >> 16) & 0xFF))
#define GTE_RGBC_C(gte)  ((uint8_t)(((gte)->data[GTE_DATA_RGBC].u32 >> 24) & 0xFF))

/* ---- Control registers (0..31) – direct ctrl[] access ---- */

/* Rotation matrix (RT) */
#define GTE_RT11(gte)  ((gte)->ctrl[GTE_CTRL_RT11_RT12].s16.lo)
#define GTE_RT12(gte)  ((gte)->ctrl[GTE_CTRL_RT11_RT12].s16.hi)
#define GTE_RT13(gte)  ((gte)->ctrl[GTE_CTRL_RT13_RT21].s16.lo)
#define GTE_RT21(gte)  ((gte)->ctrl[GTE_CTRL_RT13_RT21].s16.hi)
#define GTE_RT22(gte)  ((gte)->ctrl[GTE_CTRL_RT22_RT23].s16.lo)
#define GTE_RT23(gte)  ((gte)->ctrl[GTE_CTRL_RT22_RT23].s16.hi)
#define GTE_RT31(gte)  ((gte)->ctrl[GTE_CTRL_RT31_RT32].s16.lo)
#define GTE_RT32(gte)  ((gte)->ctrl[GTE_CTRL_RT31_RT32].s16.hi)
#define GTE_RT33(gte)  ((int32_t)(int16_t)((gte)->ctrl[GTE_CTRL_RT33].u16.lo))

/* Light matrix (LLM) */
#define GTE_L11(gte)   ((gte)->ctrl[GTE_CTRL_L11_L12].s16.lo)
#define GTE_L12(gte)   ((gte)->ctrl[GTE_CTRL_L11_L12].s16.hi)
#define GTE_L13(gte)   ((gte)->ctrl[GTE_CTRL_L13_L21].s16.lo)
#define GTE_L21(gte)   ((gte)->ctrl[GTE_CTRL_L13_L21].s16.hi)
#define GTE_L22(gte)   ((gte)->ctrl[GTE_CTRL_L22_L23].s16.lo)
#define GTE_L23(gte)   ((gte)->ctrl[GTE_CTRL_L22_L23].s16.hi)
#define GTE_L31(gte)   ((gte)->ctrl[GTE_CTRL_L31_L32].s16.lo)
#define GTE_L32(gte)   ((gte)->ctrl[GTE_CTRL_L31_L32].s16.hi)
#define GTE_L33(gte)   ((int32_t)(int16_t)((gte)->ctrl[GTE_CTRL_L33].u16.lo))

/* Light Color matrix (LCM) */
#define GTE_LR1(gte)   ((gte)->ctrl[GTE_CTRL_LR1_LR2].s16.lo)
#define GTE_LR2(gte)   ((gte)->ctrl[GTE_CTRL_LR1_LR2].s16.hi)
#define GTE_LR3(gte)   ((gte)->ctrl[GTE_CTRL_LR3_LG1].s16.lo)
#define GTE_LG1(gte)   ((gte)->ctrl[GTE_CTRL_LR3_LG1].s16.hi)
#define GTE_LG2(gte)   ((gte)->ctrl[GTE_CTRL_LG2_LG3].s16.lo)
#define GTE_LG3(gte)   ((gte)->ctrl[GTE_CTRL_LG2_LG3].s16.hi)
#define GTE_LB1(gte)   ((gte)->ctrl[GTE_CTRL_LB1_LB2].s16.lo)
#define GTE_LB2(gte)   ((gte)->ctrl[GTE_CTRL_LB1_LB2].s16.hi)
#define GTE_LB3(gte)   ((int32_t)(int16_t)((gte)->ctrl[GTE_CTRL_LB3].u16.lo))

/* Translation vector (TR) – full 32-bit signed */
#define GTE_TRX(gte)   ((gte)->ctrl[GTE_CTRL_TRX].s32)
#define GTE_TRY(gte)   ((gte)->ctrl[GTE_CTRL_TRY].s32)
#define GTE_TRZ(gte)   ((gte)->ctrl[GTE_CTRL_TRZ].s32)

/* Background color (BK) – full 32-bit signed */
#define GTE_RBK(gte)   ((gte)->ctrl[GTE_CTRL_RBK].s32)
#define GTE_GBK(gte)   ((gte)->ctrl[GTE_CTRL_GBK].s32)
#define GTE_BBK(gte)   ((gte)->ctrl[GTE_CTRL_BBK].s32)

/* Far color (FC) – full 32-bit signed */
#define GTE_RFC(gte)   ((gte)->ctrl[GTE_CTRL_RFC].s32)
#define GTE_GFC(gte)   ((gte)->ctrl[GTE_CTRL_GFC].s32)
#define GTE_BFC(gte)   ((gte)->ctrl[GTE_CTRL_BFC].s32)

/* Screen offset (OFX, OFY) – full 32-bit signed */
#define GTE_OFX(gte)   ((gte)->ctrl[GTE_CTRL_OFX].s32)
#define GTE_OFY(gte)   ((gte)->ctrl[GTE_CTRL_OFY].s32)

/* H – unsigned 16-bit (but read has sign-extension bug; we provide raw access) */
#define GTE_H_RAW(gte) ((gte)->ctrl[GTE_CTRL_H].u16.lo)
/* For emulation, if you need to emulate the read bug, use: */
#define GTE_H_READ(gte) ((int32_t)(int16_t)((gte)->ctrl[GTE_CTRL_H].u16.lo)) /* sign-extends even though it's unsigned */

/* DQA – signed 16-bit (stored in lo) */
#define GTE_DQA(gte)   ((gte)->ctrl[GTE_CTRL_DQA].s16.lo)

/* DQB – full 32-bit signed */
#define GTE_DQB(gte)   ((gte)->ctrl[GTE_CTRL_DQB].s32)

/* Z scale factors – signed 16-bit (stored in lo) */
#define GTE_ZSF3(gte)  ((gte)->ctrl[GTE_CTRL_ZSF3].s16.lo)
#define GTE_ZSF4(gte)  ((gte)->ctrl[GTE_CTRL_ZSF4].s16.lo)

/* FLAG – full 32-bit */
#define GTE_FLAG(gte)  ((gte)->ctrl[GTE_CTRL_FLAG].u32)

/* --------------------------------------------------------------------------
 * Writing macros (for setting registers)
 * -------------------------------------------------------------------------- */

/* Data registers write */
#define GTE_SET_VX0(gte, val)  ((gte)->data[GTE_DATA_VXY0].s16.lo = (int16_t)(val))
#define GTE_SET_VY0(gte, val)  ((gte)->data[GTE_DATA_VXY0].s16.hi = (int16_t)(val))
#define GTE_SET_VZ0(gte, val)  ((gte)->data[GTE_DATA_VZ0].s16.lo = (int16_t)(val))
#define GTE_SET_VX1(gte, val)  ((gte)->data[GTE_DATA_VXY1].s16.lo = (int16_t)(val))
#define GTE_SET_VY1(gte, val)  ((gte)->data[GTE_DATA_VXY1].s16.hi = (int16_t)(val))
#define GTE_SET_VZ1(gte, val)  ((gte)->data[GTE_DATA_VZ1].s16.lo = (int16_t)(val))
#define GTE_SET_VX2(gte, val)  ((gte)->data[GTE_DATA_VXY2].s16.lo = (int16_t)(val))
#define GTE_SET_VY2(gte, val)  ((gte)->data[GTE_DATA_VXY2].s16.hi = (int16_t)(val))
#define GTE_SET_VZ2(gte, val)  ((gte)->data[GTE_DATA_VZ2].s16.lo = (int16_t)(val))

#define GTE_SET_IR0(gte, val)  ((gte)->data[GTE_DATA_IR0].s16.lo = (int16_t)(val))
#define GTE_SET_IR1(gte, val)  ((gte)->data[GTE_DATA_IR1].s16.lo = (int16_t)(val))
#define GTE_SET_IR2(gte, val)  ((gte)->data[GTE_DATA_IR2].s16.lo = (int16_t)(val))
#define GTE_SET_IR3(gte, val)  ((gte)->data[GTE_DATA_IR3].s16.lo = (int16_t)(val))

#define GTE_SET_SX0(gte, val)  ((gte)->data[GTE_DATA_SXY0].s16.lo = (int16_t)(val))
#define GTE_SET_SY0(gte, val)  ((gte)->data[GTE_DATA_SXY0].s16.hi = (int16_t)(val))
#define GTE_SET_SX1(gte, val)  ((gte)->data[GTE_DATA_SXY1].s16.lo = (int16_t)(val))
#define GTE_SET_SY1(gte, val)  ((gte)->data[GTE_DATA_SXY1].s16.hi = (int16_t)(val))
#define GTE_SET_SX2(gte, val)  ((gte)->data[GTE_DATA_SXY2].s16.lo = (int16_t)(val))
#define GTE_SET_SY2(gte, val)  ((gte)->data[GTE_DATA_SXY2].s16.hi = (int16_t)(val))
#define GTE_SET_SXP(gte, val)  ((gte)->data[GTE_DATA_SXYP].s16.lo = (int16_t)(val))
#define GTE_SET_SYP(gte, val)  ((gte)->data[GTE_DATA_SXYP].s16.hi = (int16_t)(val))

#define GTE_SET_SZ0(gte, val)  ((gte)->data[GTE_DATA_SZ0].u16.lo = (uint16_t)(val))
#define GTE_SET_SZ1(gte, val)  ((gte)->data[GTE_DATA_SZ1].u16.lo = (uint16_t)(val))
#define GTE_SET_SZ2(gte, val)  ((gte)->data[GTE_DATA_SZ2].u16.lo = (uint16_t)(val))
#define GTE_SET_SZ3(gte, val)  ((gte)->data[GTE_DATA_SZ3].u16.lo = (uint16_t)(val))

#define GTE_SET_MAC0(gte, val) ((gte)->data[GTE_DATA_MAC0].s32 = (int32_t)(val))
#define GTE_SET_MAC1(gte, val) ((gte)->data[GTE_DATA_MAC1].s32 = (int32_t)(val))
#define GTE_SET_MAC2(gte, val) ((gte)->data[GTE_DATA_MAC2].s32 = (int32_t)(val))
#define GTE_SET_MAC3(gte, val) ((gte)->data[GTE_DATA_MAC3].s32 = (int32_t)(val))

#define GTE_SET_OTZ(gte, val)  ((gte)->data[GTE_DATA_OTZ].u16.lo = (uint16_t)(val))
#define GTE_SET_RGBC(gte, r,g,b,c) do { (gte)->data[GTE_DATA_RGBC].u32 = ((c)<<24)|((b)<<16)|((g)<<8)|(r); } while(0)
#define GTE_SET_IRGB(gte, r,g,b) do { (gte)->data[GTE_DATA_IRGB].u32 = ((b)<<10)|((g)<<5)|(r); } while(0)
#define GTE_SET_LZCS(gte, val) ((gte)->data[GTE_DATA_LZCS].s32 = (int32_t)(val))

/* Control registers write */
#define GTE_SET_RT11(gte, val) ((gte)->ctrl[GTE_CTRL_RT11_RT12].s16.lo = (int16_t)(val))
#define GTE_SET_RT12(gte, val) ((gte)->ctrl[GTE_CTRL_RT11_RT12].s16.hi = (int16_t)(val))
#define GTE_SET_RT13(gte, val) ((gte)->ctrl[GTE_CTRL_RT13_RT21].s16.lo = (int16_t)(val))
#define GTE_SET_RT21(gte, val) ((gte)->ctrl[GTE_CTRL_RT13_RT21].s16.hi = (int16_t)(val))
#define GTE_SET_RT22(gte, val) ((gte)->ctrl[GTE_CTRL_RT22_RT23].s16.lo = (int16_t)(val))
#define GTE_SET_RT23(gte, val) ((gte)->ctrl[GTE_CTRL_RT22_RT23].s16.hi = (int16_t)(val))
#define GTE_SET_RT31(gte, val) ((gte)->ctrl[GTE_CTRL_RT31_RT32].s16.lo = (int16_t)(val))
#define GTE_SET_RT32(gte, val) ((gte)->ctrl[GTE_CTRL_RT31_RT32].s16.hi = (int16_t)(val))
#define GTE_SET_RT33(gte, val) ((gte)->ctrl[GTE_CTRL_RT33].u16.lo = (uint16_t)(val))

#define GTE_SET_TRX(gte, val)  ((gte)->ctrl[GTE_CTRL_TRX].s32 = (int32_t)(val))
#define GTE_SET_TRY(gte, val)  ((gte)->ctrl[GTE_CTRL_TRY].s32 = (int32_t)(val))
#define GTE_SET_TRZ(gte, val)  ((gte)->ctrl[GTE_CTRL_TRZ].s32 = (int32_t)(val))

#define GTE_SET_L11(gte, val)  ((gte)->ctrl[GTE_CTRL_L11_L12].s16.lo = (int16_t)(val))
#define GTE_SET_L12(gte, val)  ((gte)->ctrl[GTE_CTRL_L11_L12].s16.hi = (int16_t)(val))
#define GTE_SET_L13(gte, val)  ((gte)->ctrl[GTE_CTRL_L13_L21].s16.lo = (int16_t)(val))
#define GTE_SET_L21(gte, val)  ((gte)->ctrl[GTE_CTRL_L13_L21].s16.hi = (int16_t)(val))
#define GTE_SET_L22(gte, val)  ((gte)->ctrl[GTE_CTRL_L22_L23].s16.lo = (int16_t)(val))
#define GTE_SET_L23(gte, val)  ((gte)->ctrl[GTE_CTRL_L22_L23].s16.hi = (int16_t)(val))
#define GTE_SET_L31(gte, val)  ((gte)->ctrl[GTE_CTRL_L31_L32].s16.lo = (int16_t)(val))
#define GTE_SET_L32(gte, val)  ((gte)->ctrl[GTE_CTRL_L31_L32].s16.hi = (int16_t)(val))
#define GTE_SET_L33(gte, val)  ((gte)->ctrl[GTE_CTRL_L33].u16.lo = (uint16_t)(val))

#define GTE_SET_RBK(gte, val)  ((gte)->ctrl[GTE_CTRL_RBK].s32 = (int32_t)(val))
#define GTE_SET_GBK(gte, val)  ((gte)->ctrl[GTE_CTRL_GBK].s32 = (int32_t)(val))
#define GTE_SET_BBK(gte, val)  ((gte)->ctrl[GTE_CTRL_BBK].s32 = (int32_t)(val))

#define GTE_SET_LR1(gte, val)  ((gte)->ctrl[GTE_CTRL_LR1_LR2].s16.lo = (int16_t)(val))
#define GTE_SET_LR2(gte, val)  ((gte)->ctrl[GTE_CTRL_LR1_LR2].s16.hi = (int16_t)(val))
#define GTE_SET_LR3(gte, val)  ((gte)->ctrl[GTE_CTRL_LR3_LG1].s16.lo = (int16_t)(val))
#define GTE_SET_LG1(gte, val)  ((gte)->ctrl[GTE_CTRL_LR3_LG1].s16.hi = (int16_t)(val))
#define GTE_SET_LG2(gte, val)  ((gte)->ctrl[GTE_CTRL_LG2_LG3].s16.lo = (int16_t)(val))
#define GTE_SET_LG3(gte, val)  ((gte)->ctrl[GTE_CTRL_LG2_LG3].s16.hi = (int16_t)(val))
#define GTE_SET_LB1(gte, val)  ((gte)->ctrl[GTE_CTRL_LB1_LB2].s16.lo = (int16_t)(val))
#define GTE_SET_LB2(gte, val)  ((gte)->ctrl[GTE_CTRL_LB1_LB2].s16.hi = (int16_t)(val))
#define GTE_SET_LB3(gte, val)  ((gte)->ctrl[GTE_CTRL_LB3].u16.lo = (uint16_t)(val))

#define GTE_SET_RFC(gte, val)  ((gte)->ctrl[GTE_CTRL_RFC].s32 = (int32_t)(val))
#define GTE_SET_GFC(gte, val)  ((gte)->ctrl[GTE_CTRL_GFC].s32 = (int32_t)(val))
#define GTE_SET_BFC(gte, val)  ((gte)->ctrl[GTE_CTRL_BFC].s32 = (int32_t)(val))

#define GTE_SET_OFX(gte, val)  ((gte)->ctrl[GTE_CTRL_OFX].s32 = (int32_t)(val))
#define GTE_SET_OFY(gte, val)  ((gte)->ctrl[GTE_CTRL_OFY].s32 = (int32_t)(val))
#define GTE_SET_H(gte, val)    ((gte)->ctrl[GTE_CTRL_H].u16.lo = (uint16_t)(val))
#define GTE_SET_DQA(gte, val)  ((gte)->ctrl[GTE_CTRL_DQA].s16.lo = (int16_t)(val))
#define GTE_SET_DQB(gte, val)  ((gte)->ctrl[GTE_CTRL_DQB].s32 = (int32_t)(val))
#define GTE_SET_ZSF3(gte, val) ((gte)->ctrl[GTE_CTRL_ZSF3].s16.lo = (int16_t)(val))
#define GTE_SET_ZSF4(gte, val) ((gte)->ctrl[GTE_CTRL_ZSF4].s16.lo = (int16_t)(val))
#define GTE_SET_FLAG(gte, val) ((gte)->ctrl[GTE_CTRL_FLAG].u32 = (uint32_t)(val))

/* --------------------------------------------------------------------------
 * Instruction construction macros
 * -------------------------------------------------------------------------- */

/* Build a complete COP2 immediate instruction word */
#define GTE_BUILD_CMD(real, sf, lm, mvmva_mx, mvmva_v, mvmva_cv) \
    (GTE_COP2_OPCODE | \
     ((uint32_t)(real) & GTE_CMD_REAL_MASK) | \
     (((uint32_t)(sf) & 1) << GTE_CMD_SF_SHIFT) | \
     (((uint32_t)(lm) & 1) << GTE_CMD_LM_SHIFT) | \
     (((uint32_t)(mvmva_mx) & 3) << GTE_CMD_MVMVA_MX_SHIFT) | \
     (((uint32_t)(mvmva_v) & 3) << GTE_CMD_MVMVA_V_SHIFT) | \
     (((uint32_t)(mvmva_cv) & 3) << GTE_CMD_MVMVA_CV_SHIFT))

/* Set fake opcode (bits 20-24) – ignored by hardware */
#define GTE_FAKE_OPCODE(fake) (((uint32_t)(fake) & 0x1F) << 24)

/* Combine real command and fake for convenience */
#define GTE_CMD_WITH_FAKE(real, fake) (GTE_BUILD_CMD(real, 0, 0, 0, 0, 0) | GTE_FAKE_OPCODE(fake))

/* --------------------------------------------------------------------------
 * Predefined instructions for commonly used commands (with typical sf/lm)
 * -------------------------------------------------------------------------- */

/* NOTE: The fake code in these macros is the one from the sorted table.
 * The hardware ignores it, but it's used by some SDK tools. */

#define GTE_INSTR_RTPS   GTE_BUILD_CMD(GTE_CMD_RTPS, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_RTPS)
#define GTE_INSTR_RTPT   GTE_BUILD_CMD(GTE_CMD_RTPT, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_RTPT)
#define GTE_INSTR_MVMVA(sf, mx, v, cv, lm) (GTE_BUILD_CMD(GTE_CMD_MVMVA, sf, lm, mx, v, cv) | GTE_FAKE_OPCODE(GTE_FAKE_MVMVA))
#define GTE_INSTR_DCPL   GTE_BUILD_CMD(GTE_CMD_DCPL, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_DCPL)
#define GTE_INSTR_DPCS   GTE_BUILD_CMD(GTE_CMD_DPCS, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_DPCS)
#define GTE_INSTR_DPCT   GTE_BUILD_CMD(GTE_CMD_DPCT, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_DPCT)
#define GTE_INSTR_INTPL  GTE_BUILD_CMD(GTE_CMD_INTPL, 1, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_INTPL)
#define GTE_INSTR_SQR(sf) (GTE_BUILD_CMD(GTE_CMD_SQR, sf, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_SQR))
#define GTE_INSTR_NCS    GTE_BUILD_CMD(GTE_CMD_NCS, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCS)
#define GTE_INSTR_NCT    GTE_BUILD_CMD(GTE_CMD_NCT, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCT)
#define GTE_INSTR_NCDS   GTE_BUILD_CMD(GTE_CMD_NCDS, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCDS)
#define GTE_INSTR_NCDT   GTE_BUILD_CMD(GTE_CMD_NCDT, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCDT)
#define GTE_INSTR_NCCS   GTE_BUILD_CMD(GTE_CMD_NCCS, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCCS)
#define GTE_INSTR_NCCT   GTE_BUILD_CMD(GTE_CMD_NCCT, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCCT)
#define GTE_INSTR_CDP    GTE_BUILD_CMD(GTE_CMD_CDP, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_CDP)
#define GTE_INSTR_CC     GTE_BUILD_CMD(GTE_CMD_CC, 1, 1, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_CC)
#define GTE_INSTR_NCLIP  GTE_BUILD_CMD(GTE_CMD_NCLIP, 0, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_NCLIP)
#define GTE_INSTR_AVSZ3  GTE_BUILD_CMD(GTE_CMD_AVSZ3, 0, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_AVSZ3)
#define GTE_INSTR_AVSZ4  GTE_BUILD_CMD(GTE_CMD_AVSZ4, 0, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_AVSZ4)
#define GTE_INSTR_OP(sf) (GTE_BUILD_CMD(GTE_CMD_OP, sf, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_OP))
#define GTE_INSTR_GPF(sf) (GTE_BUILD_CMD(GTE_CMD_GPF, sf, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_GPF))
#define GTE_INSTR_GPL(sf) (GTE_BUILD_CMD(GTE_CMD_GPL, sf, 0, 0, 0, 0) | GTE_FAKE_OPCODE(GTE_FAKE_GPL))

void gte_exec_opcode();

/* Decompiled globals (previously generated in src/_gen) */
extern GTE_REGS gte_regs;

/* Function prototypes (previously generated in src/_gen) */
int gte_clear_regs();
int gte_freeze(const char *filename, int gz_file);
int gte_read_data_register(uint8_t index);
int gte_rtps();
int gte_rtpt();
int gte_unfreeze(int unused, uint32_t *gz_file);
GTE_REG gte_write_data_register(uint8_t index, GTE_REG value);
