#pragma once
#include "SrcManager.h"
#include <windows.h>


inline void makeWindowOnTop(sf::RenderWindow& window)
{
	HWND hwnd = window.getSystemHandle();
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

inline void openWelcome(std::string& name)
{
	sf::Texture bg = *(SrcManager::instance()->getBackgound(2));
	sf::Sprite s(bg);
	sf::Text tmp = std::move(*(SrcManager::instance()->getText(39, SrcManager::instance()->getLang())));
	sf::String title = std::move(tmp.getString());
	sf::RenderWindow window(sf::VideoMode(400, 200), title, sf::Style::Resize);
	sf::Event event;
	sf::Font font = (*SrcManager::instance()->getFont(2));
	sf::Text text("", font, 60);
	text.setPosition(20.f, 90.f);
	sf::Text startMessage = std::move(*(SrcManager::instance()->getText(40, SrcManager::instance()->getLang())));
	startMessage.setCharacterSize(60);
	startMessage.setFillColor(sf::Color::White);
	makeWindowOnTop(window);
	std::string t = " ";

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				int key = (event.key.code);
				if (key == sf::Keyboard::Return && name.size() != 0)
				{
					window.close();
					return;
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				char code = (char)(event.text.unicode);
				if (code != '\b' && // backspace
					code != '\r' && // enter
					name.size() <= MAX_NAME_LEN) // limited name
				{
					// if it's the first letter make  it upperCase
					(!name.size()) ? name.push_back(toupper(code)) :
						name.push_back(code);

					// if there are " " between first name to last name, 
					// make it upperCase
					if (name.size() >= 2 && name.at(name.size() - 2) == ' ')
					{
						name.pop_back();
						name.push_back(toupper(code));
					}

				}
				else if (code == '\b') // backspace
				{
					if (name.size() > 0)
						name.pop_back();
				}
			}
		}

		text.setOutlineThickness(5);
		startMessage.setOutlineThickness(5);
		text.setOutlineColor(sf::Color::Black);
		startMessage.setOutlineColor(sf::Color::Black);
		window.draw(s);
		text.setString(name);
		window.draw(startMessage);

		window.draw(text);
		window.display();
		window.clear();
	}
	sf::sleep(sf::milliseconds(50));
}


inline int DisplayResourceNAMessageBox(const std::wstring& title, const std::wstring& msg)
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)msg.c_str(),
		(LPCWSTR)title.c_str(),
		MB_ICONHAND | MB_OK
	);

	switch (msgboxID)
	{
	case IDOK:
		
		break;
	}

	return msgboxID;
}