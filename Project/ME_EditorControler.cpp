#include "ME_EditorControler.h"
#include "ME_Editor2D.h"
#include "ME_Editor3D.h"


std::shared_ptr<EditorControler> EditorControler::instance()
{
	static std::shared_ptr<EditorControler> m_Editor(new EditorControler());
	return m_Editor;
}

EditorControler::EditorControler()
	: m_running(true), m_rot(false), m_src(SrcManager::instance()), m_txture3D(*m_src->getBackgound(0)),
	m_txture2D(*m_src->getBackgound(8)), m_bg2D(m_txture2D)
{
	m_bg3D.setSpriteSheet(m_txture3D);
	for (int i = 0; i < 20; i++)
		m_bg3D.addFrame(sf::IntRect(800 * i, 0, 800, 450));


}

void EditorControler::run(sf::RenderWindow& window)
{
	(m_src->getMod() == M2D_M) ?
		m_gameEditor = std::make_shared<Editor2D>() :
		m_gameEditor = std::make_shared<Editor3D>();

	m_running = true;
	while (m_running)
		openWin1(window);
} 

void EditorControler::openWin1(sf::RenderWindow &window)
{
	sf::Event event;
	sf::Vector2f Acurr_pos;

	////////////////////////////////////////////////////////////////////////////
	sf::Clock frameClock;
	AnimatedSprite animatedSprite(sf::seconds(0.05f), true, false);
	animatedSprite.scale(2, 2);
	////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				exit(EXIT_FAILURE);
			}
			if (event.type == sf::Event::MouseButtonPressed &&
				event.key.code == sf::Mouse::Right)
				m_rot = !m_rot;
		}

		////////////////////////////////////////////////////////////////////////
		sf::Time frameTime = frameClock.restart();
		animatedSprite.play(m_bg3D);
		animatedSprite.update(frameTime);
		////////////////////////////////////////////////////////////////////////

		(m_src->getMod() == M2D_M) ? window.draw(m_bg2D) : window.draw(animatedSprite);

		Acurr_pos = ((sf::Vector2f) sf::Mouse::getPosition(window));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_gameEditor->PlayButton((sf::Vector2f)Acurr_pos, m_rot);
			if (m_gameEditor->allGood(Acurr_pos))
			{
				m_running = false;
				return;
			}
			if (m_gameEditor->reset())
			{
				m_gameEditor->drawE(window);
				window.display();
				return;
			}
			m_gameEditor->drawE(window);
		}
		else
		{
			m_gameEditor->ShowButtonInfo((sf::Vector2f)Acurr_pos);
			m_gameEditor->drawE(window);
			m_gameEditor->ShowButton((sf::Vector2f)Acurr_pos, window, m_rot);
		}
		window.display();
		window.clear();
	}
}