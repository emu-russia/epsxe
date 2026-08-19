/**
 * \file psxdefs.h
 * \brief PlayStation hardware register and memory map definitions.
 *
 * Reference:
 *  - "Memory_Layout.pdf" (PSX memory map and I/O registers)
 *  - PSXSPX (https://psx-spx.consoledev.net/) - verified against
 *    memorymap.md, iomap.md, memorycontrol.md, soundprocessingunitspu.md,
 *    graphicsprocessingunitgpu.md, macroblockdecodermdec.md, cdromdrive.md,
 *    expansionportpio.md (issue #24)
 *
 * All addresses are physical addresses as used by the PlayStation.
 *
 * This file provides:
 *  - Memory map constants (RAM, BIOS, EXP1, Scratch, I/O base)
 *  - Register definitions with full address and offset macros
 *  - Comments in English
 *
 * Prefix: PSX_REG_ for hardware registers, PSX_EXP1_ for the EXP1 expansion
 * ROM header, PSX_ for the memory map.
 */

#pragma once

/*==============================================================================
 * Memory Map
 *============================================================================*/

/* Main RAM (2 MB default, may be 4/8 MB on development units) */
#define PSX_RAM_BASE                0x00000000
#define PSX_RAM_SIZE                (2 * 1024 * 1024)   /* 2 MB */

/* Cached and uncached mirrors of RAM */
#define PSX_RAM_CACHED_BASE         0x80000000          /* cached access */
#define PSX_RAM_UNCACHED_BASE       0xA0000000          /* uncached access */

/* BIOS ROM (512 KB) */
#define PSX_BIOS_BASE               0x1FC00000
#define PSX_BIOS_UNCACHED_BASE      0xBFC00000
#define PSX_BIOS_SIZE               (0x80000)           /* 512 KB */

/* Expansion Region 1 (ROM/RAM) - holds the EXP1 expansion ROM header.
 * Note: loosely called "PIO region" in some older documentation. */
#define PSX_EXP1_BASE               0x1F000000

/* Scratchpad RAM (data cache) - 1 KB */
#define PSX_SCRATCH_BASE            0x1F800000
#define PSX_SCRATCH_SIZE            0x400               /* 1 KB */

/* Base of the hardware region: scratchpad at 0x1F800000, hardware I/O
 * ports at 0x1F801000..0x1F803FFF */
#define PSX_HW_BASE                 0x1F800000

/*==============================================================================
 * EXP1 Expansion ROM Header (at 1F000000h)
 *============================================================================*/

/* Post-Boot Entrypoint - called by the BIOS after the "PS" logo, if the
 * Post-Boot ID string is present (return address in R31). */
#define PSX_EXP1_MAIN_OFS           0x0000
#define PSX_EXP1_MAIN               (PSX_EXP1_BASE + PSX_EXP1_MAIN_OFS)

/* Post-Boot ID string: "Licensed by Sony Computer Entertainment Inc." */
#define PSX_EXP1_LICENSE1_OFS       0x0004
#define PSX_EXP1_LICENSE1           (PSX_EXP1_BASE + PSX_EXP1_LICENSE1_OFS)

/* Post-Boot TTY message (must contain at least one 00h byte) */
#define PSX_EXP1_TTYMSG_OFS         0x0030
#define PSX_EXP1_TTYMSG             (PSX_EXP1_BASE + PSX_EXP1_TTYMSG_OFS)

/* Pre-Boot Entrypoint - called almost immediately after Reset, if the
 * Pre-Boot ID string is present. */
#define PSX_EXP1_INIT_OFS           0x0080
#define PSX_EXP1_INIT               (PSX_EXP1_BASE + PSX_EXP1_INIT_OFS)

/* Pre-Boot ID string: "Licensed by Sony Computer Entertainment Inc." */
#define PSX_EXP1_LICENSE2_OFS       0x0084
#define PSX_EXP1_LICENSE2           (PSX_EXP1_BASE + PSX_EXP1_LICENSE2_OFS)

/* Code/data area for the expansion device (after the header region;
 * 1F0000B0h..1F0000FFh is unused) */
#define PSX_EXP1_CODEDATA_OFS       0x0100
#define PSX_EXP1_CODEDATA           (PSX_EXP1_BASE + PSX_EXP1_CODEDATA_OFS)

