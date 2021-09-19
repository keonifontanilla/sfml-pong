#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Ball.h"
#include "Score.h"
#include "Constants.h"

class Game
{
private:
	sf::RenderWindow& m_window;
	Player m_player1;
	Player m_player2;
	Ball m_ball;
	sf::Font font;
	Score m_score1;
	Score m_score2;

public:
	Game(sf::RenderWindow& window);
	void Update(bool& startPlaying, float dt);
	void Render();
};

#endif // !GAME_H
