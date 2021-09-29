#include "Ball.h"

Ball::Ball(Player& player, Score& score1, Score& score2, char option)
	: m_ball(constants::ballRadius),
	m_player(player),
	m_score1(score1),
	m_score2(score2),
	m_option(option)
{
	m_velocity.x = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_velocity.y = ((std::rand() % 2 == 0) ? 1.0f : -1.0f);
	m_ball.setFillColor(sf::Color(192, 192, 192));
	m_ball.setPosition(constants::windowWidth / 2.0f, constants::windowHeight / 2.0f);
	m_ball.setOrigin(constants::ballRadius, constants::ballRadius);
}

sf::CircleShape Ball::GetBall()
{
	return m_ball;
}

sf::RectangleShape Ball::PlayerPaddle()
{
	return (m_option == 'c' || m_option == 'C') ? m_player.GetPaddle1() : m_player.GetPaddle2();
}

bool Ball::CollisionCheck()
{
	return m_ball.getGlobalBounds().intersects(Ball::PlayerPaddle().getGlobalBounds());
}

void Ball::PaddleTopCollision()
{
	if (m_option == 'c' || m_option == 'C')
	{
		if (m_player.GetVelocity().y < 0.0f)
			m_ball.setPosition(Ball::PlayerPaddle().getPosition().x + 50.0f, Ball::PlayerPaddle().getPosition().y - 50.0f);

	}
	else if (m_option == 'h' || m_option == 'H')
	{
		if (m_player.GetVelocity().y < 0.0f)
			m_ball.setPosition(Ball::PlayerPaddle().getPosition().x - 50.0f, Ball::PlayerPaddle().getPosition().y - 50.0f);
	}

	pos.y = -pos.y;
	pos.x = -pos.x;
	m_velocity.y = -m_velocity.y;
	m_angle = -m_angle;
	m_speed = -m_speed * 1.05f;
}

void Ball::PaddleBottomCollision()
{
	if (m_option == 'c' || m_option == 'C')
	{
		if (m_player.GetVelocity().y > 0.0f)
			m_ball.setPosition(Ball::PlayerPaddle().getPosition().x + 50.0f, Ball::PlayerPaddle().getPosition().y + constants::paddleHeight + 50.0f);
	}
	else if (m_option == 'h' || m_option == 'H')
	{
		if (m_player.GetVelocity().y > 0.0f)
			m_ball.setPosition(Ball::PlayerPaddle().getPosition().x - 50.0f, Ball::PlayerPaddle().getPosition().y + constants::paddleHeight + 50.0f);
	}

	pos.y = -pos.y;
	pos.x = -pos.x;
	m_velocity.y = -m_velocity.y;
	m_angle = -m_angle;
	m_speed = -m_speed * 1.05f;
}

void Ball::PaddleSideCollision()
{
	const float midRange = 20.0f;
    float yCenter = Ball::PlayerPaddle().getPosition().y + (Ball::PlayerPaddle().getSize().y / 2);

	
	if (m_ball.getPosition().y < yCenter - midRange && m_ball.getPosition().y >= Ball::PlayerPaddle().getPosition().y)
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
	else if (m_ball.getPosition().y > yCenter + midRange && m_ball.getPosition().y <= (Ball::PlayerPaddle().getPosition().y + Ball::PlayerPaddle().getSize().y))
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

bool Ball::PaddleTopCollisionCheck()
{
	return ((m_ball.getPosition().x >= Ball::PlayerPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= Ball::PlayerPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y >= Ball::PlayerPaddle().getPosition().y - 20.0f)
		&& (m_ball.getPosition().y <= Ball::PlayerPaddle().getPosition().y + 20.0f));
}

bool Ball::PaddleBottomCollisionCheck()
{
	return ((m_ball.getPosition().x >= Ball::PlayerPaddle().getPosition().x)
		&& (m_ball.getPosition().x <= Ball::PlayerPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().y <= Ball::PlayerPaddle().getPosition().y + constants::paddleHeight + 20.0f)
		&& (m_ball.getPosition().y >= Ball::PlayerPaddle().getPosition().y + constants::paddleHeight - 20.0f));
}

bool Ball::PaddleTopCornerCollisionCheck()
{
	return ((m_ball.getPosition().x >= Ball::PlayerPaddle().getPosition().x + constants::paddleWidth)
		&& (m_ball.getPosition().x <= Ball::PlayerPaddle().getPosition().x + constants::paddleWidth + 20.0f)
		&& (m_ball.getPosition().y >= Ball::PlayerPaddle().getPosition().y - 20.0f)
		&& (m_ball.getPosition().y <= Ball::PlayerPaddle().getPosition().y));
}

void Ball::Update(float dt)
{
	float angleRad = 0.0f;	

	if (Ball::PaddleTopCollisionCheck())
		Ball::PaddleTopCollision();
	else if (Ball::PaddleBottomCollisionCheck())
		Ball::PaddleBottomCollision();
	else if(Ball::CollisionCheck())
		Ball::PaddleSideCollision();

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