#include "BattleShip6.h"


bool BattleShip6::m_registerit =
ShipFactory::registerit("Ship6", [](sf::Vector2i pos, bool toRotate) ->
	std::unique_ptr<Ship> { return std::make_unique<BattleShip6>(pos, toRotate); });

BattleShip6::BattleShip6(const sf::Vector2i & pos, bool toRotate)
	:Ship(pos, toRotate)
{

}

void BattleShip6::draw(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite3d s1;

	if (m_rotate)
	{
		t1 = (*m_src->getShip(8));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 150.f, m_pos.y + 27.f);
		s1.setRotation({ 0.f,  10.0f, -9.0f });
		s1.setScale({ 1.05f,1.5f });
	}
	else 
	{
		t1 = (*m_src->getShip(6));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 10.f, m_pos.y - 50.f);
		s1.setRotation({ 60.0f,  15.0f, 10.0f });
		s1.setRotation3d({ 10.0f, 10, 11 });
		s1.setScale({ 1.6f, 1.f });
	}
	app.draw(s1);

}

void BattleShip6::draw2D(sf::RenderWindow & app)
{
	sf::Texture t1;
	sf::Sprite s1;

	if (m_rotate)
	{
		t1 = (*m_src->getShip(7));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x + 67.f, m_pos.y - 13.f);
		s1.setRotation(90);
		s1.setScale(1.35f, 1.05f);
	}
	else 
	{
		t1 = (*m_src->getShip(7));
		s1.setTexture(std::move(t1));
		s1.setPosition(m_pos.x - 12.f, m_pos.y- 13.f);
		s1.setScale(1.35f, 1.05f);
	}
	app.draw(s1);
}