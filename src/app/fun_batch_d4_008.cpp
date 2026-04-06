#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-008
// Throw stubs, motion-category switches, vtable dispatchers, static inits

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

extern "C" void FUN_71004d8c50();

extern u8  PTR_LAB_7104feab20;

extern u64 DAT_71052bfdf8;  // guard
extern u64 DAT_71052bfe00;  // stores vtable ptr

// ---- Functions ---------------------------------------------------------------

// 0x7100837d1c — [[noreturn]] __throw_out_of_range stub
[[noreturn]] void FUN_7100837d1c()
{
    abort();
}

// 0x71006c90b0 — vtable dispatch: call work_module vtable[0x98] with sentinel, check == 0x4d
u8 FUN_71006c90b0(u64 unused, s64 fighter)
{
    s32 status_kind;

    status_kind = (**(s32 (**)(s64 *, u32))(**(s64 **)(fighter + 0x50) + 0x98))
                (*(s64 **)(fighter + 0x50), 0x10000001);
    return status_kind == 0x4d;
}

// 0x71006ea020 — side-effect call then conditional byte clear
void FUN_71006ea020(s64 self, s64 ctx)
{
    FUN_71004d8c50();
    if (*(u8 *)(ctx + 0x40) != '\0') {
        *(u8 *)(self + 0x855) = 0;
    }
}

// 0x7100b30f70 — motion-category switch: return 1 for active-state motion IDs
u64 FUN_7100b30f70(s32 motion_kind)
{
    switch(motion_kind) {
    case 0x60:
    case 0x62:
    case 99:
    case 100:
    case 0x66:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xce:
    case 0xd5:
    case 0xd6:
    case 0xd8:
    case 0x100:
    case 0x133:
        goto label_return1;
    case 0x61:
    case 0x65:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9a:
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0x9e:
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
    case 200:
    case 0xc9:
    case 0xca:
    case 0xcb:
    case 0xcc:
    case 0xcd:
    case 0xcf:
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd7:
    case 0xd9:
    case 0xda:
    case 0xdb:
    case 0xdc:
    case 0xdd:
    case 0xde:
    case 0xdf:
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe4:
    case 0xe5:
    case 0xe6:
    case 0xe7:
    case 0xe8:
    case 0xe9:
    case 0xea:
    case 0xeb:
    case 0xec:
    case 0xed:
    case 0xee:
    case 0xef:
    case 0xf0:
    case 0xf1:
    case 0xf2:
    case 0xf3:
    case 0xf4:
    case 0xf5:
    case 0xf6:
    case 0xf7:
    case 0xf8:
    case 0xf9:
    case 0xfa:
    case 0xfb:
    case 0xfc:
    case 0xfd:
    case 0xfe:
    case 0xff:
    case 0x101:
    case 0x102:
    case 0x103:
    case 0x104:
    case 0x105:
    case 0x106:
    case 0x107:
    case 0x108:
    case 0x109:
    case 0x10a:
    case 0x10b:
    case 0x10c:
    case 0x10d:
    case 0x10e:
    case 0x10f:
    case 0x110:
    case 0x111:
    case 0x112:
    case 0x113:
    case 0x114:
    case 0x115:
    case 0x116:
    case 0x117:
    case 0x118:
    case 0x119:
    case 0x11a:
    case 0x11b:
    case 0x11c:
    case 0x11d:
    case 0x11e:
    case 0x11f:
    case 0x120:
    case 0x121:
    case 0x122:
    case 0x123:
    case 0x124:
    case 0x125:
    case 0x126:
    case 0x127:
    case 0x128:
    case 0x129:
    case 0x12a:
    case 299:
    case 300:
    case 0x12d:
    case 0x12e:
    case 0x12f:
    case 0x130:
    case 0x131:
    case 0x132:
        return 0;
    default:
        if (2 < (u32)((u32)motion_kind - 0x1a3u)) {
            return 0;
        }
label_return1:
        return 1;
    }
}

// 0x7100b30fb0 — motion-category switch: return 1 for specific motion IDs set B
u64 FUN_7100b30fb0(u32 motion_kind)
{
    switch(motion_kind) {
    case 0x41:
    case 200:
    case 0xcb:
    case 0xe6:
    case 0xed:
    case 0xf3:
    case 0xf5:
    case 0xff:
    case 0x109:
    case 0x10a:
    case 0x10b:
    case 0x10c:
    case 0x10d:
    case 0x10e:
    case 0x110:
    case 0x124:
    case 0x128:
    case 300:
    case 0x137:
    case 0x13a:
    case 0x13d:
    case 0x140:
    case 0x143:
    case 0x14d:
    case 0x151:
    case 0x157:
    case 0x15a:
    case 0x15d:
    case 0x160:
    case 0x163:
    case 0x166:
    case 0x169:
    case 0x16c:
    case 0x16f:
    case 0x171:
    case 0x176:
    case 0x17f:
    case 0x182:
    case 0x185:
    case 0x186:
    case 0x18a:
    case 0x18b:
    case 0x193:
    case 0x19d:
    case 0x1a0:
    case 0x1ab:
    case 0x1b0:
    case 0x1b5:
    case 0x1b8:
    case 0x1be:
    case 0x1bf:
    case 0x1c1:
    case 0x1c4:
    case 0x1cb:
    case 0x1ce:
    case 0x1d2:
        return 1;
    default:
        return 0;
    }
}

