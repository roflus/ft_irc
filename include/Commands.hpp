#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <deque>
#include "CheckCommands.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Client;
class Server;
class Commands
{
    private:

    public:
        Commands(Server& server);
        virtual             ~Commands();
        virtual void        execute(Client &client) = 0;

        Server&		        _server;
};

class Invite : public Commands
{
    public:
        Invite(Server& server);
        ~Invite();

        void                execute(Client &client);

};

class Join : public Commands
{
    public:
        Join(Server& server);
        ~Join();

        void                execute(Client &client);

};

class Kick : public Commands
{
    public:
        Kick(Server& server);
        ~Kick();

        void                execute(Client &client);

};

class Mode : public Commands
{
    public:
        Mode(Server& server);
        ~Mode();

        void                execute(Client &client);
        void                accessChannel(Client &client, std::string target);
};

class Nick : public Commands
{
    public:
        Nick(Server& server);
        ~Nick();

        void                execute(Client &client);

};

class Pass : public Commands
{
    public:
        Pass(Server& server);
        ~Pass();

        void                execute(Client &client);

};

class Privmsg : public Commands
{
    public:
        Privmsg(Server& server);
        ~Privmsg();

        void                execute(Client &client);
        void                messageClient(Client &client, std::string &target);
        void                messageChannel(Client &client, std::string &target);
};

class Quit : public Commands
{
    public:
        Quit(Server& server);
        ~Quit();

        void                execute(Client &client);

};

class Topic : public Commands
{
    public:
        Topic(Server& server);
        ~Topic();

        void                execute(Client &client);

};

class User : public Commands
{
    public:
        User(Server& server);
        ~User();

        void                execute(Client &client);

};

#endif