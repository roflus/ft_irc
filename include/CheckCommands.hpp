#ifndef CHECKCOMMANDS_HPP
# define CHECKCOMMANDS_HPP

#include <iostream>
#include <sys/socket.h>
#include <map>
#include <deque>
#include "Commands.hpp"
#include "Server.hpp"
#include "Client.hpp"

class Client;
class Server;
class Commands;

class CheckCommands
{
    public:
        CheckCommands(Server &server);
        ~CheckCommands();

        void                                    enterServer(Client &client);
        Commands*                               getCommand(std::string &command) const;
        void                                    findCommand(Client &client);
        void                                    executeCommand(Client &client, std::string key);

        std::map<std::string, Commands*>		_commands;
        Server&                                 _server;

    private:
    
};

#endif