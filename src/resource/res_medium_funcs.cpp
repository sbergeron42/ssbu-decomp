#include "types.h"

extern "C" void* memcpy(void*, const void*, u64);
extern "C" void* memset(void*, int, u64);

// Forward declaration — nn::friends::Profile is 0x100 bytes
// [derived: Ghidra FUN_7103755cb0 shows memcpy with size 0x100 for each Profile slot]
namespace nn::friends {
class Profile {
public:
    Profile();
    u8 _data[0x100];
};
}

// FUN_7103755cb0 — Initialize friend profile array
// [derived: constructs one nn::friends::Profile, copies to 100 slots at +0x259b8]
// [derived: clears u32 at +0x188 (profile count or state flag)]
// Address: 0x7103755cb0 (2,448 bytes)
void FUN_7103755cb0(char* param_1) {
    *(u32*)(param_1 + 0x188) = 0;
    nn::friends::Profile profile;
#pragma clang loop unroll(full)
    for (int i = 0; i < 100; i++) {
        memcpy(param_1 + 0x259b8 + i * 0x100, &profile, 0x100);
    }
}
