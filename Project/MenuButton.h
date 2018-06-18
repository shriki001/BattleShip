#pragma once
#include "SrcManager.h"


class MenuButton
{
public:
	MenuButton() :m_src(SrcManager::instance()){}

	virtual void render(sf::RenderWindow& window) const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual void choose() = 0;
	virtual void unchoose() = 0;
	virtual void setName(const sf::Text& newText, int offsetOption = 0) = 0;
	virtual void scale(float x = 1.f, float y = 1.f) {};
	
	virtual ~MenuButton() = default;

protected:
	std::shared_ptr<SrcManager> m_src;
};