#include "SrcManager.h"
#include <fstream>


SrcManager::SrcManager() :m_lang(EN_L), m_mod(M2D_M), m_play(MULTI_PLAYER_P)
, m_difficulity(EASY_D)
{
	setLanguage(R"(data\Language\)");
	setFonts(R"(data\Fonts\)");
	setTexts();
	OpenFile();
	setBoards(R"(data\Boards\)");
	setTexture(R"(data\Images\Buttons\)", m_ButtonVec, NUM_OF_BUTTONS);
	setTexture(R"(data\Images\Ships\)", m_ShipVec, NUM_OF_SHIPS);
	setTexture(R"(data\Images\Effects\)", m_EffectVec, NUM_OF_EFFECTS);
	setTexture(R"(data\Images\Backgrounds\)", m_BackgroundVec, NUM_OF_BACKGROUND);
	setTexture(R"(data\Images\Previews\)", m_PreviewVec, NUM_OF_BOARDS);

	setEffects();
}

/*
*	this function return one pointer to this class
*/

std::shared_ptr<SrcManager> SrcManager::instance()
{
	static std::shared_ptr<SrcManager> m_src(new SrcManager());
	return m_src;
}
/*
*	this function return Effect from the vector
*/

std::shared_ptr<sf::Texture> SrcManager::getEffect(int i) 
{
	try {
		return std::make_shared<sf::Texture>(m_EffectVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
/*
*	this function return Button from the vector
*/

std::shared_ptr<sf::Texture> SrcManager::getButtons(int i)
{
	try {
		return std::make_shared<sf::Texture>(m_ButtonVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/*
*	this function return Preview from the vector
*/

std::shared_ptr<sf::Texture> SrcManager::getPreviews(int i)
{
	try
	{
		return std::make_shared<sf::Texture>(m_PreviewVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/*
*	this function return Font from the vector
*/

std::shared_ptr<sf::Font> SrcManager::getFont(int i)
{
	try
	{
		return std::make_shared<sf::Font>(m_FontVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/*
*	this function return Background from the vector
*/

std::shared_ptr<sf::Texture> SrcManager::getBackgound(int i)
{
	try
	{
		return std::make_shared<sf::Texture>(m_BackgroundVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
/*
*	this function return Ship from the vector
*/

std::shared_ptr<sf::Texture> SrcManager::getShip(int i)
{
	try
	{
		return std::make_shared<sf::Texture>(m_ShipVec.at(i));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/*
*	this function return Board from the vector
*/

std::shared_ptr<Board> SrcManager::getBoard(int i)
{
	try
	{
		return m_board.at(i);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

/*
*	this function set Sprite Object to there vector
*/

void SrcManager::OpenFile()
{
	std::ifstream file;
	std::string tmp;

	try
	{
		file.open(R"(data\server.txt)");
		if (!file.is_open())
			throw std::runtime_error("Cannot open file for connect with GameServer\n");
	}
	catch (std::exception&)
	{
		exit(EXIT_FAILURE);
	}

	for (; getline(file, tmp);)
		m_Server.emplace_back(std::move(tmp));
	file.close();
}

void SrcManager::setTexture(std::string path, std::vector<sf::Texture> &vector, int size)
{
	for (int i = 0; i < size; ++i)
	{
		sf::Texture tmp;
		tmp.loadFromFile(path + std::to_string(i));
		vector.emplace_back(std::move(tmp));
	}
}

/*
*	this function set Board Object to his vector
*/

void SrcManager::setBoards(std::string path)
{
	for (int i = 0; i < NUM_OF_BOARDS; ++i)
		m_board.emplace_back(std::move(new Board(path + std::to_string(i))));
}

/*
*	this function set Fonts Object to his vector
*/

void SrcManager::setFonts(std::string path)
{
	for (int i = 0; i < NUM_OF_FONTS; ++i)
	{
		sf::Font tmp;
		tmp.loadFromFile(path + std::to_string(i) + ".ttf");
		m_FontVec.emplace_back(std::move(tmp));
	}
}

/*
*	this function set Language to his vector
*/

void SrcManager::setLanguage(std::string path)
{
	for (int i = 0; i < NUM_OF_LANGUAGES; ++i)
	{
		Language tmp(path + std::to_string(i) + ".txt");
		m_Language.emplace_back(std::move(tmp));
	}
}
/*
*	this function set the texts of the Game
*/

void SrcManager::setTexts()
{
	for (size_t i = 0; i < m_Language.at(EN_L).getDicSize(); ++i)
	{
		sf::Text tmp;
		tmp.setFillColor(sf::Color::White);
		m_Texts.emplace_back(std::move(tmp));
	}
}

void SrcManager::setEffects()
{
	static sf::Texture  aaa = *(getEffect(4));

	// set up the animation
	Animation walkingAnimationDown;
	walkingAnimationDown.setSpriteSheet(std::move(aaa));
	for (int i = 0; i < 10; i++)
		walkingAnimationDown.addFrame(sf::IntRect(320 * i, 0, 320, 220));

	m_EffectAnim = (walkingAnimationDown);
}


std::shared_ptr<sf::Text> SrcManager::getText(int place, int lang)
{
	std::wstring s = m_Language.at(lang).getString(place);
	m_Texts.at(place).setString(s);
	m_Texts.at(place).setFont(m_FontVec.at(lang));
	return std::make_shared<sf::Text>(m_Texts.at(place));
}


std::wstring SrcManager::getString(int place, int lang)
{
	return m_Language.at(lang).getString(place);
}


void SrcManager::setLang(int i)
{
	m_lang = i;
}


int SrcManager::getLang()
{
	return m_lang;
}


void SrcManager::setMod(int mod)
{
	m_mod = mod;
}


int SrcManager::getMod()
{
	return m_mod;
}


std::string SrcManager::IpNPort(int i)
{
	try
	{
		return m_Server.at(i);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}


int SrcManager::getPlay()
{
	return m_play;
}


void SrcManager::setPlay(int num)
{
	m_play = num;
}


Difficulity_t SrcManager::getDifficulity()
{
	return m_difficulity;
}


void SrcManager::setDifficulity(Difficulity_t num)
{
	m_difficulity = num;
}


std::shared_ptr<Animation> SrcManager::getEffects() const
{
	return std::make_shared<Animation>(m_EffectAnim);
}
