#include "pch.h"

/* static prototypes for internal functions */
static void op_SPECIAL();
static void op_BCONDZ();
static void op_COP0();


// ==================== SPECIAL OPCODE TABLE (0x00) ====================
// Index: bits 0-5 of the opcode (function field)
static OPCODE cpu_special_opcode_table[64] = {
    /* 0x00 */ op_SLL,      /* 0x01 */ op_UNKNOWN, /* 0x02 */ op_SRL,      /* 0x03 */ op_SRA,
    /* 0x04 */ op_SLLV,     /* 0x05 */ op_UNKNOWN, /* 0x06 */ op_SRLV,     /* 0x07 */ op_SRAV,
    /* 0x08 */ op_JR,       /* 0x09 */ op_JALR,    /* 0x0A */ op_UNKNOWN,  /* 0x0B */ op_UNKNOWN,
    /* 0x0C */ op_SYSCALL,  /* 0x0D */ op_BREAK,   /* 0x0E */ op_UNKNOWN,  /* 0x0F */ op_UNKNOWN,
    /* 0x10 */ op_MFHI,     /* 0x11 */ op_MTHI,    /* 0x12 */ op_MFLO,     /* 0x13 */ op_MTLO,
    /* 0x14 */ op_UNKNOWN,  /* 0x15 */ op_UNKNOWN, /* 0x16 */ op_UNKNOWN,  /* 0x17 */ op_UNKNOWN,
    /* 0x18 */ op_MULT,     /* 0x19 */ op_MULTU,   /* 0x1A */ op_DIV,      /* 0x1B */ op_DIVU,
    /* 0x1C */ op_UNKNOWN,  /* 0x1D */ op_UNKNOWN, /* 0x1E */ op_UNKNOWN,  /* 0x1F */ op_UNKNOWN,
    /* 0x20 */ op_ADD,      /* 0x21 */ op_ADDI,    /* 0x22 */ op_SUB,      /* 0x23 */ op_SUB,
    /* 0x24 */ op_AND,      /* 0x25 */ op_OR,      /* 0x26 */ op_XOR,      /* 0x27 */ op_NOR,
    /* 0x28 */ op_UNKNOWN,  /* 0x29 */ op_UNKNOWN, /* 0x2A */ op_SLT,      /* 0x2B */ op_SLTU,
    /* 0x2C */ op_UNKNOWN,  /* 0x2D */ op_UNKNOWN, /* 0x2E */ op_UNKNOWN,  /* 0x2F */ op_UNKNOWN,
    /* 0x30 */ op_UNKNOWN,  /* 0x31 */ op_UNKNOWN, /* 0x32 */ op_UNKNOWN,  /* 0x33 */ op_UNKNOWN,
    /* 0x34 */ op_UNKNOWN,  /* 0x35 */ op_UNKNOWN, /* 0x36 */ op_UNKNOWN,  /* 0x37 */ op_UNKNOWN,
    /* 0x38 */ op_UNKNOWN,  /* 0x39 */ op_UNKNOWN, /* 0x3A */ op_UNKNOWN,  /* 0x3B */ op_UNKNOWN,
    /* 0x3C */ op_UNKNOWN,  /* 0x3D */ op_UNKNOWN, /* 0x3E */ op_UNKNOWN,  /* 0x3F */ op_UNKNOWN
};

// ==================== COP0 OPCODE TABLE (0x10) ====================
// Index: bits 21-25 of the opcode (rs field)
// COP0 = Coprocessor 0 (System Control Coprocessor)
static OPCODE cpu_cop0_table[32] = {
    /* 0x00 */ op_MFC0,     /* 0x01 */ op_UNKNOWN, /* 0x02 */ op_UNKNOWN, /* 0x03 */ op_UNKNOWN,
    /* 0x04 */ op_MTC0,     /* 0x05 */ op_UNKNOWN, /* 0x06 */ op_UNKNOWN, /* 0x07 */ op_UNKNOWN,
    /* 0x08 */ op_UNKNOWN,  /* 0x09 */ op_UNKNOWN, /* 0x0A */ op_UNKNOWN, /* 0x0B */ op_UNKNOWN,
    /* 0x0C */ op_UNKNOWN,  /* 0x0D */ op_UNKNOWN, /* 0x0E */ op_UNKNOWN, /* 0x0F */ op_UNKNOWN,
    /* 0x10 */ op_UNKNOWN,  /* 0x11 */ op_UNKNOWN, /* 0x12 */ op_UNKNOWN, /* 0x13 */ op_UNKNOWN,
    /* 0x14 */ op_UNKNOWN,  /* 0x15 */ op_UNKNOWN, /* 0x16 */ op_UNKNOWN, /* 0x17 */ op_UNKNOWN,
    /* 0x18 */ op_UNKNOWN,  /* 0x19 */ op_UNKNOWN, /* 0x1A */ op_UNKNOWN, /* 0x1B */ op_UNKNOWN,
    /* 0x1C */ op_UNKNOWN,  /* 0x1D */ op_UNKNOWN, /* 0x1E */ op_UNKNOWN, /* 0x1F */ op_UNKNOWN
};

