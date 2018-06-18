#include "OptionButton.h"


OptionButton::OptionButton(const sf::Text & ButtonNameTxt, const sf::Vector2f& position)
	:m_NameText(std::move(ButtonNameTxt)), m_position(position)
{
	m_NameText.setPosition(m_position);
	m_NameText.setCharacterSize(70);
	m_NameText.setOutlineThickness(5);
	m_NameText.setOutlineColor(sf::Color::Black);

	m_fowardButton = std::make_shared<ImageMenuButton>(  (*m_src->getEffect(5)), sf::Vector2f(m_position.x + 400, m_position.y));
	m_backwardButton = std::make_shared<ImageMenuButton>((*m_src->getEffect(3)), sf::Vector2f(position.x + 725, position.y));

	m_backwardButton->scale(0.8f, 0.8f);
	m_fowardButton->scale(0.8f, 0.8f);

	m_currentOption = 0;
}

void OptionButton::addOption(const sf::Text & newOptionTxt)
{
	m_options.emplace_back(std::move(newOptionTxt));
	(m_options.end() - 1)->setPosition(m_position + sf::Vector2f(510, 0));
	(m_options.end() - 1)->setCharacterSize(70);
	(m_options.end() - 1)->setOutlineThickness(5);
	(m_options.end() - 1)->setOutlineColor(sf::Color::Black);

}


void OptionButton::render(sf::RenderWindow & window) const
{
	window.draw(m_NameText);
	m_backwardButton->render(window);
	window.draw(m_options.at(m_currentOption));
	m_fowardButton->render(window);
}

void OptionButton::update(sf::RenderWindow & window)
{
	sf::Vector2f currPos = (sf::Vector2f)sf::Mouse::getPosition(window);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_backwardButton->getGlobalBounds().contains(currPos))
		{
			m_currentOption++;
			m_currentOption %= m_options.size();

			sf::sleep(sf::milliseconds(200));
		}
		else if (m_fowardButton->getGlobalBounds().contains(currPos))
		{
			m_currentOption--;
			if (m_currentOption == -1)
				m_currentOption = short(m_options.size() - 1);

			sf::sleep(sf::milliseconds(200));
		}
	}

	if (m_fowardButton->getGlobalBounds().contains(currPos))
		m_fowardButton->choose();
	else if (m_backwardButton->getGlobalBounds().contains(currPos))
		m_backwardButton->choose();
	else
	{
		m_backwardButton->unchoose();
		m_fowardButton->unchoose();
	}
}

sf::FloatRect OptionButton::getGlobalBounds() const
{
	sf::FloatRect rect;
	rect.top = m_fowardButton->getGlobalBounds().top;
	rect.left = m_fowardButton->getGlobalBounds().left;
	rect.height = 80;
	rect.width = m_backwardButton->getGlobalBounds().left - m_fowardButton->getGlobalBounds().left + 90;

	return rect;
}

void OptionButton::setName(const sf::Text& newText, int offsetOption)
{
	m_NameText.setString(newText.getString());
	m_NameText.setFont(*newText.getFont());

	for (int i = 0; i < m_options.size(); i++) {
		m_options[i].setString((*m_src->getText(offsetOption + i, m_src->getLang())).getString());
		m_options[i].setFont(*newText.getFont());
	}

}

void OptionButton::choose()
{
	m_NameText.setFillColor(sf::Color::Red);
}

void OptionButton::unchoose()
{
	m_NameText.setFillColor(sf::Color::White);
}

int OptionButton::getChooseButton()
{
	return m_currentOption;
}

void OptionButton::reset()
{
	m_currentOption = 0;
}

void OptionButton::setCurrentOpt(int opt)
{
	m_currentOption = opt;
}
