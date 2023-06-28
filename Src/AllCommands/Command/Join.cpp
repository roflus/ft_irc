#include "../../../include/Commands.hpp"

Join::Join(Server& server) : Commands(server)
{
}

Join::~Join()
{
}

void  Join::execute(int currentSocket)
{
    std::cout << "HELLO NOW NICK" << std::endl;
    _server.message = "JOIN THE DARK SIDE\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 