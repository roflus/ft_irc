#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <iostream>
#include <sys/socket.h>
#include "CheckCommands.hpp"
#include "Server.hpp"

class Server;

// CURRENT SOCKET WORDT CLIENT *

class Commands
{
    private:

    public:
        Commands(Server& server);
        virtual ~Commands();
        virtual void execute(int currentSocket) = 0;

        Server&		_server;
        int         currentSocket;

};

class Invite : public Commands
{
    public:
        Invite(Server& server);
        ~Invite();

        void execute(int currentSocket);

};

class Join : public Commands
{
    public:
        Join(Server& server);
        ~Join();

        void execute(int currentSocket);

};

class Kick : public Commands
{
    public:
        Kick(Server& server);
        ~Kick();

        void execute(int currentSocket);

};

class Mode : public Commands
{
    public:
        Mode(Server& server);
        ~Mode();

        void execute(int currentSocket);

};

class Nick : public Commands
{
    public:
        Nick(Server& server);
        ~Nick();

        void execute(int currentSocket);

};

class Pass : public Commands
{
    public:
        Pass(Server& server);
        ~Pass();

        void execute(int currentSocket);

};

class Privmsg : public Commands
{
    public:
        Privmsg(Server& server);
        ~Privmsg();

        void execute(int currentSocket);

};

class Topic : public Commands
{
    public:
        Topic(Server& server);
        ~Topic();

        void execute(int currentSocket);

};

class User : public Commands
{
    public:
        User(Server& server);
        ~User();

        void execute(int currentSocket);

};

#endif