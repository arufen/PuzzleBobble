#include "Cannon.h"
#include "Float2.h"
#include "Main.h"
#include <vector>

using namespace std;

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