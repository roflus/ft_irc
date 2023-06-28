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
    client.message = "WHO DO YOU WANT TO INVITE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 