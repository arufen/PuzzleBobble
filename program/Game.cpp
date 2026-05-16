#include "Main.h"
#include "Game.h"

//Objects header
#include "Ball.h"
#include "Cannon.h"
#include "FrameBox.h"

//Singleton header
#include "ImageManager.h"



//Init object
vector<Ball> BallList;
Ball* RegisteredBalls[GRID_HEIGHT][GRID_WIDTH];
Cannon cannon(Cannon::CANNON_POS);
FrameBox frameBox;


//grid
//int GridList[GRID_HEIGHT][GRID_WIDTH];

void GameInit()
{
	ImageManager::GetInstance().LoadAll();
}



void GameUpdate()
{
	//Cannon mechanic
	{
		cannon.Update();
	}

	for (size_t i = 0; i < BallList.size(); i++)
	{
		BallList[i].CheckCollision();
		BallList[i].MoveBall();
	}

}



void GameRender()
{	//Framebox render
	frameBox.Render();

	//object render
	cannon.Render();



	for (size_t i = 0; i < BallList.size(); i++)
	{
		BallList[i].Render();


		////debug
		//DrawFormatString(0, 0 + (20 * i), GetColor(255, 255, 255), "Ball %d: x = %f, y = %f, gridX: %d, gridY: %d",
		//	i, 
		//	BallList[i].position.x, BallList[i].position.y,
		//	BallList[i].gridX, BallList[i].gridY);
	}

	for (size_t y = 0; y < GRID_HEIGHT; y++)
	{
		for (size_t x = 0; x < GRID_HEIGHT; x++)
		{
			if (RegisteredBalls[y][x] != NULL)
			{
				DrawFormatString(0 + (x * 100), 0 + (20 * y), GetColor(255, 255, 255), "Ball[%d][%d]",
					y, x);
			}
			

		}
	}



	

	////debug
	//DrawCircleAA(FrameBox::TOP_LEFT.x, FrameBox::TOP_LEFT.y, 3, 30, GetColor(255, 0, 0), 0);
	//DrawCircleAA(FrameBox::BOTTOM_RIGHT.x, FrameBox::BOTTOM_RIGHT.y, 3, 30, GetColor(0, 0, 255), 0);

} 



void GameExit()
{
}
