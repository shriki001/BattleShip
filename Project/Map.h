#pragma once
#include "E_includes/Sprite3d.hpp"
#include "SrcManager.h"
#include "BattleShip2.h"
#include "BattleShip4.h"
#include "BattleShip6.h"
#include <array>


class Map
{
public:
	Map(); 
	
	bool canPut(const sf::Vector2i &_place, const bool dir, const int size) const;
	void draw(const sf::Vector2i &_place, const bool dir, const int size);
	void remove(const sf::Vector2i &_place, const bool dir, const int size);
	void setType(int i, int j, std::pair<bool, int> newType);
	void display(sf::RenderWindow & _window) ;
	sf::Vector2i getPlace(int x, int y) const;
	void setSize(int i, int j, int newSize);
	void setSign(int i, int j, int newSign);
	bool inRange(const sf::Vector2f &my);
	char getSign(int x, int y) const;
	int getSize(int x, int y) const;
	void cleanMap();
	bool allOK();

	void resetAllSizes();
	void updateMiddleLeft(int x);
	void updateSmallLeft(int x);
	void updateBigLeft(int x);
	int getMiddleLeft() const;
	int getSmallLeft() const;
	int getBigLeft() const;
	
	~Map() = default;

private:
	class Info
	{
	public:
		char m_sign = '-';
		bool m_start = false;
		std::pair<bool, int> m_type = { false , 0 };
		int m_size = 0;
	};

protected:
	std::shared_ptr<SrcManager> m_src;
	std::array<std::vector<std::vector <sf::Sprite3d>>,2> textureMap;
	std::array<std::array<Info, M_ROW>, M_COL> map2;
	std::array<std::array<std::array<sf::Vector2i, M_ROW>, M_COL>,2> map_places;
	sf::Texture m_frontTexture, m_backTexture;
	int m_leftMiddle;
	int m_leftSmall;
	int m_leftBig;
};