#ifndef BALL_H
#define BALL_H
#include "Constants.h"
#include "Player.h"
#include "Score.h"

class Ball
{
private:
	Player& m_player1;
	Player& m_player2;
	sf::CircleShape m_ball;
	sf::Vector2f m_velocity;
	sf::Vector2f pos;
	Score& m_score1;
	Score& m_score2;

	float m_angle = 45.0f;
	float m_speed = 400.0f;

public:
	Ball(Player& player1, Player& player2, Score& score1, Score& score2, sf::Vector2f pos);
	sf::CircleShape GetBall();
	void Update(float dt);
	void Reset();

private:
	bool CollisionCheck(Player& player);
	void PaddleCollision(Player& player, std::string hitPos);
	bool PaddleTopCollision(Player& player);
};

#endif // !BALL_H
