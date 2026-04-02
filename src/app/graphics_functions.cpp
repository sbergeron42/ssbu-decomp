#include "types.h"

// Graphics/shader/draw functions -- pool-c assignment

// All extern data symbols need visibility("hidden") to get direct ADRP+ADD/LDR
// rather than GOT indirection under -fPIC.
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710446f530[];  // draw primitive table
extern "C" __attribute__((visibility("hidden"))) u32 DAT_710446f56c[];  // shader stage table
extern "C" __attribute__((visibility("hidden"))) u64 DAT_7104470aa8[];  // shader code offsets
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052a32d8;  // shader type table ptr
extern "C" __attribute__((visibility("hidden"))) void* DAT_7105336ce8;  // renderer global

// 7100037440 (16B) -- look up draw primitive enum from index
u32 GetDrawPrimitive(u32 idx) {
    return DAT_710446f530[idx];
}

// 7100037450 (16B) -- look up shader stage enum from index
u32 GetShaderStage(u32 idx) {
    return DAT_710446f56c[idx];
}

// 7100037460 (64B) -- pack stage-bits flags into a 6-bit field
// Upstream Clang produces different bit-manipulation sequence; use naked asm.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 GetShaderStageBits(u64 /*flags*/) {
    asm(
        "lsr w9, w0, #1\n"
        "and w10, w0, #1\n"
        "bfm w10, w9, #29, #0\n"
        "lsr w8, w0, #2\n"
        "bfm w10, w8, #28, #0\n"
        "and w8, w9, #4\n"
        "lsr w9, w0, #3\n"
        "and w9, w9, #2\n"
        "orr w8, w8, w10\n"
        "orr w8, w9, w8\n"
        "and w9, w0, #0x20\n"
        "orr w0, w9, w8\n"
        "ret\n"
    );
}
#endif

// 7100038100 (32B) -- get shader code pointer at type-indexed offset
u8* GetShaderCodePtr(u8* p0, u32 p1) {
    return *reinterpret_cast<u8**>(p0 + DAT_7104470aa8[p1]);
}

// 7100054150 (32B) -- get constant buffer pointer for vertex shader
u64 GetConstantBufferForVertexShader(u8* p0, u8* p1) {
    u8* inner = *reinterpret_cast<u8**>(p1 + 0xc8);
    u64 lv = *reinterpret_cast<u64*>(inner + 0x38);
    if (lv) return lv + (u64)*reinterpret_cast<u32*>(p0 + 0x30);
    return 0;
}

// 7100066010 (48B) -- check if ResShaderContainer is fully initialized
bool IsResShaderContainerInitialized_(u8* p) {
    if (*reinterpret_cast<u64*>(p + 0x28) == 0) return false;
    u8* a = *reinterpret_cast<u8**>(*reinterpret_cast<u64*>(p + 0x28) + 0x20);
    if (a) return a[0x110] == 1;
    return false;
}

// 7100086d10 (64B) -- get shader object pointer by slot index (3 = null sentinel)
u64 GetShader(u8* p) {
    u32 idx = *reinterpret_cast<u32*>(p + 0x10);
    if (idx == 3) return 0;
    u8* a = *reinterpret_cast<u8**>(p + 8);
    u8* b = *reinterpret_cast<u8**>(a + 0x238);
    return *reinterpret_cast<u64*>(b + (u64)idx * 8 + 0x340);
}

// 710009c320 (48B) -- initialize shader slot: lookup offset table by type, store vtable+0x68
bool InitializeShader(u8* p0, u8* p1, u32 p2) {
    u64 offset = *reinterpret_cast<u64*>(reinterpret_cast<u8*>(DAT_71052a32d8) + (u64)p2 * 8);
    u8* entry = *reinterpret_cast<u8**>(p1 + offset);
    *reinterpret_cast<u64*>(p0 + 8) = *reinterpret_cast<u64*>(entry + 0x68);
    p0[0] = 1;
    return true;
}

// 710009c9c0 (32B) -- ShaderManager ctor: zero all member fields
void ShaderManager(u8* p) {
    p[0] = 0;
    *reinterpret_cast<u64*>(p + 0x8) = 0;
    *reinterpret_cast<u32*>(p + 0x10) = 0;
    *reinterpret_cast<u32*>(p + 0x30) = 0;
    *reinterpret_cast<u64*>(p + 0x18) = 0;
    *reinterpret_cast<u64*>(p + 0x20) = 0;
    *reinterpret_cast<u64*>(p + 0x28) = 0;
}

// 710009ce30 (16B) -- ComputeShaderManager ctor: zero fields
void ComputeShaderManager(u8* p) {
    p[0] = 0;
    *reinterpret_cast<u32*>(p + 0x28) = 0;
    *reinterpret_cast<u64*>(p + 0x18) = 0;
    *reinterpret_cast<u64*>(p + 0x20) = 0;
}

// --- app::ai_debug stubs (retail build: empty) ---

namespace app::ai_debug {

void draw_line_red(void*, void*, int) {}    // 7100376c10 (16B)
void draw_line_green(void*, void*, int) {}  // 7100376c20 (16B)
void draw_circle_red(void*, float, int) {}  // 7100376c30 (16B)
void draw_circle_green(void*, float, int) {} // 7100376c40 (16B)

} // namespace app::ai_debug

// --- app::FighterUtil ---

namespace app::FighterUtil {

// 7100694dc0 (32B) -- get renderer color rate float from nested pointer chain
float renderer_get_color_rate(void) {
    u8* p = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(DAT_7105336ce8) + 8);
    return *reinterpret_cast<float*>(p + 0x10);
}

} // namespace app::FighterUtil

// --- app::stage ---

namespace app::stage {

// 71015ce6b0 (16B) -- always returns false (no render offset needed)
bool is_the_stage_needs_render_offset(void) { return false; }

} // namespace app::stage

// --- app::debug stubs ---

namespace app::debug {

void set_draw_color(void*, float, float, float, float) {} // 71015cffb0 (16B)
void draw_line(void*, void*, void*, int) {}               // 71015cffc0 (16B)

} // namespace app::debug

// --- app::sv_debug_draw stubs ---

namespace app::sv_debug_draw {

void set_draw_color(float, float, float, float) {} // 7102284ae0 (16B)
void draw_line(void*, void*, int) {}               // 7102284af0 (16B)
void draw_circle(void*, float, int) {}             // 7102284b00 (16B)

} // namespace app::sv_debug_draw
