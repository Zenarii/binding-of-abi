#define ROOM_HEIGHT 9
#define ROOM_WIDTH  13
#define TILE_SIZE   128

enum {
    TILE_EMPTY,
    TILE_BROKEN_POOP,
    TILE_MOVE_BLOCKING,
    TILE_GAP,
    TILE_TEAR_BLOCKING,
    
    TILE_POOP_S3,
    TILE_POOP_S2,
    TILE_POOP,
    
    TILE_ROCK,
    TILE_WALL,
    
    TILE_COUNT
};

typedef struct room room;
struct room {
    //b32 Door[4];
    texture Floor;
    i32 Tiles[ROOM_HEIGHT * ROOM_WIDTH];
    i32 ActiveEnemies;
    enemy Enemies[MAX_ENEMIES];
};
