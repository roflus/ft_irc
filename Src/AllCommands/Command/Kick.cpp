#include "../../../include/Commands.hpp"

Kick::Kick(Server &server) : Commands(server) {}

Kick::~Kick() {}

void Kick::execute(Client &client) {
    Channel *targetChannel;
    std::string channelName(client.getKey());
    targetChannel = _server.getChannel(channelName);
    if (!targetChannel) {
        client.setMessage(ERR_NOSUCHCHANNEL(channelName));
        return;
    }
    Client *targetClient;
    std::string clientName(client.getKey());
    targetClient = _server.getClientNickname(clientName);
    if (!targetClient) {
        client.setMessage(ERR_NOSUCHNICK(clientName));
        return;
    }
    if (targetChannel->isUserInChannel(client)) {
        if (targetChannel->isUserModerator(client)) {
            if (targetChannel->isUserInChannel(*targetClient)) {
                targetChannel->removeUser(*targetClient);
                if (targetChannel->isUserModerator(*targetClient))
                    targetChannel->removeModerator(*targetClient);
                std::string reason = client.getMessage(true);
                std::string message;
                targetClient->setMessage(MSG_KICK(client.getNickname(), targetClient->getNickname(), targetChannel->getName(), reason));
                targetChannel->sendMessageToUsers(MSG_KICK(client.getNickname(), targetClient->getNickname(), targetChannel->getName(), reason), false, client);
            } else 
                client.setMessage(ERR_USERNOTINCHANNEL(targetClient->getNickname(), targetChannel->getName()));
        } else 
            client.setMessage(ERR_CHANOPRIVSNEEDED(targetChannel->getName()));
    } else 
        client.setMessage(ERR_NOTONCHANNEL(targetChannel->getName()));
}