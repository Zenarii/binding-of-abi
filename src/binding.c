// NOTE(Abi): Headers
#include "zenlib/zenlib.h"
#include "sprite.h"
#include "tears.h"
#include "enemy.h"
#include "room.h"
#include "player.h"

struct core {
    player Player;
    tear_pool TearPool;
    texture TearSprites[TEAR_TYPE_COUNT];
    
    room CurrentRoom;
    texture DummyTexture;
    texture RockTexture;
    texture PoopTexture;
    texture PoopTextureS2;
    texture PoopTextureS3;
    texture BrokenPoopTexture;
    
    font DebugFont;
};

// NOTE(Abi): Implementations
#include "zenlib/zenlib.c"
#include "physics.c"
#include "sprite.c"
#include "tears.c"
#include "room.c"
#include "enemy.c"
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
    
    Platform->Core->DummyTexture   = ZenLoadTextureFromPNG("dummy.png", 0);
    Platform->Core->RockTexture    = ZenLoadTextureFromPNG("rock.png", 0);
    Platform->Core->PoopTexture    = ZenLoadTextureFromPNG("poop.png", 0);
    Platform->Core->PoopTextureS2  = ZenLoadTextureFromPNG("poop_stage_2.png", 0);
    Platform->Core->PoopTextureS3  = ZenLoadTextureFromPNG("poop_stage_3.png", 0);
    Platform->Core->BrokenPoopTexture = ZenLoadTextureFromPNG("broken_poop.png", 0);
    InitRoom(&Platform->Core->CurrentRoom);
    
    Platform->Core->TearSprites[TEAR_DEFAULT] = ZenLoadTextureFromPNG("tear.png", 0);
    
    Platform->Core->DebugFont = Zen2DLoadFontFromFNTAndPNG("libmono.fnt", "libmono.png");
    Zen2DSetDefaultFont(&Platform->Core->DebugFont);
}

internal void
AppUpdate() {
    DrawRoom(&Platform->Core->CurrentRoom);
    TearsBeginFrame();
    // TODO DoEnemies();
    room * Room = &Platform->Core->CurrentRoom;
    for(i32 i = 0; i < Room->ActiveEnemies; ++i) {
        DoEnemy(&Room->Enemies[0]);
    }
    DoPlayer(&Platform->Core->Player);
    TearsEndFrame();
}

internal void
AppHotUnload() {
    
}

internal void
AppHotLoad() {
    
}