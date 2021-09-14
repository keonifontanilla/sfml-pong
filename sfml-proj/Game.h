#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Ball.h"
#include "Constants.h"

class Game
{
private:
	sf::RenderWindow& m_window;
	Player m_player1;
	Player m_player2;
	Ball m_ball;

public:
	Game(sf::RenderWindow& window);
	void Update(float dt);
	void Render();
};

#endif // !GAME_H
