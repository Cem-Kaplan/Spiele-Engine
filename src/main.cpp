#include "raylib.h"
#include <player.h>
#include <map.h>
#include <colors.h>
#include <iostream>
#include <raymath.h>
#include <npc.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <cstdio>

int game(void) { 
    InitWindow(800, 600, "Game Engine");

    const int screenWidth  = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    // Player
    Rectangle player = build_player();

    float velocityY = 0.0f;
    bool isJumping  = false;

    const float gravity   = 0.8f;
    const float jumpForce = -15.0f;

    // Map collision (Boden)
    Rectangle mapCollision = {
        0.0f,
        0.8f * screenHeight,
        2.0f * screenWidth,
        0.2f * screenHeight
    };

    // Camera
    Camera2D camera = { 0 };
    camera.offset   = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom     = 1.0f;

    // Mobile Buttons
    Rectangle btnLeft  = { 40.0f, GetScreenHeight() - 140.0f, 120.0f, 120.0f };
    Rectangle btnRight = { 200.0f, GetScreenHeight() - 140.0f, 120.0f, 120.0f };
    Rectangle btnJump  = { GetScreenWidth() - 160.0f, GetScreenHeight() - 160.0f, 120.0f, 120.0f };


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
    /* ================= INPUT ================= */

    bool moveLeft  = false;
    bool moveRight = false;
    bool jumpTouch = false;

    int touchCount = GetTouchPointCount();

    for (int i = 0; i < touchCount; i++)
    {
        Vector2 touch = GetTouchPosition(i);

        if (CheckCollisionPointRec(touch, btnLeft))
            moveLeft = true;

        if (CheckCollisionPointRec(touch, btnRight))
            moveRight = true;

        if (CheckCollisionPointRec(touch, btnJump))
            jumpTouch = true;
    }

    // Links
    if (IsKeyDown(KEY_A) || moveLeft)
        player.x -= playerSpeed;

    // Rechts
    if (IsKeyDown(KEY_D) || moveRight)
        player.x += playerSpeed;

    // Jump
    if ((IsKeyPressed(KEY_SPACE) || jumpTouch) && !isJumping)
    {
        velocityY = jumpForce;
        isJumping = true;
    }

        player.x = Clamp(
            player.x,
            0.0f,
            2.0f * GetScreenWidth() - player.width
        );

        /* ================= PHYSICS ================= */

        // Gravity
        velocityY += gravity;

        // Alte Y-Position merken
        float oldY = player.y;

        // Bewegung anwenden
        player.y += velocityY;

        // Boden-Collision (NACH Bewegung!)
        if (CheckCollisionRecs(player, mapCollision))
        {
            // Nur wenn von oben gefallen
            if (oldY + player.height <= mapCollision.y)
            {
                player.y = mapCollision.y - player.height;
                velocityY = 0.0f;
                isJumping = false;
            }
        }

        /* ================= CAMERA ================= */

        camera.target = (Vector2){
            player.x + player.width * 0.5f,
            player.y + player.height * 0.5f
        };

        /* ================= DRAW ================= */

        BeginDrawing();
        ClearBackground(SKY_BLUE);

        BeginMode2D(camera);
            build_map();

            NPC* npc_1 = new NPC(0.2f, 0.6f, 0.07f, 0.2f);

            DrawRectangleRec(player, YELLOW);

            // DEBUG (optional)
            DrawRectangleLinesEx(mapCollision, 2, GREEN);
            DrawRectangleLinesEx(player, 2, RED);
        EndMode2D();

        DrawRectangleRec(btnLeft, Fade(DARKGRAY, 0.5f));
        DrawRectangleRec(btnRight, Fade(DARKGRAY, 0.5f));
        DrawRectangleRec(btnJump, Fade(DARKGREEN, 0.6f));

        DrawText("<", btnLeft.x + 45, btnLeft.y + 35, 40, WHITE);
        DrawText(">", btnRight.x + 45, btnRight.y + 35, 40, WHITE);
        DrawText("J", btnJump.x + 45, btnJump.y + 35, 40, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowTitle("Game Engine von Cem");
    mainWindow.resize(1000, 500);

    QPushButton debugButton("Test", &mainWindow);
    debugButton.resize(200, 50);
    debugButton.move(10, 10);
    
    QPushButton stopButton("Stop Test", &mainWindow);
    stopButton.resize(200, 50);
    stopButton.move(10, 70);
    
    mainWindow.show();

    QObject::connect(&debugButton, &QPushButton::clicked, [&]() {
	game();
    }); 

    QObject::connect(&stopButton, &QPushButton::clicked, [&]() {
        std::printf("Game ends");
    });

    app.exec();

    return 0;
}