// ==================== BCOND OPCODE TABLE (for conditional branches) ====================
// Index: bits 16-20 of the opcode (rt field)
// Used for opcodes 0x01 (BCONDZ) in the main table
static OPCODE cpu_bcond_opcode_table[32] = {
    /* 0x00 */ op_BLTZ,     /* 0x01 */ op_BGEZ,    /* 0x02 */ op_UNKNOWN, /* 0x03 */ op_UNKNOWN,
    /* 0x04 */ op_UNKNOWN,  /* 0x05 */ op_UNKNOWN, /* 0x06 */ op_UNKNOWN, /* 0x07 */ op_UNKNOWN,
    /* 0x08 */ op_UNKNOWN,  /* 0x09 */ op_UNKNOWN, /* 0x0A */ op_UNKNOWN, /* 0x0B */ op_UNKNOWN,
    /* 0x0C */ op_UNKNOWN,  /* 0x0D */ op_UNKNOWN, /* 0x0E */ op_UNKNOWN, /* 0x0F */ op_UNKNOWN,
    /* 0x10 */ op_BLTZAL,   /* 0x11 */ op_BGEZAL,  /* 0x12 */ op_UNKNOWN, /* 0x13 */ op_UNKNOWN,
    /* 0x14 */ op_UNKNOWN,  /* 0x15 */ op_UNKNOWN, /* 0x16 */ op_UNKNOWN, /* 0x17 */ op_UNKNOWN,
    /* 0x18 */ op_UNKNOWN,  /* 0x19 */ op_UNKNOWN, /* 0x1A */ op_UNKNOWN, /* 0x1B */ op_UNKNOWN,
    /* 0x1C */ op_UNKNOWN,  /* 0x1D */ op_UNKNOWN, /* 0x1E */ op_UNKNOWN, /* 0x1F */ op_UNKNOWN
};

// ==================== MAIN OPCODE TABLE ====================
// Index: bits 26-31 of the opcode (primary opcode)
OPCODE cpu_main_table[64] = {
    /* 0x00 */ op_SPECIAL,  /* 0x01 */ op_BCONDZ,  /* 0x02 */ op_J,        /* 0x03 */ op_JAL,
    /* 0x04 */ op_BEQ,      /* 0x05 */ op_BNE,     /* 0x06 */ op_BLEZ,     /* 0x07 */ op_BGTZ,
    /* 0x08 */ op_ADDI,     /* 0x09 */ op_ADDI,    /* 0x0A */ op_SLTI,     /* 0x0B */ op_SLTIU,
    /* 0x0C */ op_ANDI,     /* 0x0D */ op_ORI,     /* 0x0E */ op_XORI,     /* 0x0F */ op_LUI,
    /* 0x10 */ op_COP0,     /* 0x11 */ op_UNKNOWN, /* 0x12 */ gte_exec_opcode, /* 0x13 */ op_UNKNOWN,
    /* 0x14 */ op_UNKNOWN,  /* 0x15 */ op_UNKNOWN, /* 0x16 */ op_UNKNOWN,  /* 0x17 */ op_UNKNOWN,
    /* 0x18 */ op_UNKNOWN,  /* 0x19 */ op_UNKNOWN, /* 0x1A */ op_UNKNOWN,  /* 0x1B */ op_UNKNOWN,
    /* 0x1C */ op_UNKNOWN,  /* 0x1D */ op_UNKNOWN, /* 0x1E */ op_UNKNOWN,  /* 0x1F */ op_UNKNOWN,
    /* 0x20 */ op_LB,       /* 0x21 */ op_LH,      /* 0x22 */ op_LWL,      /* 0x23 */ op_LW,
    /* 0x24 */ op_LBU,      /* 0x25 */ op_LHU,     /* 0x26 */ op_LWR,      /* 0x27 */ op_UNKNOWN,
    /* 0x28 */ op_SB,       /* 0x29 */ op_SH,      /* 0x2A */ op_SWL,      /* 0x2B */ op_SW,
    /* 0x2C */ op_UNKNOWN,  /* 0x2D */ op_UNKNOWN, /* 0x2E */ op_SWR,      /* 0x2F */ op_UNKNOWN,
    /* 0x30 */ op_UNKNOWN,  /* 0x31 */ op_LWC2,    /* 0x32 */ op_UNKNOWN,  /* 0x33 */ op_UNKNOWN,
    /* 0x34 */ op_UNKNOWN,  /* 0x35 */ op_UNKNOWN, /* 0x36 */ op_UNKNOWN,  /* 0x37 */ op_UNKNOWN,
    /* 0x38 */ op_UNKNOWN,  /* 0x39 */ op_SWC2,    /* 0x3A */ op_UNKNOWN,  /* 0x3B */ op_UNKNOWN,
    /* 0x3C */ op_UNKNOWN,  /* 0x3D */ op_UNKNOWN, /* 0x3E */ op_UNKNOWN,  /* 0x3F */ op_UNKNOWN
};

// ==================== DISPATCHER FUNCTIONS ====================

// Handler for SPECIAL opcode group (0x00)
// Decodes the function field (bits 0-5) to determine the actual operation
static void op_SPECIAL() {
    cpu_special_opcode_table[cpu_opcode & 0x3F]();
}

// Handler for BCONDZ opcode group (0x01)
// Decodes the rt field (bits 16-20) to determine the branch condition
static void op_BCONDZ() {
    cpu_bcond_opcode_table[(cpu_opcode >> 16) & 0x1F]();
}

// Handler for COP0 opcode group (0x10)
// Decodes the rs field (bits 21-25) to determine the coprocessor operation
static void op_COP0() {
    cpu_cop0_table[(cpu_opcode >> 21) & 0x1F]();
}

