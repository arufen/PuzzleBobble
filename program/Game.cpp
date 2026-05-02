#include "Main.h"
#include "Game.h"

//Objects header
#include "Ball.h"
#include "Cannon.h"
#include "FrameBox.h"

//Const
const Float2 CANNON_POS(SCREEN_W / 2, 0.8f * SCREEN_H);

//Init object
Ball ballTest(Float2(SCREEN_W /2, SCREEN_H /2));
Cannon cannonTest(CANNON_POS);
FrameBox frameBox;
void GameInit()
{
	
}



void GameUpdate()
{
	//Cannon mechanic
	{
		float rotateSpeed = 2.0f;
		//Change rotation left
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			cannonTest.rotation -= rotateSpeed;
		}

		//Change rotation right
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			cannonTest.rotation += rotateSpeed;
		}

		//Shoot ball
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			cannonTest.ShootBall();
		}
	}

	for (size_t i = 0; i < cannonTest.BallList.size(); i++)
	{
		cannonTest.BallList[i].MoveBall();
	}

}



void GameRender()
{	//Framebox render
	frameBox.Render();

	//object render
	ballTest.Render();
	cannonTest.Render();

	for (size_t i = 0; i < cannonTest.BallList.size(); i++)
	{
		cannonTest.BallList[i].Render();
	}

;


}



void GameExit()
{
}
