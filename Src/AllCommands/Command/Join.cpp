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
    client.message  = "JOIN THE DARK SIDE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 