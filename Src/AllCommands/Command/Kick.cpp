#include "../../../include/Commands.hpp"

Kick::Kick(Server& server) : Commands(server)
{
}

Kick::~Kick()
{
}

void  Kick::execute(Client &client)
{
    client.setSendMessage(client.getNickname(), "", client.getMessage(true));
} 