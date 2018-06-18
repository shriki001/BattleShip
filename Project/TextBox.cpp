
#include "TextBox.h"

TextBox::TextBox(sf::Text msg, const sf::Vector2f &msgPos)
	:m_msg(msg) , m_src(SrcManager::instance())
{
	sf::Text copy = std::move(m_msg);
 	float h = copy.getLocalBounds().height;
 	float w = copy.getLocalBounds().width;
	m_bg.setSize(sf::Vector2f(w + 2, h * 2));
	m_msg.setPosition(msgPos + sf::Vector2f(20, 0));
	m_bg.setFillColor(sf::Color(0, 0, 0, 155));
	m_bg.setPosition(msgPos + sf::Vector2f(20, 0));
}

void TextBox::draw(sf::RenderWindow & windowToDraw)
{
	windowToDraw.draw(m_bg);
	windowToDraw.draw(m_msg);
}

void TextBox::setString(sf::Text tx)
{
	m_msg.setString(std::move(tx.getString()));
	m_msg.setFont(std::move(*tx.getFont()));
}