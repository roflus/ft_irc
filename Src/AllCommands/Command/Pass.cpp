#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server)
{
}

Pass::~Pass()
{
}

void  Pass::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    send(client.getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
} 