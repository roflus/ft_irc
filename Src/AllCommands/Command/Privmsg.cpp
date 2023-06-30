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

void    Privmsg::execute(Client &client){
    std::cout << "HELLO NOW Invite" << std::endl;

    // Check of Channel of Client
    messageClient(client);

    
} 