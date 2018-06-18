#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "Language.h"
#include "E_includes/AnimatedSprite.hpp"
#include <memory>

class SrcManager
{
public:
	// function to build one Singleton
	static std::shared_ptr<SrcManager> instance();
	std::shared_ptr<sf::Texture> getButtons(int); // return Button Texture Object
	std::shared_ptr<sf::Texture> getPreviews(int); // return Previews Texture Object
	std::shared_ptr<sf::Texture> getBackgound(int); //// return Background Texture Object
	std::shared_ptr<sf::Texture> getShip(int); //// return Ship Texture Object
	std::shared_ptr<sf::Texture> getEffect(int); //// return Effect Texture Object
	std::shared_ptr<sf::Font> getFont(int); //// return Font Object
	std::shared_ptr<Board> getBoard(int); // return pointer to Board Object
	std::shared_ptr<sf::Text> getText(int place, int lang = EN_L);
	std::wstring getString(int place, int lang = EN_L);

	void setLang(int);
	int getLang();

	void setMod(int);
	int getMod();
	std::string IpNPort(int i);
	int getPlay();
	void setPlay(int);

	Difficulity_t getDifficulity();
	void setDifficulity(Difficulity_t);

	std::shared_ptr<Animation> getEffects() const;

private:

	SrcManager();
	SrcManager(const SrcManager&) = delete;
	SrcManager& operator=(SrcManager&) = delete;
	void OpenFile();
	void setTexture(std::string, std::vector<sf::Texture>&, int);
	void setBoards(std::string); // load Boards from files
	void setFonts(std::string); // load Fonts from files
	void setLanguage(std::string); // load Language from files
	void setTexts();
	void setEffects();

	static std::shared_ptr<SrcManager> m_src; // Pointer to this class

	int m_lang;
	int m_mod;
	int m_play;
	Difficulity_t m_difficulity;

	/// The DataBase
	std::vector<sf::Texture> m_ButtonVec; // Button Vector
	std::vector<sf::Texture> m_ShipVec; // Ships Vector
	std::vector<sf::Texture> m_EffectVec; // Effects Vector
	std::vector<sf::Texture> m_BackgroundVec; // Background Vector
	std::vector<sf::Texture> m_PreviewVec; // Preview image Vector
	std::vector<sf::Font> m_FontVec; // fonts Vector
	std::vector<std::shared_ptr<Board>> m_board; // Board Object Vector
	std::vector<Language> m_Language; // Language Object Vector
	std::vector<sf::Text> m_Texts; // Text Object Vector
	std::vector<std::string> m_Server;
	Animation m_EffectAnim;
};