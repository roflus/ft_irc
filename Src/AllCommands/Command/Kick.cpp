#include "../../../include/Commands.hpp"

Kick::Kick(Server& server) : Commands(server)
{
}

Kick::~Kick()
{
}

void  Kick::execute(Client &client)
{
    send(client.getSocket(), client.getMessage(true).c_str(), client.getMessage(true).size(), 0);

} 