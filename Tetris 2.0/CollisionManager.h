#include "cBlock.h"

class CollisionManager
{
	public:
		CollisionManager();
		~CollisionManager();

		bool CheckEntityCollisions(cSquare* square, Direction dir, vector<cSquare*> oldSquares);

		//Our other CheckEntityCollisions() function takes a pointer to a block. 
		//Because a block is made up of four squares, we can get an array of pointers to these squares and just call our previous function on them.
		bool CheckEntityCollisions(cBlock* block, Direction dir, vector<cSquare*> oldSquares);

		bool CheckWallCollisions(cSquare* square, Direction dir);
		bool CheckWallCollisions(cBlock* block, Direction dir);

		bool CheckRotationCollisions(cBlock* block, vector<cSquare*> oldSquares);
		void HandleBottomCollision();

	private:

};