import idaapi
import idautils
import idc
import os
import sys

# Force load Hex-Rays plugin (may be redundant in IDA 8+)
plugin_name = "hexrays"
result = idaapi.load_plugin(plugin_name)

if result:
    print(f"[-] Plugin '{plugin_name}' loaded successfully!")
else:
    print(f"[!] Failed to load plugin '{plugin_name}'")

# Check if decompilation feature is available
if not hasattr(idaapi, "decompile"):
    print("Error: Hex-Rays decompiler plugin could not be loaded or is not available.")
    sys.exit(1)
else:
    print("Hex-Rays decompiler plugin initialized successfully.")

# Setup output directory paths
idb_path = idc.get_idb_path()          # correct for IDA 8+
idb_dir = os.path.dirname(idb_path)
output_dir = os.path.join(idb_dir, "../decompiled")

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

print(f"Saving decompiled functions to: {output_dir}")

def generate_disasm_line(ea):
    """
    Generate disassembly line compatible with different IDA versions.
    Returns disassembly string or None.
    """
    try:
        # Modern IDA API (preferred)
        return idaapi.generate_disasm_line(ea, 0)
    except Exception:
        # Fallback: use idc.get_disasm (works in most cases)
        try:
            return idc.get_disasm(ea)
        except Exception:
            return None

def fix_stack_pointer(ea):
    """
    Attempt to fix stack pointer issues for the function at address ea.
    Returns True if fix was applied.
    """
    try:
        func = idaapi.get_func(ea)
        if not func:
            return False

        # Get current stack pointer value at function start
        sp_value = idc.get_spd(ea)

        # If SP is positive, try to fix it by setting it to 0
        if sp_value > 0:
            print(f"    Attempting to fix stack pointer at 0x{ea:X} (current SP: {sp_value})")

            # Set stack pointer to 0 at function entry
            idc.set_spd(ea, 0)

            # Try to fix stack pointer throughout the function
            current_ea = func.start_ea
            while current_ea < func.end_ea:
                if idc.is_code(idc.get_flags(current_ea)):
                    current_sp = idc.get_spd(current_ea)
                    if current_sp > 0:
                        # Adjust stack pointer to be 0 or negative
                        idc.set_spd(current_ea, min(0, current_sp - sp_value))
                current_ea = idc.next_head(current_ea, func.end_ea)

            # Force re-analysis of the function
            idaapi.auto_wait()
            if hasattr(idaapi, "analyze_area"):
                idaapi.analyze_area(func.start_ea, func.end_ea)
            else:
                idc.analyze_area(func.start_ea, func.end_ea)
            return True
    except Exception as e:
        print(f"    [!] Error while fixing stack pointer: {e}")

    return False

def get_disassembly_listing(ea, error_msg=""):
    """Generate commented disassembly listing for function at ea."""
    disasm_lines = []

    func = idaapi.get_func(ea)
    if not func:
        return [f"// Cannot find function at address 0x{ea:X}"]

    func_start = func.start_ea
    func_end = func.end_ea

    # Add header
    disasm_lines.append("// " + "="*70)
    disasm_lines.append(f"// Function: {idc.get_func_name(ea)}")
    disasm_lines.append(f"// Address: 0x{func_start:X} - 0x{func_end:X}")
    if error_msg:
        disasm_lines.append(f"// Error: {error_msg}")
    disasm_lines.append(f"// SP value at entry: {idc.get_spd(ea)}")
    disasm_lines.append("// " + "="*70)
    disasm_lines.append("")

    # Get disassembly for each instruction
    current_ea = func_start
    while current_ea < func_end:
        try:
            # Generate disassembly line
            disasm_line = generate_disasm_line(current_ea)

            if disasm_line:
                # Get instruction bytes
                insn_len = idc.get_item_size(current_ea)
                bytes_str = ""
                for i in range(insn_len):
                    byte_val = idc.get_byte(current_ea + i)
                    if byte_val is not None:
                        bytes_str += f"{byte_val:02X} "
                bytes_str = bytes_str.strip()

                # Get SP delta if available
                sp_delta = idc.get_spd(current_ea)

                # Get any comments
                comment = idc.get_comment(current_ea, 0)
                rpt_comment = idc.get_comment(current_ea, 1)

                # Format the line
                line = f"// 0x{current_ea:08X}: {bytes_str:<24} {disasm_line}"
                if sp_delta:
                    line += f"  ; sp={sp_delta}"
                disasm_lines.append(line)

                # Add comments if they exist
                if comment:
                    disasm_lines.append(f"// {' '*68} ; {comment}")
                if rpt_comment:
                    disasm_lines.append(f"// {' '*68} ; (repeatable) {rpt_comment}")

            else:
                # If disassembly generation failed
                insn_len = idc.get_item_size(current_ea)
                bytes_str = ""
                for i in range(insn_len):
                    byte_val = idc.get_byte(current_ea + i)
                    if byte_val is not None:
                        bytes_str += f"{byte_val:02X} "
                bytes_str = bytes_str.strip()
                disasm_lines.append(f"// 0x{current_ea:08X}: {bytes_str:<24} [Unable to disassemble]")

        except Exception as e:
            disasm_lines.append(f"// 0x{current_ea:08X}: [Error reading instruction: {e}]")

        # Move to next instruction
        next_ea = idc.next_head(current_ea, func_end)
        if next_ea == current_ea or next_ea == 0xFFFFFFFF:
            break
        current_ea = next_ea

    disasm_lines.append("")
    disasm_lines.append("// " + "="*70)
    disasm_lines.append(f"// End of disassembly for {idc.get_func_name(ea)}")

    return disasm_lines

