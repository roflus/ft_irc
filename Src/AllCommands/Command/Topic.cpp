#include "../../../include/Commands.hpp"

Topic::Topic(Server& server) : Commands(server)
{
}

Topic::~Topic()
{
}

void  Topic::execute(int currentSocket)
{
    std::cout << "HELLO NOW Topic" << std::endl;
    _server.message = "T(R)OPIC THUNDER\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 