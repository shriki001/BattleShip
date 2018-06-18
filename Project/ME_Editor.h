#pragma once
#include "ME_Menu.h"
#include "Map.h"


class Editor
{

public:
	Editor();	
	
	virtual void ShowButton(const sf::Vector2f &currPos, sf::RenderWindow & app, const bool) = 0;
	virtual void PlayButton(const sf::Vector2f &currPos, const bool dir);
	virtual void ShowButtonInfo(const sf::Vector2f &currPos);
	virtual sf::Vector2i getPlace(const sf::Vector2f &src);
	void drawE(sf::RenderWindow &_window);
	bool allGood(sf::Vector2f curr_pos);
	void update(sf::Text &, int, int);
	sf::Text createText(int size);
	virtual bool reset();
	virtual std::shared_ptr<Map> getMap() { return m_settings; }
	virtual ~Editor() = default;

protected:
	std::shared_ptr<EditorMenu> m_Bmenu;
	std::shared_ptr<SrcManager> m_src;
	std::shared_ptr<Map> m_settings;
	Button m_ok;
	
	enum ActionType_t m_CurrState;
	bool m_rot;
	int m_leftSmall;
	int m_leftMiddle;
	int m_leftBig;
};