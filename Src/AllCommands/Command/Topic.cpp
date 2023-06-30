#include "../../../include/Commands.hpp"

Topic::Topic(Server& server) : Commands(server)
{
}

Topic::~Topic()
{
}

void  Topic::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    send(client.getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
} 