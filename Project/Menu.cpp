#include "Menu.h"



Menu::Menu(const sf::Vector2u & windowSize)
	:m_src(SrcManager::instance()),
	m_choosen(-1),
	m_bgRect({ (float)windowSize.x, (float)windowSize.y })
{
}

size_t Menu::size() const
{
	return 0;
}
