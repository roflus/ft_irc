#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "iostream"
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
    std::vector<Client *>   _users;
    std::vector<Client *>   _moderators;
    std::vector<Client *>   _invitedClients;

public:
    Channel(std::string name);
    ~Channel();

    bool    isUserInChannel(Client &client);
    bool    isUserModerator(Client &client);
    bool    isUserInvited(Client &client);

    void    addUser(Client &client);
    void    addModerator(Client &client);
    void    removeModerator(Client &Client);
    void    removeUser(Client &client);
    void    changeModerator(Client &client, Client &targetClient);
    void    addInvitedClient(Client &client);
    void    removeInvitedClient(Client &client);

    void    sendMessageToUsers(std::string message, std::string nickname);


    void    setTopic(std::string topic);
    void    setInviteOnly(bool invite);
    void    setTopicIsForMod(bool topic);
    void    setPassword(std::string password);

    std::string                 getName();
    std::string                 &getTopic();
    std::string                 getPassword();
    bool                        getInviteOnly();
    bool                        getTopicIsForMod();


};

#endif
