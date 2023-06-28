#include "../../include/Channel.hpp"

Channel::Channel(std::string name, std::string password)
    : _name(name),
      _topic("No topic"),
      _password(password) 
{

}

Channel::~Channel()
{
}

void    Channel::setTopic(std::string topic) {
    this->_topic = topic;
}

std::string Channel::getTopic(){
    return this->_topic;
}

bool    Channel::isUserInChannel(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _users.begin(); it != _users.end(); it++){
        if (*it == &client)
            return true;
    }
    return false;
}

bool    Channel::isUserModerator(Client &client) {
    std::vector<Client *>::iterator it;
    for (it = _moderators.begin(); it != _moderators.end(); it++){
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
    if (isUserInChannel(client) && !isUserModerator(client))
        _moderators.push_back(&client);
}