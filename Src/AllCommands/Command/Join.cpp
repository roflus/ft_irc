#include "../../../include/Commands.hpp"

Join::Join(Server& server) : Commands(server)
{
}

Join::~Join()
{
}

void  Join::execute(Client &client)
{
    Channel *channel;
    std::string channelName(client.getKey());
    bool isNewChannel;

    if (channelName[0] != '#'){
        std::string error = "Channel name needs to start with a '#' \n";
        client.setSendMessage("SYSTEM", "", error);
        return ;
    }
    channel = _server.getChannel(channelName);
    if (!channel) {
        isNewChannel = true;
        channel = _server.AddChannel(channelName);
    }
    
    if (!channel->isUserInChannel(client)) {
        channel->addUser(client);
        if (isNewChannel)
            channel->addModerator(client);
        std::string message = "You joined channel " + channel->getName() + "\n";
        client.setSendMessage("SYSTEM", "", message);

        message = client.getNickname() + " joined channel\n";
        channel->sendMessageToUsers(message, "SYSTEM");
    } else {
        std::string error = "You are already in this channel\n";
        client.setSendMessage("SYSTEM", "", error);
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

} 