#pragma once
#include "Player.h"


class AiRival :public Player
{
public:
	AiRival(std::string name, std::shared_ptr<Map> map);
	void draw(sf::RenderWindow & window);
	sf::Vector2i askHit(sf::RenderWindow& window, sf::Event& event);
	sf::Vector2i playMedium();
	sf::Vector2i playHard();

	void addLostTime(sf::Time toAdd);

private:
	std::shared_ptr<Map> m_PlayerMap;
	sf::Clock m_clock;
};