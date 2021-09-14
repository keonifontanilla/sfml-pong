#ifndef PLAYER_H
#define PLAYER_H
#include "Constants.h"

class Player
{
private:
	int m_playerNum = 0;

	sf::Vector2f m_velocity;
	sf::RectangleShape m_paddle;

public:
	Player(sf::Vector2f pos, int playerNum);
	sf::RectangleShape GetPaddle();	
	void Update();

private:
	void MoveUp();
	void MoveDown();
	void PaddleCheckBounds();
};

#endif // !PLAYER.H
