#include "Enums.h"
#include "Includes.h"

class Background
{
	public:
		Background();
		~Background(); 

		void DrawBackground(sf::RenderWindow& window, int g_Level);
	private:
		sf::Texture background;
		sf::Sprite sprite; 
};