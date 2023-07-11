#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server)
{
}

User::~User()
{
}

void  User::execute(Client &client)
{
    std::string username = client.getKey();
    if (username[0] == '#') {
        client.setErrorMessage("Nickname cannot start with a '#'.\n");
        return ;
    }
    if (username.empty()) {
        client.setErrorMessage("Please provide a username\n");
        return ;
    }
    client.setUsername(username);
} 