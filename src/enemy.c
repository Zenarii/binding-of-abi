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
    
    Enemy->Knockback = V2Scale(Enemy->Knockback, (1 - 2 * Platform->Delta));
    v2 Movement = v2(0, 0);
    v2 Velocity = AddV2(Movement, Enemy->Knockback);
    
    v2 PotentialPosition = AddV2(Enemy->Position, Velocity);
    v4 EnemyRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                      PotentialPosition.y - PLAYER_SIZE * 0.5,
                      PLAYER_SIZE, PLAYER_SIZE);
    
    if(AttemptMove(EnemyRect)) {
        Enemy->Position = PotentialPosition;
        Enemy->Hitbox   = EnemyRect;
    }
    else {
        if(Velocity.x) {
            f32 PrevY = Velocity.y;
            Velocity.y = 0;
            v2 PotentialPosition = AddV2(Enemy->Position, Velocity);
            v4 PlayerRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                               PotentialPosition.y - PLAYER_SIZE * 0.5,
                               PLAYER_SIZE, PLAYER_SIZE);
            if(AttemptMove(EnemyRect)) {
                Enemy->Position = PotentialPosition;
                Enemy->Hitbox   = EnemyRect;
            }
            else if(PrevY) {
                Velocity.y = PrevY;
                Velocity.x = 0;
                v2 PotentialPosition = AddV2(Enemy->Position, Velocity);
                v4 PlayerRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                                   PotentialPosition.y - PLAYER_SIZE * 0.5,
                                   PLAYER_SIZE, PLAYER_SIZE);
                if(AttemptMove(EnemyRect)) 
                    Enemy->Position = PotentialPosition;
            }
        }
    }
    
    v4 Colour = v4(1.f, 1.f, 1.f, 1.f);
    if(Enemy->TimeSinceHit < 0.5) {
        Colour.y = 0.5 + Enemy->TimeSinceHit;
        Colour.z = 0.5 + Enemy->TimeSinceHit;
        Enemy->TimeSinceHit += Platform->Delta;
    }
    
    DrawSprite(&Enemy->Sprite, Enemy->Position, Colour);
}
