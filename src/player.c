internal void
InitPlayer(player * Player) {
    Player->Head = (sprite){128*2, 128, 128, 128};
    Player->Head.Anim = (animation){2, 0, 0, 0};
    Player->Head.Texture = ZenLoadTextureFromPNG("player_head.png", 0);
    
    Player->Eyes = (sprite){128*2, 128, 128, 128};
    Player->Eyes.Anim = (animation){2, 0, 0, 0};
    Player->Eyes.Texture = ZenLoadTextureFromPNG("player_eyes.png", 0);
    
    Player->Tears = (sprite){128*2, 128, 128, 128};
    Player->Tears.Anim = (animation){2, 0, 0, 0};
    Player->Tears.Texture = ZenLoadTextureFromPNG("player_tears.png", 0);
    
    Player->Body = (sprite){1280, 128, 128, 128};
    Player->Body.Anim = (animation){10, 0, 0.15, 0};
    Player->Body.Texture = ZenLoadTextureFromPNG("player_body.png", 0);
    
    Player->Position = v2(250, 250);
    
    Player->EyeColour  = v4(0.f, 0.f, 0.f, 1.f);
    Player->SkinColour = v4(0.9, 0.75, 0.75, 1.f);
    Player->TearColour = TEAR_COLOUR_PLAYER;
}

internal void
DoPlayer(player * Player) {
    //
    // ~Movement
    //
    v2 Direction = v2(0, 0);
    if(ZenKeyDown(KEY_W)) Direction.y += 1;
    if(ZenKeyDown(KEY_S)) Direction.y -= 1;
    if(ZenKeyDown(KEY_A)) Direction.x -= 1;
    if(ZenKeyDown(KEY_D)) Direction.x += 1;
    
    if(Direction.x != 0 || Direction.y != 0)
        Direction = NormaliseV2(Direction);
    Direction.x *= PLAYER_SPEED * Platform->Delta;
    Direction.y *= PLAYER_SPEED * Platform->Delta;
    
    //
    // ~Collisions
    //
    v2 PotentialPosition = AddV2(Player->Position, Direction);
    v4 PlayerRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                       PotentialPosition.y - PLAYER_SIZE * 0.5,
                       PLAYER_SIZE, PLAYER_SIZE);
    
    if(AttemptMove(PlayerRect)) {
        Player->Position = PotentialPosition;
        Player->Hitbox   = PlayerRect;
    }
    else {
        if(Direction.x) {
            f32 PrevY = Direction.y;
            Direction.y = 0;
            v2 PotentialPosition = AddV2(Player->Position, Direction);
            v4 PlayerRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                               PotentialPosition.y - PLAYER_SIZE * 0.5,
                               PLAYER_SIZE, PLAYER_SIZE);
            if(AttemptMove(PlayerRect)) {
                Player->Position = PotentialPosition;
                Player->Hitbox   = PlayerRect;
            }
            else if(PrevY) {
                Direction.y = PrevY;
                Direction.x = 0;
                v2 PotentialPosition = AddV2(Player->Position, Direction);
                v4 PlayerRect = v4(PotentialPosition.x - PLAYER_SIZE * 0.5,
                                   PotentialPosition.y - PLAYER_SIZE * 0.5,
                                   PLAYER_SIZE, PLAYER_SIZE);
                if(AttemptMove(PlayerRect)) 
                    Player->Position = PotentialPosition;
            }
        }
    }
    
    //
    // ~Tears
    //
    v2 TearDirection = v2(0, 0);
    {
        if(ZenKeyDown(KEY_UP))    TearDirection.y += 1;
        if(ZenKeyDown(KEY_DOWN))  TearDirection.y -= 1;
        if(ZenKeyDown(KEY_LEFT))  TearDirection.x -= 1;
        if(ZenKeyDown(KEY_RIGHT)) TearDirection.x += 1;
        
        if(TearDirection.x && TearDirection.y) TearDirection.y = 0;
        if(TearDirection.x != 0 || TearDirection.y != 0)
            TearDirection = NormaliseV2(TearDirection);
    }
    
    local b32 ShootFromLeftEye = 1;
    // NOTE(abiab): DOWN, LEFT, UP, RIGHT
    v2 RightTearOffsets[] = {v2(-0.5, 0), v2(0, 0.5), v2(0.5, 0), v2(0, -0.5)};
    v2 LeftTearOffsets[]  = {v2(0.5, 0), v2(0, -0.5), v2(-0.5, 0), v2(0, 0.5)};
    
    i32 OffsetIndex = 0;
    if(TearDirection.y == -1) OffsetIndex = 0;
    if(TearDirection.x == -1) OffsetIndex = 1;
    if(TearDirection.y ==  1) OffsetIndex = 2;
    if(TearDirection.x ==  1) OffsetIndex = 3;
    
    v2 TearOffset = ShootFromLeftEye ? LeftTearOffsets[OffsetIndex] : RightTearOffsets[OffsetIndex];
    TearOffset = V2Scale(TearOffset, 30 /*Head Size*/);
    
    local f32 TearCountdown = 0;
    TearCountdown -= Platform->Delta;
    if(TearCountdown < 0 && LengthSquaredV2(TearDirection) > 0) {
        // Create Tear
        tear Tear = {0};
        Tear.Type = TEAR_DEFAULT;
        Tear.Position = AddV2(Player->Position, TearOffset);
        Tear.Direction = TearDirection;
        Tear.Speed = TEAR_SPEED;
        Tear.LifeSpan = 4;
        Tear.Colour = Player->TearColour;
        
        AddTear(&Tear);
        
        TearCountdown = PLAYER_TEAR_DELAY;
        ShootFromLeftEye = !ShootFromLeftEye;
    }
    
    //
    // ~Draw
    //
    i32 HeadEyeFrame = 0;
    if(TearCountdown > PLAYER_TEAR_DELAY - 0.2) HeadEyeFrame = 1;
    Player->Head.Anim.Frame  = HeadEyeFrame;
    Player->Eyes.Anim.Frame  = HeadEyeFrame;
    Player->Tears.Anim.Frame = HeadEyeFrame;
    
    if(Direction.y) DoAnimation(&Player->Body.Anim);
    else Player->Body.Anim.Frame = 0;
    
    DrawSprite(&Player->Body,  Player->Position, Player->SkinColour);
    DrawSprite(&Player->Head,  Player->Position, Player->SkinColour);
    DrawSprite(&Player->Tears, Player->Position, Player->TearColour);
    DrawSprite(&Player->Eyes,  Player->Position, Player->EyeColour);
}