#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Constants.h"
#include "Player.h"
#include "Score.h"

class Ball
{
private:
	Player& m_player;
	sf::CircleShape m_ball;
	sf::Vector2f m_velocity;
	sf::Vector2f pos;
	Score& m_score1;
	Score& m_score2;

	char m_option = ' ';
	float m_angle = 45.0f;
	float m_speed = 400.0f;

	enum class HitPos
	{
		topLeft,
		topRight,
		side,
		bottomLeft,
		bottomRight
	};

public:
	Ball(Player& player, Score& score1, Score& score2, char option);
	sf::CircleShape GetBall();
	void Update(float dt);
	void Reset();

private:
	sf::RectangleShape PlayerPaddle();
	bool CollisionCheck();
	void PaddleTopCollision();
	void PaddleBottomCollision();
	void PaddleSideCollision();
	bool PaddleTopCollisionCheck();
	bool PaddleBottomCollisionCheck();
	bool PaddleTopCornerCollisionCheck();
};

#endif // !BALL_H