/*==============================================================================
 * Hardware I/O Registers (relative to PSX_HW_BASE = 0x1F800000;
 * I/O ports occupy 0x1F801000..0x1F803FFF)
 *============================================================================*/

/*-----------------------------------------------------------------------------
 * Memory Control 1
 *----------------------------------------------------------------------------*/

/* Expansion 1 Base Address (usually 1F000000h) */
#define PSX_REG_EXP1_BASE_OFS       0x1000
#define PSX_REG_EXP1_BASE           (PSX_HW_BASE + PSX_REG_EXP1_BASE_OFS)

/* Expansion 2 Base Address (usually 1F802000h) */
#define PSX_REG_EXP2_BASE_OFS       0x1004
#define PSX_REG_EXP2_BASE           (PSX_HW_BASE + PSX_REG_EXP2_BASE_OFS)

/* Expansion 1 Delay/Size (usually 0013243Fh; 512Kbytes, 8bit bus) */
#define PSX_REG_EXP1_DELAY_OFS      0x1008
#define PSX_REG_EXP1_DELAY          (PSX_HW_BASE + PSX_REG_EXP1_DELAY_OFS)

/* Expansion 3 Delay/Size (usually 00003022h; 1 byte) */
#define PSX_REG_EXP3_DELAY_OFS      0x100C
#define PSX_REG_EXP3_DELAY          (PSX_HW_BASE + PSX_REG_EXP3_DELAY_OFS)

/* BIOS ROM Delay/Size (usually 0013243Fh; 512Kbytes, 8bit bus) */
#define PSX_REG_BIOS_DELAY_OFS      0x1010
#define PSX_REG_BIOS_DELAY          (PSX_HW_BASE + PSX_REG_BIOS_DELAY_OFS)

/* SPU Delay/Size (usually 200931E1h) */
#define PSX_REG_SPU_DELAY_OFS       0x1014
#define PSX_REG_SPU_DELAY           (PSX_HW_BASE + PSX_REG_SPU_DELAY_OFS)

/* CDROM Delay/Size (usually 00020843h or 00020943h) */
#define PSX_REG_CDROM_DELAY_OFS     0x1018
#define PSX_REG_CDROM_DELAY         (PSX_HW_BASE + PSX_REG_CDROM_DELAY_OFS)

/* Expansion 2 Delay/Size (usually 00070777h; 128 bytes, 8bit bus) */
#define PSX_REG_EXP2_DELAY_OFS      0x101C
#define PSX_REG_EXP2_DELAY          (PSX_HW_BASE + PSX_REG_EXP2_DELAY_OFS)

/* COM_DELAY / COMMON_DELAY (00031125h or 0000132Ch or 00001325h) */
#define PSX_REG_COM_DELAY_OFS       0x1020
#define PSX_REG_COM_DELAY           (PSX_HW_BASE + PSX_REG_COM_DELAY_OFS)

/*-----------------------------------------------------------------------------
 * Peripheral I/O Ports
 *----------------------------------------------------------------------------*/

/* JOY port - controller and memory card interface (SIO0 in old docs) */
#define PSX_REG_JOY_DATA_OFS        0x1040
#define PSX_REG_JOY_DATA            (PSX_HW_BASE + PSX_REG_JOY_DATA_OFS)
#define PSX_REG_JOY_STATUS_OFS      0x1044
#define PSX_REG_JOY_STATUS          (PSX_HW_BASE + PSX_REG_JOY_STATUS_OFS)
#define PSX_REG_JOY_MODE_OFS        0x1048
#define PSX_REG_JOY_MODE            (PSX_HW_BASE + PSX_REG_JOY_MODE_OFS)
#define PSX_REG_JOY_CTRL_OFS        0x104A
#define PSX_REG_JOY_CTRL            (PSX_HW_BASE + PSX_REG_JOY_CTRL_OFS)
#define PSX_REG_JOY_BAUD_OFS        0x104E
#define PSX_REG_JOY_BAUD            (PSX_HW_BASE + PSX_REG_JOY_BAUD_OFS)

