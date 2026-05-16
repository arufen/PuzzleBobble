	#pragma once
	#include "Float2.h"

	enum class Color
	{
		RED,
		GREEN,
		BLUE,
		YELLOW,
		PURPLE,
		ORANGE,
		SILVER,
		BLACK

	};
	class  Ball
	{
	public:

		//singleton
		constexpr static float RADIUS = 20.0f;
		constexpr static float BALL_SPEED = 16.0f;

		//Constructor
		Ball(Float2 pos);

		//Variables
		Float2 position;
		float rotation; //direction of movement
		bool canMove;
		int gridX;
		int gridY;
		Color color;

		//one time
		void ChangeRotation(float rot);
		void EnableMove();
		void DisableMove();
		void Ricochet();
		Float2 SnapToGrid(Float2 globalPos);
		Float2 SnapToGrid(Ball placedBall, Ball movingBall);
		Float2 SnapToGrid(int x, int y);
		Color CheckColor(int x, int y); //based on grid
		void CheckNearbyColor();

		void Destroy();

		//update
		void MoveBall();
		void CheckCollision();



		//Render
		void Render();
	};

