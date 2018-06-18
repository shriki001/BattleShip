
#include "MainMenu.h"
#include "TextMenuButton.h"
// #include "AudioManager.h"

sf::Texture MainMenu::bg;
//---------------------------------------------------------------------------//
/*
*
*/
MainMenu::MainMenu(const sf::Vector2u & windowSize)
	: Menu(windowSize)
{
	auto PlayButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(11, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 90));
	auto optionsButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(12, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 140));
	auto HelpButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(13, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 190));
	auto ExitButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(14, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f, windowSize.y / 4.f + 240));

	m_buttons.emplace_back(std::move(PlayButton));
	m_buttons.emplace_back(std::move(optionsButton));
	m_buttons.emplace_back(std::move(HelpButton));
	m_buttons.emplace_back(std::move(ExitButton));

	bg = std::move(*m_src->getBackgound(4));
	m_bgRect.setTexture(std::move(&bg));
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::update(sf::RenderWindow & window)
{
	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_bgRect);		// draw main menu background image

	// draws all 'buttons'
	for (auto t : m_buttons)
		t->render(window);
}

//---------------------------------------------------------------------------//
/*
*
*/
int MainMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int MainMenu::isOnButton(sf::RenderWindow & window) const
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
void MainMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void MainMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int MainMenu::handleMenuEvents(sf::Event & e)
{

	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 0)  // next Menu 
			{
				/*AudioManager::instance()->stopMusic(0);*/
				///return 0;/// 
				return 3;
			}

			else if (isChoosen() == 1) // options
				return 2;
			/// 				
			else if (isChoosen() == 2) // help
				return 1;


			else if (isChoosen() == 3)	//choose "Exit"
				return -3;
		}
	}
	return -2;
}

void MainMenu::setNames()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 11), m_src->getLang())));
}