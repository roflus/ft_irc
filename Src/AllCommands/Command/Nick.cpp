#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server) {}

Nick::~Nick() {}

void  Nick::execute(Client &client) {
    std::string nickname(client.getKey());
    if (nickname[0] == '#') {
        if (client.getRegistrated()) {
            client.setErrorMessage("Password cannot be empty.\n");
        }
        else {
            std::string message = "Password cannot be empty.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    client.setNickname(nickname);
    if (client.getRegistrated()) {
        std::string message = "Your new nickname is: " + client.getNickname() +".\n";
        client.setSendMessage("SYSTEM", "", message);
    }
    else {
        std::string message = "Your new nickname is: " + client.getNickname() +".\n";
        send(client.getSocket(), message.c_str(), message.size(), 0);
    }
} 