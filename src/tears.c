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

// IDEA(abiab) maybe take pointer and have multiple tear pools for collisions???
internal void
DoTears() {
    tear_pool * TearPool = &Platform->Core->TearPool;
    for(i32 i = 0; i < TearPool->ActiveTears; ++i) {
        tear * Tear = &TearPool->Tears[i];
        
        Tear->TimeAlive += Platform->Delta;
        if(Tear->TimeAlive > Tear->LifeSpan) {
            *Tear = TearPool->Tears[--TearPool->ActiveTears];
        }
        
        Tear->Position.x += Tear->Direction.x * Tear->Speed * Platform->Delta;
        Tear->Position.y += Tear->Direction.y * Tear->Speed * Platform->Delta;
        
        // TODO(abiab) Collisions
        
        v4 Destination = v4(Tear->Position.x - TEAR_SIZE * 0.5,
                            Tear->Position.y - TEAR_SIZE * 0.5,
                            TEAR_SIZE, TEAR_SIZE);
        Zen2DPushTextureRectTint(Destination, Platform->Core->TearSprites[Tear->Type], v4(0, 0, 100, 100), Tear->Colour);
    }
}