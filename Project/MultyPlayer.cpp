#include "MultyPlayer.h"
#include <fstream>
#include "utilities.h"


MultyPlayer::MultyPlayer(std::string name) :Player(name), m_canPlay(false)
{
	sf::Socket::Status status;
	status = connect(m_src->IpNPort(0), stoi(m_src->IpNPort(1)));
	if (status != sf::Socket::Done)
	{
		DisplayResourceNAMessageBox(L"Connection FAILED", L"Sorry we couldn't connect\n"
			"try again later\n");
		haveConnection = false;
	}
	else
	{
		haveConnection = true;
		send(INITIAL_NAME_DATA, name);
		receive();
	}
}


sf::Vector2i MultyPlayer::askHit(sf::RenderWindow & window, sf::Event& event)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(EXIT_FAILURE);
		}
	}

	send(GET_COORD);
	receive();

	return m_vec;
}


void MultyPlayer::draw(sf::RenderWindow & window)
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


bool MultyPlayer::getHit(sf::Vector2i pos)
{
	send(GET_HIT, pos);
	receive();
	return m_hit;
}


bool MultyPlayer::getTurn()
{
	send(TURN);
	receive();
	return m_turn;
}


sf::Socket::Status MultyPlayer::connect(const sf::IpAddress & IP, int port)
{
	sf::Socket::Status stat = me.connect(IP, port);
	return stat;
}


sf::Socket::Status MultyPlayer::send(PacketType type, const std::string & msg)
{
	sf::Packet packet;
	packet << type << msg;
	return me.send(packet);
}


sf::Socket::Status MultyPlayer::send(PacketType type, const int i, const int j, const char sign)
{
	std::string tmp(1, sign);
	sf::Packet packet;
	packet << type << i << j << tmp;
	return me.send(packet);
}


sf::Socket::Status MultyPlayer::send(PacketType type, const sf::Vector2i &vec)
{
	sf::Packet packet;
	packet << type << vec.x << vec.y;
	return me.send(packet);
}


sf::Socket::Status MultyPlayer::send(PacketType type, const bool hit)
{
	sf::Packet packet;
	packet << type << hit;
	return me.send(packet);
}


sf::Socket::Status MultyPlayer::send(PacketType type)
{
	sf::Packet packet;
	packet << type;
	return me.send(packet);
}


sf::Socket::Status MultyPlayer::send(PacketType type, const int score)
{
	sf::Packet packet;
	packet << type << score;
	return me.send(packet);
}


void MultyPlayer::receive()
{
	sf::SocketSelector selector;
	selector.add(me);
	sf::Socket::Status status = sf::Socket::NotReady;
	bool tmp = true;
	sf::Packet packet;
	PacketType type;



	if (selector.wait(CONNECT_TIME))
		status = me.receive(packet);
	else
	{
		DisplayResourceNAMessageBox(L"Connection FAILED", L"Match not found!! "
			"Try again later\n\tDisconnect...");
		haveConnection = false;
	}


	switch (status)
	{
	case sf::Socket::Done:
		packet >> type;
		if (type == INITIAL_NAME_DATA)
		{
			packet >> m_msg;
			m_name = m_msg;
		}
		else if (type == CAN_PLAY)
		{
			bool play;
			packet >> play;
			m_canPlay = play;
		}
		else if (type == SERVER_MSG)
		{
			packet >> m_msg >> tmp;
			if (tmp) haveConnection = false;
			win = 1;
		}
		else if (type == GET_COORD)
			packet >> m_vec.x >> m_vec.y;

		else if (type == WHOWON)
			packet >> win;

		else if (type == GET_HIT)
			packet >> m_hit;

		else if (type == TURN)
			packet >> m_turn;
		break;
	}
}
