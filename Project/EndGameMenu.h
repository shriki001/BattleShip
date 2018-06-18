#pragma once
#include "Menu.h"
#include "TextMenuButton.h"

class EndGameMenu : public Menu
{
public:
	EndGameMenu(const sf::Vector2u& windowSize = { 1000,1000 });

	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);
	int isChoosen() const override;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x) override;
	void unchoose() override;
	int handleMenuEvents(sf::Event & e);
	void setNames() override;
	void setMode(int mode);

private:
	static sf::Texture bg;
	int m_mode;			// win or lost
};