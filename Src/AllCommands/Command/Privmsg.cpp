#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server)
{
}

Privmsg::~Privmsg()
{
}

void  Privmsg::execute(int currentSocket)
{
    std::cout << "HELLO NOW Privmsg" << std::endl;
    _server.message = "LETS GET PERSONAL WITH YOUR PRIVMSG\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 