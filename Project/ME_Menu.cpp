#pragma once
#include "ME_Menu.h"

EditorMenu::EditorMenu() : m_src(SrcManager::instance())
{
	m_currAct.setState(10);
	Button Ship6({ 10.f, 95.f * 0 + 20.f }, 0, { 280.f, 70.f }, std::move(*m_src->getButtons(2)), std::move(*m_src->getText(2, m_src->getLang())));
	Button Ship4({ 10.f, 94.f * 1 + 20.f }, 1, { 240.f, 60.f }, std::move(*m_src->getButtons(3)), std::move(*m_src->getText(2, m_src->getLang())));
	Button Ship2({ 10.f, 96.f * 2 + 20.f }, 2, { 200.f, 70.f }, std::move(*m_src->getButtons(4)), std::move(*m_src->getText(2, m_src->getLang())));
	Button remove({ 35.f, 95.f * 3 + 20.f }, 3, { 60.f, 60.f }, std::move(*m_src->getButtons(5)), std::move(*m_src->getText(2, m_src->getLang())));
	Button clear({ 35.f, 95.f * 4 + 20.f }, 4, { 60.f, 60.f }, std::move(*m_src->getButtons(6)), std::move(*m_src->getText(2, m_src->getLang())));

	m_buttons.emplace_back(std::move(Ship6));
	m_buttons.emplace_back(std::move(Ship4));
	m_buttons.emplace_back(std::move(Ship2));
	m_buttons.emplace_back(std::move(remove));
	m_buttons.emplace_back(std::move(clear));

	Button t({ -100,-100 }, -1, { 0,0 }, std::move(*m_src->getButtons(7)));
	m_buttons.emplace_back(std::move(t));
}


void EditorMenu::draw(sf::RenderWindow& window)
{
	sf::RectangleShape selcted2;
	selcted2.setFillColor(sf::Color::Transparent);
	selcted2.setOutlineColor(sf::Color::Yellow);
	selcted2.setOutlineThickness(4);

	for (int i = 0; i < m_buttons.size()-1; i++)
	{
		if (m_currAct.getState() <= 3 && i == m_currAct.getState())
		{
			m_buttons.at(i).selected(true);
			window.draw(selcted2);
		}
		else
			m_buttons.at(i).selected(false);

		sf::Text tx = std::move(*m_src->getText(i, m_src->getLang()));
		m_buttons.at(i).draw(window, false, std::move(tx));
	}
}

Button* EditorMenu::getclickedButton(const sf::Vector2f &currPos)
{
	try
	{
		for (auto& button : m_buttons)
			if (button.isClickedOnButton(currPos))
			{
				m_currAct = button;
				return &button;
			}
	}
	catch (std::exception&)
	{
		return &m_buttons.at(5);
	}
	return &m_buttons.at(5);
}

Button* EditorMenu::isHoveredOnButton(const sf::Vector2f &currPos)
{
	try
	{
		for (int i = 0; i < m_buttons.size(); ++i)
			if (m_buttons.at(i).isClickedOnButton(currPos))
				return &m_buttons.at(i);
	}
	catch (std::exception&)
	{
		return &m_buttons.at(5);
	}
	return &m_buttons.at(5);
}

bool EditorMenu::inRange(const sf::Vector2f &my, const sf::Vector2f &p1, const sf::Vector2f &p2) const
{
	return (my.x >= p1.x && my.y >= p1.y) && (my.x <= p2.x && my.y <= p2.y);
}

Button EditorMenu::operator[](int index) const
{
	return m_buttons.at(index);
}