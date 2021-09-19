#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include <iostream>

Ball::Ball(Player& player1, Player& player2, sf::Vector2f pos)
	: m_ball(constants::ballRadius),
	m_player1(player1),
	m_player2(player2)
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

void Ball::PaddleCollision(Player& player, sf::Vector2f& pos)
{
	const float midRange = 20.0f;
	float xCenter = player.GetPaddle().getPosition().x + (player.GetPaddle().getSize().x / 2);
    float yCenter = player.GetPaddle().getPosition().y + (player.GetPaddle().getSize().y / 2);

	// Top of paddle
	if ((m_ball.getPosition().x >= player.GetPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= player.GetPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y <= player.GetPaddle().getPosition().y))
	{
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;

		std::cout << "TOP" << std::endl;
	} // Bottom of paddle
	else if ((m_ball.getPosition().x >= player.GetPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= player.GetPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y >= player.GetPaddle().getPosition().y + constants::paddleHeight))
	{
		pos.y = -pos.y;
		m_velocity.y = -m_velocity.y;
		std::cout << "BOTTOM" << std::endl;
	} // Side of paddle
	else if (m_ball.getPosition().y < yCenter - midRange && m_ball.getPosition().y >= player.GetPaddle().getPosition().y)
	{
		if (pos.x < 0 && pos.y > 0 || pos.x > 0 && pos.y > 0)
		{
			pos.y = -pos.y;
			m_velocity.y = -m_velocity.y;
		}
		std::cout << "LOW" << std::endl;
	}
	else if (m_ball.getPosition().y < yCenter + midRange && m_ball.getPosition().y > yCenter - midRange)
	{
		std::cout << "MID" << std::endl;
	}
	else if (m_ball.getPosition().y > yCenter + midRange && m_ball.getPosition().y <= (player.GetPaddle().getPosition().y + player.GetPaddle().getSize().y))
	{
		if (pos.x < 0 && pos.y < 0 || pos.x > 0 && pos.y < 0)
		{
			pos.y = -pos.y;
			m_velocity.y = -m_velocity.y;
		}
		std::cout << "HIGH" << std::endl;
	}
	
	pos.x = -pos.x;
	m_speed = -m_speed;
	m_angle = -m_angle;
}

void Ball::Update(float dt)
{	
	float angleRad = 0.0f;

	if (Ball::CollisionCheck(m_player1))
		Ball::PaddleCollision(m_player1, pos);
	else if (Ball::CollisionCheck(m_player2))
		Ball::PaddleCollision(m_player2, pos);

	angleRad = m_angle * constants::PI / 180.0f;
	pos.x = m_velocity.x * dt * std::cos(angleRad) * m_speed;
	pos.y = m_velocity.y * dt * std::sin(angleRad) * m_speed;

	if (m_ball.getPosition().y - constants::ballRadius < 0 || m_ball.getPosition().y + constants::ballRadius > constants::windowHeight)
	{
		pos.y = -pos.y;
		m_angle = -m_angle;
	}

	if (m_ball.getPosition().x < 0 || m_ball.getPosition().x > constants::windowWidth)
		Ball::Reset();

	m_ball.move(pos);
}

void Ball::Reset()
{
	m_ball.setPosition(constants::windowWidth / 2, constants::windowHeight / 2);
}