/* SIO - serial port */
#define PSX_REG_SIO_DATA_OFS        0x1050
#define PSX_REG_SIO_DATA            (PSX_HW_BASE + PSX_REG_SIO_DATA_OFS)
#define PSX_REG_SIO_STATUS_OFS      0x1054
#define PSX_REG_SIO_STATUS          (PSX_HW_BASE + PSX_REG_SIO_STATUS_OFS)
#define PSX_REG_SIO_MODE_OFS        0x1058
#define PSX_REG_SIO_MODE            (PSX_HW_BASE + PSX_REG_SIO_MODE_OFS)
#define PSX_REG_SIO_CTRL_OFS        0x105A
#define PSX_REG_SIO_CTRL            (PSX_HW_BASE + PSX_REG_SIO_CTRL_OFS)
#define PSX_REG_SIO_MISC_OFS        0x105C
#define PSX_REG_SIO_MISC            (PSX_HW_BASE + PSX_REG_SIO_MISC_OFS)
#define PSX_REG_SIO_BAUD_OFS        0x105E
#define PSX_REG_SIO_BAUD            (PSX_HW_BASE + PSX_REG_SIO_BAUD_OFS)

/* RAM size (usually 00000B88h; 2MB RAM mirrored in first 8MB) */
#define PSX_REG_RAM_SIZE_OFS        0x1060
#define PSX_REG_RAM_SIZE            (PSX_HW_BASE + PSX_REG_RAM_SIZE_OFS)

/*-----------------------------------------------------------------------------
 * Interrupt (IRQ) Controller
 *----------------------------------------------------------------------------*/

/* I_STAT - Interrupt status register */
#define PSX_REG_I_STAT_OFS          0x1070
#define PSX_REG_I_STAT              (PSX_HW_BASE + PSX_REG_I_STAT_OFS)

/* I_MASK - Interrupt mask register */
#define PSX_REG_I_MASK_OFS          0x1074
#define PSX_REG_I_MASK              (PSX_HW_BASE + PSX_REG_I_MASK_OFS)

/*-----------------------------------------------------------------------------
 * DMA Channels (each channel: MADR at +0x00, BCR at +0x04, CHCR at +0x08)
 *----------------------------------------------------------------------------*/

/* DMA0 - MDECin (RAM to MDEC) */
#define PSX_REG_MDEC_IN_MADR_OFS    0x1080
#define PSX_REG_MDEC_IN_MADR        (PSX_HW_BASE + PSX_REG_MDEC_IN_MADR_OFS)
#define PSX_REG_MDEC_IN_BCR_OFS     0x1084
#define PSX_REG_MDEC_IN_BCR         (PSX_HW_BASE + PSX_REG_MDEC_IN_BCR_OFS)
#define PSX_REG_MDEC_IN_CHCR_OFS    0x1088
#define PSX_REG_MDEC_IN_CHCR        (PSX_HW_BASE + PSX_REG_MDEC_IN_CHCR_OFS)

/* DMA1 - MDECout (MDEC to RAM) */
#define PSX_REG_MDEC_OUT_MADR_OFS   0x1090
#define PSX_REG_MDEC_OUT_MADR       (PSX_HW_BASE + PSX_REG_MDEC_OUT_MADR_OFS)
#define PSX_REG_MDEC_OUT_BCR_OFS    0x1094
#define PSX_REG_MDEC_OUT_BCR        (PSX_HW_BASE + PSX_REG_MDEC_OUT_BCR_OFS)
#define PSX_REG_MDEC_OUT_CHCR_OFS   0x1098
#define PSX_REG_MDEC_OUT_CHCR       (PSX_HW_BASE + PSX_REG_MDEC_OUT_CHCR_OFS)

/* DMA2 - GPU (lists + image data) */
#define PSX_REG_GPU_DMA_MADR_OFS    0x10A0
#define PSX_REG_GPU_DMA_MADR        (PSX_HW_BASE + PSX_REG_GPU_DMA_MADR_OFS)
#define PSX_REG_GPU_DMA_BCR_OFS     0x10A4
#define PSX_REG_GPU_DMA_BCR         (PSX_HW_BASE + PSX_REG_GPU_DMA_BCR_OFS)
#define PSX_REG_GPU_DMA_CHCR_OFS    0x10A8
#define PSX_REG_GPU_DMA_CHCR        (PSX_HW_BASE + PSX_REG_GPU_DMA_CHCR_OFS)

