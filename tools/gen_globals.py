#!/usr/bin/env python3
"""
Generate C declarations for decompiled ePSXe globals from IDA data listings.

Inputs:
  varlist.txt                 - IDA .data/.rdata declarations (named + unnamed vars)
  varunknown_by_modules.txt   - per-module unknown var listings
  undeclared_per_file.txt     - file<TAB>identifier pairs that fail to compile (C2065)
  src/*.c                     - module sources (to check usage patterns)

Outputs:
  src/_gen/globals.h          - extern declarations for data globals + fn-ptr vars
  src/_gen/globals.c          - definitions (with initializers where known)
  src/_gen/funcs.h            - prototypes for functions defined in src modules
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
VARLIST = ROOT / "varlist.txt"
VARUNKNOWN = ROOT / "varunknown_by_modules.txt"
UNDECL = ROOT / "tools" / "undeclared_per_file.txt"
SRC = ROOT / "src"
GEN = SRC / "_gen"

OUT_H = GEN / "globals.h"
OUT_C = GEN / "globals.c"
OUT_F = GEN / "funcs.h"


# ---------------------------------------------------------------------------
# IDA line parsing
# ---------------------------------------------------------------------------

def load_ida_map():
    raw = []
    ida_decl_re = re.compile(r'^\.[a-z0-9]+:([0-9A-Fa-f]+)\s+(\w+)\s')
    for path in (VARLIST, VARUNKNOWN, ROOT / 'data.txt'):
        if not path.exists():
            continue
        lines = path.read_text(encoding='utf-8', errors='ignore').splitlines()
        i = 0
        while i < len(lines):
            line = lines[i]
            if line.strip().endswith('\\') and i + 1 < len(lines) \
                    and not ida_decl_re.match(lines[i + 1]):
                joined = line.strip()[:-1].strip() + ' ' + lines[i + 1].strip()
                raw.append(joined)
                i += 2
                continue
            raw.append(line)
            i += 1
    decl = {}
    for line in raw:
        m = re.match(r'^\.[a-z0-9]+:([0-9A-Fa-f]+)\s+(\w+)\s+(.+?)\s*(?:;.*)?$', line)
        if m:
            decl.setdefault(m.group(2), (m.group(1), m.group(3), line))
    return decl


def parse_number(tok):
    tok = tok.strip()
    if tok == '?':
        return None
    if tok.startswith("'"):
        s = tok[1:-1]
        return s.encode('latin1')
    if tok.endswith('h') or tok.endswith('H'):
        return int(tok[:-1], 16)
    if tok.endswith('b') or tok.endswith('B'):
        return int(tok[:-1], 2)
    if tok.endswith('o'):
        return int(tok[:-1], 8)
    if '.' in tok or 'e' in tok.lower():
        return float(tok)
    try:
        return int(tok, 10)
    except ValueError:
        raise ValueError(f"cannot parse token: {tok!r}")


def split_top_level(s):
    tokens, depth, cur = [], 0, ''
    for ch in s:
        if ch in '(<>':
            depth += 1
            cur += ch
        elif ch in ')>':
            depth -= 1
            cur += ch
        elif ch == ',' and depth == 0:
            tokens.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        tokens.append(cur)
    return tokens


def parse_ida_values(valpart):
    """Returns (values|('uninit_array',N)|None, is_float)."""
    valpart = valpart.strip()
    if valpart == '?':
        return None, False
    m = re.match(r'^([0-9A-Fa-f]+h?)\s*dup\s*\(\s*\?\s*\)$', valpart)
    if m:
        g = m.group(1)
        count = int(g[:-1], 16) if g.endswith('h') else (int(g[:-1], 2) if g.endswith('b') else int(g, 10))
        return ('uninit_array', count), False
    values = []
    any_float = False
    for tok in split_top_level(valpart):
        tok = tok.strip()
        m = re.match(r'^([0-9A-Fa-f]+h?)\s*dup\s*\((.+)\)$', tok)
        if m:
            g = m.group(1)
            count = int(g[:-1], 16) if g.endswith('h') else (int(g[:-1], 2) if g.endswith('b') else int(g, 10))
            inner, f = parse_ida_values(m.group(2))
            if inner is None:
                return None, False
            values.extend(inner * count)
            any_float = any_float or f
            continue
        v = parse_number(tok)
        if v is None:
            return None, False
        if isinstance(v, bytes):
            values.extend(v)
            continue
        values.append(v)
        if isinstance(v, float):
            any_float = True
    return values, any_float


# ---------------------------------------------------------------------------
# usage analysis
# ---------------------------------------------------------------------------

_src_cache = None


def src_texts():
    global _src_cache
    if _src_cache is None:
        _src_cache = {}
        for f in SRC.glob('*.c'):
            if f.name == 'pch.c':
                continue
            _src_cache[f.name] = f.read_text(encoding='utf-8', errors='ignore')
    return _src_cache


def is_defined_function(name):
    for fname, text in src_texts().items():
        if re.search(r'(?m)^[ \t]*(?!(?:if|for|while|switch|return|else|do|case|goto)\b)'
                     r'(?:[A-Za-z_][\w \*\(\)]*?)\b' + re.escape(name)
                     + r'\s*\([^;{}]*?\)\s*(?:\([^;{}]*?\))?\s*\{', text):
            return True
    return False


def used_as_call(name):
    for fname, text in src_texts().items():
        if re.search(r'\b' + re.escape(name) + r'\s*\(', text):
            return True
    return False


def usage_indexed(name):
    for fname, text in src_texts().items():
        if re.search(r'\b' + re.escape(name) + r'\s*\[', text):
            return True
    return False


# ---------------------------------------------------------------------------
# declaration generation
# ---------------------------------------------------------------------------

CTYPES = {'db': 'unsigned char', 'dw': 'unsigned short',
          'dd': 'unsigned int', 'dq': 'unsigned __int64'}

SPECIAL = {
    'controller_port_modes': 'unsigned int controller_port_modes[8];',
    'mouse_accumulated_x': 'int mouse_accumulated_x;',
    'mouse_accumulated_y': 'int mouse_accumulated_y;',
    'mouse_buttons_state': 'unsigned int mouse_buttons_state;',
    'mouse_delta_x': 'int mouse_delta_x;',
    'mouse_delta_y': 'int mouse_delta_y;',
    'guncon_position': 'unsigned int guncon_position;',
    'joystick_button_state1': 'unsigned char joystick_button_state1[4];',
    'joystick_button_state2': 'unsigned char joystick_button_state2[4];',
    'joystick_button_state3': 'unsigned char joystick_button_state3[4];',
    'joystick_button_state4': 'unsigned char joystick_button_state4[4];',
    'pad_analog_mode_flags': 'unsigned char pad_analog_mode_flags[8];',
    'pad1_buttons_low': 'unsigned short pad1_buttons_low;',
    'pad1_buttons_high': 'unsigned short pad1_buttons_high;',
    'pad2_buttons_low': 'unsigned short pad2_buttons_low;',
    'pad2_buttons_high': 'unsigned short pad2_buttons_high;',
    'pad3_buttons_low': 'unsigned short pad3_buttons_low;',
    'pad3_buttons_high': 'unsigned short pad3_buttons_high;',
    'pad4_buttons_low': 'unsigned short pad4_buttons_low;',
    'pad4_buttons_high': 'unsigned short pad4_buttons_high;',
    'pad1_analog_joy_x': 'unsigned short pad1_analog_joy_x;',
    'pad1_analog_joy_y': 'unsigned short pad1_analog_joy_y;',
    'pad1_analog_joy2_x': 'unsigned short pad1_analog_joy2_x;',
    'pad1_analog_joy2_y': 'unsigned short pad1_analog_joy2_y;',
    'pad2_analog_joy_x': 'unsigned short pad2_analog_joy_x;',
    'pad2_analog_joy_y': 'unsigned short pad2_analog_joy_y;',
    'pad2_analog_joy2_x': 'unsigned short pad2_analog_joy2_x;',
    'pad2_analog_joy2_y': 'unsigned short pad2_analog_joy2_y;',
    'pad3_analog_joy_x': 'unsigned short pad3_analog_joy_x;',
    'pad3_analog_joy_y': 'unsigned short pad3_analog_joy_y;',
    'pad3_analog_joy2_x': 'unsigned short pad3_analog_joy2_x;',
    'pad3_analog_joy2_y': 'unsigned short pad3_analog_joy2_y;',
    'pad4_analog_joy_x': 'unsigned short pad4_analog_joy_x;',
    'pad4_analog_joy_y': 'unsigned short pad4_analog_joy_y;',
    'pad4_analog_joy2_x': 'unsigned short pad4_analog_joy2_x;',
    'pad4_analog_joy2_y': 'unsigned short pad4_analog_joy2_y;',
    'spu_voice_param': 'SPU_VOICE_PARAM spu_voice_param[24];',
    'force_feedback_effect_handles2': 'void *force_feedback_effect_handles2[4];',
    'code_ptr': 'uint8_t *code_ptr;',
    'joystick_axis_1_negative_triggered': 'int joystick_axis_1_negative_triggered[4];',
    'joystick_axis_1_positive_triggered': 'int joystick_axis_1_positive_triggered[4];',
    'joystick_axis_2_negative_triggered': 'int joystick_axis_2_negative_triggered[4];',
    'joystick_axis_2_positive_triggered': 'int joystick_axis_2_positive_triggered[4];',
    'joystick_axis_3_negative_triggered': 'int joystick_axis_3_negative_triggered[4];',
    'joystick_axis_3_positive_triggered': 'int joystick_axis_3_positive_triggered[4];',
    'joystick_axis_4_negative_triggered': 'int joystick_axis_4_negative_triggered[4];',
    'joystick_axis_4_positive_triggered': 'int joystick_axis_4_positive_triggered[4];',
    'joystick_axis_5_negative_triggered': 'int joystick_axis_5_negative_triggered[4];',
    'joystick_axis_5_positive_triggered': 'int joystick_axis_5_positive_triggered[4];',
    'joystick_axis_6_negative_triggered': 'int joystick_axis_6_negative_triggered[4];',
    'joystick_axis_6_positive_triggered': 'int joystick_axis_6_positive_triggered[4];',
    'joystick_axis_7_negative_triggered': 'int joystick_axis_7_negative_triggered[4];',
    'joystick_axis_7_positive_triggered': 'int joystick_axis_7_positive_triggered[4];',
    'cdr_status_command_2': 'unsigned char cdr_status_command_2[8];',
    'cdr_status_command_3': 'unsigned char cdr_status_command_3[8];',
    'increase_slot_state_request': 'int increase_slot_state_request;',
    'dynarec_clear_request': 'int dynarec_clear_request;',
    'adjust_timing': 'int adjust_timing;',
    'aW': 'char aW[8];',
    'asc_44E24C': 'char asc_44E24C[64];',
    'FileName': 'char FileName[256];',
    'keyboard_escape_pressed': 'int keyboard_escape_pressed[2];',
    'load_state_request': 'int load_state_request;',
    'make_snapshot_request': 'int make_snapshot_request[2];',
    'netplay_reset_request': 'int netplay_reset_request;',
    'save_state_request': 'int save_state_request;',
    'screen_pic_display_counter': 'int screen_pic_display_counter;',
    'selected_slot_for_mode_switch': 'int selected_slot_for_mode_switch;',
    'sio_irq_assert_request': 'int sio_irq_assert_request[2];',
    'switch_controller_slot_request': 'int switch_controller_slot_request;',
    'toggle_pad_mode_request': 'int toggle_pad_mode_request;',
    'toggle_sio_irq_request': 'int toggle_sio_irq_request;',
    'toggle_xenogears_trick_request': 'int toggle_xenogears_trick_request;',
    'ui_feedback_timer': 'int ui_feedback_timer;',
    'rumble_big_motor_state': 'unsigned char rumble_big_motor_state[8];',
    'rumble_small_motor_state': 'unsigned char rumble_small_motor_state[8];',
    'sio_multitap_command_buffer': 'unsigned char sio_multitap_command_buffer[0x40];',
    'sio_multitap_command_byte': 'unsigned char sio_multitap_command_byte[0x40];',
    'sio_response_buffer_analog_byte': 'unsigned char sio_response_buffer_analog_byte[8];',
    'sio_response_buffer_config_byte': 'unsigned char sio_response_buffer_config_byte[8];',
    'sio_response_buffer_config_byte2': 'unsigned char sio_response_buffer_config_byte2[8];',
    'sio_response_buffer_config_byte3': 'unsigned char sio_response_buffer_config_byte3[8];',
    'sio_response_buffer_data1': 'unsigned char sio_response_buffer_data1[0x100];',
    'sio_response_buffer_data2': 'unsigned char sio_response_buffer_data2[0x100];',
    'sio_response_buffer_id': 'unsigned char sio_response_buffer_id[8];',
    'GUID_Keyboard': 'GUID GUID_Keyboard;',
    'GUID_Mouse': 'GUID GUID_Mouse;',
    'joystick_button_1_triggered': 'int joystick_button_1_triggered[4];',
    'joystick_button_2_triggered': 'int joystick_button_2_triggered[4];',
    'memcard2_checksum': 'unsigned int memcard2_checksum;',
    'memcard2_data': 'unsigned char memcard2_data[0x2000];',
    'memcard2_id_byte': 'unsigned char memcard2_id_byte;',
    'memcard_current_address': 'unsigned int memcard_current_address;',
    'word_50BF7B': 'unsigned short word_50BF7B;',
    'SendASPI32Command_cb': 'int (__cdecl *SendASPI32Command_cb)(LPSRB);',
    'GetASPI32SupportInfo_cb': 'DWORD (__stdcall *GetASPI32SupportInfo_cb)(void);',
    'ppf_file_data': 'char *ppf_file_data;',
    'error_log_file': 'FILE *error_log_file;',
    'dynarec_active': 'unsigned char dynarec_active;',
    'console_log_enabled': 'unsigned char console_log_enabled;',
    'console_allocated': 'unsigned char console_allocated;',
}

# Extern-only declarations: defined by a handwritten module (not globals.c)
SPECIAL_EXTERN = {
    'cheat_db': 'CHEAT_DB_ENTRY cheat_db[200];',
    'mini_cheat_db': 'MINI_CHEAT_ENTRY mini_cheat_db[200];',
}


def gen_data_decl(name, addr, rest, full_line):
    """Return a C definition line for a data variable, or None if not data."""
    rest = re.sub(r'\s*;.*$', '', rest).strip()
    m = re.match(r'^(db|dw|dd|dq)\s+(.+)$', rest)
    if not m:
        # struct forms: TYPE <?> or TYPE <init...>
        m2 = re.match(r'^(\w+)\s*<\?\s*>?$', rest)
        if m2:
            return f"{map_type(m2.group(1))} {name};"
        m3 = re.match(r'^(\w+)\s*<(.+)>$', rest, re.S)
        if m3:
            return f"{map_type(m3.group(1))} {name} = {convert_struct_init('<' + m3.group(2) + '>')};"
        return None
    kind, valpart = m.group(1), m.group(2).strip()
    values, is_float = parse_ida_values(valpart)
    idx = usage_indexed(name)
    if isinstance(values, tuple) and values[0] == 'uninit_array':
        size = values[1]
        return f"{CTYPES[kind]} {name}[{size:#x}];"
    return gen_array_decl(kind, values, is_float, name, idx)


def map_type(t):
    return {'_BIOS_DESCR': 'BIOS_DESCR',
            'MINI_CHEAR_ENTRY': 'MINI_CHEAT_ENTRY'}.get(t, t)


def convert_struct_init(init):
    """Convert IDA struct initializer <...> to C {...}, with string handling."""
    s = re.sub(r"'([^']*)'", lambda m: '"' + m.group(1) + '"', init.strip())
    # convert IDA hex numbers (0Dh, 0C8EC73C0h, 10023458h) to C hex
    s = re.sub(r'\b([0-9A-Fa-f]+)h\b', lambda m: '0x' + m.group(1), s)
    depth = 0
    out = []
    for ch in s:
        if ch == '<':
            out.append('{')
            depth += 1
        elif ch == '>':
            out.append('}')
            depth -= 1
        else:
            out.append(ch)
    return ''.join(out)


def gen_array_decl(kind, values, is_float, name, indexed):
    ctype = CTYPES[kind]
    if is_float:
        ctype = {'dd': 'float', 'dq': 'double'}.get(kind, ctype)
    if values is None:
        if indexed:
            return f"{ctype} {name}[1];"
        return f"{ctype} {name};"
    n = len(values)
    if n == 1 and not indexed:
        v = values[0]
        if isinstance(v, float):
            lit = repr(v)
            if '.' not in lit and 'e' not in lit:
                lit += '.0'
            return f"{ctype} {name} = {lit}{'f' if ctype == 'float' else ''};"
        return f"{ctype} {name} = {v:#x};"
    items = []
    for v in values:
        if isinstance(v, float):
            lit = repr(v)
            if '.' not in lit and 'e' not in lit:
                lit += '.0'
            items.append(lit + ('f' if ctype == 'float' else ''))
        else:
            items.append(f"{v:#x}")
    if n <= 64:
        return f"{ctype} {name}[{n}] = {{{', '.join(items)}}};"
    return f"{ctype} {name}[{n}];"


def extern_of(decl):
    decl = decl.rstrip(';')
    # strip initializer for the extern form
    m = re.match(r'^(.*?)\s*=\s*.*$', decl)
    if m:
        decl = m.group(1).rstrip()
    return f"extern {decl};"


# ---------------------------------------------------------------------------
# function prototypes from src definitions
# ---------------------------------------------------------------------------

def find_prototype(name):
    for fname, text in src_texts().items():
        for m in re.finditer(r'(?m)^[ \t]*(?!(?:if|for|while|switch|return|else|do|case|goto)\b)'
                             r'((?:[A-Za-z_][\w \*\(\)]*?)\b'
                             + re.escape(name)
                             + r'\s*\([^;{}]*?\)\s*(?:\([^;{}]*?\))?)\s*\{', text):
            sig = m.group(1).strip()
            if sig.count('(') != sig.count(')'):
                continue
            if not re.search(r'\b' + re.escape(name) + r'\s*\(', sig):
                continue
            return sig + ';'
    return None


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------

def main():
    decl = load_ida_map()
    # alias table: byte_X -> unk_X and vice versa (IDA sometimes renames)
    alias = {}
    for k in list(decl):
        for a, b in (('byte_', 'unk_'), ('unk_', 'byte_')):
            if k.startswith(a):
                alias.setdefault(b + k[len(a):], k)
    need = {}
    for line in UNDECL.read_text(encoding='utf-8-sig', errors='ignore').splitlines():
        parts = line.split('\t')
        if len(parts) == 2:
            need.setdefault(parts[1], []).append(parts[0])
    # accumulate ids from previous runs so regenerating doesn't drop decls
    union_file = ROOT / 'tools' / 'need_union.txt'
    if union_file.exists():
        for line in union_file.read_text(encoding='utf-8-sig').splitlines():
            line = line.strip().lstrip('\ufeff')
            if line:
                need.setdefault(line, []).append('(accumulated)')
    union_file.parent.mkdir(parents=True, exist_ok=True)
    union_file.write_text('\n'.join(sorted(need)) + '\n', encoding='utf-8')

    h = ["/* AUTO-GENERATED by tools/gen_globals.py — do not edit */",
         "#pragma once", '#include <stdint.h>', '']
    c = ['/* AUTO-GENERATED by tools/gen_globals.py — do not edit */',
         '#include "pch.h"', '']
    emitted = set()
    fn_protos = []
    fnptr_decls = []
    manual = []

    for name in sorted(need):
        # 1) functions defined in src modules -> prototypes (header gen)
        if is_defined_function(name):
            continue
        # 2) function-pointer variables (called but not defined)
        if used_as_call(name):
            if re.search(r'^(SPU|GPU|NET|PAD|EXT|CDR)', name):
                cc = '__stdcall' if not name.startswith(('CDR', 'PSE')) else '__cdecl'
            elif name.startswith('PSE'):
                cc = '__cdecl'
            else:
                cc = '__cdecl'
            d = f"int ({cc} *{name})();"
            fnptr_decls.append(d)
            continue
        # 3) special-cased manual declarations
        if name in SPECIAL:
            d = SPECIAL[name]
            h.append(extern_of(d))
            c.append(d)
            emitted.add(name)
            continue
        if name in SPECIAL_EXTERN:
            h.append('extern ' + SPECIAL_EXTERN[name])
            emitted.add(name)
            continue
        # 4) data variables with IDA declarations
        src = decl.get(name)
        if src is None and name in alias:
            src = decl.get(alias[name])
        if src:
            addr, rest, full_line = src
            d = gen_data_decl(name, addr, rest, full_line)
            if d:
                h.append(extern_of(d))
                c.append(d)
                emitted.add(name)
                continue
            manual.append((name, f'non-data form: {rest[:70]!r}'))
            continue
        manual.append((name, 'no IDA decl / unknown'))

    # function prototypes: for every function defined in src modules,
    # emit its prototype (prevents implicit-declaration redefinition errors).
    all_funcs = set()
    for fname, text in src_texts().items():
        for m in re.finditer(r'(?m)^[ \t]*(?!(?:if|for|while|switch|return|else|do|case|goto)\b)'
                             r'(?:[A-Za-z_][\w \*\(\)]*?)\b([A-Za-z_]\w*)\s*\([^;{}]*?\)'
                             r'\s*(?:\([^;{}]*?\))?\s*\{', text):
            all_funcs.add(m.group(1))
    for name in sorted(all_funcs):
        proto = find_prototype(name)
        if proto:
            fn_protos.append(proto)
        elif name in need and is_defined_function(name):
            manual.append((name, 'defined in src but no prototype extracted'))

    for d in fnptr_decls:
        h.append(extern_of(d))
        c.append(d)

    # ensure special/extern-only entries are always emitted even if not in `need`
    for name, d in sorted(SPECIAL.items()):
        if name not in emitted:
            h.append(extern_of(d))
            c.append(d)
    for name, d in sorted(SPECIAL_EXTERN.items()):
        if name not in emitted:
            h.append('extern ' + d)

    GEN.mkdir(parents=True, exist_ok=True)
    OUT_H.write_text('\n'.join(h) + '\n', encoding='utf-8')
    OUT_C.write_text('\n'.join(c) + '\n', encoding='utf-8')
    OUT_F.write_text('/* AUTO-GENERATED by tools/gen_globals.py — do not edit */\n'
                     '#pragma once\n\n' + '\n'.join(sorted(set(fn_protos))) + '\n',
                     encoding='utf-8')
    print(f"globals.h: {len(h)} lines, globals.c: {len(c)} lines, funcs.h: {len(set(fn_protos))} protos")
    print(f"fnptr vars: {len(fnptr_decls)}")
    print(f"manual ({len(manual)}):")
    for n, why in manual:
        print(f"  {n}: {why}", file=sys.stderr)


if __name__ == '__main__':
    main()
