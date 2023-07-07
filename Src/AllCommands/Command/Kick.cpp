#include "../../../include/Commands.hpp"

Kick::Kick(Server &server) : Commands(server)
{
}

Kick::~Kick()
{
}

void Kick::execute(Client &client)
{
    /*
        Takes 3 arguments, 1 optional
        first argument is the channel
        second is the user
        third(optional) is the reason

        check if this client is moderator
        check first argument if channel
        then check if second argument is a user
        then if user is in that channel
        if so remove from the user list/moderator list in channel
    */
    Channel *targetChannel;
    std::string channelName(client.getKey());
    targetChannel = _server.getChannel(channelName);
    if (!targetChannel) {
        client.setErrorMessage("Channel does not exist\n");
        return;
    }
    Client *targetClient;
    std::string clientName(client.getKey());
    targetClient = _server.getClientNickname(clientName);
    if (!targetClient) {
        client.setErrorMessage("User does not exist\n");
        return;
    }
    if (targetChannel->isUserInChannel(client)) {
        if (targetChannel->isUserModerator(client)) {
            if (targetChannel->isUserInChannel(*targetClient))
            {
                targetChannel->removeUser(*targetClient);
                if (targetChannel->isUserModerator(*targetClient))
                    targetChannel->removeModerator(*targetClient);
                std::string reason = client.getKey();
                std::string message;
                if (reason.empty()) {
                    targetClient->setSendMessage("SYSTEM", channelName, "You have been kicked from channel by: " + client.getNickname() + "\n");
                    message = clientName + " has been removed from group\n";
                }
                else {
                    targetClient->setSendMessage("SYSTEM", channelName, "You have been kicked from channel by: " + client.getNickname() + " " + reason + "\n");
                    message = clientName + " has been removed from group: " + reason + "\n";
                }
                targetChannel->sendMessageToUsers(message, "SYSTEM");
            } else {
                client.setErrorMessage("This user is not in this channel\n");
            }
        } else {
            client.setErrorMessage("You must be a moderator in this channel to kick someone\n");
        }
    } else {
        client.setErrorMessage("You are not in this channel\n");
    }
}