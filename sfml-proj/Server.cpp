#include "Server.h"

void Server::LaunchServer()
{
    sf::UdpSocket socket;
    if (socket.bind(50000) == sf::Socket::Done)
        std::cout << "Server Connected" << std::endl;
}