/* DMA3 - CDROM (CDROM to RAM) */
#define PSX_REG_CD_DMA_MADR_OFS     0x10B0
#define PSX_REG_CD_DMA_MADR         (PSX_HW_BASE + PSX_REG_CD_DMA_MADR_OFS)
#define PSX_REG_CD_DMA_BCR_OFS      0x10B4
#define PSX_REG_CD_DMA_BCR          (PSX_HW_BASE + PSX_REG_CD_DMA_BCR_OFS)
#define PSX_REG_CD_DMA_CHCR_OFS     0x10B8
#define PSX_REG_CD_DMA_CHCR         (PSX_HW_BASE + PSX_REG_CD_DMA_CHCR_OFS)

/* DMA4 - SPU */
#define PSX_REG_SPU_DMA_MADR_OFS    0x10C0
#define PSX_REG_SPU_DMA_MADR        (PSX_HW_BASE + PSX_REG_SPU_DMA_MADR_OFS)
#define PSX_REG_SPU_DMA_BCR_OFS     0x10C4
#define PSX_REG_SPU_DMA_BCR         (PSX_HW_BASE + PSX_REG_SPU_DMA_BCR_OFS)
#define PSX_REG_SPU_DMA_CHCR_OFS    0x10C8
#define PSX_REG_SPU_DMA_CHCR        (PSX_HW_BASE + PSX_REG_SPU_DMA_CHCR_OFS)

/* DMA5 - PIO (Expansion Port) */
#define PSX_REG_PIO_DMA_MADR_OFS    0x10D0
#define PSX_REG_PIO_DMA_MADR        (PSX_HW_BASE + PSX_REG_PIO_DMA_MADR_OFS)
#define PSX_REG_PIO_DMA_BCR_OFS     0x10D4
#define PSX_REG_PIO_DMA_BCR         (PSX_HW_BASE + PSX_REG_PIO_DMA_BCR_OFS)
#define PSX_REG_PIO_DMA_CHCR_OFS    0x10D8
#define PSX_REG_PIO_DMA_CHCR        (PSX_HW_BASE + PSX_REG_PIO_DMA_CHCR_OFS)

/* DMA6 - OTC (reverse clear OT, GPU related) */
#define PSX_REG_OTC_DMA_MADR_OFS    0x10E0
#define PSX_REG_OTC_DMA_MADR        (PSX_HW_BASE + PSX_REG_OTC_DMA_MADR_OFS)
#define PSX_REG_OTC_DMA_BCR_OFS     0x10E4
#define PSX_REG_OTC_DMA_BCR         (PSX_HW_BASE + PSX_REG_OTC_DMA_BCR_OFS)
#define PSX_REG_OTC_DMA_CHCR_OFS    0x10E8
#define PSX_REG_OTC_DMA_CHCR        (PSX_HW_BASE + PSX_REG_OTC_DMA_CHCR_OFS)

/* DPCR - DMA Control register */
#define PSX_REG_DMA_PCR_OFS         0x10F0
#define PSX_REG_DMA_PCR             (PSX_HW_BASE + PSX_REG_DMA_PCR_OFS)

/* DICR - DMA Interrupt register */
#define PSX_REG_DMA_ICR_OFS         0x10F4
#define PSX_REG_DMA_ICR             (PSX_HW_BASE + PSX_REG_DMA_ICR_OFS)

/*-----------------------------------------------------------------------------
 * Root Counters (Timers) - the PSX has only THREE timers (0..2)
 *----------------------------------------------------------------------------*/

/* Timer 0 - Dotclock */
#define PSX_REG_T0_COUNT_OFS        0x1100
#define PSX_REG_T0_COUNT            (PSX_HW_BASE + PSX_REG_T0_COUNT_OFS)
#define PSX_REG_T0_MODE_OFS         0x1104
#define PSX_REG_T0_MODE             (PSX_HW_BASE + PSX_REG_T0_MODE_OFS)
#define PSX_REG_T0_TARGET_OFS       0x1108
#define PSX_REG_T0_TARGET           (PSX_HW_BASE + PSX_REG_T0_TARGET_OFS)

/* Timer 1 - Horizontal Retrace */
#define PSX_REG_T1_COUNT_OFS        0x1110
#define PSX_REG_T1_COUNT            (PSX_HW_BASE + PSX_REG_T1_COUNT_OFS)
#define PSX_REG_T1_MODE_OFS         0x1114
#define PSX_REG_T1_MODE             (PSX_HW_BASE + PSX_REG_T1_MODE_OFS)
#define PSX_REG_T1_TARGET_OFS       0x1118
#define PSX_REG_T1_TARGET           (PSX_HW_BASE + PSX_REG_T1_TARGET_OFS)

