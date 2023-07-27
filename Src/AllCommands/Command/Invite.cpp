#include "../../../include/Commands.hpp"

Invite::Invite(Server& server) : Commands(server) {}

Invite::~Invite() {}

void  Invite::execute(Client &client) {
    std::string channelName = client.getKey();
    Channel *targetChannel = _server.getChannel(channelName);
    if (!targetChannel) {
        client.setMessage(ERR_NOSUCHCHANNEL(channelName));
        return ;
    }
    std::string clientName = client.getKey();
    Client *targetClient = _server.getClientNickname(clientName);
    if (!targetClient) {
        client.setMessage(ERR_NOSUCHNICK(clientName));
        return ;
    }
    if (!targetChannel->isUserInChannel(client)) {
        client.setMessage(ERR_NOTONCHANNEL(targetChannel->getName()));
        return ;
    }
    if (targetChannel->isUserModerator(client)) {
        if (targetChannel->isUserInChannel(*targetClient)) {
            client.setMessage(ERR_USERONCHANNEL(targetClient->getNickname(), targetChannel->getName()));
            return;
        }
        if (targetChannel->getUserLimit() > 0) {
            if (targetChannel->getUserLimit() == targetChannel->getUsersCount()) {
                client.setMessage(ERR_CHANNELISFULL(targetChannel->getName()));
                return ;
            }
        }
        targetChannel->addInvitedClient(*targetClient);
        targetClient->setMessage(MSG_INVITING(client.getNickname(), targetClient->getNickname(), targetChannel->getName()));
        client.setMessage(RPL_INVITING(client.getNickname(), targetClient->getNickname(), targetChannel->getName()));
    } else 
        client.setMessage(ERR_CHANOPRIVSNEEDED(targetChannel->getName()));
} 