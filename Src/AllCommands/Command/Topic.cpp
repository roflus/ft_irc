#include "../../../include/Commands.hpp"

Topic::Topic(Server& server) : Commands(server)
{
}

Topic::~Topic()
{
}

void  Topic::execute(Client &client)
{
    std::string channelName(client.getKey());
    Channel *channel;
    channel = _server.GetChannel(channelName);
    if (!channel)
        return ;
    if (channel->isUserInChannel(client)) {
        if (client.getArguments().size() == 0) {
            std::string &topic = channel->getTopic();
            send(client.getSocket(), topic.c_str(), topic.size(), 0);
        } else {
            if (channel->isUserModerator(client)) {
                channel->setTopic(client.getMessage(false));
            } else {
                std::string message = "Topic can only be set by Moderators";
                send(client.getSocket(), message.c_str(), message.size(), 0);
                return ;
            }
        }
    } else {
        std::string message = "You are not in the Channel";
        send(client.getSocket(), message.c_str(), message.size(), 0);
        return ;
    }
    /*
        eerste argument is channel
        de rest is topic

        als er geen rest is dan vraag je topic op dus stuurt t naar deze client.


        eerst checken of user in channel zit
            2 argumenten
                opvragen topic
            meerdere 
                als moderator is dan topic ceranderen
                else can niet
        else user is not in channel;
    */
} 