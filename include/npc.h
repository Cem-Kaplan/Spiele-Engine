#include <raylib.h>
#include <iostream>
#include <string>

class NPC : public Rectangle
{
public:
    NPC(float x, float y, float width, float height) {
        x = x * GetScreenWidth();
        y = y * GetScreenHeight();
        width = width * GetScreenWidth();
        height = height * GetScreenHeight();

        DrawRectangle(x, y, width, height, BLACK);
    };

    void talk() {
        std::cout << "Hallo" << std::endl;
    };
};