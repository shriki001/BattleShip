#include "BattleShip4.h"


bool BattleShip4::m_registerit =
ShipFactory::registerit("Ship4", [](sf::Vector2i pos, bool toRotate) ->
	std::unique_ptr<Ship> { return std::make_unique<BattleShip4>(pos, toRotate); });

BattleShip4::BattleShip4(const sf::Vector2i & pos, bool toRotate)
	:Ship(pos, toRotate)
{

}

void BattleShip4::draw(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite3d s1;
	
	if (m_rotate)
	{
		t1 = (*m_src->getShip(5));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x-95.f, m_pos.y + 10.f);
		s1.setRotation({ 2.f,  20.f, -9.0f });
		s1.setScale({ 1.05f,1.15f });
	}
	else 
	{
		t1 = (*m_src->getShip(3));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 10.f, m_pos.y - 50.f);
		s1.setRotation({ 60.0f,  15.0f, 10.0f });
		s1.setRotation3d({ 10.0f, 10, 12 });
//		s1.scale({ 0.5f,0.5f });
	}
	app.draw(s1);
}

void BattleShip4::draw2D(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite s1;
	t1 = (*m_src->getShip(4));
	s1.setTexture(std::move(t1));
	s1.scale(0.75f, 1.f);

	if (m_rotate)
	{
		s1.setPosition(m_pos.x + 67.f, m_pos.y - 5.f);
		s1.setRotation(90);
	}
	else 
	{
		t1 = (*m_src->getShip(4));
		s1.setTexture(std::move(t1));
		s1.setPosition(float(m_pos.x), m_pos.y - 7.f);
	}
	app.draw(s1);
}