#include "EndMenu.h"

EndMenu::EndMenu() : close(false), selectedItem(0), option(0)
{
	FontManager::Instance()->SetText(menuItems[0], "Play Again?", 100, 140, FONT_SIZE, sf::Color::Red, true);
	FontManager::Instance()->SetText(menuItems[1], "Quit", 100, 160, FONT_SIZE, sf::Color::White, true);
}

EndMenu::~EndMenu()
{

}

void EndMenu::DrawEndMenu(sf::RenderWindow& window, sf::Event& event)
{
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				close = true;
				return;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Down) //move down the menu options
				{
					MoveDown();
				}
				else if (event.key.code == sf::Keyboard::Up) //move up the menu options
				{
					MoveUp();
				}
				else if (event.key.code == sf::Keyboard::Return) // if enter is pressed
				{
					ChooseOption();
					return;
				}

			}
		}

		window.clear();
		for (int i = 0; i < MENU_ITEMS; i++)
			window.draw(menuItems[i]);
		window.display();
	}

}

void EndMenu::MoveUp()
{
	if (selectedItem > 0)
	{
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::White, false);
		selectedItem--;
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::Red, false);
	}
}

void EndMenu::MoveDown()
{
	if (selectedItem + 1 < MENU_ITEMS)
	{
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::White, false);
		selectedItem++;
		FontManager::Instance()->UpdateText(menuItems[selectedItem], NULL, sf::Color::Red, false);
	}
}

int EndMenu::ChooseOption()
{
	switch (selectedItem)
	{
		case 1:
		{
			option = 1;
		} break;

		case 2:
		{
			option = 2;
		} break; 
	}

	return option;
}