#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ArticleModule.h"
#include "app/modules/PostureModule.h"
#include "app/modules/ModelModule.h"
#include "app/modules/WorkModule.h"

// pool-a: FighterSpecializer_Reflet — Chrom article accessors + magic kind
// All functions operate on article ID 5 (Chrom) via the accessor's ArticleModule.
// [derived: Ghidra decompilation + disassembly verification for each address]

typedef float float4 __attribute__((vector_size(16)));

#define HIDDEN __attribute__((visibility("hidden")))

// [derived: GOT entry at 0x71052a7a88 → pointer to 16-byte zero vector]
extern "C" void *PTR_ConstantZero_71052a7a88 HIDDEN;

// Article objects contain a BattleObjectModuleAccessor* at offset +0x8
// [derived: all Chrom article functions load *(article+8) as accessor]
static inline app::BattleObjectModuleAccessor* article_acc(void* article) {
    return *reinterpret_cast<app::BattleObjectModuleAccessor**>((u8*)article + 8);
}

// Article ID for Chrom in Reflet's moveset
// [derived: all 5 functions pass literal 5 to get_article]
#define ARTICLE_CHROM 5

namespace app::FighterSpecializer_Reflet {

// 0x710100d090 (76 bytes) — get_final_chrom_pos
// Returns Chrom article's position, or zero vector if article doesn't exist.
// [derived: disassembly at 0x710100d090 — ldr q0,[x0] return via posture->pos()]
extern "C" float4 get_final_chrom_pos(BattleObjectModuleAccessor* acc) {
    ArticleModule* art = static_cast<ArticleModule*>(acc->article_module);
    void* article = art->get_article(ARTICLE_CHROM);
    if (article) {
        PostureModule* posture = static_cast<PostureModule*>(article_acc(article)->posture_module);
        return *(float4*)posture->pos();
    }
    return *(float4*)PTR_ConstantZero_71052a7a88;
}

// 0x710100d0e0 (76 bytes) — set_final_chrom_pos
// Sets Chrom article's position via PostureModule::set_pos.
// [derived: disassembly at 0x710100d0e0 — str q0,[sp]; posture->set_pos(sp)]
extern "C" void set_final_chrom_pos(BattleObjectModuleAccessor* acc, float4 pos) {
    ArticleModule* art = static_cast<ArticleModule*>(acc->article_module);
    void* article = art->get_article(ARTICLE_CHROM);
    if (article) {
        PostureModule* posture = static_cast<PostureModule*>(article_acc(article)->posture_module);
        posture->set_pos(&pos);
    }
}

// 0x710100d130 (68 bytes) — get_final_chrom_lr
// Returns Chrom article's facing direction (lr), or 0.0 if absent.
// [derived: disassembly at 0x710100d130 — tail call br x1 to posture->lr()]
extern "C" f32 get_final_chrom_lr(BattleObjectModuleAccessor* acc) {
    ArticleModule* art = static_cast<ArticleModule*>(acc->article_module);
    void* article = art->get_article(ARTICLE_CHROM);
    if (article) {
        PostureModule* posture = static_cast<PostureModule*>(article_acc(article)->posture_module);
        return posture->lr();
    }
    return 0.0f;
}

// 0x710100d180 (116 bytes) — set_final_chrom_lr
// Sets Chrom article's facing direction, then updates rotation Y.
// [derived: disassembly at 0x710100d180 — set_lr then tail-call update_rot_y_lr]
extern "C" void set_final_chrom_lr(BattleObjectModuleAccessor* acc, f32 lr) {
    ArticleModule* art = static_cast<ArticleModule*>(acc->article_module);
    void* article = art->get_article(ARTICLE_CHROM);
    if (article) {
        PostureModule* posture = static_cast<PostureModule*>(article_acc(article)->posture_module);
        posture->set_lr(lr);
        posture->update_rot_y_lr();
    }
}

// 0x710100d200 (100 bytes) — set_final_chrom_joint_rotate
// Sets a joint rotation on Chrom article's ModelModule.
// [derived: disassembly at 0x710100d200 — model->set_joint_rotate(hash, &rot, 0, 0)]
extern "C" void set_final_chrom_joint_rotate(BattleObjectModuleAccessor* acc, u64 hash, float4 rot) {
    ArticleModule* art = static_cast<ArticleModule*>(acc->article_module);
    void* article = art->get_article(ARTICLE_CHROM);
    if (article) {
        ModelModule* model = static_cast<ModelModule*>(article_acc(article)->model_module);
        model->set_joint_rotate(hash, (u64)&rot, 0, 0);
    }
}

// 0x7101006b60 (108 bytes) — get_magickind
// Reads a work int's bit flags to determine magic type.
// [derived: disassembly at 0x7101006b60 — tbnz bit checks, priority order]
// Priority: bit7→7(thunder), bit0→0(fire), bit4→4(wind), bit5→5(nosferatu), bit6→6(elthunder), else→-1
extern "C" s32 get_magickind(BattleObjectModuleAccessor* acc, s32 work_id) {
    WorkModule* work = static_cast<WorkModule*>(acc->work_module);
    u32 flags = (u32)work->get_int(work_id);
    if (flags & (1u << 7)) return 7;
    if (flags & (1u << 0)) return 0;
    if (flags & (1u << 4)) return 4;
    if (flags & (1u << 5)) return 5;
    return (flags & 0x40) ? 6 : -1;
}

} // namespace app::FighterSpecializer_Reflet
