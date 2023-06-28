#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server)
{
}

Privmsg::~Privmsg()
{
}

void  Privmsg::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    client.message = "WHO DO YOU WANT TO INVITE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 