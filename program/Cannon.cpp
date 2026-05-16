#include "Cannon.h"
#include "Float2.h"
#include "Main.h"
#include "Game.h"
#include <vector>
#include <algorithm>
#include "FrameBox.h"


using namespace std;

//constant
const Float2 Cannon::CANNON_POS(SCREEN_W / 2, 
								FrameBox::TOP_LEFT.y + Ball::RADIUS + (GRID_HEIGHT * Ball::RADIUS * 2));

void Cannon::Render()
{
	Float2 offset;
	offset.x = cosf(TO_RADIAN(rotation)) * LINE_LENGTH;
	offset.y = sinf(TO_RADIAN(rotation)) * LINE_LENGTH;

	int color = GetColor(255, 0, 0);
	DrawLineAA(position.x, position.y, position.x + offset.x, position.y + offset.y, color, 3.0f);
}

void Cannon::ShootBall()
{

	Ball ballTemp(position);
	ballTemp.ChangeRotation(rotation);
	ballTemp.EnableMove();
	BallList.push_back(ballTemp);
}

void Cannon::Update()
{
	float rotateSpeed = 2.0f;
	//Change rotation left
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		rotation -= rotateSpeed;
	}

	//Change rotation right
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		rotation += rotateSpeed;
	}

	//clamp rotation between 0 and 180 degrees
	float offset = 10.0f; //to prevent infinite bounce
	rotation = max(-180.0f + offset, min(rotation, 0.0f - offset)); 

	//Shoot ball
	if (PushHitKey(KEY_INPUT_SPACE) || PushHitKey(KEY_INPUT_UP))
	{
		ShootBall();
	}
}