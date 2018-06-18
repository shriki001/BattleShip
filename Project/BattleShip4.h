#pragma once
#include "ShipFactory.h"
class BattleShip4 : public Ship
{
public:
	BattleShip4(const sf::Vector2i &pos, bool toRotate = false);
	void draw(sf::RenderWindow &app);
	void draw2D(sf::RenderWindow & app);
private:

	static bool m_registerit;
};

