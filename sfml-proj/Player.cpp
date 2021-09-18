#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(sf::Vector2f pos, int playerNum) 
	: m_paddle(sf::Vector2f(constants::paddleWidth, constants::paddleHeight))
{
	m_playerNum = playerNum;
	m_paddle.setPosition(pos.x, pos.y);
}

sf::RectangleShape Player::GetPaddle()
{
	return m_paddle;
}

sf::Vector2f Player::GetVelocity()
{
	return m_velocity;
}

void Player::MoveUp()
{
	m_velocity.y = -5.0f;
	m_paddle.move(m_velocity);
}

void Player::MoveDown()
{
	m_velocity.y = 5.0f;
	m_paddle.move(m_velocity);
}

void Player::PaddleCheckBounds()
{
	if (m_paddle.getPosition().y < 0)
		Player::MoveDown();
	if (m_paddle.getPosition().y + constants::paddleHeight > 600)
		Player::MoveUp();
}

void Player::Update()
{
	if (m_playerNum == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			Player::MoveUp();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			Player::MoveDown();
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Player::MoveUp();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Player::MoveDown();
	}

	Player::PaddleCheckBounds();
}