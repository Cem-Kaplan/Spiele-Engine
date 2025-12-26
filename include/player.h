const float playerSpeed = 4.0f;

Rectangle build_player(){
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    const float spawnX = 0.5 * screenWidth;
    const float spawnY = 0.6 * screenHeight;
    const float playerWidth = 0.07 * screenWidth;
    const float playerHeight = 0.2 * screenHeight;

    static Rectangle player = {spawnX, spawnY, playerWidth, playerHeight}; 
    return player;
};