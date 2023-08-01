
#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    :   _name(name),
        _topic("No topic"),
        _password(""),
        _inviteOnly(false),
        _topicIsForMod(true),
        _hasPassword(false),
        _userLimit(0)
{}

Channel::~Channel() {}

void    Channel::setTopic(std::string topic) { this->_topic = topic; }
void    Channel::setInviteOnly(bool invite) { this->_inviteOnly = invite; }
void    Channel::setTopicIsForMod(bool topic) { this->_topicIsForMod = topic; }
void    Channel::setUserLimit(int limit) { this->_userLimit = limit; }

void        Channel::setPassword(std::string password, bool status) { 
    this->_password = password;
    _hasPassword = status;
}

std::string&    Channel::getTopic() { return _topic; }
std::string     Channel::getName() { return this->_name; }
bool            Channel::getInviteOnly() { return this->_inviteOnly; }
bool            Channel::getTopicIsForMod() { return this->_topicIsForMod; }
size_t          Channel::getUserLimit() { return this->_userLimit; }
size_t          Channel::getUsersCount() { return this->_users.size(); }
std::string     Channel::getPassword() { return this->_password; }
bool            Channel::hasPassword() { return this->_hasPassword; }

void    Channel::sendMessageToUsers(std::string message, bool skip, Client &skipClient) {
    std::vector<Client *>::iterator it;
    Client *client;
    for(it = _users.begin(); it != _users.end(); it++) {
        client = *it;
        if (client->getNickname() == skipClient.getNickname()) {
            if (!skip)
                client->setMessage(message);
        }    
        else
            client->setMessage(message);
    }
}

std::string Channel::getModes()
{
    std::string modes = "+n";
    if (_inviteOnly)
        modes += "i";
    if (_topicIsForMod)
        modes += "t";
    if (_hasPassword)
        modes += "k";
    if (_userLimit)
        modes += "l";
    return modes;
}
