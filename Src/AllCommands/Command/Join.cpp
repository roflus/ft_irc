#include "../../../include/Commands.hpp"

Join::Join(Server& server) : Commands(server) {}

Join::~Join() {}

void  Join::execute(Client &client) {
    Channel *channel;
    std::string channelName(client.getKey());
    bool isNewChannel;

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
        if (!channel->getInviteOnly()) {
            channel->addUser(client);
            if (isNewChannel)
                channel->addModerator(client);
        }
        else {
            if (channel->isUserInvited(client)) {
                channel->addUser(client);
                channel->removeInvitedClient(client);
            } else {
                client.setMessage(ERR_INVITEONLYCHAN(channel->getName()));
                return ;
            }
        }
        client.setMessage(MSG_JOIN(client.getNickname(), channel->getName()));
        channel->sendMessageToUsers(MSG_JOIN(client.getNickname(), channel->getName()));
    } else
        client.setMessage(ERR_USERONCHANNEL(client.getNickname(), channel->getName()));
}
    /*
        Channel name meegeven: start with #
        channel password meegeven als het nodig is. 
        deze user in vector van client zetten
        en ook van moderators?
        add this channel to map in server class
        Deze user een message geven dat het gelukt is met joinen 
        l. This message includes information such as the channel name, the user's nickname, and any additional relevant details.
        Additionally, the server broadcasts a JOIN message to all users in the channel, 
        notifying them that a new user has joined. This message typically contains the nickname of the joining user.
    */