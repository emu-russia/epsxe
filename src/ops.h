#pragma once

/**
 * \file ops.h
 * \brief Interpreter handlers for the MIPS R3000 instruction set.
 *
 * Declares one handler function per supported MIPS instruction. Each
 * handler decodes the current cpu_opcode and updates the CPU state
 * (cpu_gpr, cpu_HI/cpu_LO, reg_pc, COP0 registers). The handlers are
 * dispatched through cpu_main_table (see op_tabs.h).
 */

/**
 * \brief Executes the MIPS SLL (shift-left-logical) instruction.
 */
void op_SLL();

/**
 * \brief Executes the MIPS SRL (shift-right-logical) instruction.
 */
void op_SRL();

/**
 * \brief Executes the MIPS SRA (shift-right-arithmetic) instruction.
 */
void op_SRA();

/**
 * \brief Executes the MIPS SLLV (shift-left-logical-variable) instruction.
 */
void op_SLLV();

/**
 * \brief Executes the MIPS SRLV (shift-right-logical-variable) instruction.
 */
void op_SRLV();

/**
 * \brief Executes the MIPS SRAV (shift-right-arithmetic-variable) instruction.
 */
void op_SRAV();

/**
 * \brief Executes the MIPS JR (jump-register) instruction.
 */
void op_JR();

/**
 * \brief Executes the MIPS JALR (jump-and-link-register) instruction.
 */
void op_JALR();

/**
 * \brief Executes the MIPS SYSCALL instruction.
 *
 * Triggers the system-call exception: stores the PC into cop0_epc,
 * sets cop0_cause to the system-call code and jumps to the exception
 * vector 0x80000080.
 */
void op_SYSCALL();

/**
 * \brief Executes the MIPS BREAK instruction (no-op in this implementation).
 */
void op_BREAK();

/**
 * \brief Executes the MIPS MFHI (move-from-HI) instruction.
 */
void op_MFHI();

/**
 * \brief Executes the MIPS MTHI (move-to-HI) instruction.
 */
void op_MTHI();

/**
 * \brief Executes the MIPS MFLO (move-from-LO) instruction.
 */
void op_MFLO();

/**
 * \brief Executes the MIPS MTLO (move-to-LO) instruction.
 */
void op_MTLO();

/**
 * \brief Executes the MIPS MULT (signed multiply) instruction.
 *
 * Computes the 64-bit product of rs and rt and stores it in HI:LO.
 */
void op_MULT();

/**
 * \brief Executes the MIPS MULTU (unsigned multiply) instruction.
 *
 * Computes the 64-bit unsigned product of rs and rt and stores it
 * in HI:LO.
 */
void op_MULTU();

/**
 * \brief Executes the MIPS DIV (signed divide) instruction.
 *
 * Stores the quotient in LO and the remainder in HI; division by
 * zero yields HI = rs and LO = -1.
 */
void op_DIV();

/**
 * \brief Executes the MIPS DIVU (unsigned divide) instruction.
 *
 * Stores the unsigned quotient in LO and the remainder in HI;
 * division by zero yields HI = rs and LO = -1.
 */
void op_DIVU();

/**
 * \brief Executes the MIPS ADD instruction.
 */
void op_ADD();

/**
 * \brief Executes the MIPS SUB instruction.
 */
void op_SUB();

/**
 * \brief Executes the MIPS AND instruction.
 */
void op_AND();

/**
 * \brief Executes the MIPS OR instruction.
 */
void op_OR();

/**
 * \brief Executes the MIPS XOR instruction.
 */
void op_XOR();

/**
 * \brief Executes the MIPS NOR instruction.
 */
void op_NOR();

/**
 * \brief Executes the MIPS SLT (set-on-less-than, signed) instruction.
 */
void op_SLT();

/**
 * \brief Executes the MIPS SLTU (set-on-less-than, unsigned) instruction.
 */
void op_SLTU();

/**
 * \brief Executes the MIPS MFC0 (move-from-Coprocessor-0) instruction.
 */
void op_MFC0();

/**
 * \brief Executes the MIPS MTC0 (move-to-Coprocessor-0) instruction.
 *
 * Writes a GPR into a COP0 register, with special handling for the
 * Status, Cause and BPC registers (including a Xenogears CD-ROM
 * workaround), and may take an interrupt exception when the write
 * enables one.
 */
void op_MTC0();

/**
 * \brief Executes the MIPS BLTZ (branch-on-less-than-zero) instruction.
 */
