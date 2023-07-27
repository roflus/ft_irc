#include "../../../include/Commands.hpp"

Join::Join(Server& server) : Commands(server) {}

Join::~Join() {}

void  Join::execute(Client &client) {
    Channel *channel;
    std::string channelName(client.getKey());
    std::string password;
    bool isNewChannel = false;

    if (channelName[0] != '#') {
        client.setMessage(ERR_NOSUCHCHANNEL(channelName));
        return ;
    }
    channel = _server.getChannel(channelName);
    if (!channel) {
        isNewChannel = true;
        channel = _server.AddChannel(channelName);
    }
    if (!channel->isUserInChannel(client)) {
        if (channel->getUserLimit() > 0) {
            if (channel->getUserLimit() == channel->getUsersCount()) {
                client.setMessage(ERR_CHANNELISFULL(channel->getName()));
                return ;
            }
        }
        password = client.getKey();
        if (!channel->getInviteOnly()) {
            if (isNewChannel) {
                channel->addUser(client);
                channel->addModerator(client);
                if (!password.empty())
                    channel->setPassword(password, true);
            }
            else {
                if (channel->hasPassword() == false)
                    channel->addUser(client);
                else {
                    if (password == channel->getPassword())
                        channel->addUser(client);
                    else {
                        client.setMessage(ERR_BADCHANNELKEY(channel->getName()));
                        return ;
                    }
                }
            }   
        }
        else {
            if (channel->isUserInvited(client)) {
                if (channel->hasPassword() == false) {
                    channel->addUser(client);
                    channel->removeInvitedClient(client);
                }
                else {
                    if (password == channel->getPassword()) {
                        channel->addUser(client);
                        channel->removeInvitedClient(client);
                    }
                    else {
                        client.setMessage(ERR_BADCHANNELKEY(channel->getName()));
                        return;
                    }
                }
            } else {
                client.setMessage(ERR_INVITEONLYCHAN(channel->getName()));
                return ;
            }
        }
        channel->sendMessageToUsers(MSG_JOIN(client.getNickname(), channel->getName()), false, client);
        client.setMessage(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
    } else
        client.setMessage(ERR_USERONCHANNEL(client.getNickname(), channel->getName()));
}