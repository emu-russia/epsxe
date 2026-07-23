/*
 * PSX Hardware Register Definitions
 * Based on "Memory_Layout.pdf" (PSX memory map and I/O registers)
 * All addresses are physical addresses as used by the PlayStation.
 *
 * This file provides:
 *  - Memory map constants (RAM, BIOS, PIO, Scratch, I/O base)
 *  - Register definitions with full address and offset macros
 *  - Comments in English
 *
 * Prefix: PSX_REG_ for hardware registers, PSX_PIO_ for PIO, PSX_ for memory map.
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

/* Parallel I/O (PIO) region – used for expansion devices */
#define PSX_PIO_BASE                0x1F000000

/* Scratchpad RAM (data cache) – 1 KB */
#define PSX_SCRATCH_BASE            0x1F800000
#define PSX_SCRATCH_SIZE            0x400               /* 1 KB */

/* Base address for most I/O registers (hardware control) */
#define PSX_HW_BASE                 0x1F800000

/*==============================================================================
 * PIO (Parallel I/O) Offsets
 *============================================================================*/

#define PSX_PIO_MAIN_OFS            0x0000
#define PSX_PIO_MAIN                (PSX_PIO_BASE + PSX_PIO_MAIN_OFS)
/* Address of main() routine for PIO device */

#define PSX_PIO_LICENSE1_OFS        0x0004
#define PSX_PIO_LICENSE1            (PSX_PIO_BASE + PSX_PIO_LICENSE1_OFS)
/* License string: "Licensed by Sony Computer Entertainment Inc.\0" */

#define PSX_PIO_INIT_OFS            0x0080
#define PSX_PIO_INIT                (PSX_PIO_BASE + PSX_PIO_INIT_OFS)
/* Address of init() routine for PIO device */

#define PSX_PIO_LICENSE2_OFS        0x0084
#define PSX_PIO_LICENSE2            (PSX_PIO_BASE + PSX_PIO_LICENSE2_OFS)
/* Duplicate license string */

#define PSX_PIO_CODEDATA_OFS        0x00B4
#define PSX_PIO_CODEDATA            (PSX_PIO_BASE + PSX_PIO_CODEDATA_OFS)
/* Code/data area for PIO device */

/*==============================================================================
 * Hardware I/O Registers (relative to PSX_HW_BASE = 0x1F801000)
 *============================================================================*/

/*-----------------------------------------------------------------------------
 * Unknown / delay registers (often used for timing)
 *----------------------------------------------------------------------------*/

#define PSX_REG_UNKNOWN_0x1000_OFS  0x1000
#define PSX_REG_UNKNOWN_0x1000      (PSX_HW_BASE + PSX_REG_UNKNOWN_0x1000_OFS)

#define PSX_REG_UNKNOWN_0x1004_OFS  0x1004
#define PSX_REG_UNKNOWN_0x1004      (PSX_HW_BASE + PSX_REG_UNKNOWN_0x1004_OFS)

#define PSX_REG_UNKNOWN_0x1008_OFS  0x1008
#define PSX_REG_UNKNOWN_0x1008      (PSX_HW_BASE + PSX_REG_UNKNOWN_0x1008_OFS)

#define PSX_REG_UNKNOWN_0x100C_OFS  0x100C
#define PSX_REG_UNKNOWN_0x100C      (PSX_HW_BASE + PSX_REG_UNKNOWN_0x100C_OFS)

#define PSX_REG_ROM_DELAY_OFS  		0x1010
#define PSX_REG_ROM_DELAY      		(PSX_HW_BASE + PSX_REG_ROM_DELAY_OFS)
/* ROM delay */

#define PSX_REG_SPU_DELAY_OFS       0x1014
#define PSX_REG_SPU_DELAY           (PSX_HW_BASE + PSX_REG_SPU_DELAY_OFS)
/* SPU delay */

#define PSX_REG_DV5_DELAY_OFS       0x1018
#define PSX_REG_DV5_DELAY           (PSX_HW_BASE + PSX_REG_DV5_DELAY_OFS)
/* DV5 delay */

