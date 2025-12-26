void build_map(){
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    static float mapWidth = 2.0f * screenWidth;
    static float mapHeight = 0.2f * screenHeight;
    static float mapX = 0.0f * screenWidth;
    static float mapY = 0.8f * screenHeight;
    static float mapTileLength = 0.2f * screenWidth;

    static Rectangle map = {mapX, mapY, mapWidth, mapHeight};

    // Baum
    static float treeWidth = 0.04f * screenWidth;
    static float treeHeight = 0.2f * screenHeight;
    static float treeX_1 = 0.03f * screenWidth;
    // align tree bottom to top of map so collisions/visuals match
    static float treeY = mapY - treeHeight;

    static Rectangle tree_1 = {treeX_1, treeY, treeWidth, treeHeight};

    // load texture once
    static Texture2D textur = {0};
    if (textur.id == 0) {
        textur = LoadTexture("assets/images/Sand.png");
    }

    // number of tiles to cover the map width (add 1 to ensure full coverage)
    int tiles = (int)(mapWidth / mapTileLength) + 1;

    // source rect is the whole texture; destination rect defines position+size on screen
    Rectangle src = {0.0f, 0.0f, (float)textur.width, (float)textur.height};
    for (int x = 0; x < tiles; x++ ) {
        Rectangle dest = { mapX + x * mapTileLength, mapY, mapTileLength, mapHeight };
        DrawTexturePro(textur, src, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
    }

    DrawRectangleRec(tree_1, GREEN);
}