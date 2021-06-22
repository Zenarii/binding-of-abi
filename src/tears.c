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
    Log("Removing tear %d/%d", index, TearPool->ActiveTears);
    if(index == 0 && TearPool->ActiveTears == 1) {
        TearPool->ActiveTears = 0;
        return 1;
    }
    
    TearPool->Tears[index] = TearPool->Tears[--TearPool->ActiveTears];
    return 0;
}

// IDEA(abiab) maybe take pointer and have multiple tear pools for collisions???
internal void
DoTears() {
    tear_pool * TearPool = &Platform->Core->TearPool;
    for(i32 i = 0; i < TearPool->ActiveTears; ++i) {
        tear * Tear = &TearPool->Tears[i];
        
        Tear->TimeAlive += Platform->Delta;
        if(Tear->TimeAlive > Tear->LifeSpan) {
            if(RemoveTear(i)) break;
        }
        
        Tear->Position.x += Tear->Direction.x * Tear->Speed * Platform->Delta;
        Tear->Position.y += Tear->Direction.y * Tear->Speed * Platform->Delta;
        
        // NOTE(abiab): Collisions
        // TODO(abi): time this, super inefficient method
        {
            v4 TearRect = v4(Tear->Position.x - TEAR_SIZE * 0.5f,
                             Tear->Position.y - TEAR_SIZE * 0.5f,
                             TEAR_SIZE, TEAR_SIZE);
            
            for(int x = 0; x < ROOM_WIDTH; ++x) {
                for(int y = 0; y < ROOM_HEIGHT; ++y) {
                    if(Platform->Core->CurrentRoom.Tiles[x + y * ROOM_WIDTH] < TILE_BLOCKING) continue;
                    
                    v4 TileRect = v4(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                    if(AABBCollision(TearRect, TileRect)) {
                        if(RemoveTear(i)) break;
                    }
                }
            }
        }
        
        v4 Destination = v4(Tear->Position.x - TEAR_SIZE * 0.5,
                            Tear->Position.y - TEAR_SIZE * 0.5,
                            TEAR_SIZE, TEAR_SIZE);
        Zen2DPushTextureRectTint(Destination, Platform->Core->TearSprites[Tear->Type], v4(0, 0, 100, 100), Tear->Colour);
    }
}