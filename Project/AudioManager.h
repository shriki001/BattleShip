#pragma once
#include <SFML/Audio.hpp> // reload from settings.h
#include "settings.h"
#include <memory>


class AudioManager
{
public:

	// function to build one Singleton
	static std::shared_ptr<AudioManager> instance();
	void setSounds();
	void setMusics();

	void playSound(int x, bool playInLoop = false);
	void pauseSound(int x);

	void playMusic(int x, bool playInLoop = true);
	void stopMusic(int x);
	void pauseMusic(int x);
	void reMute();

	bool isMute() const;

private:
	AudioManager();
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(AudioManager&) = delete;
	static std::shared_ptr<AudioManager> m_src; // Pointer to this class

	// databases' setters
	void setSoundBuffs(std::string path/*std::vector<sf::SoundBuffer> &vector*/);

	/***   The DataBases   ***/
	std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffs;   // SOINDS' vector
	std::vector<sf::Sound> m_sounds;
	std::vector<std::unique_ptr<sf::Music>> m_musics;

	bool m_mute;
	void muteAll();
};