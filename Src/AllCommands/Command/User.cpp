#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server) {}

User::~User() {}

void  User::execute(Client &client) {
    std::string username = client.getKey();
    std::string message;
    if (client.getRegistrated())
        client.setErrorMessage("Username can't be changed, change Nickname with command NICK\n");
    else
    {
        if (username[0] == '#') {
            message = "SYSTEM: Username cannot start with a '#'.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
            return ;
        }    
        if (username.empty()) {
            message = "SYSTEM: Please provide a username.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
            return ;
        }
        client.setUsername(username);
        message = "SYSTEM: Your new user- and nickname is: " + client.getUsername() +".\n";
        send(client.getSocket(), message.c_str(), message.size(), 0);
    }
}