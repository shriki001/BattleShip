#include "Chat.h"
/*#include "PacketType.h"*/
#include <iostream>

Chat::Chat(const std::string & name_) :name(name_)
{
}


sf::Socket::Status Chat::connect(const sf::IpAddress & IP, unsigned short port)
{
	//connect to server
	sf::Socket::Status stat = me.connect(IP, port);
	me.setBlocking(false);
	return stat;
}

sf::Socket::Status Chat::send(PacketChat type, const std::string & msg)
{
	sf::Packet packet;
	packet << type << msg;
	return me.send(packet);
}

sf::Socket::Status Chat::receive(std::string & msg)
{
	sf::Packet packet;
	sf::Socket::Status status = me.receive(packet);
	PacketChat type;
	packet >> type;
	if (status == sf::Socket::Done)
		packet >> msg;
	
	return status;
}