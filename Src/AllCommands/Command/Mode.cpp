#include "../../../include/Commands.hpp"

Mode::Mode(Server& server) : Commands(server)
{
}

Mode::~Mode()
{
}

void  Mode::execute(int currentSocket)
{
    std::cout << "HELLO NOW Mode" << std::endl;
    _server.message = "MODE YOU OR MODE ME\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 