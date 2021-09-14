#ifndef BALL_H
#define BALL_H
#include "Constants.h"
#include "Player.h"

class Ball
{
private:
	Player& m_player1;
	Player& m_player2;
	sf::CircleShape m_ball;
	sf::Vector2f m_velocity;

	float m_angle = 45.0f;
	float m_speed = 400.0f;

public:
	Ball(Player& player1, Player& player2, sf::Vector2f pos);
	sf::CircleShape GetBall();
	void Update(float dt);
	void Reset();

private:
	bool CollisionCheck(Player& player);
	void PaddleCollision(Player& player, sf::Vector2f& pos);
};

#endif // !BALL_H
