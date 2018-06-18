#pragma once
#include "Player.h"
#include "SFML/Network.hpp"


class MultyPlayer : public Player
{
public:
	MultyPlayer(std::string name);

	sf::Vector2i askHit(sf::RenderWindow& window, sf::Event& event);
	void draw(sf::RenderWindow & window);
	bool getHit(sf::Vector2i pos);
	void receive();
	bool getTurn();
	void setWin(short num) { win = num; }
	short getWin() { return win; }
	bool getConnection() const { return haveConnection; }
	void Disconnect() { me.disconnect(); }

	sf::Socket::Status send(PacketType, const int i,const int j, const char sign);
	sf::Socket::Status connect(const sf::IpAddress & IP, int port);
	sf::Socket::Status send(PacketType type, const std::string&);
	sf::Socket::Status send(PacketType, const sf::Vector2i&);
	sf::Socket::Status send(PacketType type, const bool);
	sf::Socket::Status send(PacketType type, const int);
	sf::Socket::Status send(PacketType type);

private:
	std::string m_msg;
	sf::Vector2i m_vec{ -1,-1 };
	sf::TcpSocket me;
	bool m_canPlay;
	int m_score;
	bool m_hit = false;
	bool m_turn;
	bool haveConnection;
	short win;
};