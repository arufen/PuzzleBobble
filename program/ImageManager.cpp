#include "ImageManager.h"
#include "HelpfulFunc.h"
#include "Game.h"

void ImageManager::LoadAll()
{
	//Ball images
	RedBall.InitialImageAndSize(LoadGraph("data/red.png"));
	GreenBall.InitialImageAndSize(LoadGraph("data/green.png"));
	BlueBall.InitialImageAndSize(LoadGraph("data/blue.png"));
	YellowBall.InitialImageAndSize(LoadGraph("data/yellow.png"));

	Background.InitialImageAndSize(LoadGraph("data/bg.png"));
	Background.x = SCREEN_W / 2.0f;
	Background.y = (SCREEN_H / 2.0f);
}