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
    std::vector<Client *>   _users;
    std::vector<Client *>   _moderators;
public:
    Channel(std::string name, std::string password);
    ~Channel();

    bool    isUserInChannel(Client &client);
    bool    isUserModerator(Client &client);

    void    addUser(Client &client);
    void    addModerator(Client &client);
    void    removeModerator(Client &Client);
    void    removeUser(Client &client);



    void    setTopic(std::string topic);

    std::string                 getName();
    std::string                 getTopic();
    std::string                 getPassword();
    std::vector<std::string>    getUsers();


};

#endif
