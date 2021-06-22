global char * RoomString = 
"2222222222222" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2000000000002" \
"2222222222222";


internal void
InitRoom(room * Room) {
    for(int i = 0; i < ROOM_WIDTH * ROOM_HEIGHT; ++i) {
        switch(RoomString[i]) {
            case '2': {
                Room->Tiles[i] = TILE_WALL;
            } break;
            case '0': {
                Room->Tiles[i] = TILE_EMPTY;
            } break;
        }
    }
    Room->ActiveEnemies = 1;
    Room->Enemies[0].Position = v2(400, 400);
    Room->Enemies[0].Sprite = (sprite){128, 128, 128, 128};
    Room->Enemies[0].Sprite.Texture = Platform->Core->DummyTexture;
}

internal void
DrawRoom(room * Room) {
    for(i32 x = 0; x < ROOM_WIDTH; ++x) {
        for(i32 y = 0; y < ROOM_HEIGHT; ++y) {
            
            v4 Rect = v4(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            switch(Room->Tiles[x + y * ROOM_WIDTH]) {
                case(TILE_EMPTY): break;
                case(TILE_ROCK): {
                    //Zen2DPushRect(Rect, v4(0.f, 0.f, 1.f, 1.f)); 
                } break;
                case(TILE_WALL): {
                    v4 Colour = v4(1.f, 0.f, 0.f, 1.f);
                    Zen2DPushRect(Rect, Colour); 
                } break;
            }
        }
    }
}