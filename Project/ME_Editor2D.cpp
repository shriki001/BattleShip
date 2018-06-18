#pragma once
#include "ME_Editor2D.h"
#include "Map.h"


void Editor2D::ShowButton(const sf::Vector2f &currPos, sf::RenderWindow & app, const bool dir)
{
	int size = 0;
	switch (m_CurrState)
	{
	case 0: size = 6; break;
	case 1: size = 4; break;
	case 2: size = 2; break;
	}
	sf::Sprite3d s1;
	sf::Texture t1;

	std::shared_ptr<Ship> shipObj;

	Button* b = m_Bmenu->isHoveredOnButton(currPos);
	if (b)
		b->toShow(false);

	if (m_settings->inRange(currPos))
	{
		sf::Vector2i z = getPlace(currPos);
		s1.setPosition((sf::Vector2f) m_settings->getPlace(z.x, z.y));
		if (m_CurrState >= 0 && m_CurrState <= 2)
		{
			if (m_settings->canPut(z, dir, size) &&
				((size == 2 && m_settings->getSmallLeft() > 0) ||
				(size == 4 && m_settings->getMiddleLeft() > 0) ||
					(size == 6 && m_settings->getBigLeft() > 0)))
				s1.setColor(sf::Color(0, 255, 0, 180));
			else
				s1.setColor(sf::Color(255, 0, 0, 180));

			if (dir)			//ROTATED
			{
				if (m_CurrState == DRAW_6_A)
				{
					t1 = (*m_src->getShip(7));
					s1.setTexture(std::move(t1));
					s1.setRotation(90);
					s1.setScale(1.35f, 1.05f);
					s1.setPosition(s1.getPosition().x + 67, s1.getPosition().y - 13);
				}
				else if (m_CurrState == DRAW_4_A)
				{
					t1 = (*m_src->getShip(4));
					s1.setTexture(std::move(t1));
					s1.setRotation(90);
					s1.setPosition(s1.getPosition().x + 67, s1.getPosition().y - 5);
					s1.setScale({ 0.75f,1.0f });
				}
				else if (m_CurrState == DRAW_2_A)
				{
					t1 = (*m_src->getShip(1));
					s1.setTexture(std::move(t1));
					s1.setRotation(90);
					s1.setPosition(s1.getPosition().x + 58, s1.getPosition().y);
					s1.setScale(0.6f, 1.f);
				}
			}
			else
			{
				if (m_CurrState == DRAW_6_A)
				{
					t1 = (*m_src->getShip(7));
					s1.setTexture(std::move(t1));
					s1.setPosition(s1.getPosition().x - 12, s1.getPosition().y - 13);
					s1.setScale(1.35f, 1.05f);
				}
				else if (m_CurrState == DRAW_4_A)
				{
					t1 = (*m_src->getShip(4));
					s1.setTexture(std::move(t1));
					s1.setScale({ 0.75f,1.0f });
					s1.setPosition(s1.getPosition().x, s1.getPosition().y - 7);
				}
				else if (m_CurrState == DRAW_2_A)
				{
					t1 = (*m_src->getShip(1));
					s1.setTexture(std::move(t1));
					s1.setPosition(s1.getPosition().x - 9, s1.getPosition().y);
					s1.setScale(0.65f, 1.0f);
				}
			}
		}
		else if (m_CurrState == ERASE_MODE_A) // case 5
		{
			sf::Texture frontTexture, backTexture;
			frontTexture = *m_src->getButtons(1);
			backTexture = *m_src->getButtons(1);
			sf::Sprite3d s(std::move(frontTexture), std::move(backTexture));
			s.setPosition(s1.getPosition().x - 17, s1.getPosition().y - 54);
			s.scale({ 0.2f,0.2f });
			app.draw(s);
		}
	}
	app.draw(s1);
}