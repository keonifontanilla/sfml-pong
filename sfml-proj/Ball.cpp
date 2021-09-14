#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include <iostream>

Ball::Ball(Player& player1, Player& player2, sf::Vector2f pos) 
	: m_ball(constants::ballRadius), 
	  m_player1(player1),
	  m_player2(player2),
	  m_velocity(-1.0f, -1.0f)
{
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

void Ball::PaddleCollision(Player& player)
{
    float xCenter = player.GetPaddle().getPosition().x + (player.GetPaddle().getSize().x / 2);
    float yCenter = player.GetPaddle().getPosition().y + (player.GetPaddle().getSize().y / 2);
	float midRange = 20.0f;

    /*if (m_ball.getPosition().y < yCenter && m_ball.getPosition().y >= m_player1.GetPaddle().getPosition().y)
        std::cout << "LOW" << std::endl;
    else if (m_ball.getPosition().y > yCenter && m_ball.getPosition().y <= (m_player1.GetPaddle().getPosition().y + m_player1.GetPaddle().getSize().y))
        std::cout << "HIGH" << std::endl;*/

	/*if (CollisionCheck(m_player1))
	{
		std::cout << "BALL Y " << m_ball.getPosition().y << std::endl;
		std::cout << "CENTER Y " << yCenter << std::endl;
		std::cout << "+ RANGE " << yCenter + midRange << std::endl;
		std::cout << "- RANGE " << yCenter - midRange << std::endl;
	}*/

	if (m_ball.getPosition().y < yCenter + midRange && m_ball.getPosition().y > yCenter - midRange)
	{
		// Check if paddle is moving
		std::cout << "MID" << std::endl;
	}

}

void Ball::Update(float dt)
{	
	sf::Vector2f pos;
	float angleRad = m_angle * constants::PI / 180.0f;
	pos.x = m_velocity.x * dt * std::cos(angleRad) * m_speed;
	pos.y = m_velocity.y * dt * std::sin(angleRad) * m_speed;

	if (CollisionCheck(m_player1) || CollisionCheck(m_player2))
	{
		PaddleCollision(m_player1);
		pos.x = -pos.x;
		m_speed = -m_speed;
		m_angle = -m_angle;
	}

	if (m_ball.getPosition().y - constants::ballRadius < 0 || m_ball.getPosition().y + constants::ballRadius > 600)
	{
		pos.y = -pos.y;
		m_angle = -m_angle;
	}

	m_ball.move(pos);
}

void Ball::Reset()
{
	
}