#pragma once

#include "cSquare.h"

class cBlock
{
	public:
		cBlock();
		// The constructor just sets the block location and calls SetupSquares 
		cBlock(int x, int y, BlockType type);

		void SetupSquares(int x, int y);
		void Draw(sf::RenderWindow& window);
		void Move(Direction dir);
		void Rotate();
		int* GetRotatedSquares();

		// This returns a pointer to an array of pointers to the squares of the block. 
		cSquare** GetSquares()
		{
			return m_Squares;
		}

	private:
		// Location of the center of the block 
		int m_CenterX;
		int m_CenterY;

		// Type of block 
		BlockType m_Type;

		// Array of pointers to the squares that make up the block
		cSquare* m_Squares[4];
};