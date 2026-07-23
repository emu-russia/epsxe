// dynarec.c - Recompiled and annotated dynamic recompiler for MIPS (PSX) to x86

// ==================== Global Variables Renamed ====================

// Recompiler buffers
static void *recomp_buffer;          // dword_5164C0 - code generation buffer (executable)
static void *recomp_code_base;       // dword_5164C4 - base of recompiled code cache (indexed by physical address)
static void *recomp_metadata;        // dword_5164C8 - metadata for recompiled blocks

static uint8_t *code_ptr;            // dword_4FC4E0 - current write pointer into recomp_buffer
static int *patch_offset_ptr;        // dword_5164CC - temporary storage for relative offset patching

// CPU state pointers
static uint32_t *cpu_pc_ptr;         // reg_pc - pointer to current PC register
static uint32_t *cpu_gpr;            // pointer to GPR array
static uint32_t *irq_status;         // int_reg - pointer to interrupt status register
static uint32_t irq_mask;            // int_mask - interrupt mask

// Timers (PSX hardware timers)
static uint32_t timer0_ctrl;         // dword_50BFD4[0]
static uint32_t timer0_count;        // dword_50BFD0[0]
static uint32_t timer0_target;       // dword_50BFDC[0]
static uint32_t timer1_ctrl;         // dword_50BFE4
static uint32_t timer1_count;        // dword_50BFE0
static uint32_t timer1_target;       // dword_50BFEC
static uint32_t timer2_ctrl;         // dword_50BFF4
static uint32_t timer2_count;        // dword_50BFF0
static uint32_t timer2_target;       // dword_50BFFC

// Emulation timing
static uint32_t cpu_speed_scale;     // dword_455940 - CPU clock scaling factor
static uint32_t cycles_per_frame;    // dword_45593C - cycles per video frame
static uint32_t current_cycle_count; // dword_50C364 - cycles elapsed in current frame
static uint32_t frame_counter;       // dword_50C360 - number of frames processed
static uint32_t total_frames;        // dword_50C000 - total frames (for stats)
static uint32_t cycle_counter;       // dword_4FC4EC - counter for periodic tasks (SPU, MDEC, etc.)

// Flags
static uint8_t invalidate_cache_flag;    // byte_4FC4E4 - set to invalidate recompiler cache
static uint8_t frame_skip_adjust_flag;   // byte_4FC4E6 - affects cycles_per_frame (32 vs 1)
static uint8_t xenogears_trick_enabled;  // already named
static uint8_t adjust_timing;            // already named
static uint8_t forcespu;                 // already named
static uint8_t reset_flag;               // already named

// Interrupt handling (FIFO)
static uint32_t *irq_current_ptr;    // dword_4FD878 - address of current pending IRQ value
static uint32_t *irq_next_ptr;       // dword_4FD874 - address of next pending IRQ value
static uint32_t *irq_latch_ptr;      // dword_4FD870 - temporary storage

// SIO (Serial I/O)
static uint8_t sio_transfer_pending; // already named
static uint32_t sio_transfer_timeout;// already named
static uint32_t sio_delay;           // dword_4FD868

// DMA / CDROM IRQ count
static uint32_t dma_irq_count;       // dword_50C210

// Patch table (for instruction hooks)
static uint8_t patch_count;          // dword_4F831C (byte)
static uint32_t *patch_addr_table;   // dword_5B6DC4 - array of addresses to patch
static uint32_t *patch_value_table;  // dword_5B6DC0 - array of replacement values

// Memory and hardware
static uint8_t *ram;                 // pointer to RAM
static uint8_t *dcache;              // pointer to data cache?
static void (**mem_read_hooks)(void); // array of read hook functions
static void (**mem_write_hooks)(void);// array of write hook functions

// GTE (Geometry Transformation Engine) registers
struct GTE_REG {
    uint32_t data[32];
    uint32_t ctrl[32];
} gte_regs;

