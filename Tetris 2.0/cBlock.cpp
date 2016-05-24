#include "cBlock.h"

cBlock::cBlock()
{
}

cBlock::cBlock(int x, int y, BlockType type) : m_CenterX(x), m_CenterY(y),
m_Type(type)
{
	// Set our square pointers to null            
	for (int i = 0; i<4; i++)
	{
		m_Squares[i] = NULL;
	}

	SetupSquares(x, y);
}

//SetupSquares() initializes the locations of the block's squares with respect to its center. 
//It takes the center point of the block so we can move it to somewhere else on the screen and reset its shape.
void cBlock::SetupSquares(int x, int y)
{
	// This function takes the center location of the block. We set our data 
	// members to these values to make sure our squares don't get defined 
	// around a new center without our block's center values changing too. 
	m_CenterX = x;
	m_CenterY = y;

	// Make sure that any current squares are deleted 
	for (int i = 0; i<4; i++)
	{
		if (m_Squares[i])
			delete m_Squares[i];
	}

	switch (m_Type)
	{
	case SQUARE_BLOCK:
	{
		// [0][2]                
		// [1][3] 
		m_Squares[0] = new cSquare(x - SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x - SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[3] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
	} break;
	case T_BLOCK:
	{
		//    [0]
		// [2][1][3] 
		m_Squares[0] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x - SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[3] = new cSquare(x + (SQUARE_MEDIAN * 3), y + SQUARE_MEDIAN,
			m_Type);
	} break;
	case L_BLOCK:
	{
		// [0]
		// [1]
		// [2][3] 
		m_Squares[0] = new cSquare(x - SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x - SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x - SQUARE_MEDIAN, y + (SQUARE_MEDIAN * 3),
			m_Type);
		m_Squares[3] = new cSquare(x + SQUARE_MEDIAN, y + (SQUARE_MEDIAN * 3),
			m_Type);
	} break;
	case BACKWARDS_L_BLOCK:
	{
		//    [0]
		//    [1]
		// [3][2]        
		m_Squares[0] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x + SQUARE_MEDIAN, y + (SQUARE_MEDIAN * 3),
			m_Type);
		m_Squares[3] = new cSquare(x - SQUARE_MEDIAN, y + (SQUARE_MEDIAN * 3),
			m_Type);
	} break;
	case STRAIGHT_BLOCK:
	{
		// [0]
		// [1]
		// [2]
		// [3] 
		m_Squares[0] = new cSquare(x + SQUARE_MEDIAN, y - (SQUARE_MEDIAN * 3),
			m_Type);
		m_Squares[1] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[3] = new cSquare(x + SQUARE_MEDIAN, y + (SQUARE_MEDIAN * 3),
			m_Type);
	} break;
	case S_BLOCK:
	{
		//    [1][0]
		// [3][2] 
		m_Squares[0] = new cSquare(x + (SQUARE_MEDIAN * 3), y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[3] = new cSquare(x - SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
	} break;
	case BACKWARDS_S_BLOCK:
	{
		// [0][1]
		//    [2][3]
		m_Squares[0] = new cSquare(x - SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[1] = new cSquare(x + SQUARE_MEDIAN, y - SQUARE_MEDIAN,
			m_Type);
		m_Squares[2] = new cSquare(x + SQUARE_MEDIAN, y + SQUARE_MEDIAN,
			m_Type);
		m_Squares[3] = new cSquare(x + (SQUARE_MEDIAN * 3), y + SQUARE_MEDIAN,
			m_Type);
	} break;
	}
}

void cBlock::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i<4; i++)
	{
		m_Squares[i]->Draw(window);
	}
}

// Move() simply changes the block's center and calls the squares' move functions.
void cBlock::Move(Direction dir)
{
	switch (dir)
	{
	case LEFT:
	{
		m_CenterX -= SQUARE_MEDIAN * 2;
	} break;
	case RIGHT:
	{
		m_CenterX += SQUARE_MEDIAN * 2;
	} break;
	case DOWN:
	{
		m_CenterY += SQUARE_MEDIAN * 2;
	} break;
	}

	for (int i = 0; i<4; i++)
	{
		m_Squares[i]->Move(dir);
	}
}

void cBlock::Rotate()
{
	// We need two sets of temporary variables so we don't incorrectly
	// alter one of them.If we set x to -y, then set y to x, we'd actually 
	// be setting y to -y because x is now -y 
	int x1, y1, x2, y2;

	for (int i = 0; i<4; i++)
	{

		// Get the center of the current square
		x1 = m_Squares[i]->GetCenterX();
		y1 = m_Squares[i]->GetCenterY();

		// Move the square so it's positioned at the origin 
		x1 -= m_CenterX;
		y1 -= m_CenterY;

		// Do the actual rotation
		x2 = -y1;
		y2 = x1;

		// Move the square back to its proper location 
		x2 += m_CenterX;
		y2 += m_CenterY;

		// Set the square's location to our temporary variables 
		m_Squares[i]->SetCenterX(x2);
		m_Squares[i]->SetCenterY(y2);
		
	}
}

// This function gets the locations of the squares after
// a rotation and returns an array of those values. 
int* cBlock::GetRotatedSquares()
{
	int* temp_array = new int[8];
	int x1, y1, x2, y2;

	for (int i = 0; i<4; i++)
	{
		x1 = m_Squares[i]->GetCenterX();
		y1 = m_Squares[i]->GetCenterY();

		x1 -= m_CenterX;
		y1 -= m_CenterY;

		x2 = -y1;
		y2 = x1;

		x2 += m_CenterX;
		y2 += m_CenterY;

		// Instead of setting the squares, we just store the values
		temp_array[i * 2] = x2;
		temp_array[i * 2 + 1] = y2;
	}

	return temp_array;
}




