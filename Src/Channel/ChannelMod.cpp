#include "../../include/Channel.hpp"

bool    Channel::isUserModerator(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _moderators.begin(); it != _moderators.end(); it++) {
        if (*it == &client)
            return true;
    }
    return false;
}

void    Channel::addModerator(Client &client) {
    if (isUserInChannel(client) && !isUserModerator(client)) {
        _moderators.push_back(&client);
        client.setIsModerator(true);
    }
}

void    Channel::removeModerator(Client& client) {
    if (isUserInChannel(client)) {
        std::vector<Client*>::iterator it;
        for (it = _moderators.begin(); it != _moderators.end(); ) {
            if (*it == &client) {
                it = _moderators.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void    Channel::changeModerator(Client &client, Client &targetClient) {
    if (isUserInChannel(targetClient)) {
        if (isUserModerator(targetClient)) {
            removeModerator(targetClient);
            targetClient.setSendMessage("SYSTEM", _name, "You've been removed as moderator by " + client.getNickname() + "\n");
            client.setSendMessage("SYSTEM", _name, "You have removed " + targetClient.getNickname() + " as moderator\n");
        }
        else {
            addModerator(targetClient);
            targetClient.setSendMessage("SYSTEM", _name, client.getNickname() + " made your moderator in this channel\n");
            client.setSendMessage("SYSTEM", _name, "You have made " + targetClient.getNickname() + " moderator in this channel\n");
        }
    }
    else {    
        client.setSendMessage("SYSTEM", _name, "User is not in Channel");
    }
}