# Get total number of functions for progress counter
all_functions = list(idautils.Functions())

# Excluding LIB
filtered_functions = []
for ea in all_functions:
    func = idaapi.get_func(ea)
    if func and (func.flags & idaapi.FUNC_LIB):
        continue
    filtered_functions.append(ea)
all_functions = filtered_functions

total_functions = len(all_functions)
current_function = 0
failed_functions = []
fixed_functions = []

# Iterate through all functions in the binary
for ea in all_functions:
    current_function += 1
    func_name = idc.get_func_name(ea)
    if not func_name:
        continue

    # Sanitize the function name for the file system
    safe_chars = [c for c in func_name if c.isalnum() or c == '_']
    safe_func_name = "".join(safe_chars).strip()
    filename = f"{safe_func_name}.c"
    out_file = os.path.join(output_dir, filename)

    decompiled_successfully = False
    error_message = ""

    try:
        # First attempt: try to decompile normally
        cfunc = idaapi.decompile(ea)
        if cfunc:
            decompiled_successfully = True
            with open(out_file, "w", encoding="utf-8") as f:
                f.write("#include \"pch.h\"\n")
                f.write(str(cfunc))
            print(f"[{current_function} / {total_functions}] Decompiled: {func_name} -> {filename}")

    except Exception as e:
        error_message = str(e)
        print(f"[{current_function} / {total_functions}] First attempt failed for {func_name}: {error_message}")

    # If first attempt failed, try to fix stack pointer and decompile again
    if not decompiled_successfully:
        sp_value = idc.get_spd(ea)
        if sp_value > 0 or "positive sp value" in error_message.lower():
            print(f"[{current_function} / {total_functions}] Stack pointer issue detected for {func_name} (SP={sp_value}), attempting fix...")

            if fix_stack_pointer(ea):
                fixed_functions.append(func_name)
                # Try decompilation again after fixing
                try:
                    idaapi.auto_wait()  # Wait for autoanalysis to complete
                    cfunc = idaapi.decompile(ea)
                    if cfunc:
                        decompiled_successfully = True
                        with open(out_file, "w", encoding="utf-8") as f:
                            f.write(str(cfunc))
                        print(f"[{current_function} / {total_functions}] Successfully decompiled after SP fix: {func_name} -> {filename}")
                except Exception as e:
                    error_message = str(e)
                    print(f"[{current_function} / {total_functions}] Decompilation still failed after SP fix: {error_message}")
            else:
                print(f"[{current_function} / {total_functions}] Could not fix stack pointer for {func_name}")

    # If still failed, dump disassembly
    if not decompiled_successfully:
        failed_functions.append((func_name, error_message))
        print(f"[{current_function} / {total_functions}] Dumping disassembly for: {func_name}")

        try:
            with open(out_file, "w", encoding="utf-8") as f:
                # Write decompilation failure header in C style
                f.write("/*\n")
                f.write(" * WARNING: Hex-Rays decompilation failed for this function\n")
                f.write(f" * Function: {func_name}\n")
                f.write(f" * Address: 0x{ea:X}\n")
                if error_message:
                    f.write(f" * Error: {error_message}\n")
                f.write(f" * Stack pointer at entry: {idc.get_spd(ea)}\n")
                f.write(" * \n")
                f.write(" * The following is a disassembly listing for manual analysis.\n")
                f.write(" * Each instruction is commented with // for C compatibility.\n")
                f.write(" */\n\n")

                # Write disassembly
                disasm_lines = get_disassembly_listing(ea, error_message)
                for line in disasm_lines:
                    f.write(line + "\n")

        except Exception as write_e:
            print(f"[!] Critical error writing disassembly for {func_name}: {write_e}")

# Print summary
print("\n" + "="*70)
print("BATCH DECOMPILATION SUMMARY")
print("="*70)
print(f"Total functions processed: {total_functions}")
print(f"Successfully decompiled: {total_functions - len(failed_functions)}")
print(f"Failed to decompile: {len(failed_functions)}")
print(f"Functions with stack fixes applied: {len(fixed_functions)}")

if failed_functions:
    print("\nFailed functions list:")
    for func_name, error in failed_functions:
        print(f"  - {func_name}: {error}")

if fixed_functions:
    print("\nFunctions with applied stack fixes:")
    for func_name in fixed_functions:
        print(f"  - {func_name}")

print("="*70)
print(f"Output directory: {output_dir}")
print("Batch decompilation finished.")