/* Timer 2 - 1/8 system clock */
#define PSX_REG_T2_COUNT_OFS        0x1120
#define PSX_REG_T2_COUNT            (PSX_HW_BASE + PSX_REG_T2_COUNT_OFS)
#define PSX_REG_T2_MODE_OFS         0x1124
#define PSX_REG_T2_MODE             (PSX_HW_BASE + PSX_REG_T2_MODE_OFS)
#define PSX_REG_T2_TARGET_OFS       0x1128
#define PSX_REG_T2_TARGET           (PSX_HW_BASE + PSX_REG_T2_TARGET_OFS)

/*-----------------------------------------------------------------------------
 * CDROM Registers (8-bit, accessed with a 2-bit index)
 *----------------------------------------------------------------------------*/

/* 1F801800h - CD Index/Status Register (Bit0-1 R/W, Bit2-7 Read Only) */
#define PSX_REG_CD_INDEX_STATUS_OFS 0x1800
#define PSX_REG_CD_INDEX_STATUS     (PSX_HW_BASE + PSX_REG_CD_INDEX_STATUS_OFS)

/* 1F801801h - CD Command Register (W) / Response Fifo (R, usually Index1) */
#define PSX_REG_CD_COMMAND_OFS      0x1801
#define PSX_REG_CD_COMMAND          (PSX_HW_BASE + PSX_REG_CD_COMMAND_OFS)
#define PSX_REG_CD_RESPONSE_OFS     0x1801
#define PSX_REG_CD_RESPONSE         (PSX_HW_BASE + PSX_REG_CD_RESPONSE_OFS)

/* 1F801802h - CD Parameter Fifo (W) / Data Fifo 8bit/16bit (R) */
#define PSX_REG_CD_PARAM_OFS        0x1802
#define PSX_REG_CD_PARAM            (PSX_HW_BASE + PSX_REG_CD_PARAM_OFS)
#define PSX_REG_CD_DATA_OFS         0x1802
#define PSX_REG_CD_DATA             (PSX_HW_BASE + PSX_REG_CD_DATA_OFS)

/* 1F801803h - CD Request Register (W) / Interrupt Enable+Flag (R) */
#define PSX_REG_CD_REQUEST_OFS      0x1803
#define PSX_REG_CD_REQUEST          (PSX_HW_BASE + PSX_REG_CD_REQUEST_OFS)
#define PSX_REG_CD_INT_OFS          0x1803
#define PSX_REG_CD_INT              (PSX_HW_BASE + PSX_REG_CD_INT_OFS)

/*-----------------------------------------------------------------------------
 * GPU Registers
 *----------------------------------------------------------------------------*/

/* 1F801810h - GP0: send GPU commands/packets (W); GPUREAD: read responses (R) */
#define PSX_REG_GPU_GP0_OFS         0x1810
#define PSX_REG_GPU_GP0             (PSX_HW_BASE + PSX_REG_GPU_GP0_OFS)

/* 1F801814h - GP1: send display control commands (W); GPUSTAT: read status (R) */
#define PSX_REG_GPU_GP1_OFS         0x1814
#define PSX_REG_GPU_GP1             (PSX_HW_BASE + PSX_REG_GPU_GP1_OFS)

/*-----------------------------------------------------------------------------
 * MDEC Registers
 *----------------------------------------------------------------------------*/

/* 1F801820h - MDEC command/parameter (W); data/response (R) */
#define PSX_REG_MDEC_CMD_OFS        0x1820
#define PSX_REG_MDEC_CMD            (PSX_HW_BASE + PSX_REG_MDEC_CMD_OFS)

/* 1F801824h - MDEC control/reset (W); status (R) */
#define PSX_REG_MDEC_STATUS_OFS     0x1824
#define PSX_REG_MDEC_STATUS         (PSX_HW_BASE + PSX_REG_MDEC_STATUS_OFS)

/*-----------------------------------------------------------------------------
 * SPU Control Registers (sound processing unit)
 *----------------------------------------------------------------------------*/

/* MVOL - Main Volume Left/Right */
#define PSX_REG_SPU_MVOL_L_OFS      0x1D80
#define PSX_REG_SPU_MVOL_L          (PSX_HW_BASE + PSX_REG_SPU_MVOL_L_OFS)
#define PSX_REG_SPU_MVOL_R_OFS      0x1D82
#define PSX_REG_SPU_MVOL_R          (PSX_HW_BASE + PSX_REG_SPU_MVOL_R_OFS)

