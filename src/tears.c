internal void
AddTear(tear * Tear) {
    tear_pool * TearPool = &Platform->Core->TearPool;
    if(TearPool->ActiveTears >= MAX_TEARS) {
        local ReplaceIndex = 0;
        TearPool->Tears[ReplaceIndex++] = *Tear;
        ReplaceIndex %= 100;
    }
    else {
        TearPool->Tears[TearPool->ActiveTears++] = *Tear;
    }
}

// NOTE(abi): Returns true if removed the last active tear
internal b32
RemoveTear(i32 index) {
    tear_pool * TearPool = &Platform->Core->TearPool;
    
    {
        TearPool->DyingTears[TearPool->ActiveDyingTears] = TearPool->Tears[index];
        TearPool->DyingTears[TearPool->ActiveDyingTears].TimeAlive = 0;
        TearPool->DyingTears[TearPool->ActiveDyingTears].LifeSpan  = 0.2;
        TearPool->ActiveDyingTears++;
    }
    
    if(index == 0 && TearPool->ActiveTears == 1) {
        TearPool->ActiveTears = 0;
        return 1;
    }
    
    TearPool->Tears[index] = TearPool->Tears[--TearPool->ActiveTears];
    return 0;
}

// IDEA(abiab) maybe take pointer and have multiple tear pools for collisions???
internal void
TearsBeginFrame() {
    tear_pool * TearPool = &Platform->Core->TearPool;
    for(i32 i = 0; i < TearPool->ActiveTears; ++i) {
        tear * Tear = &TearPool->Tears[i];
        
        Tear->TimeAlive += Platform->Delta;
        if(Tear->TimeAlive > Tear->LifeSpan) {
            if(RemoveTear(i)) goto NoMoreTears;
        }
        
        Tear->Position.x += Tear->Direction.x * Tear->Speed * Platform->Delta;
        Tear->Position.y += Tear->Direction.y * Tear->Speed * Platform->Delta;
        
        // NOTE(abiab): Collisions
        // TODO(abi): time this, super inefficient method
        // also add masks here
        {
            v4 TearRect = v4(Tear->Position.x - TEAR_SIZE * 0.5f,
                             Tear->Position.y - TEAR_SIZE * 0.5f,
                             TEAR_SIZE, TEAR_SIZE);
            Tear->Hitbox = TearRect;
            
            for(int x = 0; x < ROOM_WIDTH; ++x) {
                for(int y = 0; y < ROOM_HEIGHT; ++y) {
                    i32 TileIndex = x + y * ROOM_WIDTH;
                    i32 * Tile = &Platform->Core->CurrentRoom.Tiles[TileIndex];
                    if(*Tile < TILE_TEAR_BLOCKING) continue;
                    
                    v4 TileRect = v4(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                    // NOTE(abi): if collision occurs
                    if(AABBCollision(TearRect, TileRect)) {
                        if(*Tile == TILE_POOP)         *Tile = TILE_POOP_S2;
                        else if(*Tile == TILE_POOP_S2) *Tile = TILE_POOP_S3;
                        else if(*Tile == TILE_POOP_S3) *Tile = TILE_BROKEN_POOP;
                        
                        if(RemoveTear(i)) goto NoMoreTears;
                    }
                }
            }
        }
    }
    
    NoMoreTears:;
}

internal void
TearsEndFrame() {
    tear_pool * TearPool = &Platform->Core->TearPool;
    for(i32 i = 0; i < TearPool->ActiveTears; ++i) {
        tear * Tear = &TearPool->Tears[i];
        
        for(i32 i = 0; i < Platform->Core->CurrentRoom.ActiveEnemies; ++i) {
            enemy * Enemy = &Platform->Core->CurrentRoom.Enemies[i];
            if(AABBCollision(Tear->Hitbox, Enemy->Hitbox)) {
                if(RemoveTear(i)) break;
            }
        }
        
        
        v4 Destination = v4(Tear->Position.x - TEAR_SIZE * 0.5,
                            Tear->Position.y - TEAR_SIZE * 0.5,
                            TEAR_SIZE, TEAR_SIZE);
        Zen2DPushTextureRectTint(Destination, Platform->Core->TearSprites[Tear->Type], v4(0, 0, 100, 100), Tear->Colour);
    }
    
    for(i32 i = 0; i < TearPool->ActiveDyingTears; ++i) {
        tear * Tear = &TearPool->DyingTears[i];
        Tear->TimeAlive += Platform->Delta;
        if(Tear->TimeAlive > Tear->LifeSpan) {
            TearPool->DyingTears[i] = TearPool->DyingTears[--TearPool->ActiveDyingTears];
        }
        
        i32 Frame = Tear->TimeAlive > 0.1 ? 2 : 1;
        
        v4 Destination = v4(Tear->Position.x - TEAR_SIZE * 0.5,
                            Tear->Position.y - TEAR_SIZE * 0.5,
                            TEAR_SIZE, TEAR_SIZE);
        Zen2DPushTextureRectTint(Destination, Platform->Core->TearSprites[Tear->Type], v4(100 * Frame, 0, 100, 100), Tear->Colour);
    }
}