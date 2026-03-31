#!/usr/bin/env python3
"""asm-differ configuration for SSBU Decomp."""
from pathlib import Path


def apply(config, args):
    root = Path(__file__).parent

    config['arch'] = 'aarch64'
    config['baseimg'] = str(root / 'data' / 'main.elf')
    config['myimg'] = str(root / 'build' / 'ssbu-decomp.elf')
    config['source_directories'] = [str(root / 'src')]
    config['objdump_executable'] = r'C:\llvm-8.0.0\bin\llvm-objdump.exe'
    config['show_line_numbers_default'] = False
