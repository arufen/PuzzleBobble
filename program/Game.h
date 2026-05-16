#pragma once

#include "Ball.h"
#include <vector>
using namespace std;
#define SCREEN_W	800
#define SCREEN_H	600

//Grid
#define GRID_WIDTH 8
#define GRID_HEIGHT 12

//BallList
extern vector<Ball> BallList; //for checking hitbox
extern Ball* RegisteredBalls[GRID_HEIGHT][GRID_WIDTH];

void GameInit();	//	‰Šú‰»ˆ—
void GameUpdate();	//	XVˆ—
void GameRender();	//	•`‰æˆ—
void GameExit();	//	I—¹ˆ—
