#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server) {}

Privmsg::~Privmsg() {}

void    Privmsg::messageClient(Client &client, std::string &target) {
    Client *targetClient = _server.getClientNickname(target);
    if (targetClient != NULL) {
        if (client.getMessage(false).empty())
            client.setErrorMessage("Please enter a message.\n");
        else
            targetClient->setSendMessage(client.getNickname(), "", client.getMessage(true));
    }
    else 
        client.setErrorMessage("User is not available, try again.\n");
}

void   Privmsg::messageChannel(Client &client, std::string &target) {
    Channel *targetChannel;
    targetChannel = _server.getChannel(target);
    if (!targetChannel) {
        client.setErrorMessage("This is not a valid channel.\n");
        return;
    }
    if (targetChannel->isUserInChannel(client)) {
        std::string message = client.getMessage(true);
        if (!message.empty())
            targetChannel->sendMessageToUsers(message, client.getNickname());
    } else 
        client.setErrorMessage("You are not in channel " + target + ".\n");
}

void    Privmsg::execute(Client &client) {
    std::string target(client.getKey());
    if (target.empty()) 
        client.setErrorMessage("Please add Channel and or User.\n");
    else {
        if (target[0] == '#') {
            messageChannel(client, target);
        } else 
            messageClient(client, target);
    }
}