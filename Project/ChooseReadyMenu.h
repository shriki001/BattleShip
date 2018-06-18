#pragma once
#include "Menu.h"

class ChooseReadyMenu : public Menu
{
public:
	ChooseReadyMenu(const sf::Vector2u& windowSize = { 1000,1000 });

	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);

	int isChoosen() const override;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x) override;
	void unchoose() override;

	int handleMenuEvents(sf::Event &e);
	void setNames() override;
	size_t size() const;
	int getMap() const;

private:
	static sf::Texture bg;
	int m_currPreview;
	sf::Texture m_currTexture;
	sf::Sprite m_currSprite;

};