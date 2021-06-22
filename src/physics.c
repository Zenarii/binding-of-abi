internal b32
AABBCollision(v4 RectA, v4 RectB) {
    return (RectA.x < RectB.x + RectB.Width &&
            RectA.x + RectA.Width > RectB.x &&
            RectA.y + RectA.Height > RectB.y &&
            RectA.y < RectB.y + RectB.Height);
}

internal b32
AttemptMove(v4 Desired) {
    for(int x = 0; x < ROOM_WIDTH; ++x) {
        for(int y = 0; y < ROOM_HEIGHT; ++y) {
            if(Platform->Core->CurrentRoom.Tiles[x + y * ROOM_WIDTH] < TILE_MOVE_BLOCKING) continue;
            
            v4 TileRect = v4(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            if(AABBCollision(Desired, TileRect)) {
                return 0;
            }
        }
    }
    return 1;
}