#define PLAYER_SPEED 200
#define PLAYER_SIZE 128
#define PLAYER_TEAR_DELAY 0.7

typedef struct player player;
struct player {
    sprite Head;
    sprite Eyes;
    sprite Body;
    sprite Tears;
    
    v2 Position;
    
    v4 SkinColour;
    v4 EyeColour;
    v4 TearColour;
    
    v4 Hitbox;
};

