### MIPS Instruction Types

| Type | -31- | Format (bits) | -0- |
|------|------|---------------|-----|
| R    | opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) |
| I    | opcode (6) | rs (5) | rt (5) | immediate (16) |
| J    | opcode (6) | address (26) |

### R-Type Instructions (Opcode 000000)

Main processor instructions that do not require a target address, immediate value, or branch displacement use an R-type coding format. This format has fields for specifying up to three registers and a shift amount.

For instructions that do not use all of these fields, the unused fields are coded with all 0 bits. All R-type instructions use a 000000 opcode. The operation is specified by the function field.

| opcode (6) | rs (5) | rt (5) | rd (5) | sa (5) | function (6) |
|------------|--------|--------|--------|--------|--------------|

#### Instructions

| Instruction | Format | opcode | rs | rt | rd | sa | function |
|-------------|--------|--------|----|----|----|----|----------|
| add | rd, rs, rt | 000000 | | | | | 100000 |
| addu | rd, rs, rt | 000000 | | | | | 100001 |
| and | rd, rs, rt | 000000 | | | | | 100100 |
| break | | 000000 | 0 | 0 | 0 | 0 | 001101 |
| div | rs, rt | 000000 | | | 0 | 0 | 011010 |
| divu | rs, rt | 000000 | | | 0 | 0 | 011011 |
| jalr | rd, rs | 000000 | | 0 | | 0 | 001001 |
| jr | rs | 000000 | | 0 | 0 | 0 | 001000 |
| mfhi | rd | 000000 | 0 | 0 | | 0 | 010000 |
| mflo | rd | 000000 | 0 | 0 | | 0 | 010010 |
| mthi | rs | 000000 | | 0 | 0 | 0 | 010001 |
| mtlo | rs | 000000 | | 0 | 0 | 0 | 010011 |
| mult | rs, rt | 000000 | | | 0 | 0 | 011000 |
| multu | rs, rt | 000000 | | | 0 | 0 | 011001 |
| nor | rd, rs, rt | 000000 | | | | | 100111 |
| or | rd, rs, rt | 000000 | | | | | 100101 |
| sll | rd, rt, sa | 000000 | 0 | | | | 000000 |
| sllv | rd, rt, rs | 000000 | | | | 0 | 000100 |
| slt | rd, rs, rt | 000000 | | | | | 101010 |
| sltu | rd, rs, rt | 000000 | | | | | 101011 |
| sra | rd, rt, sa | 000000 | 0 | | | | 000011 |
| srav | rd, rt, rs | 000000 | | | | 0 | 000111 |
| srl | rd, rt, sa | 000000 | 0 | | | | 000010 |
| srlv | rd, rt, rs | 000000 | | | | 0 | 000110 |
| sub | rd, rs, rt | 000000 | | | | | 100010 |
| subu | rd, rs, rt | 000000 | | | | | 100011 |
| syscall | | 000000 | 0 | 0 | 0 | 0 | 001100 |
| xor | rd, rs, rt | 000000 | | | | | 100110 |

### I-Type Instructions (All opcodes except 000000, 00001x, and 0100x)

I-type instructions have a 16-bit immediate field that codes an immediate operand, a branch target offset, or a displacement for a memory operand. For a branch target offset, the immediate field contains the signed difference between the address of the following instruction and the target label, with the two low order bits dropped. The dropped bits are always 0 since instructions are word-aligned.

For the bgez, bgtz, blez, and bltz instructions, the rt field is used as an extension of the opcode field.

| opcode (6) | rs (5) | rt | immediate (16) |
|------------|--------|----|----------------|

#### Instructions

| Instruction | Format | opcode | rs | rt | immediate |
|-------------|--------|--------|----|----|-----------|
| addi | rt, rs, immediate | 001000 | | | |
| addiu | rt, rs, immediate | 001001 | | | |
| andi | rt, rs, immediate | 001100 | | | |
| beq | rs, rt, label | 000100 | | | |
| bgez | rs, label | 000001 | | rt = 00001 | |
| bgtz | rs, label | 000111 | | rt = 00000 | |
| blez | rs, label | 000110 | | rt = 00000 | |
| bltz | rs, label | 000001 | | rt = 00000 | |
| bne | rs, rt, label | 000101 | | | |
| lb | rt, immediate(rs) | 100000 | | | |
| lbu | rt, immediate(rs) | 100100 | | | |
| lh | rt, immediate(rs) | 100001 | | | |
| lhu | rt, immediate(rs) | 100101 | | | |
| lui | rt, immediate | 001111 | 0 | | |
| lw | rt, immediate(rs) | 100011 | | | |
| lwc1 | rt, immediate(rs) | 110001 | | | |
| ori | rt, rs, immediate | 001101 | | | |
| sb | rt, immediate(rs) | 101000 | | | |
| slti | rt, rs, immediate | 001010 | | | |
| sltiu | rt, rs, immediate | 001011 | | | |
| sh | rt, immediate(rs) | 101001 | | | |
| sw | rt, immediate(rs) | 101011 | | | |
| swc1 | rt, immediate(rs) | 111001 | | | |
| xori | rt, rs, immediate | 001110 | | | |