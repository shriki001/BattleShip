#include "ImageMenuButton.h"


ImageMenuButton::ImageMenuButton(sf::Texture t, const sf::Vector2f& position)
	:m_texture(std::move(t))
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}

sf::FloatRect ImageMenuButton::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void ImageMenuButton::choose()
{
	m_sprite.setColor(sf::Color::Red);
}

void ImageMenuButton::unchoose()
{
	m_sprite.setColor(sf::Color::White);
}


void ImageMenuButton::render(sf::RenderWindow & window) const
{
	window.draw(m_sprite);
}