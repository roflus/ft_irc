#include "../../include/Server.hpp"

Channel* Server::getChannel(std::string channelName) {
    std::map<std::string, Channel *>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); it++) {
        if (channelName == it->first)
            return it->second;
    }
    return NULL;
}

Channel* Server::AddChannel(std::string channelName) {
    Channel *newChannel;
    newChannel = new Channel(channelName);
    _channels.insert(std::make_pair(channelName, newChannel));
    return newChannel;
}

// void     Server::RemoveChannel(std::string channelName) {

// }
