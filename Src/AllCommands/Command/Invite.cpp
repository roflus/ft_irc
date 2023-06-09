#include "../../../include/Commands.hpp"

Invite::Invite(Server& server) : Commands(server) {}

Invite::~Invite() {}

void  Invite::execute(Client &client) {
    std::string channelName = client.getKey();
    Channel *targetChannel = _server.getChannel(channelName);
    if (!targetChannel) {
        client.setErrorMessage("Channel not found.\n");
        return ;
    }
    std::string clientName = client.getKey();
    Client *targetClient = _server.getClientNickname(clientName);
    if (!targetClient) {
        client.setErrorMessage("Client not found.\n");
        return ;
    }
    if (targetChannel->isUserModerator(client)) {
        if (targetChannel->getInviteOnly()) {
            if (targetChannel->getUserLimit() > 0) {
                if (targetChannel->getUserLimit() == targetChannel->getUsersCount()) {
                    client.setErrorMessage("Cannot invite anyone, reached channels userlimit.\n");
                    return ;
                }
            }
            if (!targetChannel->isUserInChannel(*targetClient)) {
                targetChannel->addInvitedClient(*targetClient);
                std::string message = "You are nou invited to: " + targetChannel->getName() + ". Use JOIN to join the channel you are invited to.\n";
                targetClient->setSendMessage("SYSTEM", "", message);
            }
        } else
            client.setErrorMessage("Cant invite in this channel.\n");
    } else 
        client.setErrorMessage("You are not moderator in this channel.\n");
} 
                /* 
                    add to list of invited people?
                    send message to user it is invited
                    they us join to get into channel 
                */