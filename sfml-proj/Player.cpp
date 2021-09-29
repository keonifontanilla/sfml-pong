#include "Player.h"

Player::Player(Server& server, Client& client, char option)
	: m_paddle1(sf::Vector2f(constants::paddleWidth, constants::paddleHeight)),
	m_paddle2(sf::Vector2f(constants::paddleWidth, constants::paddleHeight)),
	m_server(server),
	m_client(client),
	m_option(option)
{
	m_paddle1.setPosition(0.0f, 5.0f);
	m_paddle2.setPosition(constants::windowWidth - constants::paddleWidth, 5.0f);
}

sf::RectangleShape Player::GetPaddle1()
{
	return m_paddle1;
}

sf::RectangleShape Player::GetPaddle2()
{
	return m_paddle2;
}

sf::Vector2f Player::GetVelocity()
{
	return m_velocity;
}

void Player::MoveUp(sf::RectangleShape& paddle)
{
	m_velocity.y = -5.0f;
	paddle.move(m_velocity);
}

void Player::MoveDown(sf::RectangleShape& paddle)
{
	m_velocity.y = 5.0f;
	paddle.move(m_velocity);
}

void Player::PaddleCheckBounds(sf::RectangleShape& paddle)
{
	if (paddle.getPosition().y < 0)
		Player::MoveDown(paddle);
	if (paddle.getPosition().y + constants::paddleHeight > 600)
		Player::MoveUp(paddle);
}

void Player::Update()
{
	sf::Vector2f pos;
	if (m_option == 'c' || m_option == 'C')
	{
		m_client.SendPaddlePos(m_paddle1.getPosition().x, m_paddle1.getPosition().y);
		pos = m_client.ReceivePaddlePos();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			Player::MoveUp(m_paddle1);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			Player::MoveDown(m_paddle1);

		m_paddle2.setPosition(pos);
		Player::PaddleCheckBounds(m_paddle1);
	}
	else if(m_option == 'h' || m_option == 'H')
	{
		m_server.SendPaddlePos(m_paddle2.getPosition().x, m_paddle2.getPosition().y);
		pos = m_server.ReceivePaddlePos();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			Player::MoveUp(m_paddle2);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Player::MoveDown(m_paddle2);

		m_paddle1.setPosition(pos);
		Player::PaddleCheckBounds(m_paddle2);
	}
}