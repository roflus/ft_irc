
#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    : _name(name),
      _topic("No topic"),
      _password("hallo")
{

}

Channel::~Channel()
{
}

void    Channel::setTopic(std::string topic) {
    this->_topic = topic;
}

std::string &Channel::getTopic() {
    return _topic;
}

std::string Channel::getName() {
    return this->_name;
}


void    Channel::sendMessageToUsers(std::string message) {
    std::vector<Client *>::iterator it;
    Client *client;
    for(it = _users.begin(); it != _users.end(); it++) {
        client = *it;
        send(client->getSocket(), message.c_str(), message.size(), 0);
    }
}

bool    Channel::isUserInChannel(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _users.begin(); it != _users.end(); it++) {
        if (*it == &client)
            return true;
    }
    return false;
}

bool    Channel::isUserModerator(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _moderators.begin(); it != _moderators.end(); it++) {
        if (*it == &client)
            return true;
    }
    return false;
}

void    Channel::addUser(Client &client) {
    if (!isUserInChannel(client))
        _users.push_back(&client);
}

void    Channel::addModerator(Client &client) {
    if (isUserInChannel(client) && !isUserModerator(client)) {
        _moderators.push_back(&client);
        client.setIsModerator(true);
    }
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
