#include "SinglePlayer.h"
#include "Map.h"



SinglePlayer::SinglePlayer(std::string name) :
	Player(name)
{
	m_myMaps = std::make_shared<Map>();
}

sf::Vector2i SinglePlayer::askHit(sf::RenderWindow& window, sf::Event& event)
{
	sf::Vector2i tmp = std::move(getPlace(sf::Mouse::getPosition(window)));
	if (tmp.x < 0 || tmp.x > 9 ||
		tmp.y < 0 || tmp.y > 9)
		return { -1,-1 };

	sf::Vector2i MousePos = std::move(tmp);
	while (window.pollEvent(event)) 
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(EXIT_FAILURE);
		}
	}

	sf::sleep(sf::seconds(0.1f));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (getPlayerSign(MousePos.x, MousePos.y) == 0)
			return MousePos;
	}
	return { -1,-1 };
}


void SinglePlayer::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < M_ROW; i++)
		for (int j = 0; j < M_COL; j++)
			if (m_sign.at(i).at(j) != 0)
				window.draw(m_myHitMaps[m_src->getMod()].at(i).at(j));
}