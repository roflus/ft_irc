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

void Channel::removeModerator(Client& client) {
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