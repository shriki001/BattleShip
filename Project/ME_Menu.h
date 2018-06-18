#pragma once
#include "ME_Button.h"

class EditorMenu
{
public:
	EditorMenu();
	void draw(sf::RenderWindow&);
	Button* getclickedButton(const sf::Vector2f &currPos);
	Button* isHoveredOnButton(const sf::Vector2f &currPos) ;
	bool inRange(const sf::Vector2f &my, const sf::Vector2f &p1, const sf::Vector2f &p2) const;
	Button operator[](int index) const;
	~EditorMenu() = default;
	
private:
	std::shared_ptr<SrcManager> m_src;
	std::vector<Button> m_buttons;
	Button m_currColor;
	Button m_currAct;
};