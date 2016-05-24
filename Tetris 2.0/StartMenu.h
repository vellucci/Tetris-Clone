#pragma once
#ifndef StartMenu_H
#define StartMenu_H

#include "Includes.h"
#include "FontManager.h"
#define MENU_ITEMS 2
#define FONT_SIZE 12

class StartMenu
{
	public:
		StartMenu();
		~StartMenu();

		void DrawMenu(sf::RenderWindow& window, sf::Event& currEvent);
		//functions to switch menu options
		void MoveUp();
		void MoveDown();
		int ChooseOption();

		bool close; 
	private:
		
		int selectedItem; //keep track of the selected item in the menu
		int option;  
		sf::Text menuItems[MENU_ITEMS];

		sf::Texture background;
		sf::Sprite sprite; 
};

#endif