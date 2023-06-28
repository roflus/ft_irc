#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <sys/socket.h>
#include "CheckCommands.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Client;
class Server;

// CURRENT SOCKET WORDT CLIENT *

class Commands
{
    private:

    public:
        Commands(Server& server);
        virtual ~Commands();
        virtual void execute(Client &client) = 0;

        Server&		_server;
};

class Invite : public Commands
{
    public:
        Invite(Server& server);
        ~Invite();

        void execute(Client &client);

};

class Join : public Commands
{
    public:
        Join(Server& server);
        ~Join();

        void execute(Client &client);

};

class Kick : public Commands
{
    public:
        Kick(Server& server);
        ~Kick();

        void execute(Client &client);

};

class Mode : public Commands
{
    public:
        Mode(Server& server);
        ~Mode();

        void execute(Client &client);

};

class Nick : public Commands
{
    public:
        Nick(Server& server);
        ~Nick();

        void execute(Client &client);

};

class Pass : public Commands
{
    public:
        Pass(Server& server);
        ~Pass();

        void execute(Client &client);

};

class Privmsg : public Commands
{
    public:
        Privmsg(Server& server);
        ~Privmsg();

        void execute(Client &client);

};

class Topic : public Commands
{
    public:
        Topic(Server& server);
        ~Topic();

        void execute(Client &client);

};

class User : public Commands
{
    public:
        User(Server& server);
        ~User();

        void execute(Client &client);

};

#endif