#define PSX_REG_PIO_DELAY_OFS  		0x101C
#define PSX_REG_PIO_DELAY      		(PSX_HW_BASE + PSX_REG_PIO_DELAY_OFS)
/* PIO delay */

#define PSX_REG_COM_DELAY_OFS       0x1020
#define PSX_REG_COM_DELAY           (PSX_HW_BASE + PSX_REG_COM_DELAY_OFS)
/* COM delay */

/*-----------------------------------------------------------------------------
 * Serial I/O (SIO) – two channels
 *----------------------------------------------------------------------------*/

/* SIO0 */
#define PSX_REG_SIO0_DATA_OFS       0x1040
#define PSX_REG_SIO0_DATA           (PSX_HW_BASE + PSX_REG_SIO0_DATA_OFS)
#define PSX_REG_SIO0_STATUS_OFS     0x1044
#define PSX_REG_SIO0_STATUS         (PSX_HW_BASE + PSX_REG_SIO0_STATUS_OFS)
#define PSX_REG_SIO0_MODE_OFS       0x1048
#define PSX_REG_SIO0_MODE           (PSX_HW_BASE + PSX_REG_SIO0_MODE_OFS)
#define PSX_REG_SIO0_CONTROL_OFS    0x104A
#define PSX_REG_SIO0_CONTROL        (PSX_HW_BASE + PSX_REG_SIO0_CONTROL_OFS)
#define PSX_REG_SIO0_BAUD_OFS       0x104E
#define PSX_REG_SIO0_BAUD           (PSX_HW_BASE + PSX_REG_SIO0_BAUD_OFS)

/* SIO1 */
#define PSX_REG_SIO1_DATA_OFS       0x1050
#define PSX_REG_SIO1_DATA           (PSX_HW_BASE + PSX_REG_SIO1_DATA_OFS)
#define PSX_REG_SIO1_STATUS_OFS     0x1054
#define PSX_REG_SIO1_STATUS         (PSX_HW_BASE + PSX_REG_SIO1_STATUS_OFS)
#define PSX_REG_SIO1_MODE_OFS       0x1058
#define PSX_REG_SIO1_MODE           (PSX_HW_BASE + PSX_REG_SIO1_MODE_OFS)
#define PSX_REG_SIO1_CONTROL_OFS    0x105A
#define PSX_REG_SIO1_CONTROL        (PSX_HW_BASE + PSX_REG_SIO1_CONTROL_OFS)
#define PSX_REG_SIO1_BAUD_OFS       0x105E
#define PSX_REG_SIO1_BAUD           (PSX_HW_BASE + PSX_REG_SIO1_BAUD_OFS)

/* RAM size (read-only) */
#define PSX_REG_RAM_SIZE_OFS        0x1060
#define PSX_REG_RAM_SIZE            (PSX_HW_BASE + PSX_REG_RAM_SIZE_OFS)

/*-----------------------------------------------------------------------------
 * Interrupt (IRQ) Controller
 *----------------------------------------------------------------------------*/

#define PSX_REG_INT_REG_OFS         0x1070
#define PSX_REG_INT_REG             (PSX_HW_BASE + PSX_REG_INT_REG_OFS)
#define PSX_REG_INT_MASK_OFS        0x1074
#define PSX_REG_INT_MASK            (PSX_HW_BASE + PSX_REG_INT_MASK_OFS)

/*-----------------------------------------------------------------------------
 * DMA Channels
 *----------------------------------------------------------------------------*/

/* MDEC (Macroblock Decoder) DMA 0 */
#define PSX_REG_MDEC_DMA0_MADR_OFS  0x1080
#define PSX_REG_MDEC_DMA0_MADR      (PSX_HW_BASE + PSX_REG_MDEC_DMA0_MADR_OFS)
#define PSX_REG_MDEC_DMA0_BCR_OFS   0x1084
#define PSX_REG_MDEC_DMA0_BCR       (PSX_HW_BASE + PSX_REG_MDEC_DMA0_BCR_OFS)
#define PSX_REG_MDEC_DMA0_CHCR_OFS  0x1088
#define PSX_REG_MDEC_DMA0_CHCR      (PSX_HW_BASE + PSX_REG_MDEC_DMA0_CHCR_OFS)

