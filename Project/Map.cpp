#include "Map.h"
#include "ShipFactory.h"


Map::Map()
	:m_src(SrcManager::instance()),
	m_frontTexture(std::move(*m_src->getButtons(0))),
	m_backTexture(*m_src->getButtons(1))
{
	m_leftBig = LEFT_BIG;
	m_leftSmall = LEFT_SMALL;
	m_leftMiddle = LEFT_NIDDLE;
	cleanMap();

	for (int i = 0; i < M_ROW; i++)
	{
		std::array<std::vector<sf::Sprite3d>, 2> tempRow;
		for (int j = 0; j < M_COL; j++)
		{
			map_places[M2D_M].at(i).at(j) = { i * 60 + 350, j * 60 + 90 };
			map_places[M3D_M].at(i).at(j) = { i * 70 + 450 - j * 20, j * 40 + 190 + i * 10 };
			sf::Sprite3d s2d(std::move(m_frontTexture), std::move(m_backTexture));
			sf::Sprite3d s3d(s2d);
			s3d.setPosition(sf::Vector2f(map_places[M3D_M][i][j]));
			s2d.setPosition(sf::Vector2f(map_places[M2D_M][i][j]));
			s3d.setRotation({ 60.0f,  -20.0f, 10.0f });
			s3d.scale(sf::Vector2f(2, 2));
			s2d.scale(1.75f, 1.75f);
			tempRow[M3D_M].emplace_back(std::move(s3d));
			tempRow[M2D_M].emplace_back(std::move(s2d));
		}
		textureMap[M3D_M].emplace_back(std::move(tempRow[M3D_M]));
		textureMap[M2D_M].emplace_back(std::move(tempRow[M2D_M]));
	}
}

void Map::display(sf::RenderWindow & _window)
{
	std::shared_ptr<Ship> ship;
	for (int i = 0; i < M_ROW; i++)
	{
		for (int j = 0; j < M_COL; j++)
		{
			sf::Vector2i position = map_places[m_src->getMod()][i][j];
			char sign = Map::getSign(i, j);
			int shipSize = getSize(i, j);
			if (sign == '-')
				_window.draw(textureMap[m_src->getMod()][i][j]);
			else
			{
				bool setRotate;
				if (sign == '^' || sign == '<')
				{
					setRotate = (sign == '^') ? true : false;

					ship = ShipFactory::create("Ship" + std::to_string(shipSize), position, setRotate);

					try {
						if (m_src->getMod() == M2D_M)
							ship->draw2D(_window);
						else if ((shipSize > 0))
							ship->draw(_window);
					}
					catch (std::exception&)
					{
						;
					}
				}
			}
		}
	}
}

bool Map::inRange(const sf::Vector2f & my)
{
	sf::Vector2f topCorner = sf::Vector2f(150.f, 162.f);
	sf::Vector2f  bottomCorner = sf::Vector2f(1020.f, 650.f);
	return (my.x >= topCorner.x && my.y >= topCorner.y) &&
		(my.x <= bottomCorner.x && my.y <= bottomCorner.y);
}

void Map::remove(const sf::Vector2i &_place, const bool dir, const int size)
{
	char _s = (dir) ? '^' : '<';
	try
	{
		if (getSign(_place.x, _place.y) == '<')
			for (int i = 0; i < size && (_place.x + i) >= 0; i++)
			{
				setSign(_place.x + i, _place.y, '-');
				setSize(_place.x + i, _place.y, 0);
			}

		else if (getSign(_place.x, _place.y) == '^')
			for (int i = 0; i < size && (_place.y + i) >= 0; i++)
			{
				setSign(_place.x, _place.y + i, '-');
				setSize(_place.x, _place.y + i, 0);
			}

		else if (getSign(_place.x, _place.y) == '#')
		{
			int i;
			if (getSign(_place.x - 1, _place.y) == '-')
			{
				for (i = 1; i < size && (_place.y - i) >= 0; i++)
					if (getSign(_place.x, _place.y - i) == '^')
						break;
				return remove({ _place.x, _place.y - i }, dir, size);
			}
			else
			{
				for (i = 1; i < size && (_place.x - i) >= 0; i++)
					if (getSign(_place.x - i, _place.y) == '<')
						break;
				return remove({ _place.x - i, _place.y }, dir, size);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return;
	}
}

void Map::cleanMap()
{
	for (int i = 0; i < M_ROW; i++)
		for (int j = 0; j < M_COL; j++)
			map2[i][j].m_sign = '-';
}

sf::Vector2i Map::getPlace(int x, int y) const
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

bool Map::canPut(const sf::Vector2i &_place, const bool dir, const int size) const
{
	std::string check;
	try
	{
		if (getSign(_place.x, _place.y) != '-')
			return false;

		if (!dir)
		{
			if (_place.x + size > 10)
				return false;
			for (int i = 1; i < size; i++)
				check += getSign(_place.x + i, _place.y);
		}
		else
		{
			if (_place.y + size > 10)
				return false;
			for (int i = 1; i < size; i++)
				check += getSign(_place.x, _place.y + i);
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (!size) ? false : check == std::string(size - 1, '-');
}

void Map::draw(const sf::Vector2i &_place, const bool dir, const int size)
{
	char _s = (dir) ? '^' : '<';
	try
	{
		std::string check;
		if (canPut(_place, dir, size))
		{
			if (_s == '<')
			{
				setType(_place.x, _place.y, { false, size });
				setSign(_place.x, _place.y, _s);
				for (int i = 1; i < size; i++)
					setSign(_place.x + i, _place.y, '#');
				for (int i = 0; i < size; ++i)
					setSize(_place.x + i, _place.y, size);
			}
			else if (_s == '^')
			{
				setType(_place.x, _place.y, { true, size });
				setSign(_place.x, _place.y, _s);
				for (int i = 1; i < size; i++)
					setSign(_place.x, _place.y + i, '#');
				for (int i = 0; i < size; ++i)
					setSize(_place.x, _place.y + i, size);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
}


bool Map::allOK()
{
	return m_leftBig == 0 && m_leftMiddle == 0 && m_leftSmall == 0;
}

char Map::getSign(int x, int y) const
{
	try
	{
		map2.at(x).at(y).m_sign;
		return map2.at(x).at(y).m_sign;
	}
	catch (std::exception&)
	{
		return '-';
	}
}

int Map::getSize(int x, int y) const
{
	try
	{
		map2.at(x).at(y).m_size;
		return map2[x][y].m_size;
	}
	catch (std::exception&)
	{
		return 0;
	}
}


void Map::setSize(int i, int j, int newSize)
{
	map2[i][j].m_size = newSize;
}

void Map::setSign(int i, int j, int newSign)
{
	map2[i][j].m_sign = newSign;
}

void Map::setType(int i, int j, std::pair<bool, int> newType)
{
	map2[i][j].m_type = newType;
}


void Map::resetAllSizes()
{
	m_leftMiddle = LEFT_NIDDLE;
	m_leftSmall = LEFT_SMALL;
	m_leftBig = LEFT_BIG;
}

void Map::updateMiddleLeft(int x)
{
	m_leftMiddle += x;
}

void Map::updateSmallLeft(int x)
{
	m_leftSmall += x;
}

void Map::updateBigLeft(int x)
{

	m_leftBig += x;
}

int Map::getMiddleLeft() const
{
	return m_leftMiddle;
}

int Map::getSmallLeft() const
{
	return m_leftSmall;
}

int Map::getBigLeft() const
{
	return m_leftBig;
}