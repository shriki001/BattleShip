#include "EndGameMenu.h"
#include "SrcManager.h"
#include "ImageMenuButton.h"
//---------------------------------------------------------------------------//
/*
*
*/

sf::Texture EndGameMenu::bg;

EndGameMenu::EndGameMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize)
{

	auto aButton = std::make_shared<ImageMenuButton>(std::move(*m_src->getButtons(8)), sf::Vector2f(0, windowSize.y - 64.f));
	m_buttons.emplace_back(std::move(aButton));

	bg = std::move(*m_src->getBackgound(10));
	m_bgRect.setTexture(std::move(&bg));

}

//---------------------------------------------------------------------------//
/*
*
*/
void EndGameMenu::update(sf::RenderWindow & window)
{
	bg = *(m_src->getBackgound(m_src->getLang() + 10));
	m_bgRect.setTexture(&bg);

	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void EndGameMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_bgRect);		// draw main menu background image



	static sf::Text msg;
	static sf::Texture tmp;
	sf::Sprite img;
	window.clear();
	if (m_mode == 1)
	{
		msg = (std::move(*(m_src->getText(37, m_src->getLang()))));
		tmp = std::move((*m_src->getBackgound(6)));
		msg.setFillColor(sf::Color::Green);
	}
	else
	{
		msg = (std::move(*(m_src->getText(38, m_src->getLang()))));
		tmp = std::move((*m_src->getBackgound(7)));
		msg.setFillColor(sf::Color::Red);
	}
	msg.setOutlineThickness(5);
	msg.setOutlineColor(sf::Color::Black);
	msg.setCharacterSize(70);
	std::wstring tm(msg.getString());
	std::wstring tm1;
	std::wstring tm2;
	size_t size = tm.find(L'&');
	tm1 = tm.substr(0, size);
	tm2 = tm.substr(size + 1, tm.size() - 1);
	msg.setString(tm1);


	img.setTexture(tmp);
	window.draw(img);
	msg.setPosition(420, 200);
	window.draw(msg);
	msg.setString(tm2);
	msg.setPosition(500, 300);
	window.draw(msg);

	// draws all 'buttons'
	for (const auto& t : m_buttons)
		t->render(window);

}

//---------------------------------------------------------------------------//
/*
*
*/
int EndGameMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int EndGameMenu::isOnButton(sf::RenderWindow & window) const
{
	sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition(window);
	int i = 0;

	for (auto it = m_buttons.begin(); it != m_buttons.end(); it++, i++)
	{
		if ((*it)->getGlobalBounds().contains(currPos))
			return i;
	}

	return -1;
}

//---------------------------------------------------------------------------//
/*
*
*/
void EndGameMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void EndGameMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int EndGameMenu::handleMenuEvents(sf::Event & e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 0)
				return -1;

		}
	}
	return -2;		// keeps to be in this menu
}

void EndGameMenu::setNames()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 17), m_src->getLang())));
}

void EndGameMenu::setMode(int mode)
{
	m_mode = mode;
}