/* MDEC DMA 1 */
#define PSX_REG_MDEC_DMA1_MADR_OFS  0x1090
#define PSX_REG_MDEC_DMA1_MADR      (PSX_HW_BASE + PSX_REG_MDEC_DMA1_MADR_OFS)
#define PSX_REG_MDEC_DMA1_BCR_OFS   0x1094
#define PSX_REG_MDEC_DMA1_BCR       (PSX_HW_BASE + PSX_REG_MDEC_DMA1_BCR_OFS)
#define PSX_REG_MDEC_DMA1_CHCR_OFS  0x1098
#define PSX_REG_MDEC_DMA1_CHCR      (PSX_HW_BASE + PSX_REG_MDEC_DMA1_CHCR_OFS)

/* GPU DMA */
#define PSX_REG_GPU_DMA_MADR_OFS    0x10A0
#define PSX_REG_GPU_DMA_MADR        (PSX_HW_BASE + PSX_REG_GPU_DMA_MADR_OFS)
#define PSX_REG_GPU_DMA_BCR_OFS     0x10A4
#define PSX_REG_GPU_DMA_BCR         (PSX_HW_BASE + PSX_REG_GPU_DMA_BCR_OFS)
#define PSX_REG_GPU_DMA_CHCR_OFS    0x10A8
#define PSX_REG_GPU_DMA_CHCR        (PSX_HW_BASE + PSX_REG_GPU_DMA_CHCR_OFS)

/* CD-ROM DMA */
#define PSX_REG_CD_DMA_MADR_OFS     0x10B0
#define PSX_REG_CD_DMA_MADR         (PSX_HW_BASE + PSX_REG_CD_DMA_MADR_OFS)
#define PSX_REG_CD_DMA_BCR_OFS      0x10B4
#define PSX_REG_CD_DMA_BCR          (PSX_HW_BASE + PSX_REG_CD_DMA_BCR_OFS)
#define PSX_REG_CD_DMA_CHCR_OFS     0x10B8
#define PSX_REG_CD_DMA_CHCR         (PSX_HW_BASE + PSX_REG_CD_DMA_CHCR_OFS)

/* SPU DMA */
#define PSX_REG_SPU_DMA_MADR_OFS    0x10C0
#define PSX_REG_SPU_DMA_MADR        (PSX_HW_BASE + PSX_REG_SPU_DMA_MADR_OFS)
#define PSX_REG_SPU_DMA_BCR_OFS     0x10C4
#define PSX_REG_SPU_DMA_BCR         (PSX_HW_BASE + PSX_REG_SPU_DMA_BCR_OFS)
#define PSX_REG_SPU_DMA_CHCR_OFS    0x10C8
#define PSX_REG_SPU_DMA_CHCR        (PSX_HW_BASE + PSX_REG_SPU_DMA_CHCR_OFS)

/* DMA 5 */
#define PSX_REG_DMA5_MADR_OFS       0x10D0
#define PSX_REG_DMA5_MADR           (PSX_HW_BASE + PSX_REG_DMA5_MADR_OFS)
#define PSX_REG_DMA5_BCR_OFS        0x10D4
#define PSX_REG_DMA5_BCR            (PSX_HW_BASE + PSX_REG_DMA5_BCR_OFS)
#define PSX_REG_DMA5_CHCR_OFS       0x10D8
#define PSX_REG_DMA5_CHCR           (PSX_HW_BASE + PSX_REG_DMA5_CHCR_OFS)

/* DMA 6 */
#define PSX_REG_DMA6_MADR_OFS       0x10E0
#define PSX_REG_DMA6_MADR           (PSX_HW_BASE + PSX_REG_DMA6_MADR_OFS)
#define PSX_REG_DMA6_BCR_OFS        0x10E4
#define PSX_REG_DMA6_BCR            (PSX_HW_BASE + PSX_REG_DMA6_BCR_OFS)
#define PSX_REG_DMA6_CHCR_OFS       0x10E8
#define PSX_REG_DMA6_CHCR           (PSX_HW_BASE + PSX_REG_DMA6_CHCR_OFS)

