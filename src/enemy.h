#define MAX_ENEMIES 64
#define ENEMY_SIZE  128

typedef struct enemy enemy;
struct enemy {
    sprite Sprite;
    
    v2 Position;
    v4 Hitbox;
    f32 TimeSinceHit;
    v2 Knockback;
};