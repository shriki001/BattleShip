#pragma once
#include "MenuButton.h"

class ImageMenuButton : public MenuButton
{
public:
	ImageMenuButton(sf::Texture t = {}, const sf::Vector2f& position = { 0.f,0.f });

	void render(sf::RenderWindow& window) const;

	sf::FloatRect getGlobalBounds() const;
	void setName(const sf::Text& newText, int offsetOption) {}
	void choose();
	void unchoose();

	void scale(float x = 1.f, float y = 1.f)
	{
		m_sprite.scale(x, y);
	}

private:
	/*static*/ sf::Texture m_texture;
	sf::Sprite m_sprite;
};

