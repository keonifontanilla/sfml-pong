#ifndef CLIENT_H
#define CLIENT_H
#include <SFML/Network.hpp>
#include <iostream>

class Client
{
private:
	sf::UdpSocket m_socket;

public:
	bool ClientConnect();
	void SendConnectionMsg();
	sf::Vector2f ReceivePaddlePos();
	void SendPaddlePos(float x, float y);
};

#endif // !CLIENT_H

