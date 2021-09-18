#include <SFML/Graphics.hpp>
#include "Game.h"

Game::Game(sf::RenderWindow& window)
    : m_window(window),
      m_player1(sf::Vector2f(0.0f, 0.0f), 0),
      m_player2(sf::Vector2f(window.getSize().x - constants::paddleWidth,
                             window.getSize().y - constants::paddleHeight), 1),
	  m_ball(m_player1, m_player2, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f))
{

}

void Game::Update(bool& startPlaying, float dt)
{
    if (!startPlaying)
    {
        if (sf::Keyboard().isKeyPressed(sf::Keyboard::Space))
            startPlaying = true;
    }
    else
    {
        m_player1.Update();
        m_player2.Update();
        m_ball.Update(dt);
    }
}

void Game::Render()
{
    m_window.clear(sf::Color::Black);

    m_window.draw(m_player1.GetPaddle());
    m_window.draw(m_player2.GetPaddle());
    m_window.draw(m_ball.GetBall());

    m_window.display();
}
