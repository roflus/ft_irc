#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server)
{
}

User::~User()
{
}

void  User::execute(Client &client)
{
    client.setSendMessage(client.getNickname(), "", client.getMessage(true));
} 