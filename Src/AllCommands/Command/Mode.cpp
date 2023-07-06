#include "../../../include/Commands.hpp"

Mode::Mode(Server& server) : Commands(server)
{
}

Mode::~Mode()
{
}

void  Mode::execute(Client &client)
{
    client.setSendMessage(client.getNickname(), "", client.getMessage(true));
} 