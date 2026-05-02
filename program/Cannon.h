#pragma once
#include "Float2.h"
#include <vector>
#include "Ball.h"
#include "HelpfulFunc.h"

using namespace std;

class Cannon
{
public:

	//Singleton
	constexpr static float LINE_LENGTH = 100.0f;

	//Constructor
	Cannon(Float2 pos) : 
		position(pos),
		rotation(-90.0f)
	{
	}

	//transform
	Float2 position;
	float rotation;	

	//Store Ball
	vector<Ball> BallList;

	//Shoot Ball
	void ShootBall();

	//Draw render
	void Render();
};