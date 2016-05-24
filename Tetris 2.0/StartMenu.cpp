#include "StartMenu.h"

StartMenu::StartMenu() : selectedItem(0), option(0), close(false)
{
	FontManager::Instance()->SetText(menuItems[0], "Start Game", 120, 220, FONT_SIZE, sf::Color::Red, true);
	FontManager::Instance()->SetText(menuItems[1], "Quit Game", 120, 250, FONT_SIZE, sf::Color::White, true);

	background.loadFromFile("background.jpg");
	sprite.setTexture(background);
}

StartMenu::~StartMenu()
{
	
}

void StartMenu::DrawMenu(sf::RenderWindow& window, sf::Event& currEvent)
{
	while (true)
	{
		while (window.pollEvent(currEvent))
		{
			if (currEvent.type == sf::Event::Closed)
			{
				window.close();
				close = true; 
				return;
			}
			else if (currEvent.type == sf::Event::KeyPressed)
			{
				if (currEvent.key.code == sf::Keyboard::Down) //move down the menu options
				{
					MoveDown();
				}
				else if (currEvent.key.code == sf::Keyboard::Up) //move up the menu options
				{
					MoveUp();
				}
				else if (currEvent.key.code == sf::Keyboard::Return) // if enter is pressed
				{
					ChooseOption();
					return;
				}

			}
		}

		window.clear();
		window.draw(sprite); 
		for (int i = 0; i < MENU_ITEMS; i++)
			window.draw(menuItems[i]);
		window.display();
	}
}

void StartMenu::MoveUp()
{
	if (selectedItem > 0)
	{
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::White, false);
		selectedItem--;
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::Red, false);
	}
}

void StartMenu::MoveDown()
{
	if (selectedItem + 1 < MENU_ITEMS)
	{
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::White, false);
		selectedItem++;
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::Red, false);
	}
}

int StartMenu::ChooseOption()
{
	switch (selectedItem)
	{
	case 0: //user clicks on play 
		option = 1;
		break;
	case 1: //user clicks on quit
		option = 2;
		break;
	}

	return option;
}