
#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    :   _name(name),
        _topic("No topic"),
        _password("hallo"),
        _topicIsForMod(true),
        _inviteOnly(false),
        _userLimit(0)
{}

Channel::~Channel() {}

void        Channel::setTopic(std::string topic) { this->_topic = topic; }
void        Channel::setInviteOnly(bool invite) { this->_inviteOnly = invite; }
void        Channel::setTopicIsForMod(bool topic) { this->_topicIsForMod = topic; }
void        Channel::setPassword(std::string password) { this->_password = password; }
void        Channel::setUserLimit(int limit) { this->_userLimit = limit; }

std::string &Channel::getTopic() { return _topic; }
std::string Channel::getName() { return this->_name; }
bool        Channel::getInviteOnly() { return this->_inviteOnly; }
bool        Channel::getTopicIsForMod() { return this->_topicIsForMod; }
int         Channel::getUserLimit() { return this->_userLimit; }
size_t      Channel::getUsersCount() { return this->_users.size(); }

void    Channel::sendMessageToUsers(std::string message, std::string nickname) {
    std::vector<Client *>::iterator it;
    Client *client;
    for(it = _users.begin(); it != _users.end(); it++) {
        client = *it;
        client->setSendMessage(nickname, _name, message);
    }
}