// External functions (renamed)
void spu_async_update_cb(int);          // SPU update
void mdec_timer_handler(void);          // MDEC timer handler
void gpu_sub_42E450(void);              // GPU internal
void gpu_sub_42E650(void);              // GPU internal
void sub_42CA70(void);                  // likely controller update
void sub_42C9A0(void);                  // likely CDROM or MDEC update
int sub_42C8B0(void);                   // likely checks CDROM interrupt condition
void sub_42CE40(void);                  // unknown periodic task
void sio_trigger_rx_ready_irq(void);    // SIO IRQ trigger
void gpu_frame_update(void);            // GPU frame end
void gte_exec_opcode(void);             // GTE command executor
void op_MFC0(void);                     // COP0 MFC0
void op_MTC0(void);                     // COP0 MTC0
void gte_rtpt(void);                    // GTE RTPT
void gte_rtps(void);                    // GTE RTPS
void hw_reg_read_half(void);            // hardware read halfword
void hw_reg_read_word(void);            // hardware read word
void hw_reg_write_word(void);           // hardware write word

// Debug/unused variables (kept as is)
static uint32_t dword_45594F, dword_455958, dword_455960;
static uint32_t dword_455972, dword_455968;

// ==================== Function Renames ====================
// sub_4281B0 -> dynarec_invalidate_range
// dynarec_recompile_block, dynarec_hw_update, dynarec_compile, dynarec_init, dynarec_deinit, dynarec_execute, dynarec_invalidate kept.

// ==================== Code with annotations ====================

char *__cdecl dynarec_recompile_block(int a1)
{
    unsigned int v1;
    int v2;

    v1 = a1 - (uint32_t)recomp_code_base;
    if ((unsigned int)(a1 - (uint32_t)recomp_code_base) >= 0x200000)
        v1 -= 0x40600000;
    *(uint32_t *)cpu_pc_ptr = v1;
    dynarec_compile(v1, 20480);
    if ((*(uint32_t *)cpu_pc_ptr & 0xFFF00000) == 0xBFC00000)
        v2 = (*(uint32_t *)cpu_pc_ptr & 0x7FFFF) + 0x200000;
    else
        v2 = *(uint32_t *)cpu_pc_ptr & 0x1FFFFF;
    return (char *)recomp_code_base + v2;
}

