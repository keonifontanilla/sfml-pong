#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Server.h"
#include "Client.h"
#include "Constants.h"

class Player
{
private:
	sf::Vector2f m_velocity;
	sf::RectangleShape m_paddle1;
	sf::RectangleShape m_paddle2;
	Server& m_server;
	Client& m_client;

	char m_option = ' ';

public:
	Player(Server& server, Client& client, char option);
	sf::RectangleShape GetPaddle1();	
	sf::RectangleShape GetPaddle2();	
	sf::Vector2f GetVelocity();
	void Update();

private:
	void MoveUp(sf::RectangleShape& paddle);
	void MoveDown(sf::RectangleShape& paddle);
	void PaddleCheckBounds(sf::RectangleShape& paddle);
};

#endif // !PLAYER.H
