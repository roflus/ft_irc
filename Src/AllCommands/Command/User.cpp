#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server) {}

User::~User() {}

void  User::execute(Client &client) {
    std::string username = client.getKey();
    std::string arguments;
    std::string message;
    if (client.getRegistrated()) {
        client.setMessage(ERR_ALREADYREGISTRED(client.getNickname()));
        return ;
    }
    if (username[0] == '#') {
        message = ERR_ERRONEUSNICKNAME(username);
        client.setMessage(message);
        return ;
    }    
    if (username.empty()) {
        message = ERR_NEEDMOREPARAMS(std::string("USER"));
        client.setMessage(message);
        return ;
    }
    client.setUsername(username);
    arguments = client.getKey();
    if (!arguments.empty()) {
        client.setHostname(arguments);
        arguments = client.getKey();
        if (!arguments.empty()) {
            client.setServername(arguments);
            arguments = client.getKey();
            if (!arguments.empty())
                client.setRealname(arguments);
        }
    }
}