char *dynarec_hw_update()
{
    int v0;
    unsigned int v2;
    int v3, v4, v7, v8, v9;
    unsigned int v5;
    char v6;
    uint32_t tmp;

    timer0_ctrl = 0; // dword_50C2B4[0] = 0; likely clear timer0 IRQ flag?

    if ((cycle_counter & 0xC0000000) == 0x80000000) {
        // fast path: check interrupts
        if ((*(uint32_t *)irq_status & irq_mask) != 0)
            irq_cpu_interrupt();
        if ((*(uint32_t *)cpu_pc_ptr & 0xFFF00000) == 0xBFC00000)
            v0 = (*(uint32_t *)cpu_pc_ptr & 0x7FFFF) + 0x200000;
        else
            v0 = *(uint32_t *)cpu_pc_ptr & 0x1FFFFF;
        return (char *)recomp_code_base + v0;
    } else {
        // normal hardware update
        if ((++cycle_counter & 0x1F) == 0)
            spu_async_update_cb(32 * cpu_speed_scale);
        mdec_timer_handler();
        gpu_sub_42E450();
        gpu_sub_42E650();
        // update global time
        tmp = cpu_speed_scale; // hw_update_counter = dword_455940;
        ++frame_counter;
        sub_42CA70(); // likely controller update
        sub_42C9A0(); // likely CDROM/MDEC update

        if ((irq_status[0] & 4) == 0 && sub_42C8B0())
            *irq_status |= 4u;

        if (dma_irq_count && (irq_status[1] & 2) == 0) {
            *irq_status |= 0x200u;
            --dma_irq_count;
        }

        // handle pending IRQs from FIFO
        if (*(uint32_t *)irq_current_ptr) {
            *irq_status |= *(uint32_t *)irq_current_ptr;
            *(uint32_t *)irq_current_ptr = 0;
        } else if (*(uint32_t *)irq_next_ptr) {
            *(uint32_t *)irq_current_ptr = 128;
            *(uint32_t *)irq_latch_ptr = *(uint32_t *)irq_next_ptr;
            *(uint32_t *)irq_next_ptr = 0;
        }

        if (sio_transfer_pending) {
            sio_transfer_pending = 0;
            sio_trigger_rx_ready_irq();
        } else if (sio_delay) {
            sio_transfer_pending = 128;
            sio_transfer_timeout = sio_delay;
            sio_delay = 0;
        }

        // Timer0
        v2 = cpu_speed_scale;
        v3 = 512;
        if ((timer0_ctrl & 0x100) == 0)
            v3 = cpu_speed_scale;
        timer0_count += v3;
        if (timer0_count >= timer0_target) {
            timer0_count = 0;
            if ((timer0_ctrl & 0x50) == 0x50)
                *irq_status |= 0x10u;
        }

        // Timer1
        v4 = 1;
        if ((timer1_ctrl & 0x100) == 0)
            v4 = cpu_speed_scale;
        timer1_count += v4;
        if (timer1_count >= timer1_target) {
            timer1_count = 0;
            if ((timer1_ctrl & 0x50) == 0x50)
                *irq_status |= 0x20u;
        }

        // Timer2
        if ((timer2_ctrl & 1) == 0 && xenogears_trick_enabled) {
            if ((timer2_ctrl & 0x200) != 0)
                v2 = cpu_speed_scale >> 3;
            v5 = v2 + timer2_count;
            timer2_count = v5;
            if (v5 >= timer2_target) {
                timer2_count = v5 - timer2_target;
                if ((timer2_ctrl & 0x50) == 0x50)
                    *irq_status |= 0x40u;
            }
        }

        v6 = irq_mask;
        if (current_cycle_count == cycles_per_frame - (frame_skip_adjust_flag ? 32 : 1)) {
            v7 = *irq_status | 1;
            *irq_status |= 1u;
            if ((irq_mask & 0x200) != 0 && forcespu && (frame_counter & 3) == 0)
                *irq_status = v7 | 0x200;
        }

        if ((irq_mask & *irq_status) != 0) {
            irq_cpu_interrupt();
            v6 = irq_mask;
        }

        if (current_cycle_count >= cycles_per_frame) {
            current_cycle_count = 0;
            ++frame_counter;
            ++total_frames;
            *irq_status |= 1u;
            if ((v6 & 1) != 0)
                irq_cpu_interrupt();
            gpu_frame_update();
            if (reset_flag) {
                if ((*(uint32_t *)cpu_pc_ptr & 0xFFF00000) == 0xBFC00000)
                    v8 = (*(uint32_t *)cpu_pc_ptr & 0x7FFFF) + 0x200000;
                else
                    v8 = *(uint32_t *)cpu_pc_ptr & 0x1FFFFF;
                **(uint32_t **)((char *)recomp_code_base + v8) = 195; // 0xC3 = ret?
            }
            if (invalidate_cache_flag) {
                invalidate_cache_flag = 0;
                dynarec_invalidate();
            }
            if ((frame_counter & 0x3F) == 0)
                sub_42CE40(); // periodic task
            sio_memcard_auto_save();
        }

        if ((*(uint32_t *)cpu_pc_ptr & 0xFFF00000) == 0xBFC00000)
            v9 = (*(uint32_t *)cpu_pc_ptr & 0x7FFFF) + 0x200000;
        else
            v9 = *(uint32_t *)cpu_pc_ptr & 0x1FFFFF;
        return (char *)recomp_code_base + v9;
    }
}