/* DMA control */
#define PSX_REG_DMA_PCR_OFS         0x10F0
#define PSX_REG_DMA_PCR             (PSX_HW_BASE + PSX_REG_DMA_PCR_OFS)
#define PSX_REG_DMA_ICR_OFS         0x10F4
#define PSX_REG_DMA_ICR             (PSX_HW_BASE + PSX_REG_DMA_ICR_OFS)

/*-----------------------------------------------------------------------------
 * Root Counters (Timers)
 *----------------------------------------------------------------------------*/

/* Timer 0 */
#define PSX_REG_T0_COUNT_OFS        0x1100
#define PSX_REG_T0_COUNT            (PSX_HW_BASE + PSX_REG_T0_COUNT_OFS)
#define PSX_REG_T0_MODE_OFS         0x1104
#define PSX_REG_T0_MODE             (PSX_HW_BASE + PSX_REG_T0_MODE_OFS)
#define PSX_REG_T0_TARGET_OFS       0x1108
#define PSX_REG_T0_TARGET           (PSX_HW_BASE + PSX_REG_T0_TARGET_OFS)

/* Timer 1 */
#define PSX_REG_T1_COUNT_OFS        0x1110
#define PSX_REG_T1_COUNT            (PSX_HW_BASE + PSX_REG_T1_COUNT_OFS)
#define PSX_REG_T1_MODE_OFS         0x1114
#define PSX_REG_T1_MODE             (PSX_HW_BASE + PSX_REG_T1_MODE_OFS)
#define PSX_REG_T1_TARGET_OFS       0x1118
#define PSX_REG_T1_TARGET           (PSX_HW_BASE + PSX_REG_T1_TARGET_OFS)

/* Timer 2 */
#define PSX_REG_T2_COUNT_OFS        0x1120
#define PSX_REG_T2_COUNT            (PSX_HW_BASE + PSX_REG_T2_COUNT_OFS)
#define PSX_REG_T2_MODE_OFS         0x1124
#define PSX_REG_T2_MODE             (PSX_HW_BASE + PSX_REG_T2_MODE_OFS)
#define PSX_REG_T2_TARGET_OFS       0x1128
#define PSX_REG_T2_TARGET           (PSX_HW_BASE + PSX_REG_T2_TARGET_OFS)

/* Timer 3 */
#define PSX_REG_T3_COUNT_OFS        0x1130
#define PSX_REG_T3_COUNT            (PSX_HW_BASE + PSX_REG_T3_COUNT_OFS)
#define PSX_REG_T3_MODE_OFS         0x1134
#define PSX_REG_T3_MODE             (PSX_HW_BASE + PSX_REG_T3_MODE_OFS)
#define PSX_REG_T3_TARGET_OFS       0x1138
#define PSX_REG_T3_TARGET           (PSX_HW_BASE + PSX_REG_T3_TARGET_OFS)

/*-----------------------------------------------------------------------------
 * CDROM Registers (8-bit)
 *----------------------------------------------------------------------------*/

#define PSX_REG_CDROM_REG0_OFS      0x1800
#define PSX_REG_CDROM_REG0          (PSX_HW_BASE + PSX_REG_CDROM_REG0_OFS)
#define PSX_REG_CDROM_REG1_OFS      0x1801
#define PSX_REG_CDROM_REG1          (PSX_HW_BASE + PSX_REG_CDROM_REG1_OFS)
#define PSX_REG_CDROM_REG2_OFS      0x1802
#define PSX_REG_CDROM_REG2          (PSX_HW_BASE + PSX_REG_CDROM_REG2_OFS)
#define PSX_REG_CDROM_REG3_OFS      0x1803
#define PSX_REG_CDROM_REG3          (PSX_HW_BASE + PSX_REG_CDROM_REG3_OFS)

/*-----------------------------------------------------------------------------
 * GPU Registers
 *----------------------------------------------------------------------------*/

