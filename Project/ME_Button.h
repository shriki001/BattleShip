#pragma once
#include "TextBox.h"

class Button
{
public:
	Button(sf::Vector2f pos = { 0,0 }, int stat = 1,
		   sf::Vector2f buttonSize = { 45,45 },
		const sf::Texture& toDraw = {}, sf::Text s = {});
	void draw(sf::RenderWindow &_window, bool flag, sf::Text tx);
	void setPosition(float x, float y);
	sf::Vector2f getPos() const;
	int getColor() const;
	void setState(int x);
	int getState() const;
	sf::Vector2f getSize() const;
	std::shared_ptr<TextBox> getText();
	void toShow(bool flag);
	void selected(bool flag);
	void setString(sf::Text tx);
	
	bool isClickedOnButton(const sf::Vector2f &_pos) const;
	bool inRange(const sf::Vector2f &my, const sf::Vector2f &p1, const sf::Vector2f &p2) const;
	~Button() = default;

	sf::FloatRect GetBoundingRect() const;
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Texture m_body;
	std::shared_ptr<SrcManager> m_src;
	std::shared_ptr<TextBox> m_purposeText;
	bool m_showInfo;
	bool m_selected;
	int cl;
	int state;

	
	
};