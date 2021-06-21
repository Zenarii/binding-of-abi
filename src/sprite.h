//
// ~Animation
//

typedef struct animation animation;
struct animation {
    i32 Frames;
    i32 Frame;
    f32 FrameLength;
    f32 TimeSinceLastFrame;
};

//
// ~Sprite
//

typedef struct sprite sprite;
struct sprite {
    f32 SheetWidth;
    f32 SheetHeight;
    f32 Width;
    f32 Height;
    animation Anim;
    texture Texture;
};