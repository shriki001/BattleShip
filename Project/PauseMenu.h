#pragma once
#include "Menu.h"


class PauseMenu : public Menu
{
public:
	PauseMenu(const sf::Vector2u& windowSize = { 1000,1000 });

	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);
	int isChoosen() const override;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x) override;
	void unchoose() override;
	int handleMenuEvents(sf::Event & e);
	void setNames() override;

	void syncOptionName();
private:
	static sf::Texture bg;
};