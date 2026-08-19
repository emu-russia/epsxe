#pragma once

/**
 * \file op_tabs.h
 * \brief MIPS opcode dispatch table for the interpreter.
 *
 * Declares the handler-function pointer type used by the interpreter
 * and the main opcode dispatch table that maps primary opcodes to
 * their instruction handlers.
 */

/** \brief Pointer type for a MIPS instruction handler function (takes no arguments, returns void). */
typedef void (*OPCODE)();

/** \brief Main MIPS opcode dispatch table, indexed by bits 26-31 of the opcode; each entry is the handler for that primary opcode. */
extern OPCODE cpu_main_table[64];