// 0x7100b30fe0 — motion-category switch: return 1 for specific motion IDs set C
u64 FUN_7100b30fe0(u32 motion_kind)
{
    switch(motion_kind) {
    case 0x46:
    case 199:
    case 0xef:
    case 0x118:
    case 0x123:
    case 0x127:
    case 0x12a:
    case 0x12d:
    case 0x13c:
    case 0x13f:
    case 0x142:
    case 0x145:
    case 0x14f:
    case 0x155:
    case 0x159:
    case 0x15c:
    case 0x15f:
    case 0x162:
    case 0x165:
    case 0x168:
    case 0x16b:
    case 0x16e:
    case 0x172:
    case 0x17a:
    case 0x17b:
    case 0x180:
    case 0x188:
    case 0x191:
    case 0x195:
    case 0x19f:
    case 0x1a2:
    case 0x1ad:
    case 0x1b2:
    case 0x1b7:
    case 0x1ba:
    case 0x1c3:
    case 0x1c6:
    case 0x1cd:
    case 0x1d0:
    case 0x1d5:
        return 1;
    default:
        return 0;
    }
}

// 0x7100b31010 — motion-category switch: return 1 for specific motion IDs set D
u64 FUN_7100b31010(u32 motion_kind)
{
    switch(motion_kind) {
    case 0x42:
    case 0x43:
    case 0xc0:
    case 0xc1:
    case 0xc5:
    case 0xc6:
    case 0xc9:
    case 0xe9:
    case 0xea:
    case 0xeb:
    case 0xec:
    case 0xee:
    case 0xf1:
    case 0xf4:
    case 0xf6:
    case 0xf7:
    case 0x11f:
    case 0x121:
    case 0x122:
    case 0x125:
    case 0x126:
    case 0x129:
    case 0x131:
    case 0x132:
    case 0x138:
    case 0x139:
    case 0x13b:
    case 0x13e:
    case 0x141:
    case 0x144:
    case 0x14e:
    case 0x152:
    case 0x154:
    case 0x158:
    case 0x15b:
    case 0x15e:
    case 0x161:
    case 0x164:
    case 0x167:
    case 0x16a:
    case 0x16d:
    case 0x174:
    case 0x177:
    case 0x178:
    case 0x179:
    case 0x187:
    case 0x18c:
    case 400:
    case 0x194:
    case 0x19e:
    case 0x1a1:
    case 0x1ac:
    case 0x1b1:
    case 0x1b6:
    case 0x1b9:
    case 0x1c2:
    case 0x1c5:
    case 0x1cc:
    case 0x1cf:
    case 0x1d4:
        return 1;
    default:
        return 0;
    }
}

// 0x7100c2cd60 — vtable call with local array init
u64 FUN_7100c2cd60(s64 *self)
{
    u32 out_buffer[18];

    out_buffer[0] = 0;
    (**(void (**)(s64 *, u32 *))(*self + 0x50))(self, out_buffer);
    return 1;
}

// 0x7100cec310 — vtable chain dispatch: call vtable[0x110], check masked != 0x1ea
u8 FUN_7100cec310(u64 unused, s64 fighter)
{
    u32 status_kind;

    status_kind = (**(u32 (**)())(**(s64 **)(*(s64 *)(fighter + 0x20) + 0x40) + 0x110))();
    return (status_kind & 0xfffffffe) != 0x1ea;
}

// 0x7100d12af0 — static init: set vtable ptr, then assign to two fields of ctx
void FUN_7100d12af0(u64 unused, s64 ctx)
{
    s32 acquired;

    if ((DAT_71052bfdf8 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052bfdf8);
        if (acquired != 0) {
            DAT_71052bfe00 = (u64)&PTR_LAB_7104feab20;
            __cxa_guard_release(&DAT_71052bfdf8);
        }
    }
    *(u64 **)(ctx + 0x318) = &DAT_71052bfe00;
    *(u8 *)(ctx + 0xe8) = 6;
}
