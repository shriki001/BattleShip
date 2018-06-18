#pragma once
#include "SrcManager.h"
#include "Player.h"

class SinglePlayer : public Player
{
public:
	SinglePlayer(std::string name);
 	sf::Vector2i askHit(sf::RenderWindow& window, sf::Event& event);
	void draw(sf::RenderWindow & window);
	std::shared_ptr<Map> getMap() {return m_myMaps;}

};