#include "../../../include/Commands.hpp"

Pass::Pass(Server& server) : Commands(server)
{
}

Pass::~Pass()
{
}

void  Pass::execute(int currentSocket)
{
    std::cout << "HELLO NOW Pass" << std::endl;
    _server.message = "PASS THE QUICHE\n";
    send(currentSocket, _server.message, strlen(_server.message), 0);
} 