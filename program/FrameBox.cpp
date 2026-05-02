#include "FrameBox.h"

#include "FrameBox.h"
#include "Ball.h"
#include "Game.h"

void FrameBox::Render()
{
    float lengthX = Ball::RADIUS * 8 * 2;
    float lengthY = Ball::RADIUS * 12 * 2;

    // Center of screen minus half the box size
    Float2 posOrigin;
    posOrigin.x = (SCREEN_W / 2.0f) - (lengthX / 2.0f);
    posOrigin.y = (SCREEN_H / 2.0f) - (lengthY / 2.0f);

    Float2 posOrigin2;
    posOrigin2.x = posOrigin.x + lengthX;
    posOrigin2.y = posOrigin.y + lengthY;

    // Box behind (filled, white)
    DrawBoxAA(posOrigin.x, posOrigin.y, posOrigin2.x, posOrigin2.y, GetColor(255, 120, 120), 1);

    // Box front (outline only — make it slightly bigger for the border effect)
    float outline = 4.0f; // thickness of outline in pixels
    DrawBoxAA(
        posOrigin.x - outline,
        posOrigin.y - outline,
        posOrigin2.x + outline,
        posOrigin2.y + outline,
        GetColor(0, 0, 0), // outline color, change as u want
        0 // 0 = not filled = just outline
    );
}