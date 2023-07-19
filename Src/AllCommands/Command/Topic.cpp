#include "../../../include/Commands.hpp"

Topic::Topic(Server& server) : Commands(server) {}

Topic::~Topic() {}

void  Topic::execute(Client &client) {
    std::string channelName(client.getKey());
    Channel *channel;
    channel = _server.getChannel(channelName);
    if (!channel)
        return ;
    if (channel->isUserInChannel(client)) {
        if (client.getArguments().size() == 0) {
            client.setMessage(RPL_TOPIC(channel->getName(), channel->getTopic()));
        } else {
            if (channel->getTopicIsForMod()) {
                if (channel->isUserModerator(client)) {
                    channel->setTopic(client.getMessage(false));
                } else {
                    client.setMessage(ERR_CHANOPRIVSNEEDED(channel->getName()));
                    return ;
                }
            } else
                channel->setTopic(client.getMessage(false));
        }
    } else
        client.setMessage(ERR_NOTONCHANNEL(client.getUsername()));
} 