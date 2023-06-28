#ifndef CHECKCOMMANDS_HPP
# define CHECKCOMMANDS_HPP

#include <iostream>
#include <sys/socket.h>
#include <map>
#include "Commands.hpp"
#include "Server.hpp"

class Server;
class Commands;


class CheckCommands
{
    public:
        CheckCommands(Server &server);
        ~CheckCommands();

        Commands*       getCommand(std::string &command) const;
        void            findCommand(int currentSocket, char *buffer);
        void            executeCommand(int currentSocket, std::string key);




        std::map<std::string, Commands*>		_commands;
        Server&                                 _server;


    
    private:







};

#endif