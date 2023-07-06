#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server)
{
}

Privmsg::~Privmsg()
{
}

void    Privmsg::messageClient(Client &client, std::string &target){
    Client *targetClient = _server.getClientNickname(target);
    if (targetClient != NULL) 
    {
        targetClient->setSendMessage(client.getMessage(true));
        //send(targetClient->getSocket(), client.getMessage(true).c_str(), client.getMessage(true).size(), 0);
    }
    else{
        const char *error = "USERNAME NOT ONLINE, TRY AGAIN\n";
        send(client.getSocket(), error, strlen(error), 0);
    }
}

void   Privmsg::messageChannel(Client &client, std::string &target) {
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    if (!targetChannel)
        return;
    if (targetChannel->isUserInChannel(client))
    {
        std::string message = client.getMessage(true);
        if (!message.empty())
            targetChannel->sendMessageToUsers(message);
    } else {
        std::string message = "not in channel\n";
        send(client.getSocket(), message.c_str(), message.size(), 0);
    }
}

void    Privmsg::execute(Client &client){
    // Check of Channel of Client
    // channel is met # username is zonder
    std::string target(client.getKey());
    if (target[0] == '#') {
        messageChannel(client, target);
    } else 
        messageClient(client, target);
} 