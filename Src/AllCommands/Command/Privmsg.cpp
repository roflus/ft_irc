#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server)
{
}

Privmsg::~Privmsg()
{
}

void    Privmsg::messageClient(Client &client, std::string &target){
    Client *targetClient = _server.getClientNickname(target);
    if (targetClient != NULL) {
        targetClient->setSendMessage(client.getNickname(), "", client.getMessage(true));
    }
    else 
        client.setErrorMessage("User is not available, try again.\n");
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
            targetChannel->sendMessageToUsers(message, client.getNickname());
    } else {
        std::string error = "You are not in channel " + target + ".\n";
        client.setErrorMessage(error);
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