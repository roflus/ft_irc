#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server)
{
}

Nick::~Nick()
{
}

void  Nick::execute(int currentSocket)
{
    std::cout << "HELLO NOW NICK" << std::endl;
    _server.message = "NICK-o-LODEON\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 