#include "../../../include/Commands.hpp"

Quit::Quit(Server& server) : Commands(server)
{
}

Quit::~Quit()
{
}

void  Quit::execute(Client &client)
{
    //if (!client.getArguments().empty())
    //    send(client.getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
    close(client.getSocket());
    exit(0);
} 