/* RVOL - Reverb Output Volume Left/Right */
#define PSX_REG_SPU_RVOL_L_OFS      0x1D84
#define PSX_REG_SPU_RVOL_L          (PSX_HW_BASE + PSX_REG_SPU_RVOL_L_OFS)
#define PSX_REG_SPU_RVOL_R_OFS      0x1D86
#define PSX_REG_SPU_RVOL_R          (PSX_HW_BASE + PSX_REG_SPU_RVOL_R_OFS)

/* KON - Key ON (Start Attack/Decay/Sustain) (W) */
#define PSX_REG_SPU_KON_L_OFS       0x1D88
#define PSX_REG_SPU_KON_L           (PSX_HW_BASE + PSX_REG_SPU_KON_L_OFS)
#define PSX_REG_SPU_KON_R_OFS       0x1D8A
#define PSX_REG_SPU_KON_R           (PSX_HW_BASE + PSX_REG_SPU_KON_R_OFS)

/* KOFF - Key OFF (Start Release) (W) */
#define PSX_REG_SPU_KOFF_L_OFS      0x1D8C
#define PSX_REG_SPU_KOFF_L          (PSX_HW_BASE + PSX_REG_SPU_KOFF_L_OFS)
#define PSX_REG_SPU_KOFF_R_OFS      0x1D8E
#define PSX_REG_SPU_KOFF_R          (PSX_HW_BASE + PSX_REG_SPU_KOFF_R_OFS)

/* PMON - Pitch Modulation Enable flags */
#define PSX_REG_SPU_PMON_L_OFS      0x1D90
#define PSX_REG_SPU_PMON_L          (PSX_HW_BASE + PSX_REG_SPU_PMON_L_OFS)
#define PSX_REG_SPU_PMON_R_OFS      0x1D92
#define PSX_REG_SPU_PMON_R          (PSX_HW_BASE + PSX_REG_SPU_PMON_R_OFS)

/* NON - Noise mode enable flags */
#define PSX_REG_SPU_NON_L_OFS       0x1D94
#define PSX_REG_SPU_NON_L           (PSX_HW_BASE + PSX_REG_SPU_NON_L_OFS)
#define PSX_REG_SPU_NON_R_OFS       0x1D96
#define PSX_REG_SPU_NON_R           (PSX_HW_BASE + PSX_REG_SPU_NON_R_OFS)

/* EON - Reverb mode aka Echo On flags */
#define PSX_REG_SPU_EON_L_OFS       0x1D98
#define PSX_REG_SPU_EON_L           (PSX_HW_BASE + PSX_REG_SPU_EON_L_OFS)
#define PSX_REG_SPU_EON_R_OFS       0x1D9A
#define PSX_REG_SPU_EON_R           (PSX_HW_BASE + PSX_REG_SPU_EON_R_OFS)

/* ENDX - Voice 0..23 ON/OFF status (R) */
#define PSX_REG_SPU_ENDX_L_OFS      0x1D9C
#define PSX_REG_SPU_ENDX_L          (PSX_HW_BASE + PSX_REG_SPU_ENDX_L_OFS)
#define PSX_REG_SPU_ENDX_R_OFS      0x1D9E
#define PSX_REG_SPU_ENDX_R          (PSX_HW_BASE + PSX_REG_SPU_ENDX_R_OFS)

/* 1F801DA0h - unknown (some kind of read-only status register, or garbage) */
#define PSX_REG_SPU_UNKNOWN_1DA0_OFS 0x1DA0
#define PSX_REG_SPU_UNKNOWN_1DA0    (PSX_HW_BASE + PSX_REG_SPU_UNKNOWN_1DA0_OFS)

/* mBASE - Sound RAM Reverb Work Area Start Address */
#define PSX_REG_SPU_MBASE_OFS       0x1DA2
#define PSX_REG_SPU_MBASE           (PSX_HW_BASE + PSX_REG_SPU_MBASE_OFS)

/* Sound RAM IRQ Address (IRQ9) */
#define PSX_REG_SPU_IRQ9_ADDR_OFS   0x1DA4
#define PSX_REG_SPU_IRQ9_ADDR       (PSX_HW_BASE + PSX_REG_SPU_IRQ9_ADDR_OFS)

