#include "types.h"

// Particle/emitter functions -- pool-c assignment

extern "C" void FUN_7100088060(void*);
extern "C" void FUN_71000a4f60(void*,void*,void*,void*,void*,u64,u64,u32);
extern "C" bool FUN_71000ac200(void*,void*,u32,void*,void*);
extern "C" void FUN_710395a570(s32*);

// 71000a4f20 (16B) -- copy emitter handle field from src to dst
// Leaf function; matches directly.
void InitializeEmitter(u8* p0, u8* p1) {
    *reinterpret_cast<u64*>(p1 + 0x98) = *reinterpret_cast<u64*>(p0 + 0x8c0);
}

// 71000ac1c0 (64B) -- unpack emitter callback struct fields, call inner, return 1
// Prologue mov-x29-sp scheduling fixed by fix_prologue.py; movz→orr by fix_movz_to_orr.py
bool EmitterDrawCallback(u64* p) {
    FUN_71000ac200((void*)p[0], (void*)p[1], *(u32*)((u8*)p + 0x10), (void*)p[3], (void*)p[4]);
    return true;
}

