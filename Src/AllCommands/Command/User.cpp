#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server)
{
}

User::~User()
{
}

void  User::execute(int currentSocket)
{
    std::cout << "HELLO NOW User" << std::endl;
    _server.message = "WHO, ME? NO THE USER\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 