#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server) {}

Nick::~Nick() {}

void  Nick::execute(Client &client) {
    std::string nickname(client.getKey());
    std::string message;
    if (nickname.empty()) {
        if (client.getRegistrated()) {
            client.setErrorMessage("Nickname cannot be empty.\n");
        }
        else {
            message = "SYSTEM: Nickname cannot be empty.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
    return ;
    }
    else if (nickname[0] == '#') {
        if (client.getRegistrated()) {
            client.setErrorMessage("Password cannot be empty.\n");
        }
        else {
            message = "SYSTEM: Password cannot be empty.\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    Client *checkClientNickname = _server.getClientNickname(nickname);
    if (!checkClientNickname) {
        client.setNickname(nickname);
        if (client.getRegistrated())
            client.setSendMessage("SYSTEM", "", "Your new nickname is: " + \
                                    client.getNickname() +".\n");
        else {
            message = "SYSTEM: Your new nickname is: " + client.getNickname() +".\n";
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
    }
    else
        client.setErrorMessage("Nickname is being used by other Client.\n");
} 