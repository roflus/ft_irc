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
    send(client.getSocket(), client.getMessage(true).c_str(), client.getMessage(true).size(), 0);

} 