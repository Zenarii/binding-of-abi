//
// ~Animation
//


internal void
DoAnimation(animation * Anim) {
    Anim->TimeSinceLastFrame += Platform->Delta;
    if(Anim->TimeSinceLastFrame > Anim->FrameLength) {
        Anim->Frame++;
        Anim->TimeSinceLastFrame -= Anim->FrameLength;
        if(Anim->Frame > Anim->Frames) Anim->Frame = 0;
    }
}

//
// ~Sprite
//

internal void
DrawSprite(sprite * Sprite, v2 Position, v4 Colour) {
    v4 Destination = v4(Position.x - Sprite->Width * 0.5,
                        Position.y - Sprite->Width * 0.5,
                        Sprite->Width, Sprite->Height);
    v4 Source = v4(Sprite->Width * Sprite->Anim.Frame, 0, PLAYER_SIZE, PLAYER_SIZE);
    
    Zen2DPushTextureRectTint(Destination, Sprite->Texture, Source, Colour);
}
