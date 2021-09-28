#include "Client.h"

bool Client::ClientConnect()
{
    if (m_socket.bind(50001) == sf::Socket::Done)
    {
        std::cout << "Client Connected" << std::endl;
        return true;
    }
    return false;
}

void Client::SendConnectionMsg()
{
    sf::IpAddress recipient = sf::IpAddress::LocalHost;
    unsigned short port = 50000;
    std::string connectionMsg = "Client connected";
    sf::Packet packet;
    packet << connectionMsg;
    m_socket.send(packet, recipient, port);
}

sf::Vector2f Client::ReceivePaddlePos()
{
    sf::IpAddress recipient;
    unsigned short port;
    sf::Vector2f pos;
    sf::Packet packet;
    m_socket.receive(packet, recipient, port);
    packet >> pos.x >> pos.y;
    return pos;
}

void Client::SendPaddlePos(float x, float y)
{
    sf::IpAddress recipient = sf::IpAddress::LocalHost;
    unsigned short port = 50000;
    sf::Packet packet;
    packet << x << y;
    m_socket.send(packet, recipient, port);
}
