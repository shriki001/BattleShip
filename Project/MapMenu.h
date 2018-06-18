#pragma once
#include "Menu.h"

class MapMenu : public Menu
{
public:
	MapMenu(const sf::Vector2u& windowSize = { 1000,1000 });

	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);

	int isChoosen() const override;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x) override;
	void unchoose() override;

	int handleMenuEvents(sf::Event &e);
	void setNames() override;

	size_t size() const;

private:
	static sf::Texture bg;
};

