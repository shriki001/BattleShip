#pragma once
#include "SrcManager.h"

class TextBox
{
public:
	TextBox(sf::Text msg, const sf::Vector2f &msgPos);
	void draw(sf::RenderWindow& windowToDraw);
	void setString(sf::Text tx);
	~TextBox() = default;

private:
	std::shared_ptr<SrcManager> m_src;
	sf::RectangleShape m_bg;
	sf::Text m_msg;
	sf::Vector2f m_position;
};