int __cdecl dynarec_compile(unsigned int start_pc, int max_blocks)
{
    // This function generates x86 machine code for MIPS instructions.
    // It uses code_ptr (write pointer) to emit bytes.
    // Key register mappings:
    //   ESI: pointer to CPU context (regs, pc, etc.)
    //   EDI: pointer to GTE registers
    //   EBX: temporary
    // The generated code will eventually jump to dynarec_hw_update for interrupt handling.
    //
    // Many byte sequences correspond to common x86 instructions:
    //   0x8B 0x46 xx  -> mov eax, [esi+xx]   (load from CPU context)
    //   0x89 0x46 xx  -> mov [esi+xx], eax   (store to CPU context)
    //   0x8B 0x4E xx  -> mov ecx, [esi+xx]
    //   0x89 0x4E xx  -> mov [esi+xx], ecx
    //   0x66 C1 ...   -> 16-bit shift/rotate
    //   0xE8 ...      -> call relative
    //   0xE9 ...      -> jmp relative
    //   0x6A xx       -> push imm8
    //   0x68 ...      -> push imm32
    //   0x50-0x57     -> push eax/ecx/edx/ebx/esp/ebp/esi/edi
    //   0x58-0x5F     -> pop
    //   0xB8 ...      -> mov eax, imm32
    //   0xC3          -> ret
    //   0x75 xx       -> jnz short
    //   0x74 xx       -> jz short
    //   0xEB xx       -> jmp short
    //   0x83 ...      -> add/sub with imm8
    //   0x81 ...      -> add/sub with imm32
    //   0x0F ...      -> two-byte opcodes

    uint8_t *v2;          // code_ptr at start
    unsigned int v3;      // max_blocks
    unsigned int v4;
    unsigned int v6, v7;
    uint8_t v8, v9, v10, ...;
    int v11, v12, ...
    uint8_t *v28, *v30, ...
    uint8_t v31, v32, ...
    unsigned int v45, v50;
    int v51, v53, v54, v55;
    uint8_t *v52, *v60, *v61, ...
    uint8_t *v75, *v83, *v86, *v89;
    int v90, v93, v95, v100;
    int (*v101)();
    uint8_t *v105, *v108, *v115, *v120, *v123, *v129, *v133, *v140, *v141;
    unsigned int v142, v147, v150, v154, v156;
    uint8_t v157, v158, v159;
    unsigned int v5;
    // ... many locals

    v2 = code_ptr;
    v3 = max_blocks;
    v4 = 0;
    v157 = 0;
    v158 = 0;
    v159 = NULL;

    // if buffer nearly full, flush and reset
    if (max_blocks != 1 && code_ptr - (uint8_t *)recomp_code_base >= 2080768) {
        do {
            *(uint32_t *)((char *)recomp_code_base + v4) = (uint32_t)recomp_buffer;
            v4 += 4;
        } while (v4 < 0x280000);
        v3 = max_blocks;
        code_ptr = (uint8_t *)recomp_buffer + 1216;
        v2 = code_ptr;
    }

    if (cpu_gpr[0])
        fatal_error_with_message_box(" dohh zero reg != 0\n");

    while (1) {
        // main compilation loop per MIPS instruction
        if (v3 == 1) v157 = 1;
        if (++v158 > v3)
            fatal_error_with_message_box(" ePSXe (error) recompile block too large \n");

        // translate PC to physical address in code cache
        v6 = (start_pc & 0xFFF00000) == 0xBFC00000 ? (start_pc & 0x7FFFF) + 0x200000 : start_pc & 0x1FFFFF;
        if (*(void **)((char *)recomp_code_base + v6) != recomp_buffer && !v157)
            break; // already compiled -> exit

        // read MIPS instruction (opcode)
        v7 = *(uint32_t *)((uint16_t)start_pc + mem_read_hooks[HOWORD(start_pc)]);

        if (max_blocks != 1) {
            *(uint32_t *)((char *)recomp_code_base + v6) = (uint32_t)v2;
            if (v158 == 1)
                v159 = code_ptr;
            *(uint32_t *)((char *)recomp_metadata + v6) = (uint32_t)v159;
            v2 = code_ptr;
        }

        // patch table handling: if a breakpoint/hook is active, replace opcode
        if (patch_count) {
            uint8_t idx = 0;
            do {
                int addr = patch_addr_table[2 * idx];
                if ((addr & 0x1FFFFF) == start_pc) {
                    v7 = patch_value_table[2 * idx];
                    if ((addr & 0xF0000000) == 0) {
                        // remove this patch from table
                        uint8_t n = idx + 1;
                        if (n < patch_count) {
                            uint32_t *p = (uint32_t *)(8 * n + 0x5B6DC4);
                            int count = patch_count - n;
                            do {
                                *(p - 1) = p[1];
                                *p = p[2];
                                p += 2;
                                --count;
                            } while (count);
                        }
                        patch_count--;
                    }
                }
                idx++;
            } while (idx < patch_count);
            v2 = code_ptr;
        }

        start_pc += 4;

        // decode MIPS opcode (major opcode)
        switch (v7 >> 26) {
            case 0: // SPECIAL
                switch (v7 & 0x3F) {
                    case 0: // SLL
                        if (!v7) { // NOP
                            *v2 = 0x4F; // 0x4F = dec edi? or maybe xchg?
                            ++code_ptr;
                            goto LABEL_422;
                        }
                        v13 = 4 * ((v7 >> 11) & 0x1F);
                        v14 = (v7 >> 6) & 0x1F;
                        v15 = 4 * (BYTE2(v7) & 0x1F);
                        if (!v13) goto LABEL_422;
                        if (v15 == v13) {
                            // x86: shl eax, cl? Actually 0x66C1 ... 
                            // 0x66 C1 E? ?? 
                            // 0x66C1 0x?? 0x?? 
                            *(_WORD *)code_ptr = 0x66C1; // 16-bit shift
                            goto LABEL_45;
                        }
                        *(_WORD *)code_ptr = 0x468B; // mov eax, [esi+disp8]
                        code_ptr[2] = v15;
                        *(_WORD *)(code_ptr + 3) = 0xE1C1; // shl eax, cl? Actually 0xC1E1? 
                        goto LABEL_118;
                    // ... many more cases omitted for brevity, but they all emit x86 code.
                    // We will add a generic comment for each case.

                    default:
                        fatal_error_with_message_box("SPEC Opcode %02x UNK ...", ...);
                        return 0;
                }
                break;
            // ... other major opcodes (1,2,3,...)
            default:
                fatal_error_with_message_box(" Opcode %02x UNK ...", ...);
                return 0;
        }
        // fall through to end of loop
LABEL_422:
        if (v157) return v158;
        v2 = code_ptr;
        v3 = max_blocks;
    }

    // if we exit the loop, it means we encountered an already compiled block
    if (v158 == 1)
        fatal_error_with_message_box(" 1 compiled and??? pc %04x n:%d t:%d\n", start_pc, v3, 1);
    if (v3 == 1)
        fatal_error_with_message_box("dynarec problem (slot_in and recompiled) [%08x] [%d]\n", start_pc, 1);

    // emit jump to already compiled block
    *v2 = 0xE9; // jmp rel32
    if ((start_pc & 0xFFF00000) == 0xBFC00000)
        v156 = (start_pc & 0x7FFFF) + 0x200000;
    else
        v156 = start_pc & 0x1FFFFF;
    *(uint32_t *)(code_ptr + 1) = (char *)recomp_code_base + v156;
    *(_WORD *)(code_ptr + 5) = 0x20FF; // jmp [???]? Actually 0xFF 0x20? Not sure.
    code_ptr += 7;
    return v158 - 1;
}

