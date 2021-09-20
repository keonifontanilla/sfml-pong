#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include <iostream>

Ball::Ball(Player& player1, Player& player2, Score& score1, Score& score2, sf::Vector2f pos)
	: m_ball(constants::ballRadius),
	m_player1(player1),
	m_player2(player2),
	m_score1(score1),
	m_score2(score2)
{
	m_velocity.x = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_velocity.y = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_ball.setFillColor(sf::Color(192, 192, 192));
	m_ball.setPosition(pos.x, pos.y);
	m_ball.setOrigin(constants::ballRadius, constants::ballRadius);
}

sf::CircleShape Ball::GetBall()
{
	return m_ball;
}

bool Ball::CollisionCheck(Player& player)
{
	return m_ball.getGlobalBounds().intersects(player.GetPaddle().getGlobalBounds());
}

void Ball::PaddleCollision(Player& player, HitPos hitPos)
{
	const float midRange = 20.0f;
	float xCenter = player.GetPaddle().getPosition().x + (player.GetPaddle().getSize().x / 2);
    float yCenter = player.GetPaddle().getPosition().y + (player.GetPaddle().getSize().y / 2);

	if (hitPos == HitPos::topLeft)
	{
		if (player.GetVelocity().y < 0.0f)
			m_ball.setPosition(m_player1.GetPaddle().getPosition().x + 50.0f, m_player1.GetPaddle().getPosition().y - 50.0f);
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;
		m_angle = -m_angle;
	}
	else if (hitPos == HitPos::topRight)
	{
		if (player.GetVelocity().y < 0.0f)
			m_ball.setPosition(m_player2.GetPaddle().getPosition().x - 50.0f, m_player2.GetPaddle().getPosition().y - 50.0f);
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;
		m_angle = -m_angle;
	}
	else if (hitPos == HitPos::bottomLeft)
	{
		if (player.GetVelocity().y > 0.0f)
			m_ball.setPosition(m_player1.GetPaddle().getPosition().x + 50.0f, m_player1.GetPaddle().getPosition().y + constants::paddleHeight + 50.0f);
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;
		m_angle = -m_angle;
	}
	else if (hitPos == HitPos::bottomRight)
	{
		if (player.GetVelocity().y > 0.0f)
			m_ball.setPosition(m_player2.GetPaddle().getPosition().x - 50.0f, m_player2.GetPaddle().getPosition().y + constants::paddleHeight + 50.0f);
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;
		m_angle = -m_angle;
	}
	else if (m_ball.getPosition().y < yCenter - midRange && m_ball.getPosition().y >= player.GetPaddle().getPosition().y)
	{
		if (pos.x < 0 && pos.y > 0 || pos.x > 0 && pos.y > 0)
		{
			pos.y = -pos.y;
			m_velocity.y = -m_velocity.y;
			m_angle = 30.0f;
		}
		else
		{
			m_angle = -m_angle;
		}
		std::cout << "LOW" << std::endl;
	}
	else if (m_ball.getPosition().y < yCenter + midRange && m_ball.getPosition().y > yCenter - midRange)
	{
		m_angle = 45.0f;
		m_angle = -m_angle;
		std::cout << "MID" << std::endl;
	}
	else if (m_ball.getPosition().y > yCenter + midRange && m_ball.getPosition().y <= (player.GetPaddle().getPosition().y + player.GetPaddle().getSize().y))
	{
		if (pos.x < 0 && pos.y < 0 || pos.x > 0 && pos.y < 0)
		{
			pos.y = -pos.y;
			m_velocity.y = -m_velocity.y;
			m_angle = 30.0f;
		}
		else
		{
			m_angle = -m_angle;
		}
		std::cout << "HIGH" << std::endl;
	}
	
	pos.x = -pos.x;
	m_speed = -m_speed * 1.05f;
}

bool Ball::PaddleTopCollision(Player& player)
{
	return ((m_ball.getPosition().x >= player.GetPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= player.GetPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y >= player.GetPaddle().getPosition().y - 20.0f)
		&& (m_ball.getPosition().y <= player.GetPaddle().getPosition().y + 20.0f));
}

bool Ball::PaddleBottomCollision(Player& player)
{
	return ((m_ball.getPosition().x >= player.GetPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= player.GetPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y <= player.GetPaddle().getPosition().y + constants::paddleHeight + 20.0f)
		&& (m_ball.getPosition().y >= player.GetPaddle().getPosition().y + constants::paddleHeight - 20.0f));
}

void Ball::Update(float dt)
{
	float angleRad = 0.0f;	

	if (Ball::PaddleTopCollision(m_player1))
		Ball::PaddleCollision(m_player1, HitPos::topLeft);
	else if (Ball::PaddleTopCollision(m_player2))
		Ball::PaddleCollision(m_player2, HitPos::topRight);
	else if (Ball::PaddleBottomCollision(m_player1))
		Ball::PaddleCollision(m_player1, HitPos::bottomLeft);
	else if (Ball::PaddleBottomCollision(m_player2))
		Ball::PaddleCollision(m_player2, HitPos::bottomRight);
	else if(Ball::CollisionCheck(m_player1))
		Ball::PaddleCollision(m_player1, HitPos::side);
	else if (Ball::CollisionCheck(m_player2))
		Ball::PaddleCollision(m_player2, HitPos::side);

	angleRad = m_angle * constants::PI / 180.0f;
	pos.x = m_velocity.x * dt * std::cos(angleRad) * m_speed;
	pos.y = m_velocity.y * dt * std::sin(angleRad) * m_speed;

	if (m_ball.getPosition().y - constants::ballRadius < 0 || m_ball.getPosition().y + constants::ballRadius > constants::windowHeight)
	{
		pos.y = -pos.y;
		m_angle = -m_angle;
	}

	if (m_ball.getPosition().x < 0)
	{
		Ball::Reset();
		m_score2.IncrementScore();
	}
	else if (m_ball.getPosition().x > constants::windowWidth)
	{
		Ball::Reset();
		m_score1.IncrementScore();
	}

	m_ball.move(pos);
}

void Ball::Reset()
{
	m_velocity.x = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_velocity.y = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_speed = 400.0f;
	m_angle = 45.0f;
	m_ball.setPosition(constants::windowWidth / 2, constants::windowHeight / 2);
}