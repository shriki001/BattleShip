#include "TextMenuButton.h"

sf::Font TextMenuButton::m_font = *(SrcManager::instance()->getFont(EN_L)); 

TextMenuButton::TextMenuButton(sf::Text name, const sf::Vector2f& position)
	:m_text(std::move(name))
		
{
	m_text.setPosition(position);
	m_text.setOutlineThickness(5);
	m_text.setCharacterSize(70);
	m_text.setOutlineColor(sf::Color::Black);
}

sf::FloatRect TextMenuButton::getGlobalBounds() const
{
	return m_text.getGlobalBounds();
}

void TextMenuButton::choose()
{
	m_text.setFillColor(sf::Color::Red);
}

void TextMenuButton::unchoose()
{
	m_text.setFillColor(sf::Color::White);
}

void TextMenuButton::setName(const sf::Text& newText, int offsetOption)
{
	m_text.setString(newText.getString());
	m_text.setFont(*newText.getFont());
}


void TextMenuButton::render(sf::RenderWindow & window) const
{
	window.draw(m_text);
}