#include "../../../include/Commands.hpp"

Mode::Mode(Server& server) : Commands(server)
{
}

Mode::~Mode()
{
}

void  Mode::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    client.message = "WHO DO YOU WANT TO INVITE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 