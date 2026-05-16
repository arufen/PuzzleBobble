#include "Ball.h"
#include "Main.h"
#include "Float2.h"
#include "HelpfulFunc.h"
#include "FrameBox.h"
#include "Hit.h"
#include <cmath>
#include "ImageManager.h"

//Constructor
Ball::Ball(Float2 pos) :
	position(pos),
	rotation(0.0f),
	canMove(false),
	gridX(-1),
	gridY(-1)
{
	//Random color (for testing only use red, green, blue,yellow only)
	int randomColor = GetRand(3);
	switch (randomColor)
	{
	case 0:
		color = Color::RED;
		break;
	case 1:
		color = Color::GREEN;
		break;
	case 2:
		color = Color::BLUE;
		break;
	case 3:
		color = Color::YELLOW;
		break;
	}
}

//One time function
void Ball::EnableMove()
{
	canMove = true;
}

void Ball::DisableMove()
{
	canMove = false;
}

void Ball::ChangeRotation(float rot)
{
	this->rotation = rot;
}

void Ball::Ricochet()
{
	float a = rotation / 10;
	float b = 9 - a;
	float c = b * 20;
	rotation += c;
}

//Update
void Ball::MoveBall()
{
	//only moves after shooting
	if (canMove == true)
	{
		MoveTowards(position.x, position.y, rotation, BALL_SPEED);
	}
}

Float2 Ball::SnapToGrid(Float2 globalPos)
{
	//info
	float topBorder = FrameBox::TOP_LEFT.y + RADIUS;
	float leftBorder = FrameBox::TOP_LEFT.x + RADIUS;
	float rightBorder = FrameBox::BOTTOM_RIGHT.x - RADIUS;

	float gridSize = Ball::RADIUS * 2;

	Float2 snappedPos;
	//convert to local position
	snappedPos.x = globalPos.x - leftBorder;
	snappedPos.y = globalPos.y - topBorder;

	//grid position
	Float2 gridPos;
	gridPos.x = round(snappedPos.x / gridSize);
	gridPos.y = round(snappedPos.y / gridSize);

	//snap to world position
	snappedPos = SnapToGrid(static_cast<int>(gridPos.x), 
							static_cast<int>(gridPos.y));

	return snappedPos;
}

Float2 Ball::SnapToGrid(Ball placedBall, Ball movingBall)
{
	Float2 snappedPos;
	
	//Check angle based on hexagon shape
	float angle = GetAngle(
		placedBall.position.x, placedBall.position.y, 
		movingBall.position.x, movingBall.position.y);

	// convert to 0-360
	if (angle < 0) angle += 360.0f;

	//is placed ball grid Y is even
	bool isOddRow = (placedBall.gridY % 2 == 1);

	int newGridX = -1;
	int newGridY = -1;

	// each slice is 60 degrees, starting from 0 (right)
	if (angle >= 330.0f || angle < 30.0f)          // right
	{
		newGridX = placedBall.gridX + 1;
		newGridY = placedBall.gridY;
	}
	else if (angle > 30.0f && angle <= 90.0f)      // bottom right
	{
		newGridX = isOddRow ? placedBall.gridX + 1 : placedBall.gridX;
		newGridY = placedBall.gridY + 1;
	}
	else if (angle > 90.0f && angle <= 150.0f)     // bottom left
	{
		newGridX = isOddRow ? placedBall.gridX : placedBall.gridX - 1;
		newGridY = placedBall.gridY + 1;
	}
	else if (angle > 150.0f && angle <= 210.0f)    // left
	{
		newGridX = placedBall.gridX - 1;
		newGridY = placedBall.gridY;
	}
	else if (angle > 210.0f && angle <= 270.0f)    // top left
	{
		newGridX = isOddRow ? placedBall.gridX : placedBall.gridX - 1;
		newGridY = placedBall.gridY - 1;
	}
	else if (angle > 270.0f && angle <= 330.0f)    // top right
	{
		newGridX = isOddRow ? placedBall.gridX + 1 : placedBall.gridX;
		newGridY = placedBall.gridY - 1;
	}

	snappedPos = SnapToGrid(newGridX, newGridY);

	return snappedPos;
}

//snap it to desire grid position
Float2 Ball::SnapToGrid(int x, int y)
{
	//info
	float gridSize = RADIUS * 2;
	float topBorder = FrameBox::TOP_LEFT.y + RADIUS;
	float leftBorder = FrameBox::TOP_LEFT.x + RADIUS;
	float rightBorder = FrameBox::BOTTOM_RIGHT.x - RADIUS;

	//init
	Float2 snappedPos;
	int newGridX = x;
	int newGridY = y;

	//is placed ball grid Y is even
	bool isOddRow = (y % 2 == 1);

	//clamp grid
	//for even rows
	if (isOddRow)
	{
		newGridX = max(0, min(newGridX, GRID_WIDTH - 2));
	}
	//for odd rows
	else
	{
		newGridX = max(0, min(newGridX, GRID_WIDTH - 1));
	}

	//register grid position
	//register inside ball info
	{
		gridX = newGridX;
		gridY = newGridY;
	}
	//register in RegisteredBalls
	{
		RegisteredBalls[gridY][gridX] = this;
	}

	//snap to world position
	snappedPos.x = 
		isOddRow ? 
		newGridX * gridSize + leftBorder + RADIUS :
		newGridX * gridSize + leftBorder;

	snappedPos.y = newGridY * gridSize + topBorder;

	return snappedPos;

}

