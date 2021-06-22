internal void
DoEnemy(enemy * Enemy) {
    Enemy->Hitbox = v4(Enemy->Position.x - ENEMY_SIZE * 0.5f,
                       Enemy->Position.y - ENEMY_SIZE * 0.5f,
                       ENEMY_SIZE, ENEMY_SIZE);
    
    //
    // ~Collisions
    //
    
    tear_pool * TearPool = &Platform->Core->TearPool;
    for(int i = 0; i < TearPool->ActiveTears; ++i) {
        tear Tear = TearPool->Tears[i];
        if(AABBCollision(Tear.Hitbox, Enemy->Hitbox)) {
            Enemy->TimeSinceHit = 0.f;
            Enemy->Knockback = V2Scale(Tear.Direction, 1.f);
        }
    }
    
    
    v4 Colour = v4(1.f, 1.f, 1.f, 1.f);
    if(Enemy->TimeSinceHit < 0.5) {
        Colour.y = 0.5 + Enemy->TimeSinceHit;
        Colour.z = 0.5 + Enemy->TimeSinceHit;
        Enemy->TimeSinceHit += Platform->Delta;
    }
    
    Enemy->Knockback = V2Scale(Enemy->Knockback, (1 - 2 * Platform->Delta));
    v2 Movement = v2(0, 0);
    v2 Velocity = AddV2(Movement, Enemy->Knockback);
    Enemy->Position = AddV2(Enemy->Position, Velocity);
    
    DrawSprite(&Enemy->Sprite, Enemy->Position, Colour);
}
