#pragma once
#include "Float2.h"

class  Ball
{
public:

	//singleton
	constexpr static float RADIUS = 20.0f;
	constexpr static float BALL_SPEED = 16.0f;

	//Constructor
	Ball(Float2 pos) : 
		position (pos),
		rotation(0.0f),
		canMove(false) 
	{};



	//Variables
	Float2 position;
	float rotation;
	bool canMove;

	//one time
	void ChangeRotation(float rot);
	void EnableMove();

	//update
	void MoveBall();


	//Render
	void Render();


};