Color Ball::CheckColor(int x, int y)
{
	Color color;
	color = RegisteredBalls[y][x]->color;

	return color;
}

//if nearby color are same, then destroy
//void Ball::CheckNearbyColor()
//{
//	//info (read only)
//	int currentGridX = gridX;
//	int currentGridY = gridY;
//	Color currentColor = color;
//
//
//	//is placed ball grid Y is even
//	bool isOddRow = (currentGridY % 2 == 1);
//
//
//		vector<Ball>ToDestroyBalls;
//		//Check destroyable same color balls
//		{
//			for (int targetGridY = currentGridY - 1; targetGridY < currentGridY + 3; targetGridY++)
//			{
//				if (targetGridY < 0 ||
//					targetGridY > GRID_HEIGHT - 1
//					)
//					continue;
//
//				bool isTargetEvenRow = targetGridY % 2 == 0;
//
//				for (int targetGridX = 
//						isOddRow ? 
//							!isTargetEvenRow ?  
//								currentGridX :		//for odd current grid row checking even row
//								currentGridX - 1:	//for odd current grid checking odd row (aka checking current row)
//						
//								currentGridX		//for even current grid checking and odd and even row (both row)			 	
//					;
//
//						 isOddRow ? 
//							isTargetEvenRow ?
//								targetGridX < currentGridX + 2 : //for odd current grid row checking even row
//								targetGridX < currentGridX + 3 : //for odd current grid row checking odd row (aka checking current row)
//
//							!isTargetEvenRow ?
//								targetGridX < currentGridX + 2 : //for even current grid row checking odd row
//								targetGridX < currentGridX + 3  //for even current grid row checking even row (aka checking current row)
//					;
//						isOddRow ?
//							isTargetEvenRow ?
//								targetGridX++ :		//for odd current grid row checking even row
//								targetGridX += 2 :	//for odd current grid row checking odd row (aka checking current row)
//
//							!isTargetEvenRow ?
//								targetGridX++ :		//for even current grid row checking odd row
//								targetGridX += 2	//for even current grid row checking even row (aka checking current row)			
//					)
//				{
//					//Check null
//					if (targetGridX < 0 ||
//						targetGridX > GRID_WIDTH - 1||
//						RegisteredBalls[targetGridY][targetGridX] == nullptr ||
//						RegisteredBalls[targetGridY][targetGridX] == this
//						) continue;
//
//					//Check color
//					Color targetColor = CheckColor(targetGridX, targetGridY);
//
//					//Register to destroy balls
//					if (targetColor == currentColor) ToDestroyBalls.push_back(*RegisteredBalls[targetGridY][targetGridX]);
//				}
//			}
//		}
//
//		//if there are destroyable same color
//		if (ToDestroyBalls.size() <= 0) return;
//
//		//destroy all registered balls
//		for (size_t i = 0; i < ToDestroyBalls.size(); i++)
//		{
//			ToDestroyBalls[i].Destroy();
//		}
//}

//void Ball::CheckNearbyColor()
//{
//	//info (read only)
//	int currentGridX = gridX;
//	int currentGridY = gridY;
//	Color currentColor = color;
//
//
//	//is placed ball grid Y is even
//	bool isOddRow = (currentGridY % 2 == 1);
//
//
//	vector<Ball>ToDestroyBalls;
//	//Check destroyable same color balls
//	{
//		for (int targetGridY = currentGridY - 1; targetGridY < currentGridY + 2; targetGridY++)
//		{
//			if (targetGridY < 0 || targetGridY > GRID_HEIGHT - 1) continue;
//
//			bool isTargetEvenRow = (targetGridY % 2 == 0);
//
//			// calculate start and max BEFORE the inner loop
//			int startX, maxGrid;
//
//			if (isOddRow)
//			{
//				if (isTargetEvenRow)
//				{
//					startX = currentGridX - 1; // odd current, checking even row
//					maxGrid = currentGridX + 1;
//				}
//				else
//				{
//					startX = currentGridX;     // odd current, checking odd row
//					maxGrid = currentGridX + 2;
//				}
//			}
//			else // isEvenRow
//			{
//				if (isTargetEvenRow)
//				{
//					startX = currentGridX;     // even current, checking even row
//					maxGrid = currentGridX + 2;
//				}
//				else
//				{
//					startX = currentGridX - 1; // even current, checking odd row
//					maxGrid = currentGridX + 1;
//				}
//			}
//
//			for (int targetGridX = startX; targetGridX < maxGrid; targetGridX++)
//			{
//				// bounds check
//				if (targetGridX < 0 ||
//					targetGridX > GRID_WIDTH - 1 ||
//					RegisteredBalls[targetGridY][targetGridX] == nullptr ||
//					RegisteredBalls[targetGridY][targetGridX] == this)
//					continue;
//
//				// color check
//				Color targetColor = CheckColor(targetGridX, targetGridY);
//				if (targetColor == currentColor)
//					ToDestroyBalls.push_back(*RegisteredBalls[targetGridY][targetGridX]);
//			}
//		}
//	}
//
//	//if there are destroyable same color
//	if (ToDestroyBalls.size() <= 0) return;
//
//	//destroy all registered balls
//	for (size_t i = 0; i < ToDestroyBalls.size(); i++)
//	{
//		ToDestroyBalls[i].Destroy();
//	}
//}

