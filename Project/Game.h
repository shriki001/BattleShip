#pragma once
#include "Map.h"
#include "Player.h"
#include "MainMenu.h"
#include "ME_EditorControler.h"
#include "AudioManager.h"
#include <stack>

class Game
{
public:
	Game();
	void update(sf::Event& event);
	void render();
	void run();
	void runChat(sf::RenderWindow & window, std::string name);
	void initMenus();
	void clearStack();
	void resetGame();
	static void setName(const std::string&);
	static std::string getName();
	~Game() = default;

private:
	std::shared_ptr<SrcManager> m_src;
	std::shared_ptr<AudioManager> m_audioSrc;
	std::shared_ptr<EditorControler> editor;
	std::unique_ptr<Player> m_player;
	std::shared_ptr<Player> m_rival;	

	sf::Text m_PlayerName;
	sf::Text m_RivalName;
	static std::string name;
	sf::Text m_time;
	sf::Font font;
	sf::Font chatFont;
	sf::Clock m_clock;
	sf::Vector2i q;
	sf::Texture m_bg;
	sf::Sprite s1;

	static sf::Time elapsed;

	bool m_ans;
	bool m_turn;
	void handleMenu();

	/** game's menus **/
	std::vector<std::shared_ptr<Menu>> m_menus;
	std::stack<std::shared_ptr<Menu>> m_stack;

	int m_lastMenu = -1;
	bool m_startLevel = true;

	std::shared_ptr<Menu> m_currMenuPtr;
	short won = 0;
	bool m_inEditor = false;
	bool m_isConnected = true;
	sf::RenderWindow cWindow;
	bool m_pause = false;
	static bool first;
	std::array<short, 2> counting;
	bool m_running = true;
};