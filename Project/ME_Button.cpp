
#include "ME_Button.h"

Button::Button(sf::Vector2f pos, int stat, sf::Vector2f buttonSize, const sf::Texture& toDraw, sf::Text s)
	:m_pos(pos), cl(1), state(stat), m_size(buttonSize), m_showInfo(false), m_body(toDraw)
{
	m_purposeText = std::make_shared<TextBox>(s, sf::Vector2f(pos.x + 10, pos.y));

	
	
}

void Button::draw(sf::RenderWindow &_window, bool flag, sf::Text tx)
{
	sf::RectangleShape body(m_size);
	body.setTexture(/*std::move*/(&m_body));
	body.setPosition(m_pos);

	if (m_showInfo)
		body.scale(1.4f, 1.4f);
	else if (!m_selected && !flag)
		body.setFillColor(sf::Color(0, 0, 0, 255));
	_window.draw(body);

	if (m_showInfo)
	{
		m_purposeText->setString(std::move(tx));
		m_purposeText->draw(_window);
	}
}

void Button::setPosition(float x, float y)
{
	m_pos = sf::Vector2f(x, y);
}

sf::Vector2f Button::getPos() const
{
	if (!this)
		return { 0.f,0.f };
	return m_pos;
}

int Button::getColor() const
{
	return cl;
}

sf::Vector2f Button::getSize() const
{
	return m_size;
}

std::shared_ptr<TextBox> Button::getText()
{
	return m_purposeText;
}

void Button::toShow(bool flag)
{
	m_showInfo = flag;
}

void Button::selected(bool flag)
{
	m_selected = flag;
}

void Button::setString(sf::Text tx)
{
	m_purposeText->setString(tx);
}

void Button::setState(int x)
{
	state = x;
}

int Button::getState() const
{
	return state;
}

sf::FloatRect Button::GetBoundingRect() const
{
	sf::Sprite tmp;
	tmp.setTexture(m_body);
	tmp.setPosition(m_pos);
	return tmp.getGlobalBounds();
}

bool Button::isClickedOnButton(const sf::Vector2f &_pos) const
{
	sf::Vector2f topV = getPos();
	sf::Vector2f downV = topV + getSize();
	return inRange(_pos, topV, downV);
}

bool Button::inRange(const sf::Vector2f &my, const sf::Vector2f &p1, const sf::Vector2f &p2) const
{
	return (my.x >= p1.x && my.y >= p1.y) && (my.x <= p2.x && my.y <= p2.y);
}