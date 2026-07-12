#!/usr/bin/env python3
"""
IDA Python script: Export global data variables (db, dw, dd, dq, arrays)
from .data and .rdata sections into .c and .h files.
Skips string literals and const char[] arrays.
"""

import idautils
import ida_segment
import ida_bytes
import ida_typeinf
import idc
import ida_kernwin

def is_data_or_rdata_segment(seg):
    """Check if segment is .data or .rdata (including variants like .data.rel.ro)."""
    name = ida_segment.get_segm_name(seg).lower()
    if name in ('.data', '.rdata'):
        return True
    if name.startswith('.data.') or name.startswith('.rdata.'):
        return True
    return False

def is_const_char_array(ea):
    """Return True if IDA type for this address is const char[] or similar string type."""
    t = idc.get_type(ea)
    if t is None:
        return False
    # Normalize: remove whitespace and check if it's a const char array
    t_norm = ' '.join(t.split())
    if t_norm.startswith('const char [') or t_norm.startswith('char const ['):
        return True
    return False

def export_variables():
    # Ask user for output .c file path
    c_path = ida_kernwin.ask_file(1, "*.c", "Select output C file")
    if not c_path:
        print("[!] Export cancelled.")
        return
    h_path = c_path[:-2] + ".h" if c_path.endswith('.c') else c_path + ".h"

    variables = []
    processed = set()

    target_segments = [ida_segment.getseg(seg_ea) for seg_ea in idautils.Segments()
                       if is_data_or_rdata_segment(ida_segment.getseg(seg_ea))]

    for seg in target_segments:
        for ea, name in idautils.Names():
            # Only addresses inside current segment
            if not (seg.start_ea <= ea < seg.end_ea):
                continue
            if not name or ea in processed:
                continue

            flags = ida_bytes.get_flags(ea)
            if ida_bytes.is_code(flags):
                continue
            # Skip string literals (usually covers most const char[] variables)
            if ida_bytes.is_strlit(flags):
                continue
            # Additional check: skip variables that IDA typed as const char[]
            if is_const_char_array(ea):
                continue

            # Try to get a proper C declaration
            t = idc.get_type(ea)
            if t:
                decl = t + ';'   # get_type returns without semicolon
            else:
                # Fallback: guess type from item size and flags
                item_size = ida_bytes.get_item_size(ea)
                if ida_bytes.is_byte(flags):
                    base, elem = "unsigned char", 1
                elif ida_bytes.is_word(flags):
                    base, elem = "unsigned short", 2
                elif ida_bytes.is_dword(flags):
                    base, elem = "unsigned int", 4
                elif ida_bytes.is_qword(flags):
                    base, elem = "unsigned long long", 8
                elif ida_bytes.is_oword(flags):
                    base, elem = "unsigned __int128", 16
                elif ida_bytes.is_float(flags):
                    base, elem = "float", 4
                elif ida_bytes.is_double(flags):
                    base, elem = "double", 8
                elif ida_bytes.is_pack_real(flags):
                    base, elem = "long double", item_size
                else:
                    base, elem = "unsigned char", 1

                if item_size > elem and (item_size % elem == 0):
                    count = item_size // elem
                    decl = f"{base} {name}[{count}];"
                else:
                    decl = f"{base} {name};"

            variables.append((ea, name, decl))
            processed.add(ea)

    if not variables:
        print("[*] No suitable data variables found in .data/.rdata sections.")
        return

    # Write .h file (extern declarations)
    with open(h_path, 'w') as hf:
        hf.write("#ifndef EXPORTED_DATA_H\n#define EXPORTED_DATA_H\n\n")
        for _, _, decl in variables:
            decl_no_semi = decl.rstrip(';').rstrip()
            hf.write(f"extern {decl_no_semi};\n")
        hf.write("\n#endif // EXPORTED_DATA_H\n")

    # Write .c file (definitions)
    h_basename = h_path.split('\\')[-1].split('/')[-1]  # filename only
    with open(c_path, 'w') as cf:
        cf.write(f'#include "{h_basename}"\n\n')
        for _, _, decl in variables:
            cf.write(f"{decl}\n")

    print(f"[+] Exported {len(variables)} variables.")
    print(f"    C file: {c_path}")
    print(f"    H file: {h_path}")

if __name__ == '__main__':
    export_variables()