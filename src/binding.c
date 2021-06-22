// NOTE(Abi): Headers
#include "zenlib/zenlib.h"
#include "sprite.h"
#include "tears.h"
#include "room.h"
#include "player.h"

struct core {
    player Player;
    tear_pool TearPool;
    texture TearSprites[TEAR_TYPE_COUNT];
    
    room CurrentRoom;
    
    font DebugFont;
};

// NOTE(Abi): Implementations
#include "zenlib/zenlib.c"
#include "physics.c"
#include "sprite.c"
#include "tears.c"
#include "room.c"
#include "player.c"

enum directions {
    DOWN,
    LEFT,
    UP,
    RIGHT,
};

internal void
AppInit() {
    Platform->Core = MemoryArenaAlloc(&Platform->PermenantArena, sizeof(core));
    
    InitPlayer(&Platform->Core->Player);
    InitRoom(&Platform->Core->CurrentRoom);
    
    Platform->Core->TearSprites[TEAR_DEFAULT] = ZenLoadTextureFromPNG("tear.png", 0);
    
    Platform->Core->DebugFont = Zen2DLoadFontFromFNTAndPNG("libmono.fnt", "libmono.png");
    Zen2DSetDefaultFont(&Platform->Core->DebugFont);
}

internal void
AppUpdate() {
    DrawRoom(&Platform->Core->CurrentRoom);
    DoPlayer(&Platform->Core->Player);
    DoTears();
    
    char Buffer[64] = {0};
    sprintf(Buffer, "Active Tears: %d", Platform->Core->TearPool.ActiveTears);
    Zen2DPushText(Buffer, v2(0, 0), 20);
}

internal void
AppHotUnload() {
    
}

internal void
AppHotLoad() {
    
}