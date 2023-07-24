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