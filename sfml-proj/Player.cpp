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
		MoveDown();
	if (m_paddle.getPosition().y + constants::paddleHeight > 600)
		MoveUp();
}

void Player::Update()
{
	if (m_playerNum == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			MoveUp();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			MoveDown();
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			MoveUp();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			MoveDown();
	}

	PaddleCheckBounds();
}