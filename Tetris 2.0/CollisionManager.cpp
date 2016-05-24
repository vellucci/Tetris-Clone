#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

// Check collisions between a given square and the squares in g_OldSquares
bool CollisionManager::CheckEntityCollisions(cSquare* square, Direction dir, vector<cSquare*> oldSquares)
{
	// Width/height of a square. Also the distance 
	// between two squares if they've collided. 
	int distance = SQUARE_MEDIAN * 2;

	// Center of the given square 
	int centerX = square->GetCenterX();
	int centerY = square->GetCenterY();

	// Determine the location of the square after moving
	switch (dir)
	{
		case DOWN:
		{
			centerY += distance;
		} break;
	
		case LEFT:
		{
			centerX -= distance;
		} break;

		case RIGHT:
		{
			centerX += distance;
		} break;
	}

	// Iterate through the old squares vector, checking for collisions
	for (int i = 0; i< oldSquares.size(); i++)
	{
		if ((abs(centerX - oldSquares[i]->GetCenterX()) < distance) &&
			(abs(centerY - oldSquares[i]->GetCenterY()) < distance))
		{
			return true;
		}
	}

	return false;
}

//Our other CheckEntityCollisions() function takes a pointer to a block. 
//Because a block is made up of four squares, we can get an array of pointers to these squares and just call our previous function on them.
bool CollisionManager::CheckEntityCollisions(cBlock* block, Direction dir, vector<cSquare*> oldSquares)
{
	// Get an array of the squares that make up the given block 
	cSquare** temp_array = block->GetSquares();

	// Now just call the other CheckEntityCollisions() on each square 
	for (int i = 0; i<4; i++)
	{
		if (CheckEntityCollisions(temp_array[i], dir, oldSquares))
			return true;
	}

	return false;
}

// Check collisions between a given square and the sides of the game area 
bool CollisionManager::CheckWallCollisions(cSquare* square, Direction dir)
{
	// Get the center of the square
	int x = square->GetCenterX();
	int y = square->GetCenterY();

	// Get the location of the square after moving and see if its out of bounds 
	switch (dir)
	{
	case DOWN:
	{
		if ((y + (SQUARE_MEDIAN * 2)) > GAME_AREA_BOTTOM)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;

	case LEFT:
	{

		if ((x - (SQUARE_MEDIAN * 2)) < GAME_AREA_LEFT)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;

	case RIGHT:
	{
		if ((x + (SQUARE_MEDIAN * 2)) > GAME_AREA_RIGHT)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;
	}
}

// Check for collisions between a given block a the sides of the game area 
bool CollisionManager::CheckWallCollisions(cBlock* block, Direction dir)
{
	// Get an array of squares that make up the given block
	cSquare** temp_array = block->GetSquares();

	// Call other CheckWallCollisions() on each square 
	for (int i = 0; i<4; i++)
	{
		if (CheckWallCollisions(temp_array[i], dir))
			return true;
	}

	return false;
}

bool CollisionManager::CheckRotationCollisions(cBlock* block, vector<cSquare*> oldSquares)
{
	// Get an array of values for the locations of the rotated block's squares
	int* temp_array = block->GetRotatedSquares();

	// Distance between two touching squares 
	int distance = SQUARE_MEDIAN * 2;

	for (int i = 0; i<4; i++)
	{
		// Check to see if the block will go out of bounds 
		if ((temp_array[i * 2] < GAME_AREA_LEFT) ||
			(temp_array[i * 2] > GAME_AREA_RIGHT))
		{
			delete temp_array;
			return true;
		}

		if (temp_array[i * 2 + 1] > GAME_AREA_BOTTOM)
		{
			delete temp_array;
			return true;
		}

		// Check to see if the block will collide with any squares 
		for (int index = 0; index< oldSquares.size(); index++)
		{
			if ((abs(temp_array[i * 2] - oldSquares[index]->GetCenterX()) < distance) &&
				(abs(temp_array[i * 2 + 1] - oldSquares[index]->GetCenterY()) < distance))
			{
				delete temp_array;
				return true;
			}
		}
	}

	delete temp_array;
	return false;
}

void CollisionManager::HandleBottomCollision()
{

}
