#include "BattleShip2.h"


bool BattleShip2::m_registerit =
ShipFactory::registerit("Ship2", [](sf::Vector2i pos, bool toRotate) ->
	std::unique_ptr<Ship> { return std::make_unique<BattleShip2>(pos, toRotate); });

BattleShip2::BattleShip2(const sf::Vector2i & pos, bool toRotate)
	:Ship(pos, toRotate)
{

}

void BattleShip2::draw(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite3d s1;

	if (m_rotate)
	{
		t1 = (*m_src->getShip(2));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 80.f, m_pos.y + 13.f);
		s1.setRotation({ 20.f,  30.f, -9.0f });
		s1.setScale({ 1.1f,0.72f });
	}
	else 
	{
		t1 = (*m_src->getShip(0));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 10.f, m_pos.y - 43.f);
		s1.setRotation({ 60.0f,  15.0f, 10.0f });
		s1.setRotation3d({ 10.0f, 10, 12 });
		s1.setScale({ 0.75f, 1.0f });
	}
	app.draw(s1);
}

void BattleShip2::draw2D(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite s1;

	if (m_rotate)
	{
		t1 = (*m_src->getShip(1));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x + 58.f, float(m_pos.y));
		s1.setRotation(90);
		s1.setScale(0.6f, 1.f);
	}
	else 
	{
		t1 = (*m_src->getShip(1));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x-9.f, float(m_pos.y));
		s1.setScale(0.65f, 1.0f);
	}
	app.draw(s1);
}