#include "FrameBox.h"
#include "Ball.h"
#include "Game.h"
#include "ImageManager.h"

//constant
const Float2 FrameBox::TOP_LEFT(
    (SCREEN_W / 2.0f) - (Ball::RADIUS * GRID_WIDTH),
    (SCREEN_H / 2.0f) - (Ball::RADIUS * GRID_HEIGHT)//offset from top
);
const Float2 FrameBox::BOTTOM_RIGHT(
    (SCREEN_W / 2.0f) + (Ball::RADIUS * GRID_WIDTH),
    (SCREEN_H / 2.0f) + (Ball::RADIUS * GRID_HEIGHT)
);

void FrameBox::Render()
{

    // Center of screen minus half the box size
    Float2 posOrigin = TOP_LEFT;
    Float2 posOrigin2 = BOTTOM_RIGHT;


    //// Box behind (filled, white)
    //DrawBoxAA(posOrigin.x, posOrigin.y, posOrigin2.x, posOrigin2.y, GetColor(255, 120, 120), 1);

    //// Box front (outline only — make it slightly bigger for the border effect)
    //float outline = 10.0f; // thickness of outline in pixels
    //DrawBoxAA(
    //    posOrigin.x - outline,
    //    posOrigin.y - outline,
    //    posOrigin2.x + outline,
    //    posOrigin2.y + outline,
    //    GetColor(0, 0, 0), // outline color
    //    0 // 0 = not filled = just outline
    //);

	ImageManager::GetInstance().Background.RenderCenter();
    

    //for debug
    for (int y = 0; y < GRID_HEIGHT - 1; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            float x1 = (posOrigin.x + Ball::RADIUS) + (Ball::RADIUS * x * 2);
            float y1 = (posOrigin.y + Ball::RADIUS) + (Ball::RADIUS * y * 2);

            //for odd numbers
            if (y % 2 != 0)
            {
                x1 += Ball::RADIUS;
            }
            DrawCircleAA(x1, y1, Ball::RADIUS, 30, GetColor(255, 255, 255), 0);
        }
    }
}