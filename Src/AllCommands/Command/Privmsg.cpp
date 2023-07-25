#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server) {}

Privmsg::~Privmsg() {}

void    Privmsg::messageClient(Client &client, std::string &target) {
    Client *targetClient = _server.getClientNickname(target);
    if (targetClient != NULL) {
        std::string message = client.getMessage(true);
        if (message.empty())
            client.setMessage(ERR_NOTEXTTOSEND(targetClient->getNickname()));
        else
            targetClient->setMessage(MSG_PRIVMSG(client.getNickname(), target, message));
    }
    else
        client.setMessage(ERR_NOSUCHNICK(target));
}

void   Privmsg::messageChannel(Client &client, std::string &target) {
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    if (!targetChannel) {
        client.setMessage(ERR_NOSUCHCHANNEL(target));
        return;
    }
    if (targetChannel->isUserInChannel(client)) {
        std::string message = client.getMessage(true);
        if (message.empty())
            client.setMessage(ERR_NOTEXTTOSEND(targetChannel->getName()));
        else
            targetChannel->sendMessageToUsers(MSG_PRIVMSG(client.getNickname(), target, message), true, client);
    } else 
        client.setMessage(ERR_NOTONCHANNEL(targetChannel->getName()));
}

void    Privmsg::execute(Client &client) {
    std::string target(client.getKey());
    if (target.empty())
        client.setMessage(ERR_NEEDMOREPARAMS(std::string("PRIVMSG")));
    else {
        if (target[0] == '#') {
            messageChannel(client, target);
        } else 
            messageClient(client, target);
    }
}