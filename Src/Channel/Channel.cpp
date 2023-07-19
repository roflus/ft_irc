
#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    :   _name(name),
        _topic("No topic"),
        _password(""),
        _topicIsForMod(true),
        _inviteOnly(false),
        _hasPassword(false),
        _userLimit(0)
{}

Channel::~Channel() {}

void        Channel::setTopic(std::string topic) { this->_topic = topic; }
void        Channel::setInviteOnly(bool invite) { this->_inviteOnly = invite; }
void        Channel::setTopicIsForMod(bool topic) { this->_topicIsForMod = topic; }
void        Channel::setUserLimit(int limit) { this->_userLimit = limit; }

void        Channel::setPassword(std::string password, bool status) { 
    this->_password = password;
    _hasPassword = status;
}

std::string &Channel::getTopic() { return _topic; }
std::string Channel::getName() { return this->_name; }
bool        Channel::getInviteOnly() { return this->_inviteOnly; }
bool        Channel::getTopicIsForMod() { return this->_topicIsForMod; }
int         Channel::getUserLimit() { return this->_userLimit; }
size_t      Channel::getUsersCount() { return this->_users.size(); }
std::string Channel::getPassword() { return this->_password; }
bool        Channel::hasPassword() { return this->_hasPassword; }

void    Channel::sendMessageToUsers(std::string message) {
    std::vector<Client *>::iterator it;
    Client *client;
    for(it = _users.begin(); it != _users.end(); it++) {
        client = *it;
        client->setMessage(message);
    }
}
