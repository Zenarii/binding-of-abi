global char * RoomString = 
"2222222222222" \
"2000300000002" \
"2111100000002" \
"2000000000002" \
"2111000000002" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2222222222222";


internal void
InitRoom(room * Room) {
    Room->Floor = ZenLoadTextureFromPNG("basement01.png", 0);
    
    for(int i = 0; i < ROOM_WIDTH * ROOM_HEIGHT; ++i) {
        switch(RoomString[i]) {
            case '0': {
                Room->Tiles[i] = TILE_EMPTY;
            } break;
            case '1': {
                Room->Tiles[i] = TILE_ROCK;
            } break;
            case '2': {
                Room->Tiles[i] = TILE_WALL;
            } break;
            case '3': {
                Room->Tiles[i] = TILE_POOP;
            }
        }
    }
    Room->ActiveEnemies = 1;
    Room->Enemies[0].Position = v2(128 * ROOM_WIDTH * 0.5, 128 * ROOM_HEIGHT * 0.5);
    Room->Enemies[0].Sprite = (sprite){128, 128, 128, 128};
    Room->Enemies[0].Sprite.Texture = Platform->Core->DummyTexture;
}

internal void
DrawRoom(room * Room) {
    Zen2DPushTexture(Room->Floor, v2(0, 0));
    
    for(i32 x = 0; x < ROOM_WIDTH; ++x) {
        for(i32 y = 0; y < ROOM_HEIGHT; ++y) {
            
            v4 Rect = v4(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            switch(Room->Tiles[x + y * ROOM_WIDTH]) {
                case(TILE_EMPTY): break;
                case(TILE_WALL): break;
                case(TILE_POOP): {
                    Zen2DPushTextureRect(Rect, Platform->Core->PoopTexture, v4(0, 0, TILE_SIZE, TILE_SIZE));
                } break;
                case(TILE_POOP_S2): {
                    Zen2DPushTextureRect(Rect, Platform->Core->PoopTextureS2, v4(0, 0, TILE_SIZE, TILE_SIZE));
                } break;
                case(TILE_POOP_S3): {
                    Zen2DPushTextureRect(Rect, Platform->Core->PoopTextureS3, v4(0, 0, TILE_SIZE, TILE_SIZE));
                } break;
                case(TILE_BROKEN_POOP): {
                    Zen2DPushTextureRect(Rect, Platform->Core->BrokenPoopTexture, v4(0, 0, TILE_SIZE, TILE_SIZE));
                } break;
                case(TILE_ROCK): {
                    Zen2DPushTextureRect(Rect, Platform->Core->RockTexture, v4(0, 0, TILE_SIZE, TILE_SIZE));
                } break;
            }
        }
    }
}