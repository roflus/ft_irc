#include "../../../include/Commands.hpp"

Privmsg::Privmsg(Server& server) : Commands(server)
{
}

Privmsg::~Privmsg()
{
}

void    Privmsg::messageClient(Client &client){
    std::string checkNickname(client.getKey());
    Client *recvClient = _server.getClientNickname(checkNickname);
    if (recvClient != NULL) 
        send(recvClient->getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
    else{
        const char *error = "USERNAME NOT ONLINE, TRY AGAIN\n";
        send(client.getSocket(), error, strlen(error), 0);
    }
}

/*
    Kunnen deze static functie;s worden?


    void    Privmsg::messageClient(Client &client, std::string &target){
        Client *recvClient = _server.getClientNickname(target);
        if (recvClient != NULL) 
            send(recvClient->getSocket(), client.getMessage(true), strlen(client.getMessage(true)), 0);
        else{
            const char *error = "USERNAME NOT ONLINE, TRY AGAIN\n";
            send(client.getSocket(), error, strlen(error), 0);
        }
    }

    void  Privmsg:messageChannel(Client &client, std::string &target) {
        Channel *channel;
        channel = _server.getChannel(target);
        if (!channel)
            return;
        if (channel->isUserInChannel(client))
        {
            std::string &message = client.getMessage();
            if (message)
                channel.sendMessageToUsers(message));
        } else {
            std::string message = "not in channel\n";
            send(client.getSocket(), message.cstr(), message.size(), 0);
        }
    }
*/

void    Privmsg::execute(Client &client){
    std::cout << "HELLO NOW Invite" << std::endl;

    // Check of Channel of Client
    // channel is met # username is zonder
    /*
        std::string target(client.getKey());
        if (target[0] == '#') {
            messageChannel(client, target);
        } else 
            messageClient(client, target);
    */
    
    
    messageClient(client);

    
} 