#include "SinglePlayer.h"
#include "Game.h"
#include "AIRIival.h"
#include "MultyPlayer.h"

#include "PauseMenu.h"
#include "HelpMenu.h"
#include "ChooseGameTypeMenu.h"
#include "MapMenu.h"
#include "OptionsMenu.h"
#include "ChooseReadyMenu.h"
#include "EndGameMenu.h"

#include "utilities.h"
#include "ChatBox.h"
#include "Chat.h"


sf::Time Game::elapsed = sf::Time::Zero;

static sf::RenderWindow window;
bool Game::first = true;
std::string Game::name;

Game::Game()
	:m_src(SrcManager::instance()),
	m_audioSrc(AudioManager::instance()),
	editor(EditorControler::instance()),
	m_bg(*m_src->getBackgound(2)),
	m_turn(rand() % 2),
	font(*m_src->getFont(0)),
	chatFont(*m_src->getFont(2))
{
	s1.setTexture(m_bg);
	m_time = std::move(sf::Text(std::to_string(m_src->getDifficulity()), font, 50));
	m_time.setFillColor(sf::Color::Black);
	m_time.setPosition(20, 400);

	initMenus();
	m_stack.push(m_menus[MAINMENU_M]); // push main menu
}

void Game::run()
{
	openWelcome(name);

	sf::Event event;
	window.create(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "", sf::Style::Close);

	auto beforeTime = m_clock.getElapsedTime();

	m_player = std::make_unique<SinglePlayer>(name);
	m_audioSrc->playMusic(MAINMENU_S);
	while (m_running)
	{
		window.setMouseCursorVisible(true);
		if (m_inEditor)
		{
			m_audioSrc->stopMusic(MAINMENU_S);
			m_audioSrc->playMusic(MAPEDITOR_S);
			editor->run(window);
			m_inEditor = false;
			m_stack.push(m_menus[CHOOSEGAMETYPEMENU_M]);
			m_currMenuPtr = m_stack.top();
			m_player->setMap(editor->getEditor()->getMap());
			m_audioSrc->stopMusic(MAPEDITOR_S);
			m_audioSrc->playMusic(MAINMENU_S);
		}

		if (!m_stack.empty())
		{
			m_audioSrc->pauseMusic(GAME_S);
			handleMenu();
		}

		else {			// in game mod
			if (first)
			{
				m_audioSrc->stopMusic(MAINMENU_S);

				OptionsMenu::setName(name);
				m_player->setName(OptionsMenu::getName());
				m_rival = std::make_shared<AiRival>("Computer Rival",dynamic_cast<SinglePlayer*>(m_player.get())->getMap());
				m_PlayerName = std::move(sf::Text(m_player->getName(), font, 70));
				m_PlayerName.setPosition(500, 0);

				m_RivalName = std::move(sf::Text(m_rival->getName(), font, 70));
				m_RivalName.setPosition(500, 0);
				m_PlayerName.setOutlineThickness(5);
				m_PlayerName.setOutlineColor(sf::Color::Black);

				m_RivalName.setOutlineThickness(5);
				m_RivalName.setOutlineColor(sf::Color::Black);

				auto afterTime = m_clock.getElapsedTime();
				elapsed -= (afterTime - beforeTime);

				if (m_src->getPlay() == MULTI_PLAYER_P)
				{
					std::dynamic_pointer_cast<OptionsMenu>(m_menus[OPTIONSMENU_M])->reset();
					m_src->setDifficulity(EASY_D);
					m_rival = std::make_shared<MultyPlayer>(m_player->getName());
					std::dynamic_pointer_cast<MultyPlayer>(m_rival)->setWin(0);

					if (!std::dynamic_pointer_cast<MultyPlayer>(m_rival)->getConnection())
					{
						m_isConnected = false;
						m_stack.push(m_menus[MAINMENU_M]);
						m_currMenuPtr = m_stack.top();
						first = true;
						resetGame();
						continue;
					}

					m_RivalName.setString(m_rival->getName());
					for (int i = 0; i < M_ROW; ++i)
						for (int j = 0; j < M_COL; ++j)
							std::dynamic_pointer_cast<MultyPlayer>(m_rival)->send(INITIAL_DATA, i, j, m_player->getSign(i, j));

					m_turn = std::dynamic_pointer_cast<MultyPlayer>(m_rival)->getTurn();

					m_audioSrc->playMusic(GAME_S);
					// enable chat
					static sf::Thread thread([&]()
					{
						runChat(cWindow, m_player->getName());
					});
					thread.launch();
				}
				else
					m_audioSrc->playMusic(GAME_S);

				elapsed = sf::Time::Zero;
				m_clock.restart();
				first = false;
			}
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					exit(EXIT_FAILURE);
				}
			}

			window.clear();
			update(event);
			render();

			window.display();
			if (!m_pause && m_src->getPlay() == MULTI_PLAYER_P)
			{
				std::dynamic_pointer_cast<MultyPlayer>(m_rival)->send(WHOWON);
				std::dynamic_pointer_cast<MultyPlayer>(m_rival)->receive();
				won = std::dynamic_pointer_cast<MultyPlayer>(m_rival)->getWin();
				std::dynamic_pointer_cast<MultyPlayer>(m_rival)->send(CAN_PLAY, true);
				std::dynamic_pointer_cast<MultyPlayer>(m_rival)->receive();
			}
			if (m_stack.empty() && won == 0)
			{
				m_turn = !m_turn;
				elapsed = sf::Time::Zero;
			}
			else if (won != 0)   // game has end
			{
				if (m_src->getPlay() == MULTI_PLAYER_P)
				{
					cWindow.close();
					std::dynamic_pointer_cast<MultyPlayer>(m_rival)->Disconnect();
				}

				m_stack.push(m_menus[MAINMENU_M]);
				m_stack.push(m_menus[END_MENU_M]);
				m_currMenuPtr = m_stack.top();
			}
		}
	}
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::initMenus()
{
	m_menus.resize(8);
	m_menus[MAINMENU_M] = std::make_shared<MainMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[HELPMENU_M] = std::make_shared<HelpMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[OPTIONSMENU_M] = std::make_shared<OptionsMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[MAPMENU_M] = std::make_shared<MapMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[CHOOSEREADYMENU_M] = std::make_shared<ChooseReadyMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[CHOOSEGAMETYPEMENU_M] = std::make_shared<ChooseGameTypeMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[END_MENU_M] = std::make_shared<EndGameMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));
	m_menus[PAUSEMENU_M] = std::make_shared<PauseMenu>(sf::Vector2u(SCREEN_HEIGHT, SCREEN_WIDTH));

	m_currMenuPtr = m_menus[MAINMENU_M];
}
//---------------------------------------------------------------------------//
/*
*
*/
void Game::clearStack()
{
	while (!m_stack.empty())
		m_stack.pop();
}
//---------------------------------------------------------------------------//
/*
*
*/
void Game::resetGame()
{
	cWindow.close();
	m_currMenuPtr = m_stack.top();
	counting = {};
	m_ans = false;
	won = 0;
	q = { -1,-1 };
	m_player->init();
	m_rival->init();
	first = true;
	m_turn = rand() % 2;
	m_audioSrc->playMusic(MAINMENU_S);
	m_pause = false;
}
//---------------------------------------------------------------------------//
/*
*
*/
void Game::setName(const std::string &newName)
{
	name = newName;
}

