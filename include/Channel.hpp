#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <deque>
#include "Client.hpp"

class Channel
{
private:
    std::string             _name;
    std::string             _topic;
    std::string             _password;
    bool                    _inviteOnly;
    bool                    _topicIsForMod;
    bool                    _hasPassword;
    size_t                  _userLimit;
    std::vector<Client *>   _users;
    std::vector<Client *>   _moderators;
    std::vector<Client *>   _invitedClients;

public:
    Channel(std::string name);
    ~Channel();

    bool        isUserInChannel(Client &client);
    bool        isUserModerator(Client &client);
    bool        isUserInvited(Client &client);
    void        addUser(Client &client);

    void        addModerator(Client &client);
    void        removeModerator(Client &Client);
    void        removeUser(Client &client);
    void        addInvitedClient(Client &client);
    void        removeInvitedClient(Client &client);

    void        sendMessageToUsers(std::string message, bool skip, Client &skipClient);


    void        setTopic(std::string topic);
    void        setPassword(std::string password, bool status);
    void        setInviteOnly(bool invite);
    void        setTopicIsForMod(bool topic);
    void        setUserLimit(int limit);

    std::string getName();
    std::string &getTopic();
    std::string getPassword();
    bool        hasPassword();
    bool        getInviteOnly();
    bool        getTopicIsForMod();  
    size_t      getUserLimit();
    size_t      getUsersCount(); 
    std::string getModes();       
};

#endif