/* Sound RAM Data Transfer Address */
#define PSX_REG_SPU_TRANS_ADDR_OFS  0x1DA6
#define PSX_REG_SPU_TRANS_ADDR      (PSX_HW_BASE + PSX_REG_SPU_TRANS_ADDR_OFS)

/* Sound RAM Data Transfer Fifo */
#define PSX_REG_SPU_TRANS_FIFO_OFS  0x1DA8
#define PSX_REG_SPU_TRANS_FIFO      (PSX_HW_BASE + PSX_REG_SPU_TRANS_FIFO_OFS)

/* SPUCNT - SPU Control Register */
#define PSX_REG_SPU_CNT_OFS         0x1DAA
#define PSX_REG_SPU_CNT             (PSX_HW_BASE + PSX_REG_SPU_CNT_OFS)

/* Sound RAM Data Transfer Control (should be 0004h) */
#define PSX_REG_SPU_TRANS_CTRL_OFS  0x1DAC
#define PSX_REG_SPU_TRANS_CTRL      (PSX_HW_BASE + PSX_REG_SPU_TRANS_CTRL_OFS)

/* SPUSTAT - SPU Status Register (R) */
#define PSX_REG_SPU_STAT_OFS        0x1DAE
#define PSX_REG_SPU_STAT            (PSX_HW_BASE + PSX_REG_SPU_STAT_OFS)

/* CDVOL - CD Volume Left/Right */
#define PSX_REG_SPU_CDVOL_L_OFS     0x1DB0
#define PSX_REG_SPU_CDVOL_L         (PSX_HW_BASE + PSX_REG_SPU_CDVOL_L_OFS)
#define PSX_REG_SPU_CDVOL_R_OFS     0x1DB2
#define PSX_REG_SPU_CDVOL_R         (PSX_HW_BASE + PSX_REG_SPU_CDVOL_R_OFS)

/* EXTVOL - External Volume Left/Right */
#define PSX_REG_SPU_EXTVOL_L_OFS    0x1DB4
#define PSX_REG_SPU_EXTVOL_L        (PSX_HW_BASE + PSX_REG_SPU_EXTVOL_L_OFS)
#define PSX_REG_SPU_EXTVOL_R_OFS    0x1DB6
#define PSX_REG_SPU_EXTVOL_R        (PSX_HW_BASE + PSX_REG_SPU_EXTVOL_R_OFS)

/*-----------------------------------------------------------------------------
 * SPU Reverb Configuration Area (1F801DC0h..1F801DFFh)
 *----------------------------------------------------------------------------*/

/* dAPF1 - Reverb APF Offset 1 (first register of the reverb config area) */
#define PSX_REG_SPU_REVERB_DAPF1_OFS 0x1DC0
#define PSX_REG_SPU_REVERB_DAPF1    (PSX_HW_BASE + PSX_REG_SPU_REVERB_DAPF1_OFS)

/* vLIN / vRIN - Reverb Input Volume Left/Right */
#define PSX_REG_SPU_VIN_L_OFS       0x1DFC
#define PSX_REG_SPU_VIN_L           (PSX_HW_BASE + PSX_REG_SPU_VIN_L_OFS)
#define PSX_REG_SPU_VIN_R_OFS       0x1DFE
#define PSX_REG_SPU_VIN_R           (PSX_HW_BASE + PSX_REG_SPU_VIN_R_OFS)

/*-----------------------------------------------------------------------------
 * Expansion Region 2 - Debug/Dev-unit Registers
 *----------------------------------------------------------------------------*/

/* 1F802030h - DTL-H2000 only: Secondary IRQ10 Flags (Lightgun IRQs) */
#define PSX_REG_EXP2_IRQ10_OFS      0x2030
#define PSX_REG_EXP2_IRQ10          (PSX_HW_BASE + PSX_REG_EXP2_IRQ10_OFS)

/* 1F802040h - DTL-H2000 only: Bootmode "Dip switches" (R) */
#define PSX_REG_DIP_SWITCHES_OFS    0x2040
#define PSX_REG_DIP_SWITCHES        (PSX_HW_BASE + PSX_REG_DIP_SWITCHES_OFS)

/* 1F802041h - POST (external 7 segment display, BIOS boot status) */
#define PSX_REG_POST_OFS            0x2041
#define PSX_REG_POST                (PSX_HW_BASE + PSX_REG_POST_OFS)
