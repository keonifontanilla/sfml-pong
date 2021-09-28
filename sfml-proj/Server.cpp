#include "Server.h"

bool Server::LaunchServer()
{    
    if (m_socket.bind(50000) == sf::Socket::Done)
    {
        std::cout << "Server started" << std::endl;
        return true;
    }
    return false;
}

void Server::ReceiveConnectionMsg()
{
    sf::IpAddress recipient;
    unsigned short port;
    std::string connectionMsg;
    sf::Packet packet;
    m_socket.receive(packet, recipient, port);
    packet >> connectionMsg;
    std::cout << connectionMsg << " port: " << port << std::endl;
}

void Server::SendPaddlePos(float x, float y)
{
    sf::IpAddress recipient = sf::IpAddress::LocalHost;
    unsigned short port = 50001;
    sf::Packet packet;
    packet << x << y;
    m_socket.send(packet, recipient, port);
}

sf::Vector2f Server::ReceivePaddlePos()
{
    sf::IpAddress recipient;
    unsigned short port;
    sf::Vector2f pos;
    sf::Packet packet;
    m_socket.receive(packet, recipient, port);
    packet >> pos.x >> pos.y;
    return pos;
}