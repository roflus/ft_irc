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
    client.message = "WHO DO YOU WANT TO INVITE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 