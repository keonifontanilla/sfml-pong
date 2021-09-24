#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"
#include "Score.h"
#include "Constants.h"
#include "Server.h"
#include "Client.h"

class Game
{
private:
	sf::RenderWindow m_window;
	Player m_player1;
	Player m_player2;
	Ball m_ball;
	sf::Font m_font;
	Score m_score1;
	Score m_score2;
	sf::Text m_startMsg;

	Server m_server;
	Client m_client;

public:
	Game(char connectionOption);
	void Update(bool& startPlaying, float dt);
	void Render(bool startPlaying);
	void MainGameLoop(sf::Clock, bool& startPlaying);
};

#endif // !GAME_H
