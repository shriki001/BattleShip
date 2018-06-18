#include "OptionsMenu.h"
#include "TextMenuButton.h"
#include "utilities.h"
#include "Game.h"
#include "OptionButton.h"
#include "AudioManager.h"


sf::Texture OptionsMenu::bg;
sf::Text OptionsMenu::name;
sf::Font OptionsMenu::font;
std::string OptionsMenu::strName;

OptionsMenu::OptionsMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize)
{
	auto PlayerNameButton   = std::make_shared<TextMenuButton>((*m_src->getText(26, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f -100, windowSize.y / 4.f - 100));
	auto MuteButton         = std::make_shared<OptionButton>((*m_src->getText(41, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f - 100, windowSize.y / 4.f));
	auto LangugeButton      = std::make_shared<OptionButton>((*m_src->getText(27, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f -100, windowSize.y / 4.f + 100));
	auto DifficulityButton  = std::make_shared<OptionButton>((*m_src->getText(30, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f-100, windowSize.y / 4.f + 200));
	auto ViewButton         = std::make_shared<OptionButton>((*m_src->getText(34, m_src->getLang())), sf::Vector2f(windowSize.x / 3.f-100, windowSize.y / 4.f + 300));
	auto backButton         = std::make_shared<ImageMenuButton>(std::move(*m_src->getButtons(8)), sf::Vector2f(0, windowSize.y - 64.f));

	LangugeButton->addOption(std::move(*m_src->getText(28, m_src->getLang())));
	LangugeButton->addOption(std::move(*m_src->getText(29, m_src->getLang())));
	DifficulityButton->addOption(std::move(*m_src->getText(31, m_src->getLang())));
	DifficulityButton->addOption(std::move(*m_src->getText(32, m_src->getLang())));
	DifficulityButton->addOption(std::move(*m_src->getText(33, m_src->getLang())));
	ViewButton->addOption(std::move(*m_src->getText(35, m_src->getLang())));;
	ViewButton->addOption(std::move(*m_src->getText(36, m_src->getLang())));

	MuteButton->addOption((*m_src->getText(42, m_src->getLang())));/*@*/
	MuteButton->addOption((*m_src->getText(43, m_src->getLang())));/*@*/

	m_buttons.emplace_back(std::move(PlayerNameButton));
	m_buttons.emplace_back(std::move(MuteButton));
	m_buttons.emplace_back(std::move(LangugeButton));
	m_buttons.emplace_back(std::move(DifficulityButton));
	m_buttons.emplace_back(std::move(ViewButton));
	m_buttons.emplace_back(std::move(backButton));

	bg = std::move(*m_src->getBackgound(3));
	m_bgRect.setTexture(std::move(&bg));
	font = (*SrcManager::instance()->getFont(2));
	name.setFont(font);
	name.setOutlineThickness(5);
	name.setOutlineColor(sf::Color::Black);
	name.setCharacterSize(60);
	name.setPosition(800,80);
}

//---------------------------------------------------------------------------//
/*
*
*/
void OptionsMenu::update(sf::RenderWindow & window)
{

	for (auto it = (m_buttons.begin() + 1) ; it != (m_buttons.begin() + 5); it++)
		std::dynamic_pointer_cast<OptionButton>(*it)->update(window);

	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void OptionsMenu::draw(sf::RenderWindow & window)
{
	name.setString(Game::getName());
	strName = name.getString();
	
	window.draw(m_bgRect);	// draw main menu background image
	window.draw(name);
	
	// draws all 'buttons'
	for (const auto& t : m_buttons)
		t->render(window);
}

//---------------------------------------------------------------------------//
/*
*
*/
int OptionsMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int OptionsMenu::isOnButton(sf::RenderWindow & window) const
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
void OptionsMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void OptionsMenu::unchoose()
{
	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int OptionsMenu::handleMenuEvents(sf::Event & e)
{

	if (isChoosen() == 2)
	{
		auto retVal = ((std::dynamic_pointer_cast<OptionButton>(m_buttons[2]))->getChooseButton());
		if (retVal != -1)
			m_src->setLang(retVal);
	}
	else if (isChoosen() == 3)
	{
		auto retVal = ((std::dynamic_pointer_cast<OptionButton>(m_buttons[3]))->getChooseButton());
		switch (retVal)
		{
		case 0: m_src->setDifficulity(EASY_D);  break;
		case 1: m_src->setDifficulity(MEDIUM_D); break;
		case 2: m_src->setDifficulity(IMPOSSIBLE_D); break;
		default:
			break;
		}

	}
	else if (isChoosen() == 4)
	{
		auto retVal = ((std::dynamic_pointer_cast<OptionButton>(m_buttons[4]))->getChooseButton());
		if (retVal != -1)
			m_src->setMod(retVal);

	}


	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 1)
			{
				auto retVal = ((std::dynamic_pointer_cast<OptionButton>(m_buttons[1]))->getChooseButton());
				if (retVal != -1)
					AudioManager::instance()->reMute();
			}
			if (isChoosen() == 5)
				return -1;
			if (isChoosen() == 0)
			{
				openWelcome(strName);
				Game::setName(strName);
			}
		}
	}
	return -2;		// keeps to be in this menu
}

void OptionsMenu::setNames()
{
	auto it = m_buttons.begin();
	(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 26), m_src->getLang())));
	(*(it + 1))->setName(*(m_src->getText(int(it - m_buttons.begin() + 41), m_src->getLang())), 42);
	(*(it + 2))->setName(*(m_src->getText(int(it - m_buttons.begin() + 27), m_src->getLang())), 28);
	(*(it + 3))->setName(*(m_src->getText(int(it - m_buttons.begin() + 30), m_src->getLang())), 31);
	(*(it + 4))->setName(*(m_src->getText(int(it - m_buttons.begin() + 34), m_src->getLang())), 35);

}

void OptionsMenu::reset()
{
	std::dynamic_pointer_cast<OptionButton>(m_buttons[2])->reset();
}

void OptionsMenu::syncOptionName()
{
	std::dynamic_pointer_cast<OptionButton>(m_buttons[1])->setCurrentOpt(AudioManager::instance()->isMute());
}