//---------------------------------------------------------------------------//
/*
*
*/
std::string Game::getName()
{
	return name;
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::handleMenu()
{
	sf::Event e;
	sf::Time beforeTime;

	if (std::dynamic_pointer_cast<EndGameMenu>(m_currMenuPtr))
	{
		m_audioSrc->stopMusic(GAME_S);
		if (won == 2)
			m_audioSrc->playMusic(LOST_S, false);
		else if (won == 1)
			m_audioSrc->playMusic(WIN_S, false);
		std::dynamic_pointer_cast<EndGameMenu>(m_currMenuPtr)->setMode(won);
	}

	if (std::dynamic_pointer_cast<PauseMenu>(m_currMenuPtr) && m_src->getPlay() == SINGLE_PLAYER_P)
		beforeTime = m_clock.getElapsedTime();

	do {
		while (window.pollEvent(e))
		{
			int ret_value = m_currMenuPtr->handleMenuEvents(e);
			if (ret_value == 4)
			{
				m_inEditor = true;
				return;
			}
			else if (ret_value >= 0)		// continue to next menu
			{
				if (std::dynamic_pointer_cast<PauseMenu>(m_currMenuPtr))
					resetGame();

				m_stack.push(m_menus[ret_value]);
				m_currMenuPtr = m_stack.top();
			}
			else if (ret_value == -1)		// back to prev. menu
			{
				if (std::dynamic_pointer_cast<EndGameMenu>(m_currMenuPtr))
				{
					if (m_src->getPlay() == MULTI_PLAYER_P)
						std::dynamic_pointer_cast<MultyPlayer>(m_rival)->Disconnect();
					if (won == 2)
						m_audioSrc->stopMusic(LOST_S);
					else if (won == 1)
						m_audioSrc->stopMusic(WIN_S);
					resetGame();
				}

				m_stack.pop();
				m_currMenuPtr = m_stack.top();
			}
			else if (ret_value == -3)
			{
				m_pause = false;
				if (std::dynamic_pointer_cast<PauseMenu>(m_currMenuPtr))
				{
					if (m_src->getPlay() == SINGLE_PLAYER_P)
					{
						auto afterTime = m_clock.getElapsedTime();
						elapsed -= (afterTime - beforeTime);
						std::dynamic_pointer_cast<AiRival>(m_rival)->addLostTime((afterTime - beforeTime));
					}
					m_audioSrc->playMusic(GAME_S);
				}

				clearStack();
				if (std::dynamic_pointer_cast<MainMenu>(m_currMenuPtr))
					m_running = false;
			}
		}

		if (!m_stack.empty())
		{
			if (std::dynamic_pointer_cast<ChooseReadyMenu>(m_currMenuPtr))
				m_player->debug((std::dynamic_pointer_cast<ChooseReadyMenu>(m_currMenuPtr))->getMap());

			window.clear();
			m_currMenuPtr->update(window);
			m_currMenuPtr->setNames();
			m_currMenuPtr->syncOptionName();
			m_currMenuPtr->draw(window);
			window.display();
		}
		else
			break;

	} while (true);
}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::update(sf::Event& event)
{
	window.setMouseCursorVisible(false);

	window.draw(s1);

	do
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				return;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (m_src->getPlay() == MULTI_PLAYER_P)
					{
						won = 2;
						m_pause = true;
					}
					else
					{
						m_stack.push(m_menus[PAUSEMENU_M]);
						m_currMenuPtr = m_stack.top();
					}
					return;
				}
			}
		}

		elapsed += m_clock.restart();
		if (elapsed > sf::seconds(float(m_src->getDifficulity())))
		{
			elapsed = sf::Time::Zero;
			return;
		}

		m_time.setString(std::to_string(std::abs((int)elapsed.asSeconds() -
			m_src->getDifficulity())));
		window.draw(m_time);
		if (!m_turn)
		{
			window.draw(m_RivalName);
			m_rival->draw(window);
		}
		else
		{
			window.draw(m_PlayerName);
			m_player->display(window);
			m_player->draw(window);
		}
		window.display();
		window.clear();
		window.draw(s1);

		q = (!m_turn) ? m_player->askHit(window, event) :
			m_rival->askHit(window, event);


		if (m_src->getPlay() == MULTI_PLAYER_P && !m_turn)
			std::dynamic_pointer_cast<MultyPlayer>(m_rival)->send(COORDINATE, q);

	} while (q == NO_CHOOSE);

	if (q != PAUSE_CHOOSE)    // user choose to press escape
		elapsed = sf::Time::Zero;

}

