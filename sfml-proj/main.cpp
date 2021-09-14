#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"
#include <iostream>
#include "main.h"
#include "Game.h"
#include "Constants.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(constants::windowWidth, constants::windowHeight), "Pong");
    window.setFramerateLimit(60);

    Game game(window);
    
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        game.Update(dt);
        game.Render();
    }
    
    return 0;
}