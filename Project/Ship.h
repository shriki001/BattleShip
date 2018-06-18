#pragma once
#include "SrcManager.h"
#include "E_includes/Sprite3d.hpp"
class Ship
{
public:
	Ship(sf::Vector2i pos, bool toRotate = false);
	virtual void draw(sf::RenderWindow &) = 0;
	virtual void draw2D(sf::RenderWindow &) {}
	virtual void setRotation(bool flag);
	virtual bool isRotate() const;
	virtual ~Ship() = default;

protected:
	std::shared_ptr<SrcManager> m_src;
	sf::Color m_color;
	sf::Vector2i m_pos;
	bool m_rotate;
};

