#include "../../../include/Commands.hpp"

Invite::Invite(Server& server) : Commands(server)
{
}

Invite::~Invite()
{
}

void  Invite::execute(int currentSocket)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    _server.message = "WHO DO YOU WANT TO INVITE\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 