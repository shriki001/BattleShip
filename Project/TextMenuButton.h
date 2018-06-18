#pragma once
#include "MenuButton.h"

class TextMenuButton : public MenuButton
{
public:
	TextMenuButton(sf::Text name = {} , const sf::Vector2f& position = { 0.f,0.f });
	
	void render(sf::RenderWindow& window) const;

	sf::FloatRect getGlobalBounds() const;

	void choose();
	void unchoose();

	void setName(const sf::Text& newText, int offsetOption = 0);
	std::wstring getName() { return m_text.getString();  }

private:
	static sf::Font m_font;
	sf::Text m_text;
};


