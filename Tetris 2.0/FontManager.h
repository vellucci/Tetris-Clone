#pragma once
#ifndef FontManager_H
#define FontManager_H
#include "Includes.h"

class FontManager
{
	public:

		static FontManager* Instance()
		{
			if (instance == 0)
			{
				instance = new FontManager();
				return instance;
			}
			return instance;
		}

		FontManager();

		void LoadText();
		void SetText(sf::Text& txt, string text, int x, int y, int size, sf::Color color, bool setOrigin);
		void UpdateText(sf::Text& text, const char* cstr, sf::Color color, bool setOrigin);

	private:
		static FontManager* instance;
		sf::Font font; 
		
};

typedef FontManager FontManager;

#endif