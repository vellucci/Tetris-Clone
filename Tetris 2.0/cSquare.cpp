#include "cSquare.h"

cSquare::cSquare()
{

}

// Main constructor takes location and type of block 
cSquare::cSquare(int x, int y, BlockType type) : m_CenterX(x), m_CenterY(y),
m_BlockType(type)
{
	m_Bitmap.loadFromFile("FallingBlocks.bmp");
	sprite.setTexture(m_Bitmap);
}

//draws and determines which type of block our square belongs to
void cSquare::Draw(sf::RenderWindow& window)
{

	sf::IntRect rect;
	
	// switch statement to determine the location of the square within our bitmap
	switch (m_BlockType)
	{
		case SQUARE_BLOCK:
		{
			sf::IntRect temp(RED_SQUARE_X, RED_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp; 
			break;
		}
		case T_BLOCK:
		{
			sf::IntRect temp(PURPLE_SQUARE_X, PURPLE_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
		case L_BLOCK:
		{
			sf::IntRect temp(GREY_SQUARE_X, GREY_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
		case BACKWARDS_L_BLOCK:
		{
			sf::IntRect temp(BLUE_SQUARE_X, BLUE_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
		case STRAIGHT_BLOCK:
		{
			sf::IntRect temp(GREEN_SQUARE_X, GREEN_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
		case S_BLOCK:
		{
			sf::IntRect temp(BLACK_SQUARE_X, BLACK_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
		case BACKWARDS_S_BLOCK:
		{
			sf::IntRect temp(YELLOW_SQUARE_X, YELLOW_SQUARE_Y, SQUARE_MEDIAN * 2,
				SQUARE_MEDIAN * 2);
			rect = temp;
			break;
		}
	}

	// Draw at square's current location. Remember that m_X and m_Y store the
	// center of the square.
	sf::IntRect destination(m_CenterX - SQUARE_MEDIAN, m_CenterY - SQUARE_MEDIAN,
		SQUARE_MEDIAN * 2, SQUARE_MEDIAN * 2);

	sprite.setPosition(m_CenterX - SQUARE_MEDIAN, m_CenterY - SQUARE_MEDIAN);
	sprite.setTextureRect(rect);
	sprite.setOrigin(SQUARE_MEDIAN, SQUARE_MEDIAN);
	window.draw(sprite);
}


// Remember, SQUARE_MEDIAN represents the distance from the square's center to 
// its sides. SQUARE_MEDIAN*2 gives us the width and height of our squares. 
void cSquare::Move(Direction dir)
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
}