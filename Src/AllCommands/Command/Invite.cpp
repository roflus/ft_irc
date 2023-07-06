#include "../../../include/Commands.hpp"

Invite::Invite(Server& server) : Commands(server)
{
}

Invite::~Invite()
{
}

void  Invite::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    client.setSendMessage(client.getNickname(), "", client.getMessage(true));
} 