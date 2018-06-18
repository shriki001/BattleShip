#pragma once
#include "SFML/Network.hpp"
#include "settings.h"


class Chat
{
public:
	Chat(const std::string & name);
	~Chat() = default;
	sf::Socket::Status connect(const sf::IpAddress & IP, unsigned short port);
	sf::Socket::Status send (PacketChat type, const std::string & msg);
	sf::Socket::Status receive(std::string & msg);

private:
	std::string name;
	sf::TcpSocket me;
};