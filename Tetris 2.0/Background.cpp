#include "BackGround.h"

Background::Background()
{
	background.loadFromFile("FallingBlocks.bmp");
	sprite.setTexture(background);
}

Background::~Background()
{

}

void Background::DrawBackground(sf::RenderWindow& window, int g_Level)
{
	sf::IntRect rect;

	// Set our source rectangle to the current level's background 
	switch (g_Level)
	{
		case 1:
		{
			sf::IntRect temp = { LEVEL_ONE_X, LEVEL_ONE_Y, WINDOW_WIDTH,
				WINDOW_HEIGHT };
			rect = temp;
		} break;
		case 2:
		{
			sf::IntRect temp = { LEVEL_TWO_X, LEVEL_TWO_Y, WINDOW_WIDTH,
				WINDOW_HEIGHT };
			rect = temp;
		} break;
		case 3:
		{
			sf::IntRect temp = { LEVEL_THREE_X, LEVEL_THREE_Y, WINDOW_WIDTH,
				WINDOW_HEIGHT };
			rect = temp;
		} break;
		case 4:
		{
			sf::IntRect temp = { LEVEL_FOUR_X, LEVEL_FOUR_Y, WINDOW_WIDTH,
				WINDOW_HEIGHT };
			rect = temp;
		} break; 
		case 5:
		{
			sf::IntRect temp = { LEVEL_FIVE_X, LEVEL_FIVE_Y, WINDOW_WIDTH,
				WINDOW_HEIGHT };
			rect = temp;
		} break;
	}
	
	sprite.setPosition(0, 0);
	//sprite.setScale(WINDOW_WIDTH, WINDOW_HEIGHT);

	window.draw(sprite);
	
}