#define PSX_REG_GPU_REG0_OFS        0x1810
#define PSX_REG_GPU_REG0            (PSX_HW_BASE + PSX_REG_GPU_REG0_OFS)
#define PSX_REG_GPU_REG1_OFS        0x1814
#define PSX_REG_GPU_REG1            (PSX_HW_BASE + PSX_REG_GPU_REG1_OFS)

/*-----------------------------------------------------------------------------
 * MDEC Registers
 *----------------------------------------------------------------------------*/

#define PSX_REG_MDEC_REG0_OFS       0x1820
#define PSX_REG_MDEC_REG0           (PSX_HW_BASE + PSX_REG_MDEC_REG0_OFS)
#define PSX_REG_MDEC_REG1_OFS       0x1824
#define PSX_REG_MDEC_REG1           (PSX_HW_BASE + PSX_REG_MDEC_REG1_OFS)

/*-----------------------------------------------------------------------------
 * SPU Registers (sound processing unit)
 *----------------------------------------------------------------------------*/

#define PSX_REG_SPU_MVOL_L_OFS      0x1D80
#define PSX_REG_SPU_MVOL_L          (PSX_HW_BASE + PSX_REG_SPU_MVOL_L_OFS)
#define PSX_REG_SPU_MVOL_R_OFS      0x1D82
#define PSX_REG_SPU_MVOL_R          (PSX_HW_BASE + PSX_REG_SPU_MVOL_R_OFS)

#define PSX_REG_SPU_REVERB_L_OFS    0x1D84
#define PSX_REG_SPU_REVERB_L        (PSX_HW_BASE + PSX_REG_SPU_REVERB_L_OFS)
#define PSX_REG_SPU_REVERB_R_OFS    0x1D86
#define PSX_REG_SPU_REVERB_R        (PSX_HW_BASE + PSX_REG_SPU_REVERB_R_OFS)

#define PSX_REG_SPU_KEY_ON_1_OFS    0x1D88
#define PSX_REG_SPU_KEY_ON_1        (PSX_HW_BASE + PSX_REG_SPU_KEY_ON_1_OFS)
#define PSX_REG_SPU_KEY_ON_2_OFS    0x1D8A
#define PSX_REG_SPU_KEY_ON_2        (PSX_HW_BASE + PSX_REG_SPU_KEY_ON_2_OFS)

#define PSX_REG_SPU_KEY_OFF_1_OFS   0x1D8C
#define PSX_REG_SPU_KEY_OFF_1       (PSX_HW_BASE + PSX_REG_SPU_KEY_OFF_1_OFS)
#define PSX_REG_SPU_KEY_OFF_2_OFS   0x1D8E
#define PSX_REG_SPU_KEY_OFF_2       (PSX_HW_BASE + PSX_REG_SPU_KEY_OFF_2_OFS)

#define PSX_REG_SPU_KEY_MODEFRM_1_OFS 0x1D90
#define PSX_REG_SPU_KEY_MODEFRM_1   (PSX_HW_BASE + PSX_REG_SPU_KEY_MODEFRM_1_OFS)
#define PSX_REG_SPU_KEY_MODEFRM_2_OFS 0x1D92
#define PSX_REG_SPU_KEY_MODEFRM_2   (PSX_HW_BASE + PSX_REG_SPU_KEY_MODEFRM_2_OFS)

#define PSX_REG_SPU_KEY_MODENOISE_1_OFS 0x1D94
#define PSX_REG_SPU_KEY_MODENOISE_1 (PSX_HW_BASE + PSX_REG_SPU_KEY_MODENOISE_1_OFS)
#define PSX_REG_SPU_KEY_MODENOISE_2_OFS 0x1D96
#define PSX_REG_SPU_KEY_MODENOISE_2 (PSX_HW_BASE + PSX_REG_SPU_KEY_MODENOISE_2_OFS)

