#include <SFML/Graphics.hpp>
#include "Game.h"

Game::Game(sf::RenderWindow& window)
    : m_window(window),
    m_player1(sf::Vector2f(0.0f, ((window.getSize().y - 100.0f) / 2) - constants::paddleHeight), 0),
    m_player2(sf::Vector2f(window.getSize().x - constants::paddleWidth, ((window.getSize().y + 100.0f) / 2)), 1),
    m_score1(font, sf::Vector2f(30.0f, 0.0f)),
    m_score2(font, sf::Vector2f(window.getSize().x - 46.0f, 0.0f)),
    m_ball(m_player1, m_player2, m_score1, m_score2, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f))
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
        m_score1.Update();
        m_score2.Update();
    }
}

void Game::Render()
{
    m_window.clear(sf::Color::Black);

    m_window.draw(m_player1.GetPaddle());
    m_window.draw(m_player2.GetPaddle());
    m_window.draw(m_ball.GetBall());
    m_window.draw(m_score1.GetScore());
    m_window.draw(m_score2.GetScore());

    m_window.display();
}
