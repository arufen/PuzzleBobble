#include "Ball.h"
#include "Main.h"
#include "Float2.h"
#include "HelpfulFunc.h"

void Ball::EnableMove()
{
	canMove = true;
}

void Ball::ChangeRotation(float rot)
{
	this->rotation = rot;
}

void Ball::MoveBall()
{
	//only moves after shooting
	if (canMove == true)
	{
		MoveTowards(position.x, position.y, rotation, BALL_SPEED);
	}
}

void Ball::Render()
{
	int color = GetColor(255, 255, 255);
	DrawCircleAA(this->position.x, this->position.y, RADIUS, 30, color, 1);
}



