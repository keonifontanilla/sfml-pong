#include "Client.h"

void Client::ClientConnect()
{
    sf::UdpSocket socket;
    if (socket.bind(50001) == sf::Socket::Done)
        std::cout << "Client Connected" << std::endl;
}
