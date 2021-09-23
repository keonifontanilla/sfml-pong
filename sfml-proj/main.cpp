#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

char GetConnectionOption()
{
    char option;
    do {
        std::cout << "Press H for host or C for client: ";
        std::cin >> option;
    } while (option != 'H' && option != 'h' && option != 'C' && option != 'c');
    return option;
}

int main()
{
    srand(time(NULL));
    sf::Clock clock;
    bool startPlaying = false;
    Game game(GetConnectionOption());

    game.MainGameLoop(clock, startPlaying);
    
    return 0;
}