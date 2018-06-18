#include "Ship.h"

Ship::Ship(sf::Vector2i pos, bool toRotate)
	:m_src(SrcManager::instance()),
	 m_pos(pos),
	 m_rotate(toRotate) 
{}


void Ship::setRotation(bool flag)
{
	m_rotate = flag;
}

bool Ship::isRotate() const
{
	return m_rotate;
}
