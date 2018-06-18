#include "AIRIival.h"


static int randWait = rand() % (SrcManager::instance()->getDifficulity() - 5) + 3;


static std::array<sf::Vector2i, 8> dir
{ sf::Vector2i(0,1),sf::Vector2i(0,-1),sf::Vector2i(1,0),sf::Vector2i(-1,0),
sf::Vector2i(1,1),sf::Vector2i(-1,-1),sf::Vector2i(-1,1),sf::Vector2i(1,-1) };

AiRival::AiRival(std::string name, std::shared_ptr<Map> map) : Player(name)
{
	m_PlayerMap = map;
	m_myMaps = std::make_unique<Map>();
	debug(rand() % 4);
}

void AiRival::draw(sf::RenderWindow & window)
{
	sf::Texture frontTexture;
	frontTexture = *m_src->getEffect(0);

	auto currPos = ((sf::Vector2i) sf::Mouse::getPosition(window));
	bool showCursor = (inRange((sf::Vector2f)currPos)) ? false : true;

	window.setMouseCursorVisible(showCursor);

	sf::Sprite3d s1(std::move(frontTexture), std::move(frontTexture));
	sf::Vector2i z = getPlace(currPos);
	s1.setPosition((sf::Vector2f) getPlace(z.x, z.y));

	if (m_src->getMod() == M3D_M)
		s1.setRotation({ 60.0f,  -20.0f, 10.0f });
	(m_src->getMod() == M3D_M) ? s1.scale(sf::Vector2f(2, 2)) :
		s1.scale(1.75f, 1.75f);

	for (int i = 0; i < M_ROW; i++)
		for (int j = 0; j < M_COL; j++)
			window.draw(m_myHitMaps[m_src->getMod()].at(i).at(j));
	window.draw(s1);
}


sf::Vector2i AiRival::askHit(sf::RenderWindow& window, sf::Event& event)
{
	static bool first = true;
	sf::Vector2i MousePos(-1, -1);
	switch (m_src->getDifficulity())
	{
	case MEDIUM_D:
		MousePos = playMedium();
		break;
	case IMPOSSIBLE_D:
		MousePos = playHard();
		break;
	case EASY_D:
		MousePos = { rand() % 9, rand() % 9 };
		break;
	}

	if (first)		// start clock from first entrance into AI's turn
	{
		first = false;
		m_clock.restart();
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(EXIT_FAILURE);
		}


		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				return { -2,-2 };		// code for knowing that escaped has been pressed
			}
		}

	}
	if (m_clock.getElapsedTime() > sf::seconds(float(randWait)))
	{
		sf::Time startTime = sf::Time::Zero;
		first = true;
		if (m_src->getDifficulity() != IMPOSSIBLE_D)
			randWait = rand() % (m_src->getDifficulity() - 5) + 3;
		else randWait = rand() % m_src->getDifficulity();
		if (m_PlayerSign.at(MousePos.x).at(MousePos.y) == 0)
			return MousePos;
	}
	return { -1,-1 };
}


sf::Vector2i AiRival::playMedium()
{
	static int i = 0, j = 0;
	if (i > 8)
		i = 1;
	if (j > 8)
		j = 1;
	static sf::Vector2i t;
	t = { ++i + dir[rand() % 8].x, ++j + dir[rand() % 8].y };
	if (t.x < 0 || t.y < 0 ||
		t.x > 9 || t.y > 9)
		t = { rand() % 9, rand() % 9 };
	return t;
}

sf::Vector2i AiRival::playHard()
{
	static bool randomHit = true;
	sf::Vector2i target;

	do {
		target = { rand() % 9, rand() % 9 };
		if (m_PlayerMap->getSign(target.x, target.y) != '-')
			break;
	} while (true);

	if (randomHit)
	{
		target += dir[rand() % 8];
		if (target.x < 0 || target.y < 0 ||
			target.x > 9 || target.y > 9)
			target = { rand() % 9, rand() % 9 };
	}
	randomHit = !randomHit;
	return target;
}

void AiRival::addLostTime(sf::Time toAdd)
{
	randWait += int(toAdd.asSeconds());
}
