#pragma once
#include "MenuButton.h"


class Menu
{
public:
	Menu(const sf::Vector2u& windowSize = { 1000,1000 });
	virtual void update(sf::RenderWindow & window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	
	virtual int isChoosen() const = 0;
	virtual int isOnButton(sf::RenderWindow & window) const = 0;
	virtual void choose(int x) = 0;
	virtual void unchoose() = 0;
	virtual int handleMenuEvents(sf::Event &e) = 0;

	virtual void setNames() = 0;
	virtual void getNames() {}

	virtual void syncOptionName() {}
	virtual size_t size() const;
	virtual ~Menu() = default;

protected:
	std::shared_ptr<SrcManager> m_src;
	std::vector <sf::Text> m_texts;
	std::vector<std::shared_ptr<MenuButton>> m_buttons;
	int m_choosen;
	sf::Texture m_texture;
	sf::RectangleShape m_bgRect;

};