void op_BLTZ();

/**
 * \brief Executes the MIPS BGEZ (branch-on-greater-than-or-equal-zero) instruction.
 */
void op_BGEZ();

/**
 * \brief Executes the MIPS BLTZAL (branch-on-less-than-zero-and-link) instruction.
 */
void op_BLTZAL();

/**
 * \brief Executes the MIPS BGEZAL (branch-on-greater-than-or-equal-zero-and-link) instruction.
 */
void op_BGEZAL();

/**
 * \brief Executes the MIPS J (jump) instruction.
 */
void op_J();

/**
 * \brief Executes the MIPS JAL (jump-and-link) instruction.
 */
void op_JAL();

/**
 * \brief Executes the MIPS BEQ (branch-on-equal) instruction.
 */
void op_BEQ();

/**
 * \brief Executes the MIPS BNE (branch-on-not-equal) instruction.
 */
void op_BNE();

/**
 * \brief Executes the MIPS BLEZ (branch-on-less-than-or-equal-zero) instruction.
 */
void op_BLEZ();

/**
 * \brief Executes the MIPS BGTZ (branch-on-greater-than-zero) instruction.
 */
void op_BGTZ();

/**
 * \brief Executes the MIPS ADDI (add-immediate) instruction.
 */
void op_ADDI();

/**
 * \brief Executes the MIPS SLTI (set-on-less-than-immediate, signed) instruction.
 */
void op_SLTI();

/**
 * \brief Executes the MIPS SLTIU (set-on-less-than-immediate-unsigned) instruction.
 */
void op_SLTIU();

/**
 * \brief Executes the MIPS ANDI (and-immediate) instruction.
 */
void op_ANDI();

/**
 * \brief Executes the MIPS ORI (or-immediate) instruction.
 */
void op_ORI();

/**
 * \brief Executes the MIPS XORI (xor-immediate) instruction.
 */
void op_XORI();

/**
 * \brief Executes the MIPS LUI (load-upper-immediate) instruction.
 */
void op_LUI();

/**
 * \brief Executes the MIPS LB (load-byte, sign-extended) instruction.
 */
void op_LB();

/**
 * \brief Executes the MIPS LH (load-halfword, sign-extended) instruction.
 */
void op_LH();

/**
 * \brief Executes the MIPS LWL (load-word-left, unaligned) instruction.
 */
void op_LWL();

/**
 * \brief Executes the MIPS LW (load-word) instruction.
 */
void op_LW();

/**
 * \brief Executes the MIPS LBU (load-byte-unsigned, zero-extended) instruction.
 */
void op_LBU();

/**
 * \brief Executes the MIPS LHU (load-halfword-unsigned, zero-extended) instruction.
 */
void op_LHU();

/**
 * \brief Executes the MIPS LWR (load-word-right, unaligned) instruction.
 */
void op_LWR();

/**
 * \brief Executes the MIPS SB (store-byte) instruction.
 */
void op_SB();

/**
 * \brief Executes the MIPS SH (store-halfword) instruction.
 */
void op_SH();

/**
 * \brief Executes the MIPS SWL (store-word-left, unaligned) instruction.
 */
void op_SWL();

/**
 * \brief Executes the MIPS SW (store-word) instruction.
 */
void op_SW();

/**
 * \brief Executes the MIPS SWR (store-word-right, unaligned) instruction.
 */
void op_SWR();

/**
 * \brief Executes the MIPS LWC2 (load-word-to-Coprocessor-2) instruction, loading a word into a GTE data register.
 */
void op_LWC2();

/**
 * \brief Executes the MIPS SWC2 (store-word-from-Coprocessor-2) instruction, storing a GTE data register to memory.
 */
void op_SWC2();

/**
 * \brief Reports an unknown or unimplemented opcode.
 *
 * Logs the opcode, PC and timing counters via ui_error().
 */
void op_UNKNOWN();

/* Decompiled globals (previously generated in src/_gen) */

/** \brief Set by the CD-ROM layer when a Xenogears disc is detected; used by op_MTC0 for a BPC register workaround. */
extern unsigned char xenogears_cd_detected;

/** \brief Register file of Coprocessor 0 (system control). */
extern unsigned int cop0_regs[1];

/** \brief COP0 Status Register. */
extern unsigned int cop0_sr;

/** \brief COP0 Cause Register. */
extern unsigned int cop0_cause;

/** \brief COP0 Exception Program Counter. */
extern unsigned int cop0_epc;
