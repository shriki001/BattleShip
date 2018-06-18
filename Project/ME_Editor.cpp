#include "ME_Editor.h"


Editor::Editor() :m_src(SrcManager::instance()), m_rot(false),
	m_leftMiddle(LEFT_NIDDLE), m_leftSmall(LEFT_SMALL), m_leftBig(LEFT_BIG)
{
	m_settings = std::make_shared<Map>();
	m_Bmenu = std::make_shared<EditorMenu>();

	m_ok = { { 1186,24 }, -1,{ 70.f, 70.f }, (*m_src->getButtons(9)) };
}

void Editor::drawE(sf::RenderWindow & _window)
{
	int middleSize = m_settings->getMiddleLeft();
	int smallSize = m_settings->getSmallLeft();
	int BigSize = m_settings->getBigLeft();

	auto Acurr_pos = (sf::Vector2f) sf::Mouse::getPosition(_window);
	bool showCursor = (m_settings->inRange(Acurr_pos)) ? false : true;
	_window.setMouseCursorVisible(showCursor);

	sf::Text quantityLeft2 = std::move(createText(smallSize));
	sf::Text quantityLeft4 = std::move(createText(middleSize));
	sf::Text quantityLeft6 = std::move(createText(BigSize));

	update(quantityLeft2, 2, 15);
	update(quantityLeft4, 1, 10);
	update(quantityLeft6, 0, 0);

	m_settings->display(_window);
	m_Bmenu->draw(_window);
	if ((m_Bmenu->isHoveredOnButton(Acurr_pos))->getState() != 1)
		_window.draw(quantityLeft4);
	if ((m_Bmenu->isHoveredOnButton(Acurr_pos))->getState() != 2)
		_window.draw(quantityLeft2);
	if ((m_Bmenu->isHoveredOnButton(Acurr_pos))->getState() != 0)
		_window.draw(quantityLeft6);

	sf::Text tddd;
	if (m_settings->allOK())
	{
		m_ok = { { 1186,24 }, -1,{ 70.f, 70.f }, (*m_src->getButtons(10)) };
		sf::Text continueMsg = std::move(*m_src->getText(10, m_src->getLang()));
		(m_src->getLang() == 0) ? continueMsg.setCharacterSize(60) : continueMsg.setCharacterSize(45);
		(m_src->getLang() == 0) ? continueMsg.setPosition(1015, 20) : continueMsg.setPosition(1070, 28);
		_window.draw(continueMsg);
	}
	m_ok.draw(_window, true, tddd);
}

bool Editor::reset()
{
	if (m_CurrState == RESET_MODE_A)
	{
		m_CurrState = (ActionType_t)0;
		return true;
	}
	return false;
}

sf::Vector2i Editor::getPlace(const sf::Vector2f & src)
{
	int x0 = (int)fmod((int)((src.x - 90 - 190) / 30), 40);
	int y0 = (int)fmod((int)((src.y - 70 - 120) / 30), 40);

	return sf::Vector2i(x0, y0);
}

void Editor::PlayButton(const sf::Vector2f & currPos, const bool dir)
{
	int size = 0;
	switch (m_CurrState)
	{
	case 0: size = 6; break;
	case 1: size = 4; break;
	case 2: size = 2; break;
	}
	Button* b = m_Bmenu->getclickedButton(currPos);
	m_rot = dir;
	
	// pressed on action
	if (b->getState() >= 0 && b->getState() <= 9)
		m_CurrState = (ActionType_t)(b->getState());

	if (m_CurrState == RESET_MODE_A)
	{
		m_ok = { { 1186,24 }, -1,{ 70.f, 70.f }, (*m_src->getButtons(9)) };
		m_settings->resetAllSizes();
		m_settings->cleanMap();
		return;
	}
	else if (m_CurrState == ERASE_MODE_A && m_settings->inRange(currPos))
	{
		m_ok = { { 1186,24 }, -1,{ 70.f, 70.f }, (*m_src->getButtons(9)) };
		sf::Vector2i itemPos = getPlace(currPos);
		sf::RectangleShape tmp(sf::Vector2f(40, 40));
		tmp.setFillColor(sf::Color::Black);
		tmp.setOutlineThickness(5);
		size = m_settings->getSize(itemPos.x, itemPos.y);
		switch (size)
		{
		case 2: m_settings->updateSmallLeft(1);
			break;
		case 4: m_settings->updateMiddleLeft(1);
			break;
		case 6: m_settings->updateBigLeft(1);
			break;
		}
		if (size != 0)
			m_settings->remove(itemPos, dir, size);
	}
	else if (m_settings->inRange(currPos))
	{
		sf::Vector2i itemPos = getPlace(currPos);
		if (m_settings->getSign(itemPos.x, itemPos.y) == '-')
		{
			if (m_settings->canPut(itemPos, dir, size) &&
				((size == 2 && m_settings->getSmallLeft() > 0) ||
				(size == 4 && m_settings->getMiddleLeft() > 0) ||
					(size == 6 && m_settings->getBigLeft() > 0)))
			{
				switch (size)
				{
				case 2:m_settings->updateSmallLeft(-1);
					break;
				case 4:m_settings->updateMiddleLeft(-1);
					break;
				case 6:m_settings->updateBigLeft(-1);
					break;
				}
				if (size != 0)
					m_settings->draw(itemPos, dir, size);
			}
		}
	}
}

void Editor::ShowButtonInfo(const sf::Vector2f & currPos)
{
	Button* b = m_Bmenu->isHoveredOnButton(currPos);
	if (b)
		b->toShow(true);
}

bool Editor::allGood(sf::Vector2f curr_pos)
{
	return m_settings->allOK() && m_ok.isClickedOnButton(curr_pos);
}

sf::Text Editor::createText(int size)
{
	std::string str;
	sf::Text tmp = std::move(*m_src->getText(9, m_src->getLang()));
	str = tmp.getString() + std::to_string(size);
	tmp.setString(str);
	tmp.setCharacterSize(45);
	return tmp;
}

void Editor::update(sf::Text &obj, int place, int size)
{
	obj.setPosition((*(m_Bmenu.get()))[place].getPos() + (*(m_Bmenu.get()))[place].getSize() / 2.f);
	obj.setPosition(obj.getPosition().x - size, obj.getPosition().y - 25);
}