// TODO(abi): fix issues with removing tears
// TODO(abi): collision masks

#define TEAR_SPEED 300
#define MAX_TEARS 100
#define TEAR_SIZE 30
#define TEAR_DELAY 0.2

#define TEAR_COLOUR_PLAYER v4(0.53, 0.81, 0.92, 1.f);
#define TEAR_COLOUR_BLOOD  v4(0.5, 0.05, 0.05, 1.f);

enum tear_type {
    TEAR_DEFAULT,
    
    TEAR_TYPE_COUNT
};

typedef struct tear tear;
struct tear {
    i32 Type;
    v2 Position;
    v4 Hitbox;
    v2 Direction;
    f32 Speed;
    f32 TimeAlive;
    f32 LifeSpan;
    v4 Colour;
};

typedef struct tear_pool tear_pool;
struct tear_pool {
    i32 ActiveTears;
    tear Tears[MAX_TEARS];
    i32 ActiveDyingTears;
    tear DyingTears[MAX_TEARS];
};
