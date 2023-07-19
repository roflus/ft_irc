#include "../../../include/Commands.hpp"

Nick::Nick(Server& server) : Commands(server) {}

Nick::~Nick() {}

void  Nick::execute(Client &client) {
    std::string nickname(client.getKey());
    std::string message;
    if (nickname.empty()) {
        client.setMessage(ERR_NONICKNAMEGIVEN(nickname));
        return ;
    }
    else if (nickname[0] == '#') {
        client.setMessage(ERR_ERRONEUSNICKNAME(nickname));
        return ;
    }
    Client *checkClientNickname = _server.getClientNickname(nickname);
    if (!checkClientNickname) {
        client.setMessage(MSG_NICK(client.getNickname(), nickname));
        client.setNickname(nickname);
    }
    else 
        client.setMessage(ERR_NICKNAMEINUSE(nickname));
} 


//void  Nick::execute(Client &client) {
//    std::string nickname(client.getKey());
//    std::string message;
//    if (nickname.empty()) {
//        if (client.getRegistrated()) {
//            client.setMessage(ERR_NONICKNAMEGIVEN(nickname));
//        }
//        else {
//            message = ERR_NONICKNAMEGIVEN(nickname);
//            client.setMessage(message);
//        }
//        return ;
//    }
//    else if (nickname[0] == '#') {
//        if (client.getRegistrated()) {
//            client.setMessage(ERR_ERRONEUSNICKNAME(nickname));
//        }
//        else {
//            message = ERR_ERRONEUSNICKNAME(nickname);
//            client.setMessage(message);
//        }
//        return ;
//    }
//    Client *checkClientNickname = _server.getClientNickname(nickname);
//    if (!checkClientNickname) {
//        if (client.getRegistrated())
//            client.setMessage(MSG_NICK(client.getNickname(), nickname));
//        else {
//            message = MSG_NICK(client.getNickname(), nickname);
//            client.setMessage(message);
//        }
//        client.setNickname(nickname);
//    }
//    else {
//        if (client.getRegistrated())
//            client.setMessage(ERR_NICKNAMEINUSE(nickname));
//        else {
//            message = ERR_NICKNAMEINUSE(nickname);
//            client.setMessage(message);
//        }
//    }

//} 