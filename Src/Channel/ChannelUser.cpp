#include "../../include/Channel.hpp"

bool    Channel::isUserInChannel(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _users.begin(); it != _users.end(); it++) {
        if (*it == &client)
            return true;
    }
    return false;
}

void    Channel::addUser(Client &client) {
    if (!isUserInChannel(client))
        _users.push_back(&client);
}

void Channel::removeUser(Client& client) {
    if (isUserInChannel(client)) {
        std::vector<Client*>::iterator it;
        for (it = _users.begin(); it != _users.end(); ) {
            if (*it == &client) {
                it = _users.erase(it);
            } else {
                ++it;
            }
        }
    }
}