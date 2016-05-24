#pragma once

#include "Enums.h"
#include "Includes.h"

class cSquare
{
	public:
		cSquare(); 
		cSquare(int x, int y, BlockType type);

		void Draw(sf::RenderWindow& window);
		void Move(Direction dir);

		// Accessors 
		int GetCenterX() { return m_CenterX; }
		int GetCenterY() { return m_CenterY; }

		// Mutators
		void SetCenterX(int x) { m_CenterX = x; }
		void SetCenterY(int y) { m_CenterY = y; }
		sf::Sprite sprite;
	private:
		// Location of the center of the square 
		int m_CenterX;
		int m_CenterY;

		// Type of block. Needed to locate the correct square in our bitmap 
		BlockType m_BlockType;

		// A pointer to our bitmap surface from "Main.cpp" 
		sf::Texture m_Bitmap; 
	

};