void Ball::CheckNearbyColor()
{
	int currentGridX = gridX;
	int currentGridY = gridY;
	Color currentColor = color;
	bool isOddRow = (currentGridY % 2 == 1);

	vector<Ball> ToDestroyBalls;

	for (int targetGridY = currentGridY - 1; targetGridY < currentGridY + 2; targetGridY++)
	{
		if (targetGridY < 0 || targetGridY > GRID_HEIGHT - 1) continue;

		bool isTargetSameRow = (targetGridY == currentGridY);

		int startX, maxGrid;

		if (isTargetSameRow)
		{
			startX = currentGridX - 1; // same row: x-1, x, x+1
			maxGrid = currentGridX + 2;
		}
		else if (isOddRow)
		{
			startX = currentGridX;     // odd current Å® even row: x and x+1
			maxGrid = currentGridX + 2;
		}
		else
		{
			startX = currentGridX - 1; // even current Å® odd row: x-1 and x
			maxGrid = currentGridX + 1;
		}

		for (int targetGridX = startX; targetGridX < maxGrid; targetGridX++)
		{
			if (targetGridX < 0 ||
				targetGridX > GRID_WIDTH - 1 ||
				RegisteredBalls[targetGridY][targetGridX] == nullptr ||
				RegisteredBalls[targetGridY][targetGridX] == this)
				continue;

			Color targetColor = CheckColor(targetGridX, targetGridY);
			if (targetColor == currentColor)
				ToDestroyBalls.push_back(*RegisteredBalls[targetGridY][targetGridX]);
		}
	}

	if (ToDestroyBalls.size() <= 0) return;

	for (size_t i = 0; i < ToDestroyBalls.size(); i++)
	{
		ToDestroyBalls[i].Destroy();
	}
}

void Ball::Destroy()
{
	//remove from RegisteredBalls grid
	RegisteredBalls[gridY][gridX] = nullptr;

	//delete this object from memory
	delete this;
}

//Check collision with borders and other balls
void Ball::CheckCollision()
{
	if (!this->canMove) return;
	float gridSize = RADIUS * 2;

	float topBorder = FrameBox::TOP_LEFT.y + RADIUS;
	float leftBorder = FrameBox::TOP_LEFT.x + RADIUS;
	float rightBorder = FrameBox::BOTTOM_RIGHT.x - RADIUS;

	// bounce off left and right borders
	if (position.x < leftBorder)
	{
		position.x = leftBorder; // push back in bounds
		Ricochet();
	}
	else if (position.x > rightBorder)
	{
		position.x = rightBorder; // push back in bounds
		Ricochet();
	}


	if (position.y < topBorder) //check if hit top
	{
		//Disable movement
		DisableMove();

		//Snap to grid
		position = SnapToGrid(position);

		//destroy all nearby same color
		CheckNearbyColor();
	}

	for (size_t i = 0; i < BallList.size(); i++)
	{
		if (&BallList[i] == this) continue; // skip itself

		//in contact with another ball
		if (CheckCircleHit(BallList[i].position, RADIUS, position, RADIUS))
		{
			//Disable movement
			DisableMove();

			//Check neighbour of the ball in contact and snap to grid based on angle
			position = SnapToGrid(BallList[i], *this);

			//destroy all nearby same color
			CheckNearbyColor();
	
		}
	}
	
}



//Render 
void Ball::Render()
{
	Image2 image;

	//position
	Float2 pos = position;

	switch (color)
	{
	case Color::RED:
		ImageManager::GetInstance().RedBall.RenderCenter(pos.x, pos.y);
		break;
	case Color::GREEN:
		ImageManager::GetInstance().GreenBall.RenderCenter(pos.x, pos.y);
		break;
	case Color::BLUE:
		ImageManager::GetInstance().BlueBall.RenderCenter(pos.x, pos.y);
		break;
	case Color::YELLOW:
		ImageManager::GetInstance().YellowBall.RenderCenter(pos.x, pos.y);
		break;
	}
	
	

	image.RenderCenter();
}



