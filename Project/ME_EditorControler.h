#pragma once
#include "E_includes/AnimatedSprite.hpp"
#include "ME_Editor.h"


class EditorControler
{
public:
	static std::shared_ptr<EditorControler> instance();
	void openAsk(sf::RenderWindow &window);
	void openWin1(sf::RenderWindow &window);
	void run(sf::RenderWindow& window);
	
	~EditorControler() = default;
	std::shared_ptr<Editor> getEditor() { return m_gameEditor; }
private:
	EditorControler();
	EditorControler(const EditorControler&) = delete;
	EditorControler& operator=(EditorControler&) = delete;
	std::shared_ptr<SrcManager> m_src;
	std::shared_ptr<Editor> m_gameEditor;

	sf::Texture m_txture2D;
	sf::Texture m_txture3D;
	sf::Sprite m_bg2D;
	Animation m_bg3D;
	
	bool m_running;
	bool m_rot;
};