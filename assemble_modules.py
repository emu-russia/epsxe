#!/usr/bin/env python3
"""
Simple script to assemble procedures from decompiled files into modules.
Removes #include "pch.h" from all procedures except the first one.
"""

import json
import re
import sys
from pathlib import Path


def remove_include_directive(content: str) -> str:
    """Remove #include "pch.h" directive from content."""
    return re.sub(r'^\s*#include\s*"pch\.h"\s*\n', '', content)


def assemble_modules(json_path: str, decompiled_dir: str = "decompiled", src_dir: str = "src"):
    """Assemble modules from procedures specified in the JSON file."""
    
    # Read JSON configuration
    with open(json_path, 'r', encoding='utf-8') as f:
        config = json.load(f)
    
    # Create output directory
    Path(src_dir).mkdir(parents=True, exist_ok=True)
    
    for module in config['modules']:
        module_name = module['name']
        proc_list = module['procs']
        
        output_file = Path(src_dir) / module_name
        
        print(f"Assembling module: {module_name}")
        
        with open(output_file, 'w', encoding='utf-8') as out:
            for idx, proc_name in enumerate(proc_list):
                # Read the procedure file
                proc_file = Path(decompiled_dir) / f"{proc_name}.c"
                
                try:
                    with open(proc_file, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                except FileNotFoundError:
                    print(f"  Warning: {proc_name}.c not found, skipping")
                    continue
                
                # Remove #include "pch.h" for all procedures except the first
                if idx > 0:
                    content = remove_include_directive(content)
                # For first procedure, keep the include as-is
                
                # Write the procedure content
                out.write(content)
                if not content.endswith('\n'):
                    out.write('\n')
                out.write('\n')  # Add separation between procedures
                
                print(f"  Added: {proc_name}")
        
        print(f"  Completed: {output_file}\n")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python assemble_modules.py procs.json")
        sys.exit(1)
    
    json_file = sys.argv[1]
    
    # Optional: specify custom directories
    decompiled_dir = sys.argv[2] if len(sys.argv) > 2 else "decompiled"
    src_dir = sys.argv[3] if len(sys.argv) > 3 else "src"
    
    assemble_modules(json_file, decompiled_dir, src_dir)