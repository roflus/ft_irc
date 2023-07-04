
#include "../../include/Channel.hpp"

Channel::Channel(std::string name)
    : _name(name),
      _topic("No topic"),
      _password("hallo")
{}

Channel::~Channel() {}

void        Channel::setTopic(std::string topic) { this->_topic = topic; }
std::string &Channel::getTopic() { return _topic; }
std::string Channel::getName() { return this->_name; }

void    Channel::sendMessageToUsers(std::string message) {
    std::vector<Client *>::iterator it;
    Client *client;
    for(it = _users.begin(); it != _users.end(); it++) {
        client = *it;
        send(client->getSocket(), message.c_str(), message.size(), 0);
    }
}
