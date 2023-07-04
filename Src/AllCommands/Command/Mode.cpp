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
    send(client.getSocket(), client.getMessage(true).c_str(), client.getMessage(true).size(), 0);


} 