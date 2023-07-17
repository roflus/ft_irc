#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server) {}

Nick::~Nick() {}

void  Nick::execute(Client &client) {
    std::string nickname(client.getKey());
    std::string message;
    if (nickname.empty()) {
        if (client.getRegistrated()) {
            client.setMessage(ERR_NONICKNAMEGIVEN(nickname));
        }
        else {
            message = ERR_NONICKNAMEGIVEN(nickname);
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
    return ;
    }
    else if (nickname[0] == '#') {
        if (client.getRegistrated()) {
            client.setMessage(ERR_ERRONEUSNICKNAME(nickname));
        }
        else {
            message = ERR_ERRONEUSNICKNAME(nickname);
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        return ;
    }
    Client *checkClientNickname = _server.getClientNickname(nickname);
    if (!checkClientNickname) {
        if (client.getRegistrated())
            client.setMessage(MSG_NICK(client.getNickname(), nickname));
        else {
            message = MSG_NICK(client.getNickname(), nickname);
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
        client.setNickname(nickname);
    }
    else {
        if (client.getRegistrated())
            client.setMessage(ERR_NICKNAMEINUSE(nickname));
        else {
            message = ERR_NICKNAMEINUSE(nickname);
            send(client.getSocket(), message.c_str(), message.size(), 0);
        }
    }

} 