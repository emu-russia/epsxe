# -*- coding: utf-8 -*-
"""Экспорт дизассемблированного текста секции .data с полными именами (IDA 9.x)"""

import os
import idaapi
import idautils
import idc
import ida_segment
import ida_bytes

def get_data_segment():
    for seg_ea in idautils.Segments():
        seg = ida_segment.getseg(seg_ea)
        if seg and ida_segment.get_segm_name(seg) == ".data":
            return seg
    return None

def get_label(ea):
    """Возвращает имя метки: существующее, либо сгенерированное по типу данных."""
    name = idc.get_name(ea)
    if name:
        return name

    # Определим размер элемента
    size = idc.get_item_size(ea)
    if size == 0:
        size = 1  # на всякий случай

    # Приставка по размеру (можно расширить)
    prefix = {
        1: "byte",
        2: "word",
        4: "dword",
        8: "qword",
        16: "oword",
    }.get(size, f"data{size}")  # для нестандартных размеров

    return f"{prefix}_{ea:X}"

def main():
    seg = get_data_segment()
    if not seg:
        print("[!] Сегмент .data не найден.")
        print("Доступные сегменты:")
        for seg_ea in idautils.Segments():
            seg = ida_segment.getseg(seg_ea)
            print(f"  {ida_segment.get_segm_name(seg)}  [ {seg.start_ea:08X} - {seg.end_ea:08X} ]")
        return

    idb_path = idc.get_idb_path()
    if not idb_path:
        output_path = os.path.join(os.getcwd(), "data_disasm.txt")
    else:
        output_path = os.path.join(os.path.dirname(idb_path), "data_disasm.txt")

    print(f"[*] Секция .data: {seg.start_ea:08X} - {seg.end_ea:08X}")
    print(f"[*] Сохраняю в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        for head in idautils.Heads(seg.start_ea, seg.end_ea):
            label = get_label(head)
            disasm = idc.GetDisasm(head)
            # Если метка уже есть в disasm, не дублируем; иначе добавляем
            if disasm.startswith(label):
                line = disasm
            else:
                line = f"{label} {disasm}"
            f.write(f"{head:08X}: {line}\n")

    print("[+] Готово. Все строки теперь содержат имена меток.")

if __name__ == "__main__":
    main()