//---------------------------------------------------------------------------//
/*
*
*/
void Game::render()
{
	if (m_pause)
		return;
	if (m_turn && q == PAUSE_CHOOSE)
	{
		m_stack.push(m_menus[PAUSEMENU_M]);
		m_currMenuPtr = m_stack.top();
		return;
	}
	window.clear();
	window.draw(s1);


	if (m_src->getPlay() == MULTI_PLAYER_P &&
		elapsed < sf::seconds(float(m_src->getDifficulity())))
	{
		if (m_turn)
		{
			m_ans = m_player->getHit(q);
			m_player->hit(q, m_ans);
			m_rival->setPlayerSign(q, m_ans);
			m_player->playHit(window, q, m_ans);
		}
		else
		{
			m_ans = m_rival->getHit(q);
			m_rival->hit(q, m_ans);
			m_player->setPlayerSign(q, m_ans);
			m_rival->playHit(window, q, m_ans);
		}
		std::dynamic_pointer_cast<MultyPlayer>(m_rival)->send(WHOWON);
		std::dynamic_pointer_cast<MultyPlayer>(m_rival)->receive();
		won = std::dynamic_pointer_cast<MultyPlayer>(m_rival)->getWin();
	}
	else
	{
		(m_turn) ? m_ans = m_player->getHit(q) : m_ans = m_rival->getHit(q);

		if (m_ans)
			counting.at(m_turn)++;

		(m_turn) ? m_player->hit(q, m_ans) : m_rival->hit(q, m_ans);
		(m_turn) ? m_rival->setPlayerSign(q, m_ans) : m_player->setPlayerSign(q, m_ans);
		(m_turn) ? m_player->playHit(window, q, m_ans) : m_rival->playHit(window, q, m_ans);
		if (counting.at(0) == WON)
			won = 1;
		else if (counting.at(1) == WON)
			won = 2;
	}
	window.draw(s1);
	window.draw(m_time);

	if (!m_turn)
	{
		m_rival->draw(window);
		window.draw(m_RivalName);
	}
	else
	{
		window.draw(m_PlayerName);
		m_player->display(window);
		m_player->draw(window);
	}
}
//---------------------------------------------------------------------------//
/*
 *
 */
