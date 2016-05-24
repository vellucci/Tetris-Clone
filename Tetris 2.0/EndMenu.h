#include "Includes.h"
#include "FontManager.h"
#include "Defines.h"
#define FONT_SIZE 12
#define MENU_ITEMS 2

class EndMenu
{
	public:
		EndMenu();
		~EndMenu();

		void DrawEndMenu(sf::RenderWindow& window, sf::Event& event);
		//functions to switch menu options
		void MoveUp();
		void MoveDown();

		int ChooseOption();

		void HandleWinLoseInput(sf::RenderWindow& window);

		bool close;

	private:
		sf::Text menuItems[MENU_ITEMS];
		string winLose; 
		int selectedItem;
		int option;

		
};