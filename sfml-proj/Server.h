#ifndef SERVER_H
#define SERVER_H
#include <SFML/Network.hpp>
#include <iostream>

class Server
{
private:
	sf::UdpSocket m_socket;

public:
	bool LaunchServer();
	void ReceiveConnectionMsg();
	void SendPaddlePos(float x, float y);
	sf::Vector2f ReceivePaddlePos();
};

#endif // !SERVER_H