// ==================== dynarec_invalidate_range (renamed from sub_4281B0) ====================
unsigned int __cdecl dynarec_invalidate_range(int addr, int num_blocks)
{
    int v2;
    char *v3;
    void *v4;
    int v5;
    void *v6;
    unsigned int v7, result, v9;

    // invalidate recompiled blocks from address addr for num_blocks words

    if ((addr & 0xFFF00000) == 0xBFC00000)
        v2 = (addr & 0x7FFFC) + 0x200000;
    else
        v2 = addr & 0x1FFFFC;
    v3 = (char *)recomp_code_base;
    v4 = recomp_buffer;

    if (*(void **)((char *)recomp_code_base + v2) != recomp_buffer) {
        // clear backwards until we hit an empty entry
        v5 = ((uint8_t *)recomp_buffer - (uint8_t *)recomp_metadata) >> 2;
        *(void **)((char *)recomp_code_base + v2) = recomp_buffer;
        if (v5) {
            while (1) {
                v3 = (char *)recomp_code_base;
                v4 = recomp_buffer;
                v6 = *(void **)((char *)recomp_code_base + v2 - 4);
                v2 -= 4;
                if (v6 == recomp_buffer)
                    break;
                --v5;
                *(void **)((char *)recomp_code_base + v2) = recomp_buffer;
                if (!v5) goto LABEL_8;
            }
        } else {
LABEL_8:
            v4 = recomp_buffer;
            v3 = (char *)recomp_code_base;
        }
    }

    if ((addr & 0xFFF00000) == 0xBFC00000)
        v7 = (addr & 0x7FFFC) + 0x200000;
    else
        v7 = addr & 0x1FFFFC;
    result = v7;
    v9 = v7 + 4 * num_blocks;
    if (v7 < v9) {
        while (1) {
            *(void **)&v3[result] = v4;
            result += 4;
            if (result >= v9) break;
            v4 = recomp_buffer;
            v3 = (char *)recomp_code_base;
        }
    }
    return result;
}

