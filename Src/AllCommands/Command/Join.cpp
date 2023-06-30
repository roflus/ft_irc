#include "../../../include/Commands.hpp"

Join::Join(Server& server) : Commands(server)
{
}

Join::~Join()
{
}

void  Join::execute(Client &client)
{
    std::cout << "HELLO NOW NICK" << std::endl;
    send(client.getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);

} 