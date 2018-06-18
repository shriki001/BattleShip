#include "PauseMenu.h"
#include "TextMenuButton.h"
#include "OptionButton.h"

#include "AudioManager.h"

sf::Texture PauseMenu::bg;
//---------------------------------------------------------------------------//
/*
*
*/
PauseMenu::PauseMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize)
{

	auto aButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(18, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f - 50, windowSize.y / 4.f + 200));
	auto bButton = std::make_shared<TextMenuButton>(std::move(*m_src->getText(19, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f - 50, windowSize.y / 4.f + 280));
	auto MuteButton = std::make_shared<OptionButton>(std::move(*m_src->getText(0, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f - 50, windowSize.y / 4.f + 370));

	MuteButton->addOption((*m_src->getText(0, m_src->getLang())));
	MuteButton->addOption((*m_src->getText(0, m_src->getLang())));
	
	m_buttons.emplace_back(std::move(aButton));
	m_buttons.emplace_back(std::move(bButton));
	m_buttons.emplace_back(std::move(MuteButton));

	bg = *(m_src->getBackgound(6));
	m_bgRect.setTexture(&bg);
	//	
	m_bgRect.setFillColor({ 255, 0, 0, 255 });

}

//---------------------------------------------------------------------------//
/*
*
*/
void PauseMenu::update(sf::RenderWindow & window)
{
	std::dynamic_pointer_cast<OptionButton>(m_buttons[2])->update(window);

	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void PauseMenu::draw(sf::RenderWindow & window)
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
int PauseMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int PauseMenu::isOnButton(sf::RenderWindow & window) const
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
void PauseMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void PauseMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int PauseMenu::handleMenuEvents(sf::Event & e)
{
// 	if (e.type == sf::Event::KeyPressed && e.type == sf::Keyboard::Escape)
// 	{
// 		sf::sleep(sf::milliseconds(100));
// 		return -3;
// 	}
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 2)
			{
				auto retVal = ((std::dynamic_pointer_cast<OptionButton>(m_buttons[2]))->getChooseButton());
				if (retVal != -1)
					AudioManager::instance()->reMute();
			}
			else if (isChoosen() == 0)
			{
				sf::sleep(sf::milliseconds(100));
				return -3;
			}
			else if (isChoosen() == 1)
			{
				sf::sleep(sf::milliseconds(600));
				return 0;
			}
		}
	}
	return -2;		// keeps to be in this menu
}

void PauseMenu::setNames()
{
	auto it = m_buttons.begin();
	(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 18), m_src->getLang())));
	(*(it + 1))->setName(*(m_src->getText(int(it - m_buttons.begin() + 19), m_src->getLang())));
	(*(it + 2))->setName(*(m_src->getText(int(it - m_buttons.begin() + 41), m_src->getLang())), 42);
}

void PauseMenu::syncOptionName()
{
	std::dynamic_pointer_cast<OptionButton>(m_buttons[2])->setCurrentOpt(AudioManager::instance()->isMute());
}