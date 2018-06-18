#include "Player.h"
#include "AudioManager.h"


Player::Player(std::string name) :
	m_name(name),
	m_src(SrcManager::instance()),
	m_frontTexture(std::move(*m_src->getButtons(0))),
	t1(std::move(*m_src->getEffect(1))),
	t2(std::move(*m_src->getEffect(2)))
{
	srand(unsigned(time(nullptr)));
	init();
}


sf::Vector2i Player::getPlace(const sf::Vector2i &src)
{
	for (int i = 0; i < M_ROW; i++)
		for (int j = 0; j < M_COL; j++)
			if (m_myHitMaps[m_src->getMod()][i][j].getGlobalBounds().contains(sf::Vector2f(src)))
				return sf::Vector2i(i, j);

	return { -1,-1 };
}

sf::Vector2i Player::getPlace(int x, int y)
{
	try
	{
		map_places[m_src->getMod()].at(x).at(y);
		return map_places[m_src->getMod()][x][y];
	}
	catch (std::exception&)
	{
		return { 1000,1000 };
	}
}

short Player::getPlayerSign(int x, int y) const
{
	return m_PlayerSign.at(x).at(y);
}

void Player::setPlayerSign(sf::Vector2i pos, bool ans)
{
	if (pos.x >= 0 && pos.x <= 9 &&
		pos.y >= 0 && pos.y <= 9)
		(ans) ? m_PlayerSign.at(pos.x).at(pos.y) = 2 :
		m_PlayerSign.at(pos.x).at(pos.y) = 1;
}

bool Player::inRange(const sf::Vector2f &my)
{
	sf::Vector2f topCorner = { 150.f,162.f },
		bottomCorner = { 1020.f,650.f };

	return (my.x >= topCorner.x && my.y >= topCorner.y) &&
		(my.x <= bottomCorner.x && my.y <= bottomCorner.y);
}

void Player::playHit(sf::RenderWindow & window, sf::Vector2i pos, bool ans)
{
	sf::Clock frameClock;
	sf::Texture bgTxture = (*(m_src->getBackgound(2)));
	sf::Sprite bg(bgTxture);
	sf::Vector2f animatedSpritePos;
	
	if (!ans && pos != sf::Vector2i(-1, -1))
		AudioManager::instance()->playSound(PLOOP_S);
	if (ans && pos != sf::Vector2i(-1, -1))
	{
		AudioManager::instance()->playSound(EXPLOSION_S);
		Animation walkingAnimationDown = *(m_src->getEffects());
		AnimatedSprite animatedSprite(sf::seconds(3.0), false, false);

		animatedSprite.scale(0.4f, 0.4f);
		animatedSpritePos = sf::Vector2f(map_places[m_src->getMod()][pos.x][pos.y]) - sf::Vector2f(45, 70);
		animatedSprite.setPosition(animatedSpritePos);

		static sf::Time frameTime = sf::seconds(0.f);
		while (frameTime.asSeconds() < 1.f)
		{
			frameTime += frameClock.restart();
			animatedSprite.play(walkingAnimationDown);
			animatedSprite.update(frameTime);    // update AnimatedSprite

			// draw
			window.clear();
			window.draw(bg);
			draw(window);
			window.draw(animatedSprite);
			window.display();
		}
		frameTime = sf::seconds(0.f);
	}
}

void Player::display(sf::RenderWindow & window)
{
	m_myMaps->display(window);
}

bool Player::getHit(sf::Vector2i pos)
{
	try {
		if (pos == sf::Vector2i(-1, -1))
			return false;
		return m_myMaps->getSign(pos.x, pos.y) != '-';
	}
	catch (std::exception) { return false; }
}

void Player::init()
{
	m_sign = {};
	m_PlayerSign = {};
	m_myHitMaps[M3D_M].clear();
	m_myHitMaps[M2D_M].clear();

	std::array<std::vector<sf::Sprite3d>, 2> tempRow;
	std::vector<short> tmp;

	for (int i = 0; i < M_ROW; i++)
	{
		for (int j = 0; j < M_COL; j++)
		{
			map_places[M2D_M].at(i).at(j) = { i * 60 + 350, j * 60 + 90 };
			map_places[M3D_M].at(i).at(j) = { i * 70 + 450 - j * 20, j * 40 + 190 + i * 10 };
			sf::Sprite3d s2d = (std::move(m_frontTexture), std::move(m_frontTexture));
			sf::Sprite3d s3d(s2d);
			s2d.setPosition(sf::Vector2f(map_places[M2D_M][i][j]));
			s3d.setPosition(sf::Vector2f(map_places[M3D_M][i][j]));
			s3d.setRotation({ 60.0f,  -20.0f, 10.0f });
			s3d.scale(sf::Vector2f(2, 2));
			s2d.scale(1.75f, 1.75f);
			tmp.emplace_back(0);
			tempRow[M2D_M].emplace_back(std::move(s2d));
			tempRow[M3D_M].emplace_back(std::move(s3d));
		}
		m_PlayerSign.emplace_back(tmp);
		m_sign.emplace_back(std::move(tmp));
		m_myHitMaps[M2D_M].emplace_back(std::move(tempRow[M2D_M]));
		m_myHitMaps[M3D_M].emplace_back(std::move(tempRow[M3D_M]));
	}
}

void Player::debug(int num)
{
	for (int i = 0; i < M_ROW; i++)
		for (int j = 0; j < M_COL; j++)
		{
			m_myMaps->setSign(i, j, (*m_src->getBoard(num)).show(i, j).first);
			m_myMaps->setSize(i, j, (*m_src->getBoard(num)).show(i, j).second);
		}
}

void Player::resetAll()
{
}

char Player::getSign(int i, int j) const
{
	return m_myMaps->getSign(i, j);
}

void Player::hit(sf::Vector2i pos, bool hit)
{
	try {
		if (pos == sf::Vector2i(-1, -1))
			return;

		if (!hit)
		{
			m_myHitMaps[m_src->getMod()].at(pos.x).at(pos.y).setTexture(t1);
			m_sign.at(pos.x).at(pos.y) = 1;
		}
		else
		{
			m_myHitMaps[m_src->getMod()].at(pos.x).at(pos.y).setTexture(t2);
			m_sign.at(pos.x).at(pos.y) = 2;
		}
	}
	catch (std::exception) {}
}

void Player::setName(const std::string &newName)
{
	m_name = newName;
}

std::string Player::getName() const
{
	return m_name;
}
