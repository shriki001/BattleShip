#include "MapMenu.h"
#include "TextMenuButton.h"
#include "ImageMenuButton.h"
sf::Texture MapMenu::bg;
//---------------------------------------------------------------------------//
/*
*
*/
MapMenu::MapMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize)
{
	auto createButton= std::make_shared<TextMenuButton>(/*std::move*/(*m_src->getText(20, m_src->getLang())), sf::Vector2f( windowSize.x / 3.f, windowSize.y / 4.f + 200 ));
	auto ChooseButton= std::make_shared<TextMenuButton>(/*std::move*/(*m_src->getText(21, m_src->getLang())), sf::Vector2f( windowSize.x / 3.f, windowSize.y / 4.f + 250 ));
	auto R2MainButton= std::make_shared<ImageMenuButton>(/*std::move*/(*m_src->getButtons(8)), sf::Vector2f( 0, windowSize.y -64.f ));

	m_buttons.emplace_back(std::move(createButton));
	m_buttons.emplace_back(std::move(ChooseButton));
	m_buttons.emplace_back(std::move(R2MainButton));

	bg = std::move(*m_src->getBackgound(5));
	m_bgRect.setTexture(std::move(&bg));
}

//---------------------------------------------------------------------------//
/*
*
*/
void MapMenu::update(sf::RenderWindow & window)
{
	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void MapMenu::draw(sf::RenderWindow & window)
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
int MapMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int MapMenu::isOnButton(sf::RenderWindow & window) const
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
void MapMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void MapMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int MapMenu::handleMenuEvents(sf::Event & e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 0)
			{
				return 4;
			}
			if (isChoosen() == 1)
			{
				return 5;
		    }
			if (isChoosen() == 2)
			{
				return -1;
			}
		}
	}
	return -2;		// keeps to be in this menu
}

void MapMenu::setNames()
{
	auto it = m_buttons.begin();
	for (; it != m_buttons.end()-1; ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 20), m_src->getLang())));
	(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 17), m_src->getLang())));
}

size_t MapMenu::size() const
{
	return m_buttons.size() - 1;
}
