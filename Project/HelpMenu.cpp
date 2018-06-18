#include "HelpMenu.h"
#include "SrcManager.h"
#include "ImageMenuButton.h"
//---------------------------------------------------------------------------//
/*
*
*/

sf::Texture HelpMenu::bg;

HelpMenu::HelpMenu(const sf::Vector2u & windowSize)
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
void HelpMenu::update(sf::RenderWindow & window)
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
void HelpMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_bgRect);		// draw main menu background image

   // draws all 'buttons'
	for (const auto& t : m_buttons)
		t->render(window);
}

//---------------------------------------------------------------------------//
/*
*
*/
int HelpMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int HelpMenu::isOnButton(sf::RenderWindow & window) const
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
void HelpMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void HelpMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}
 

int HelpMenu::handleMenuEvents(sf::Event & e)
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

void HelpMenu::setNames()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 17), m_src->getLang())));
}
