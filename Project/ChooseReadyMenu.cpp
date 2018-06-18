#include "ChooseReadyMenu.h"
#include "TextMenuButton.h"
#include "ImageMenuButton.h"

sf::Texture ChooseReadyMenu::bg;
//---------------------------------------------------------------------------//
/*
*
*/
ChooseReadyMenu::ChooseReadyMenu(const sf::Vector2u & windowSize)
	:Menu(windowSize), m_currPreview(0), m_currTexture(*m_src->getPreviews(m_currPreview))
{
	auto leftButton  = std::make_shared<ImageMenuButton>(std::move(*m_src->getEffect(5)), sf::Vector2f(windowSize.x / 6.f, 2 * windowSize.y / 5.f));
	auto rightButton = std::make_shared<ImageMenuButton>(std::move(*m_src->getEffect(3)), sf::Vector2f(5 * windowSize.x / 7.f, 2 * windowSize.y / 5.f));
	auto okButton    = std::make_shared<TextMenuButton>(std::move (*m_src->getText(25, m_src->getLang())), sf::Vector2f( 2.5f * windowSize.x / 6.f, windowSize.y / 4.f + 400 ));
	auto backButton  = std::make_shared<ImageMenuButton>((*m_src->getButtons(8)), sf::Vector2f(0, windowSize.y - 64.f));

	m_buttons.emplace_back(std::move(leftButton));
	m_buttons.emplace_back(std::move(rightButton));
	m_buttons.emplace_back(std::move(okButton));
	m_buttons.emplace_back(std::move(backButton));

	m_currSprite.setTexture(m_currTexture);
	m_currSprite.setScale(0.71f, 0.71f);
	m_currSprite.setPosition(windowSize.x / 3.f, windowSize.y / 5.f);
	bg = std::move(*m_src->getBackgound(1));
	m_bgRect.setTexture(std::move(&bg));


}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseReadyMenu::update(sf::RenderWindow & window)
{
	m_choosen = isOnButton(window);
	choose(m_choosen);
	unchoose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseReadyMenu::draw(sf::RenderWindow & window)
{
	window.draw(m_bgRect);		// draw main menu background image

	// draws all 'buttons'
	for (const auto& t : m_buttons)
		t->render(window);

	m_currTexture = std::move(*m_src->getPreviews(m_currPreview));
	m_currSprite.setTexture(m_currTexture);
	window.draw(m_currSprite);

}

//---------------------------------------------------------------------------//
/*
*
*/
int ChooseReadyMenu::isChoosen() const
{
	return m_choosen;
}

//---------------------------------------------------------------------------//
/*
*
*/
int ChooseReadyMenu::isOnButton(sf::RenderWindow & window) const
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
void ChooseReadyMenu::choose(int x)
{
	if (x != -1)		// chosen an option available
		m_buttons[x]->choose();
}

//---------------------------------------------------------------------------//
/*
*
*/
void ChooseReadyMenu::unchoose()
{

	for (int i = 0; i < m_buttons.size(); i++)
		if (i != m_choosen)
			m_buttons[i]->unchoose();
}


int ChooseReadyMenu::handleMenuEvents(sf::Event & e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition();
			if (isChoosen() == 0)
 			{
				m_currPreview--;
				if (m_currPreview == -1) 
					m_currPreview += NUM_OF_BOARDS;
			}
			if (isChoosen() == 1)
			{
				m_currPreview++;
				m_currPreview %= NUM_OF_BOARDS;
			}
			if (isChoosen() == 2)
			{
				return 6;
			}
			if (isChoosen() == 3)
			{
				return -1;
			}
		}
	}
	return -2;		// keeps to be in this menu
}

void ChooseReadyMenu::setNames()
{
	auto it = m_buttons.begin();
	for (; it != m_buttons.end()-1; ++it)
		(*it)->setName(*(m_src->getText(int(it - m_buttons.begin() + 23), m_src->getLang())));
}

size_t ChooseReadyMenu::size() const
{
	return m_buttons.size() - 1;
}

int ChooseReadyMenu::getMap() const
{
	return m_currPreview;
}
