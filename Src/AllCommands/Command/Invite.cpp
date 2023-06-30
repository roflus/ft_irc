#include "../../../include/Commands.hpp"

Invite::Invite(Server& server) : Commands(server)
{
}

Invite::~Invite()
{
}

void  Invite::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    send(client.getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
} 