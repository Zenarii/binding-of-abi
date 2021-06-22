#define ROOM_HEIGHT 9
#define ROOM_WIDTH  13
#define TILE_SIZE   128

enum {
    TILE_EMPTY,
    TILE_BLOCKING,
    TILE_ROCK = TILE_BLOCKING,
    TILE_WALL,
    
    TILE_COUNT
};

typedef struct room room;
struct room {
    //b32 Door[4];
    i32 Tiles[ROOM_HEIGHT * ROOM_WIDTH];
    i32 ActiveEnemies;
    enemy Enemies[MAX_ENEMIES];
};