#define PSX_REG_SPU_KEY_MODEREVERB_1_OFS 0x1D98
#define PSX_REG_SPU_KEY_MODEREVERB_1 (PSX_HW_BASE + PSX_REG_SPU_KEY_MODEREVERB_1_OFS)
#define PSX_REG_SPU_KEY_MODEREVERB_2_OFS 0x1D9A
#define PSX_REG_SPU_KEY_MODEREVERB_2 (PSX_HW_BASE + PSX_REG_SPU_KEY_MODEREVERB_2_OFS)

#define PSX_REG_SPU_KEY_CHANNELACTIVE_1_OFS 0x1D9C
#define PSX_REG_SPU_KEY_CHANNELACTIVE_1 (PSX_HW_BASE + PSX_REG_SPU_KEY_CHANNELACTIVE_1_OFS)
#define PSX_REG_SPU_KEY_CHANNELACTIVE_2_OFS 0x1D9E
#define PSX_REG_SPU_KEY_CHANNELACTIVE_2 (PSX_HW_BASE + PSX_REG_SPU_KEY_CHANNELACTIVE_2_OFS)

#define PSX_REG_SPU_SBADDR_OFS      0x1DA6
#define PSX_REG_SPU_SBADDR          (PSX_HW_BASE + PSX_REG_SPU_SBADDR_OFS)
#define PSX_REG_SPU_DATA_OFS        0x1DA8
#define PSX_REG_SPU_DATA            (PSX_HW_BASE + PSX_REG_SPU_DATA_OFS)
#define PSX_REG_SPU_REG0_OFS        0x1DAA
#define PSX_REG_SPU_REG0            (PSX_HW_BASE + PSX_REG_SPU_REG0_OFS)
#define PSX_REG_SPU_REG1_OFS        0x1DAC
#define PSX_REG_SPU_REG1            (PSX_HW_BASE + PSX_REG_SPU_REG1_OFS)
#define PSX_REG_SPU_STATUS_OFS      0x1DAE
#define PSX_REG_SPU_STATUS          (PSX_HW_BASE + PSX_REG_SPU_STATUS_OFS)

#define PSX_REG_SPU_CDVOL_L_OFS     0x1DB0
#define PSX_REG_SPU_CDVOL_L         (PSX_HW_BASE + PSX_REG_SPU_CDVOL_L_OFS)
#define PSX_REG_SPU_CDVOL_R_OFS     0x1DB2
#define PSX_REG_SPU_CDVOL_R         (PSX_HW_BASE + PSX_REG_SPU_CDVOL_R_OFS)
#define PSX_REG_SPU_EXTVOL_L_OFS    0x1DB4
#define PSX_REG_SPU_EXTVOL_L        (PSX_HW_BASE + PSX_REG_SPU_EXTVOL_L_OFS)
#define PSX_REG_SPU_EXTVOL_R_OFS    0x1DB6
#define PSX_REG_SPU_EXTVOL_R        (PSX_HW_BASE + PSX_REG_SPU_EXTVOL_R_OFS)

#define PSX_REG_SPU_REVERBCONFIG_OFS 0x1DC0
#define PSX_REG_SPU_REVERBCONFIG    (PSX_HW_BASE + PSX_REG_SPU_REVERBCONFIG_OFS)

#define PSX_REG_SPU_FACTOR_L_OFS    0x1DFC
#define PSX_REG_SPU_FACTOR_L        (PSX_HW_BASE + PSX_REG_SPU_FACTOR_L_OFS)
#define PSX_REG_SPU_FACTOR_R_OFS    0x1DFE
#define PSX_REG_SPU_FACTOR_R        (PSX_HW_BASE + PSX_REG_SPU_FACTOR_R_OFS)

/*-----------------------------------------------------------------------------
 * Debug Registers
 *----------------------------------------------------------------------------*/

#define PSX_REG_INT_2000_OFS        0x2030
#define PSX_REG_INT_2000            (PSX_HW_BASE + PSX_REG_INT_2000_OFS)
#define PSX_REG_DIP_SWITCHES_OFS    0x2040
#define PSX_REG_DIP_SWITCHES        (PSX_HW_BASE + PSX_REG_DIP_SWITCHES_OFS)
