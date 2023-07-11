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
        if (client.getRegistrated())
            client.setErrorMessage("Nickname cannot start with a '#'.\n");
        else {
            std::string message = "Nickname cannot start with a '#'.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    if (username.empty()) {
        if (client.getRegistrated())
            client.setErrorMessage("Please provide a username.\n");
        else {
            std::string message = "Please provide a username.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    client.setUsername(username);
} 