void Game::runChat(sf::RenderWindow & window, std::string name)
{
	Chat chat(name);
	sf::Socket::Status status = chat.connect(m_src->IpNPort(0), stoi(m_src->IpNPort(2)));

	if (status != sf::Socket::Done)
	{
		DisplayResourceNAMessageBox(L"Connection FAILED", L"Sorry we couldn't" 
			" connect to Chat");
		return;
	}
	chat.send(NAME, name);

	window.create(sf::VideoMode(450, 550), "", sf::Style::Close);
	ChatBox chatBox(sf::Vector2f(50, 100), 350, 5, 20, 15, chatFont);
	chatBox.setFillColor(sf::Color::Black);
	chatBox.setOutlineColor(sf::Color::Red);
	chatBox.setCharColor(sf::Color::White);
	chatBox.connectOnEnter([&](const std::string & s) {chat.send(GMSG, s); });

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			chatBox.handleEvent(event);

		std::string toBePushed;

		sf::Socket::Status status = chat.receive(toBePushed);
		if (status == sf::Socket::Done)
			chatBox.push(toBePushed);

		else if (status == sf::Socket::Disconnected)
		{
			chatBox.push("You have been disconnected");
			chatBox.draw(window);
			window.display();
			m_isConnected = false;
			return;
		}
		if (!m_isConnected)
		{
			won = 1;
			cWindow.close();
		}

		window.clear();
		chatBox.update();
		chatBox.draw(window);
		window.display();
	}

}