#include "ShipFactory.h"


std::unique_ptr<Ship> ShipFactory::create(const std::string& name, sf::Vector2i pos, bool toRotate)
{
	auto it = getMap().find(name);
	if (it == getMap().end())
		return nullptr;
	return it->second(pos, toRotate);
}

bool ShipFactory::registerit(const std::string & name, std::unique_ptr<Ship>(*f)(sf::Vector2i, bool))
{
	getMap().emplace(name, f);
	return true;
}

mymap & ShipFactory::getMap()
{
	static mymap m_map;
	return m_map;	
}
