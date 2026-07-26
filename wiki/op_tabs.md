# Opcode Dispatch Tables Module (op_tabs)

## Overview

The `op_tabs` module implements the core opcode dispatch mechanism for a MIPS R3000 CPU emulator, specifically designed for PlayStation (PS1) emulation. It provides a hierarchical table-driven approach to decode and dispatch MIPS instructions to their respective handler functions.

## Architecture

### Dispatch Hierarchy

The MIPS instruction set uses a two-level decoding scheme:

1. **Primary Opcode** (bits 26-31) - Main instruction category
2. **Secondary Opcode** (varies by instruction type) - Specific operation within the category

```
+------------------+
|  Primary Opcode  | (bits 26-31)
+--------+---------+
         |
         v
+------------------+
|  Secondary       |
|  Decoding        |
+------------------+
```

### Table Structure

The module implements four main dispatch tables:

| Table | Size | Index Source | Purpose |
|-------|------|--------------|---------|
| `cpu_main_table` | 64 entries | bits 26-31 | Primary opcode dispatch |
| `cpu_special_opcode_table` | 64 entries | bits 0-5 | SPECIAL opcode group (0x00) |
| `cpu_bcond_opcode_table` | 32 entries | bits 16-20 | Branch condition opcodes (0x01) |
| `cpu_cop0_table` | 32 entries | bits 21-25 | Coprocessor 0 operations |

## API Reference

### Types

```cpp
typedef void (*OPCODE)();
```
Function pointer type for all opcode handlers.

### Global Tables

#### `cpu_main_table[64]`

Primary dispatch table indexed by the main opcode field.

**Index:** `(cpu_opcode >> 26) & 0x3F`

**Key opcodes:**
- `0x00`: SPECIAL - routes to `cpu_special_opcode_table`
- `0x01`: BCONDZ - routes to `cpu_bcond_opcode_table`  
- `0x10`: COP0 - routes to `cpu_cop0_table`
- `0x12`: GTE - Graphics Transformation Engine (PlayStation specific)
- Memory access instructions: LB, LH, LW, SB, SH, SW, etc.
- Arithmetic: ADDI, SLTI, ANDI, ORI, XORI, LUI

#### `cpu_special_opcode_table[64]`

Secondary dispatch for R-type instructions (opcode 0x00).

**Index:** `cpu_opcode & 0x3F` (function field)

**Implements:**
- Shift operations: SLL, SRL, SRA, SLLV, SRLV, SRAV
- Jump/return: JR, JALR
- System calls: SYSCALL
- HI/LO register access: MFHI, MTHI, MFLO, MTLO
- Arithmetic: MULT, MULTU, DIV, DIVU
- ALU operations: ADD, SUB, AND, OR, XOR, NOR
- Compare: SLT, SLTU

#### `cpu_bcond_opcode_table[32]`

Secondary dispatch for branch conditions.

**Index:** `(cpu_opcode >> 16) & 0x1F` (rt field)

**Implements:**
- Compare and branch: BLTZ, BGEZ
- Branch and link: BLTZAL, BGEZAL

#### `cpu_cop0_table[32]`

Secondary dispatch for Coprocessor 0 operations.

**Index:** `(cpu_opcode >> 21) & 0x1F` (rs field)

**Implements:**
- `0x00`: MFC0 - Move From Coprocessor 0
- `0x04`: MTC0 - Move To Coprocessor 0
- `0x10`: RFE - Return From Exception (PlayStation specific)

### Dispatcher Functions

#### `void op_SPECIAL()`

Dispatcher for opcode 0x00 (SPECIAL). Extracts the function field and calls the appropriate handler from `cpu_special_opcode_table`.

```cpp
void op_SPECIAL() {
    cpu_special_opcode_table[cpu_opcode & 0x3F]();
}
```

#### `void op_BCONDZ()`

Dispatcher for opcode 0x01 (branch conditions). Extracts the condition field and calls the appropriate branch handler.

```cpp
void op_BCONDZ() {
    cpu_bcond_opcode_table[(cpu_opcode >> 16) & 0x1F]();
}
```

#### `void op_COP0()`

Dispatcher for opcode 0x10 (Coprocessor 0). Extracts the coprocessor operation field.

```cpp
void op_COP0() {
    cpu_cop0_table[(cpu_opcode >> 21) & 0x1F]();
}
```

## Instruction Decoding

### MIPS Instruction Formats

The tables support all three MIPS instruction formats:

#### R-Format (Register)
```
+--------+--------+--------+--------+--------+--------+
| opcode |  rs    |  rt    |  rd    | shamt  | funct  |
| 31-26  | 25-21  | 20-16  | 15-11  | 10-6   | 5-0    |
+--------+--------+--------+--------+--------+--------+
```
- Used by: `cpu_special_opcode_table`
- Index: funct field (bits 0-5)

#### I-Format (Immediate)
```
+--------+--------+--------+----------------------+
| opcode |  rs    |  rt    |  immediate           |
| 31-26  | 25-21  | 20-16  |  15-0                |
+--------+--------+--------+----------------------+
```
- Used by: Main table for branches, loads, stores, immediates

#### J-Format (Jump)
```
+--------+----------------------------------------+
| opcode |  target address                        |
| 31-26  |  25-0                                  |
+--------+----------------------------------------+
```
- Used by: J, JAL instructions

## PlayStation Specific Features

### Geometry Transformation Engine (GTE)

The GTE is a PlayStation-specific coprocessor (COP2) that handles 3D geometry calculations:

- **Opcode**: `0x12` in main table
- **Handler**: `gte_exec_opcode()`
- **Purpose**: Matrix operations, perspective transformation, lighting calculations

### Return From Exception (RFE)

The `RFE` instruction is PlayStation-specific for handling exceptions:

- **Index**: `0x10` in COP0 table
- **Purpose**: Restores processor status after exception handling

## Usage Example

```cpp
#include "op_tabs.h"

// Global opcode variable (set by instruction fetch)
extern uint32_t cpu_opcode;

// Execute current instruction
void execute_instruction() {
    // Primary dispatch
    cpu_main_table[(cpu_opcode >> 26) & 0x3F]();
}

// Example: Executing an ADD instruction
// opcode = 0x00200820 (ADD $1, $1, $1)
// 1. Primary: 0x00 -> op_SPECIAL()
// 2. Secondary: 0x20 -> op_ADD()
```

## Error Handling

The `op_UNKNOWN` handler is used for:
- Undefined opcodes
- Unimplemented instructions
- Invalid coprocessor operations

## Memory Layout

The original assembly implementation shows the tables located at:
- `cpu_special_opcode_table`: 0x00455C80
- `cpu_cop0_table`: 0x00455D80
- `cpu_bcond_opcode_table`: 0x00455E00
- `cpu_main_table`: 0x00455E80

## Performance Considerations

1. **Table-driven dispatch** - O(1) instruction decoding
2. **Function pointers** - Eliminates conditional branching overhead
3. **Static tables** - No runtime initialization required
4. **Cache-friendly** - Tables are small and contiguous in memory

## Dependencies

- `pch.h` - Precompiled header
- `cpu.h` - CPU state variables

## Related Components

- **CPU Core**: Uses this module for instruction dispatch
- **Memory System**: Provides data for load/store instructions
- **Exception Handler**: Interfaces with COP0 for exception management
- **GTE Core**: Handles PlayStation-specific geometry calculations