#include "AudioManager.h"
#include <iostream>

static const std::string SFX_PATH = "data/Sounds/";

//---------------------------------------------------------------------------//
/*
*
*/
AudioManager::AudioManager()
{
	setSoundBuffs(SFX_PATH);
	setSounds();
	setMusics();
}

//---------------------------------------------------------------------------//
/*
*	this function return one pointer to this class
*/

std::shared_ptr<AudioManager> AudioManager::instance()
{
	static std::shared_ptr<AudioManager> m_src(new AudioManager());
	return m_src;
}

void AudioManager::reMute()
{
	m_mute = !m_mute;
	muteAll();
}

bool AudioManager::isMute() const
{
	return m_mute;
}

void AudioManager::setSounds()
{
	for (const auto& buff : m_soundBuffs)
	{
		sf::Sound sound;
		sound.setBuffer(*buff);
		m_sounds.emplace_back(std::move(sound));
	}
}


void AudioManager::setMusics()
{
	m_musics.resize(5);

	for (auto& music : m_musics)
		music = std::move(std::make_unique<sf::Music>());

	m_musics[MAINMENU_S]->openFromFile(SFX_PATH + "main menu.ogg");
	m_musics[MAPEDITOR_S]->openFromFile(SFX_PATH + "map editor.ogg");
	m_musics[GAME_S]->openFromFile(SFX_PATH + "game.ogg");
	m_musics[WIN_S]->openFromFile(SFX_PATH + "you win.ogg");
	m_musics[LOST_S]->openFromFile(SFX_PATH + "you lost.ogg");
}



//---------------------------------------------------------------------------//
void AudioManager::playSound(int x, bool playInLoop)
{
	try {
			(m_sounds.at(x)).play();
		(m_sounds.at(x)).setLoop(playInLoop);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}


void AudioManager::pauseSound(int x)
{
	try {

		(m_sounds.at(x)).pause();
		(m_sounds.at(x)).setLoop(false); // stop if looped
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void AudioManager::playMusic(int x, bool playInLoop)
{
	try {
		(m_musics.at(x))->play();
		(m_musics.at(x))->setLoop(playInLoop); // stop if looped
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void AudioManager::stopMusic(int x)
{
	try {
		(m_musics.at(x))->stop();

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void AudioManager::pauseMusic(int x)
{
	try {
		(m_musics.at(x))->pause();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
//---------------------------------------------------------------------------//
/*
*
*/
void AudioManager::setSoundBuffs(std::string path)
{
	int i = 0;
	while (true)
	{
		auto tmp = std::make_unique<sf::SoundBuffer>();
		if (!tmp->loadFromFile(path + std::to_string(i) + ".ogg"))
			return;
		m_soundBuffs.emplace_back(std::move(tmp));
		i++;
	}
}

void AudioManager::muteAll()
{
	for (auto& music : m_musics)
		(m_mute) ? music->setVolume(0) : music->setVolume(100);
}
