#include "../../include/CheckCommands.hpp"

CheckCommands::CheckCommands(Server &server) : _server(server)
{
    this->_commands["INVITE"] = new Invite(this->_server);
    this->_commands["JOIN"] = new Join(this->_server);
    this->_commands["KICK"] = new Kick(this->_server);
    this->_commands["MODE"] = new Mode(this->_server);
    this->_commands["NICK"] = new Nick(this->_server);
    this->_commands["PASS"] = new Pass(this->_server);
    this->_commands["PRIVMSG"] = new Privmsg(this->_server);
    this->_commands["TOPIC"] = new Topic(this->_server);
    this->_commands["USER"] = new User(this->_server);
}

CheckCommands::~CheckCommands()
{
}

Commands*   CheckCommands::getCommand(std::string &command) const
{
    return this->_commands.at(command);
    
}

void  CheckCommands::findCommand(int currentSocket, char *buffer)
{
        std::string receivedMessage(buffer);
        std::string check = receivedMessage.substr(0, receivedMessage.find(' '));
        std::map<std::string, Commands*>::iterator iter = _commands.find(check);
        if (iter != _commands.end())
            executeCommand(currentSocket, check);
} 

// CURRENT SOCKET WORDT CLIENT *
void  CheckCommands::executeCommand(int currentSocket, std::string key) 
{
    Commands*    command;
    command = this->getCommand(key);
    command->execute(currentSocket);
}
