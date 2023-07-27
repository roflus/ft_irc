#include "../../../include/Commands.hpp"

User::User(Server& server) : Commands(server) {}

User::~User() {}

void  User::execute(Client &client) {
    std::string username = client.getKey();
    std::string arguments;
    if (client.getRegistrated()) {
        client.setMessage(ERR_ALREADYREGISTRED(client.getNickname()));
        return ;
    }
    if (username[0] == '#') {
        client.setMessage(ERR_ERRONEUSNICKNAME(username));
        return ;
    }    
    if (username.empty()) {
        client.setMessage(ERR_NEEDMOREPARAMS(std::string("USER")));
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