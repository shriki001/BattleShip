#pragma once
#include "SrcManager.h"
#include "Map.h"
#include "E_includes/AnimatedSprite.hpp"

class Player
{
public:
	Player(std::string name);
	
	virtual void playHit(sf::RenderWindow & window, sf::Vector2i pos, bool ans);
	virtual sf::Vector2i askHit(sf::RenderWindow& window, sf::Event& event) = 0;
	virtual sf::Vector2i getPlace(const sf::Vector2i &src);
	virtual void setPlayerSign(sf::Vector2i pos, bool ans);
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual short getPlayerSign(int x, int y) const;
	virtual bool inRange(const sf::Vector2f &my);
	virtual sf::Vector2i getPlace(int x, int y);
	virtual char getSign(int i, int j) const;
	void display(sf::RenderWindow & window);
	virtual void hit(sf::Vector2i, bool);
	virtual void setName(const std::string&);
	virtual std::string getName()const;
	virtual bool getHit(sf::Vector2i);
	virtual void init();
	virtual void debug(int num);
	virtual void resetAll();
	virtual void setMap(std::shared_ptr<Map> map) { m_myMaps = map; }
	
	virtual ~Player() = default;

protected:
	std::shared_ptr<SrcManager> m_src;
	std::shared_ptr<Map> m_myMaps;
	

	std::vector<std::vector<short>> m_sign;
	std::vector<std::vector<short>> m_PlayerSign;
	std::array<std::vector<std::vector<sf::Sprite3d>>,2> m_myHitMaps;
	std::array<std::array<std::array <sf::Vector2i, M_ROW>, M_COL>,2> map_places;
	
	std::string m_name;
	sf::Texture m_frontTexture, m_backTexture, t1, t2;
};