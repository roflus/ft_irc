#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server) {}

User::~User() {}

void  User::execute(Client &client) {
    std::string username = client.getKey();
    std::string message;
    if (client.getRegistrated()) {
        client.setMessage(ERR_ALREADYREGISTRED(client.getNickname()));
        return ;
    }
    if (username[0] == '#') {
        message = ERR_ERRONEUSNICKNAME(username);
        send(client.getSocket(), message.c_str(), message.size(), 0);
        return ;
    }    
    if (username.empty()) {
        message = ERR_NEEDMOREPARAMS(std::string("USER"));
        send(client.getSocket(), message.c_str(), message.size(), 0);
        return ;
    }
    // Client *checkClientname = _server.getClientUsername(username);
    // if (!checkClientname) {
    //     checkClientname = _server.getClientNickname(username);
    //     if (!checkClientname) {
            client.setUsername(username);
            message = MSG_USER(username);
            send(client.getSocket(), message.c_str(), message.size(), 0);
    //     }
    //     else {
    //         message = ERR_NICKNAMEINUSE(username);
    //         send(client.getSocket(), message.c_str(), message.size(), 0);   
    //     }
    // }
    // else {
    //     message = ERR_NICKNAMEINUSE(username);
    //     send(client.getSocket(), message.c_str(), message.size(), 0);    
    // }
}