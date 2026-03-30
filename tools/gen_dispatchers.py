#!/usr/bin/env python3
"""
Generate C++ source for vtable dispatcher functions.

Input: a config file with one function per line:
  module_field vtable_offset function_name [param_spec]

param_spec is optional and describes extra params beyond the accessor:
  i=s32, u=u32, f=f32, b=bool(and #1), p=void*

Example:
  posture_module 0xb0 PostureModule__lr_impl
  posture_module 0xb8 PostureModule__set_lr_impl f
  status_module 0x110 StatusModule__status_kind_impl

Output: a .cpp file with all dispatchers.
"""

import sys
from pathlib import Path


PARAM_TYPES = {
    'i': 's32',
    'u': 'u32',
    'f': 'f32',
    'b': 'bool',
    'p': 'void*',
}


def parse_config(filepath: str) -> list[dict]:
    entries = []
    with open(filepath) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            if len(parts) < 3:
                continue
            entry = {
                'field': parts[0],
                'vtable_offset': parts[1],
                'name': parts[2],
                'params': parts[3] if len(parts) > 3 else '',
                'ret': parts[4] if len(parts) > 4 else 'void',
            }
            entries.append(entry)
    return entries


def gen_function(entry: dict) -> str:
    field = entry['field']
    voff = entry['vtable_offset']
    name = entry['name']
    params = entry['params']
    ret = entry['ret']

    # Build parameter list
    param_list = ['BattleObjectModuleAccessor* accessor']
    call_args = ['module']
    cast_params = ['void*']
    bool_ands = []

    for i, p in enumerate(params):
        ptype = PARAM_TYPES.get(p, 'u32')
        pname = f'p{i+1}'
        param_list.append(f'{ptype} {pname}')
        call_args.append(pname)
        cast_params.append(ptype)
        if p == 'b':
            bool_ands.append(pname)

    params_str = ', '.join(param_list)
    args_str = ', '.join(call_args)
    cast_str = ', '.join(cast_params)
    ret_type = PARAM_TYPES.get(ret, ret)

    # Check if we need bool AND instructions (these aren't pure dispatchers)
    has_bools = len(bool_ands) > 0

    lines = []
    lines.append(f'{ret_type} {name}({params_str}) {{')
    lines.append(f'    auto* module = accessor->{field};')
    lines.append(f'    auto* vtable = *reinterpret_cast<void***>(module);')

    fn_type = f'{ret_type} (*)({cast_str})'
    lines.append(f'    return reinterpret_cast<{fn_type}>(vtable[{voff} / 8])({args_str});')
    lines.append(f'}}')

    return '\n'.join(lines)


def main():
    if len(sys.argv) < 2:
        print("Usage: python tools/gen_dispatchers.py <config_file> [output.cpp]")
        sys.exit(1)

    config_file = sys.argv[1]
    entries = parse_config(config_file)

    output = []
    output.append('#include "app/BattleObjectModuleAccessor.h"')
    output.append('')
    output.append('namespace app::lua_bind {')
    output.append('')

    for entry in entries:
        output.append(gen_function(entry))
        output.append('')

    output.append('} // namespace app::lua_bind')
    output.append('')

    result = '\n'.join(output)

    if len(sys.argv) > 2:
        Path(sys.argv[2]).write_text(result)
        print(f"Generated {len(entries)} functions -> {sys.argv[2]}")
    else:
        print(result)


if __name__ == '__main__':
    main()
