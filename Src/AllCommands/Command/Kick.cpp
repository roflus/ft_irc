#include "../../../include/Commands.hpp"

Kick::Kick(Server& server) : Commands(server)
{
}

Kick::~Kick()
{
}

void  Kick::execute(int currentSocket)
{
    std::cout << "HELLO NOW Kick" << std::endl;
    _server.message = "KICK THE BALL\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 