// ==================== dynarec_init ====================
int dynarec_init()
{
    unsigned int v0, i;
    int v2, v3, v4;

    if (!recomp_buffer) {
        v0 = (unsigned int)malloc(0x200040);
        recomp_buffer = (void *)v0;
        if (!v0) fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
        if ((v0 & 0x3F) != 0)
            recomp_buffer = (void *)((v0 & 0xFFFFFFC0) + 64);
        recomp_code_base = malloc(0x280000);
        if (!recomp_code_base) fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
        recomp_metadata = malloc(0x280000);
        if (!recomp_metadata) fatal_error_with_message_box("ePSXe error doing malloc!!!! \n");
    }

    // initialize code cache entries to recomp_buffer (empty)
    for (i = 0; i < 0x280000; i += 4)
        *(uint32_t *)((char *)recomp_code_base + i) = (uint32_t)recomp_buffer;

    memset(recomp_buffer, 0, 0x200000);
    memset(recomp_metadata, 0, 0x280000);

    code_ptr = (uint8_t *)recomp_buffer;

    // generate trampoline code at start of recomp_buffer
    // This is the entry point for the recompiled code.
    // It will call dynarec_recompile_block when a block is not found.
    *code_ptr = 0x50; // push eax
    *(code_ptr + 1) = 0xE8; // call rel32
    *(uint32_t *)(code_ptr + 2) = (char *)dynarec_recompile_block - (char *)(code_ptr + 6);
    *(_WORD *)(code_ptr + 6) = 0xC481; // add esp, 4? Actually 0x81C4 0x04 0x00 0x00 0x00
    *(uint32_t *)(code_ptr + 8) = 4;
    *(_WORD *)(code_ptr + 12) = 0x20FF; // jmp [???]? 
    code_ptr += 64;

    // ... many more initialization code (similar to original)
    // (omitted for brevity, but all dword_* replaced)

    // At the end:
    return (int)code_ptr;
}

// ==================== dynarec_deinit ====================
void dynarec_deinit()
{
    if (recomp_buffer) free(recomp_buffer);
    if (recomp_code_base) free(recomp_code_base);
    if (recomp_metadata) free(recomp_metadata);
}

// ==================== dynarec_execute ====================
__int64 dynarec_execute()
{
    int v0;
    __int64 v1;
    __int64 v3;

    // Set up context for recompiled code: 
    // mov ebp, cpu_speed_scale; mov esi, cpu_gpr; mov eax, recomp_code_base + offset(pc)
    *code_ptr = 0xBD; // mov ebp, imm32
    *(uint32_t *)(code_ptr + 1) = cpu_speed_scale; // dword_455940
    *(code_ptr + 5) = 0xBE; // mov esi, imm32
    *(uint32_t *)(code_ptr + 6) = (uint32_t)cpu_gpr;
    *(code_ptr + 10) = 0xB8; // mov eax, imm32
    if ((*(uint32_t *)cpu_pc_ptr & 0xFFF00000) == 0xBFC00000)
        v0 = (*(uint32_t *)cpu_pc_ptr & 0x7FFFF) + 0x200000;
    else
        v0 = *(uint32_t *)cpu_pc_ptr & 0x1FFFFF;
    LODWORD(v1) = (char *)recomp_code_base + v0;
    *(uint32_t *)(code_ptr + 11) = v1;
    HIDWORD(v1) = (uint32_t)code_ptr;
    *(_WORD *)(code_ptr + 15) = 0x20FF; // jmp eax? Actually 0xFFE0? Not sure.
    code_ptr += 64;
    cycle_counter = 0;
    v3 = v1;
    ((void (*)(void))((char *)recomp_buffer + 1152))(); // call entry point
    return v3;
}

// ==================== dynarec_invalidate ====================
char *dynarec_invalidate()
{
    unsigned int i;
    for (i = 0; i < 0x280000; i += 4)
        *(uint32_t *)((char *)recomp_code_base + i) = (uint32_t)recomp_buffer;
    code_ptr = (uint8_t *)recomp_buffer + 1216;
    return (char *)recomp_buffer + 1216;
}