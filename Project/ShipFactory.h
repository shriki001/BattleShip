#pragma once
#include <algorithm>
#include <map>
#include "Ship.h"


using mymap = std::map<std::string, std::unique_ptr<Ship>(*)(sf::Vector2i, bool)>;

class ShipFactory 
{
public:
	static std::unique_ptr<Ship> create(const std::string& name, sf::Vector2i, bool);
	static bool registerit(const std::string& name, std::unique_ptr<Ship>(*)(sf::Vector2i, bool));

private:
	static mymap& getMap();
};