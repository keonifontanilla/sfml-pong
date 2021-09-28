#include "Game.h"

Game::Game(char connectionOption)
    : m_window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "Pong"),
    m_player(m_server, m_client, connectionOption),
    m_score1(m_font, sf::Vector2f(30.0f, 0.0f)),
    m_score2(m_font, sf::Vector2f(m_window.getSize().x - 46.0f, 0.0f))
    //m_ball(m_player1, m_player2, m_score1, m_score2, sf::Vector2f(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f))
{
    if (connectionOption == 'h' || connectionOption == 'H')
    {
        m_server.LaunchServer();
        m_server.ReceiveConnectionMsg();
    }
    else if (connectionOption == 'c' || connectionOption == 'C')
    {
        if (m_client.ClientConnect())
            m_client.SendConnectionMsg();
    }

    m_window.setFramerateLimit(60);
    m_font.loadFromFile("font.ttf");
}

void Game::MainGameLoop(sf::Clock clock, bool& startPlaying)
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        float dt = clock.restart().asSeconds();

        Game::Update(startPlaying, dt);
        Game::Render(startPlaying);
    }
}

void Game::Update(bool& startPlaying, float dt)
{
    if (!startPlaying)
    {
        if (sf::Keyboard().isKeyPressed(sf::Keyboard::Space))
            startPlaying = true;
        /*m_startMsg.setFont(m_font);
        m_startMsg.setString("Press space to start game");
        m_startMsg.setCharacterSize(24);
        m_startMsg.setFillColor(sf::Color::White);
        m_startMsg.setStyle(sf::Text::Bold);
        m_startMsg.setPosition(m_ball.GetBall().getPosition().x / 2.0f + constants::ballRadius, m_ball.GetBall().getPosition().y + 50.0f);*/
    }
    else
    {
        m_player.Update();
        //m_ball.Update(dt);
        m_score1.Update();
        m_score2.Update();
    }
}

void Game::Render(bool startPlaying)
{
    m_window.clear(sf::Color::Black);

    if (!startPlaying)
        m_window.draw(m_startMsg);
    m_window.draw(m_player.GetPaddle1());
    m_window.draw(m_player.GetPaddle2());
    //m_window.draw(m_ball.GetBall());
    m_window.draw(m_score1.GetScore());
    m_window.draw(m_score2.GetScore());

    m_window.display();
}
