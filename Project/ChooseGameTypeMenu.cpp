#include "ChooseGameTypeMenu.h"
#include "SrcManager.h"
#include "TextMenuButton.h"
#include "ImageMenuButton.h"


sf::Texture ChooseGameTypeMenu::bg;
//---------------------------------------------------------------------------//
/*
*
*/
ChooseGameTypeMenu::ChooseGameTypeMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize)
{

	auto PlayEZButton = std::make_shared<TextMenuButton>(/*std::move*/(*m_src->getText(15, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 90));
	auto PlayHardButton = std::make_shared<TextMenuButton>(/*std::move*/(*m_src->getText(16, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 230));
	auto backButton = std::make_shared<ImageMenuButton>(std::move(*m_src->getButtons(8)), sf::Vector2f(0, windowSize.y - 64.f));

	m_buttons.emplace_back(std::move(PlayEZButton));
	m_buttons.emplace_back(std::move(PlayHardButton));
	m_buttons.emplace_back(std::move(backButton));

	bg = std::move(*m_src->getBackgound(9));
	m_bgRect.setTexture(std::move(&bg));

}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseGameTypeMenu::update(sf::RenderWindow & window)
{
	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseGameTypeMenu::draw(sf::RenderWindow & window)
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
int ChooseGameTypeMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int ChooseGameTypeMenu::isOnButton(sf::RenderWindow & window) const
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
void ChooseGameTypeMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseGameTypeMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int ChooseGameTypeMenu::handleMenuEvents(sf::Event & e)
{

	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 0)
			{
				m_src->setPlay(SINGLE_PLAYER_P);
				return -3;
			}

			if (isChoosen() == 1)
			{
				m_src->setPlay(MULTI_PLAYER_P);
				///	AudioManager::instance()->stopMusic(0);
				return -3;
			}
			else if (isChoosen() == 2)		// back
			{
				return -1;
			}
		}
	}
	return -2;		// keeps to be in this menu
}

void ChooseGameTypeMenu::setNames()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 15), m_src->getLang())));
}