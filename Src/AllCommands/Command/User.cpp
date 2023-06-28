#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server)
{
}

User::~User()
{
}

void  User::execute(Client &client)
{
    std::cout << "HELLO NOW Invite" << std::endl;
    client.message = "WHO DO YOU WANT TO INVITE\n";
    send(client.getSocket(), client.message, strlen(client.message), 0);
} 