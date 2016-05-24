#include "FontManager.h"

FontManager* FontManager::instance = NULL;

FontManager::FontManager()
{

}

void FontManager::LoadText()
{
	font.loadFromFile("DFHeiE.ttc");
}

// This function displays text to the screen. It takes the text //
// to be displayed, the location to display it, the size of the //
// text, and the color of the text
void FontManager::SetText(sf::Text& txt, string text, int x, int y, int size, sf::Color color, bool setOrigin)
{
	txt.setFont(font);
	txt.setString(text);
	txt.setPosition(x, y);
	txt.setCharacterSize(size); 
	txt.setColor(color);

	//if (setOrigin)
		//txt.setOrigin(txt.getGlobalBounds().width / 2.0f, txt.getLocalBounds().height / 2.0f);
}

//will update the string of the text if needed and color and will keep the text centered if specified
void FontManager::UpdateText(sf::Text& text, const char* txt, sf::Color color, bool setOrigin)
{
	if (txt != NULL)
		text.setString(txt);

	if (setOrigin)
		text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);

	text.setColor(color);
}
