#pragma once
#include "Float2.h"
#include "Main.h"
#include "Game.h"
#include "Ball.h"

class FrameBox
{
public:

	//Singelton

	//same as posOrigin
	//const static Float2 TOP_LEFT
	//(
	//((SCREEN_W / 2.0f) - ((Ball::RADIUS * GRID_WIDTH * 2) / 2.0f)),
	//((SCREEN_H / 2.0f) - ((Ball::RADIUS * GRID_HEIGHT * 2 )/ 2.0f) + -50.0f)
	//)
	const static Float2 TOP_LEFT;
	const static Float2 BOTTOM_RIGHT;
	


	void Render();


}; 